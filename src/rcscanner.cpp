/* UI Converter MFC2QT (C) 2018 Holger Gerth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <memory>
#include <assert.h>

#include <QValidator>
#include <QStringList>
#include <QRegExp>
#include <QDebug>

#include <QFontMetrics>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QStyle>
#include <QTextEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QListView>
#include <QTableView>
#include <QRadioButton>
#include <QDateTimeEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileInfo>

#include "ctrldefinitions.h"
#include "ressourcedef.h"
#include "rcscanner.h"
#include "dialogpreview.h"

namespace {

    const int COMBOBOX_HEIGHT = 12;

    QString peekLine( QFile& rcFile )
    {
        QString nextLine;
        if( !rcFile.atEnd() ) {
            qint64 cpos = rcFile.pos();
            nextLine = rcFile.readLine();
            rcFile.seek( cpos );
            cpos = rcFile.pos();
        }
        return nextLine;
    }

    Control::CONTROL extractType( const QString& line )
    {
        Control::CONTROL ctrlType = Control::UNKNOWN;
        if( line.startsWith( Control::controls[Control::ICON] ) ) {
            ctrlType = Control::ICON;
        }
        else if( line.startsWith( Control::controls[Control::LTEXT] ) ) {
            ctrlType = Control::LTEXT;
        }
        else if( line.startsWith( Control::controls[Control::CTEXT] ) ) {
            ctrlType = Control::CTEXT;
        }
        else if( line.startsWith( Control::controls[Control::RTEXT] ) ) {
            ctrlType = Control::RTEXT;
        }
        else if( line.startsWith( Control::controls[Control::EDITTEXT] ) ) {
            ctrlType = Control::EDITTEXT;
        }
        else if( line.startsWith( Control::controls[Control::PUSHBUTTON] ) ) {
            ctrlType = Control::PUSHBUTTON;
        }
        else if( line.startsWith( Control::controls[Control::DEFPUSHBUTTON] ) ) {
            ctrlType = Control::DEFPUSHBUTTON;
        }
        else if( line.startsWith( Control::controls[Control::PUSHBOX] ) ) {
            ctrlType = Control::PUSHBOX;
        }
        else if( line.startsWith( Control::controls[Control::LISTBOX] ) ) {
            ctrlType = Control::LISTBOX;
        }
        else if( line.startsWith( Control::controls[Control::GROUPBOX] ) ) {
            ctrlType = Control::GROUPBOX;
        }
        else if( line.startsWith( Control::controls[Control::CHECKBOX] ) ) {
            ctrlType = Control::CHECKBOX;
        }
        else if( line.startsWith( Control::controls[Control::RADIOBUTTON] ) ) {
            ctrlType = Control::RADIOBUTTON;
        }
        else if( line.startsWith( Control::controls[Control::COMBOBOX] ) ) {
            ctrlType = Control::COMBOBOX;
        }
        else if( line.startsWith( Control::controls[Control::CCONTROL] ) ) {
            ctrlType = Control::CCONTROL;
        }
        else {
            assert( false );
            return ctrlType;
        }

        return ctrlType;
    }

    Control::WIDGET getWidgetType( const ControlData& ctrlData )
    {
        switch( ctrlData.ctrlType ) {
        case Control::ICON:
            return Control::QIMAGE;
        case Control::EDITTEXT:
            return Control::QLINEEDIT;
        case Control::LTEXT:
        case Control::CTEXT:
        case Control::RTEXT:
            return Control::QLABEL;
        case Control::PUSHBOX:      // handle Pushbox like Pushbutton
        case Control::PUSHBUTTON:
        case Control::DEFPUSHBUTTON:
            return Control::QPUSHBUTTON;
        case Control::GROUPBOX:
            return Control::QGROUPBOX;
        case Control::CHECKBOX:
            return Control::QCHECKBOX;
        case Control::RADIOBUTTON:
            return Control::QRADIOBUTTON;
        case Control::COMBOBOX:
            return Control::QCOMBOBOX;
        case Control::LISTBOX:
            return Control::QLISTVIEW;
        case Control::SCROLLBAR:
            return Control::QSCROLLBAR;
        default:
            break;
        }

        // handle custom MFC controls
        if ( ctrlData.ctrlType == Control::CCONTROL ) {
            if ( ctrlData.cctype.contains( CTL_STATIC ) ) {
                return Control::QLABEL;
            }
            else if( ctrlData.cctype.contains( CTL_BUTTON ) ) {
                if( ctrlData.style.contains( CTS_AUTOCHECKBOX ) ) {
                    return Control::QCHECKBOX;
                }
                else if( ctrlData.style.contains( CTS_AUTORADIOBUTTON ) ) {
                    return Control::QRADIOBUTTON;
                }
                else {
                    return Control::QPUSHBUTTON;
                }
            }
            else if( ctrlData.cctype.contains( CTL_LISTVIEW ) ) {
                return Control::QLISTVIEW;
            }
            else if( ctrlData.cctype.contains( CTL_PROFUISGRID ) ) {
                return Control::QTABLEVIEW;
            }
            else if( ctrlData.cctype.contains( CTL_PROFUISDTP ) ) {
                return Control::QDATETIMEEDIT;
            }
            else if( ctrlData.cctype.contains( CTL_PROFUISCTRLBAR ) ) {
                return Control::QMENUBAR;
            }

            qDebug() << "Unsupported custom control: " << ctrlData.cctype;
            return Control::ERRORWIDGET;
        }

        assert( false );

        return Control::ERRORWIDGET;
    }

    QSize getFontSize( QFont font )
    {
        QFontMetrics metrics( font );

        // QFontMetrics::averageCharWidth doesn't deliver the right value, see https://support.microsoft.com/en-us/kb/145994
        int w = metrics.size( Qt::TextSingleLine, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" ).width();
        w = ( w / 26 + 1 ) /2;

        int h = metrics.height() + 1;

        return QSize(w, h);
    }
}

RCScanner::RCScanner( QObject * parent )
    : QObject( parent )
    , errorCode( ERR_SUCCESS )
{
}

RCScanner::~RCScanner()
{
}

void RCScanner::readFile( const QString& filePath )
{
    if ( filePath.isEmpty() ) return;
    if ( !QFileInfo(filePath).exists() ) return;

    QFile rcFile( filePath );
    if ( ! rcFile.open(QIODevice::ReadOnly) ) {
        QMessageBox::critical(dynamic_cast<QWidget*>(parent()), "Error", "Failed to open resource file.");
        return;
    }

    // clear rc data
    dialogGuis.clear();

    // get dialogs and other resources
    while( !rcFile.atEnd() )
    {
        QString nextLine = peekLine( rcFile );

        if( nextLine.contains( "GUIDELINES" ) ) {
            processGuidelines( rcFile );
        }
        else if( nextLine.contains( "AFX_DIALOG_LAYOUT" ) ) {
            processDialogLayout( rcFile );
        }
        else if( nextLine.contains( "DLGINIT" ) ) {
            processDlgInit( rcFile );
        }
        else if( nextLine.contains( SDIALOG ) ) {
            processDialog( rcFile );
        }
        else if( nextLine.contains( QRegExp( "\\s+ ICON " ) ) ) {
            processImage( rcFile );
        }
        else if( nextLine.contains( QRegExp( "\\s+ BITMAP " ) ) ) {
            processImage( rcFile );
        }
        else if( nextLine.contains( QRegExp( "^STRINGTABLE" ) ) ) {
            processStringTable( rcFile );
        }
        else {
            // ignore
            rcFile.readLine();
        }
    }

    rcFile.close();
}

ObjectDataSP RCScanner::getDialogData( const QString& dlgID )
{
    auto dialogDataMfc = getMfcDialogData( dlgID );
    auto dlgObjectData = createDialog( dialogDataMfc );

    auto dialogData = dynamic_cast<DialogData*>( dlgObjectData.get() );
    foreach ( const QString& line, dialogDataMfc.ctrlDef ) {
        auto child = createWidget( getControlData(line) );
        dialogData->addChild( child );
    }

    return dlgObjectData;
}

bool RCScanner::isNewControl( const QString& line )
{
    QString type = line.left( line.indexOf( " " ) );
    for ( Control::CONTROL i = Control::C_FIRST; i <= Control::C_LAST; ++i ) {
        if( type.compare( Control::controls[i] ) == 0 ) {
            return true;
        }
    }
    return false;
}

void RCScanner::processGuidelines( QFile& rcFile )
{
    bool started = false;
    while ( !rcFile.atEnd() ) {

        QString line = QString::fromLatin1( rcFile.readLine() ).trimmed();
        if ( line.startsWith(SBEGIN) ) {
            started = true;
            continue;
        }

        if ( line.startsWith(SEND) ) {
            started = false;
            break;
        }

        if ( started ) {
            if( line.contains(SDIALOG) ) {
                // <2DO> handle dialog guidelines info
                while ( ! line.startsWith(SEND) ) {
                    line = QString::fromLatin1( rcFile.readLine() ).trimmed();
                }
            }
        }
    }
}

void RCScanner::processDialogLayout( QFile& rcFile )
{
    bool started = false;
    while ( !rcFile.atEnd() ) {

        QString line = QString::fromLatin1( rcFile.readLine() ).trimmed();
        if ( line.startsWith(SBEGIN) ) {
            started = true;
            continue;
        }

        if ( line.startsWith(SEND) ) {
            started = false;
            break;
        }

        if ( started ) {
            // <2DO> handle dialog layout
        }
    }
}

void RCScanner::processDlgInit( QFile& rcFile )
{
    bool started = false;
    while ( !rcFile.atEnd() ) {

        QString line = QString::fromLatin1( rcFile.readLine() ).trimmed();
        if ( line.startsWith(SBEGIN) ) {
            started = true;
            continue;
        }

        if ( line.startsWith(SEND) ) {
            started = false;
            break;
        }

        if ( started ) {
            // <2DO> handle dialog init
        }
    }
}

void RCScanner::processDialog( QFile& rcFile )
{
    MfcDialogData dlgData;
    bool readControlDefinitions = false;
    while ( !rcFile.atEnd() ) {

        QString line = QString::fromLatin1( rcFile.readLine() ).trimmed();

        if ( ! readControlDefinitions ) {

            if ( line.contains(SDIALOG) ) {
                dlgData.id = line.left( line.indexOf( ' ' ) );
                dlgData.type = SDIALOGEX;

                QStringList geometry = line.mid( id.length() + QString( " " + QString( SDIALOGEX )+ " ").length() ).split( QRegExp( ", " ) );
                if( !geometry.isEmpty() ) {
                    dlgData.pos.setX( geometry.at( XPOS ).toInt() );
                    dlgData.pos.setY( geometry.at( YPOS ).toInt() );

                    dlgData.size.setWidth( geometry.at( WIDTHPOS ).toInt() );
                    dlgData.size.setHeight( geometry.at( HEIGHTPOS ).toInt() );
                }
            }
            else if ( line.startsWith(SFONT) ) {
                line = line.mid( line.indexOf( " " ) );
                line.remove( QRegExp("\"") );

                QStringList fontData = line.split( QRegExp(",") );

                dlgData.font.setFamily( fontData.at(FONTPOS) );
                dlgData.font.setPointSize( fontData.at(FONTSIZEPOS).toInt() );
                if ( fontData.length() > WEIGHTPOS ) {
                    dlgData.font.setWeight( calculateFontWeight(fontData.at(WEIGHTPOS).toInt()) );
                }
                if ( fontData.length() > ITALICPOS ) {
                    dlgData.font.setItalic( fontData.at(ITALICPOS).toInt() == TRUE );
                }
            }
            else if ( line.startsWith(SSTYLE) ) {
                // <2DO> SSTYLE
            }
            else if ( line.startsWith(SEXSTYLE) ){
                // <2DO> SEXSTYLE
            }
            else if ( line.startsWith(SCAPTION) ) {
                QStringList caption = line.split( QRegExp("\"") );
                dlgData.title = caption.at( CAPTIONPOS );
            }
            else if ( line.startsWith(SBEGIN) ) {
                readControlDefinitions = true;
            }
            else {
                assert( false );
            }
        }
        else {
            if ( line.startsWith(SEND) ) {
                readControlDefinitions = false;
                break;
            }

            if ( ! isNewControl(line) ) {
                line = dlgData.ctrlDef.back() + line;
                dlgData.ctrlDef.pop_back();
            }

            dlgData.ctrlDef.append( line );
        }
    }

    dialogGuis.insert( dlgData.id, dlgData );
}

void RCScanner::processImage( QFile& rcFile )
{
    QString line = QString::fromLatin1( rcFile.readLine() ).trimmed();
    QStringList parts = line.split( QRegExp( "\\s+" ) );

    // <2DO> processImage
    //QString id = parts[0];
    //QString type = parts[1];
    QString filePath = parts[2];
    filePath.remove( "\"" );
    images.append( filePath );
}

void RCScanner::processStringTable( QFile& rcFile )
{
    bool started = false;
    while ( !rcFile.atEnd() ) {
        QString line = QString::fromLatin1( rcFile.readLine() ).trimmed();

        if ( line.startsWith(SBEGIN) ) {
            started = true;
            continue;
        }

        if ( line.startsWith(SEND) ) {
            started = false;
            break;
        }

        if ( started ) {
            QString identifier = line.left( line.indexOf( " " ) );
            QString value = line.mid( identifier.length() + 1 ).trimmed();
            value.remove( "\"" );

            stringTable.insert( identifier, value );
        }
    }
}

QStringList RCScanner::getDialogIDs( void ) const
{
    return dialogGuis.keys();
}

MfcDialogData RCScanner::getMfcDialogData( const QString& id ) const
{
    return dialogGuis.value( id );
}

const QStringList& RCScanner::getImages() const
{
    return images;
}

const QStringMap& RCScanner::getStringTable() const
{
    return stringTable;
}

int RCScanner::calculateFontWeight( int ms_weight )
{
    int ratio = QT_MAX / FW_MAX;
    if( ms_weight <= FW_LIGHT ) {
        ratio = QFont::Light / FW_LIGHT;
    }
    else if ( ms_weight <= FW_NORMAL ) {
        ratio = QFont::Normal / FW_NORMAL;
    }
    else if ( ms_weight <= FW_DEMIBOLD ) {
        ratio = QFont::DemiBold / FW_DEMIBOLD;
    }
    else if ( ms_weight <= FW_BOLD ) {
        ratio = QFont::Bold / FW_BOLD;
    }
    else if ( ms_weight <= FW_BLACK ) {
        ratio = QFont::Black / FW_BLACK;
    }
    return ms_weight * ratio;
}

ControlData RCScanner::getControlData( const QString& line )
{
    ControlData ctrlData;
    ctrlData.ctrlType = extractType( line );

    QStringList characteristics = line.mid( Control::controlLen(ctrlData.ctrlType) ).trimmed().split( ',' );
    auto getCharacteristic = [&]( int idx ) -> QString
    {
        QString rv;
        if( idx >= 0 && idx < characteristics.size() ) {
            rv = characteristics.at( idx );
        }
        return rv;
    };

    switch( ctrlData.ctrlType ) {
    case Control::EDITTEXT:
    case Control::LISTBOX:
    case Control::SCROLLBAR:
        ctrlData.id = getCharacteristic( Position::CTL_ID );
        ctrlData.pos.setX( getCharacteristic(Position::CTL_X).toInt() );
        ctrlData.pos.setY( getCharacteristic(Position::CTL_Y).toInt() );
        ctrlData.size.setWidth( getCharacteristic(Position::CTL_WIDTH).toInt() );
        ctrlData.size.setHeight( getCharacteristic(Position::CTL_HEIGHT).toInt() );
        ctrlData.style = getCharacteristic( Position::CTL_STYLE );
        ctrlData.xstyle = getCharacteristic( Position::CTL_XSTYLE );
        break;
    case Control::COMBOBOX:
        ctrlData.id = getCharacteristic( Position::CTL_ID );
        ctrlData.pos.setX( getCharacteristic(Position::CTL_X).toInt() );
        ctrlData.pos.setY( getCharacteristic(Position::CTL_Y).toInt() );
        ctrlData.size.setWidth( getCharacteristic(Position::CTL_WIDTH).toInt() );
        ctrlData.size.setHeight( COMBOBOX_HEIGHT );
        ctrlData.style = getCharacteristic( Position::CTL_STYLE );
        ctrlData.xstyle = getCharacteristic( Position::CTL_XSTYLE );
        ctrlData.virtualHeight = getCharacteristic(Position::CTL_HEIGHT);
        break;
    case Control::ICON:
    case Control::LTEXT:
    case Control::RTEXT:
    case Control::CTEXT:
    case Control::PUSHBUTTON:
    case Control::PUSHBOX:
    case Control::DEFPUSHBUTTON:
    case Control::CHECKBOX:
    case Control::RADIOBUTTON:
    case Control::GROUPBOX:
        ctrlData.id = getCharacteristic( Position::CWT_ID );
        ctrlData.text = getCharacteristic( Position::CWT_TEXT );
        ctrlData.pos.setX( getCharacteristic(Position::CWT_X).toInt() );
        ctrlData.pos.setY( getCharacteristic(Position::CWT_Y).toInt() );
        ctrlData.size.setWidth( getCharacteristic(Position::CWT_WIDTH).toInt() );
        ctrlData.size.setHeight( getCharacteristic(Position::CWT_HEIGHT).toInt() );
        ctrlData.style = getCharacteristic( Position::CWT_STYLE );
        ctrlData.xstyle = getCharacteristic( Position::CWT_XSTYLE );
        break;
    case Control::CCONTROL:
        ctrlData.id = getCharacteristic( Position::CCL_ID );
        ctrlData.cctype = getCharacteristic( Position::CCL_TYPE );
        ctrlData.text = getCharacteristic( Position::CCL_TEXT );
        ctrlData.pos.setX( getCharacteristic(Position::CCL_X).toInt() );
        ctrlData.pos.setY( getCharacteristic(Position::CCL_Y).toInt() );
        ctrlData.size.setWidth( getCharacteristic(Position::CCL_WIDTH).toInt() );
        ctrlData.size.setHeight( getCharacteristic(Position::CCL_HEIGHT).toInt() );
        ctrlData.style = getCharacteristic( Position::CCL_STYLE );
        ctrlData.xstyle = getCharacteristic( Position::CCL_XSTYLE );
        break;
    default:
        assert( false );
    }
    ctrlData.type = getWidgetType( ctrlData );
    ctrlData.text = ctrlData.text.remove( "\"" );

    return ctrlData;
}

QPoint RCScanner::toPixel( const QPoint & pos )
{
    QSize fontSize = getFontSize(font);
    return QPoint( (fontSize.width() * pos.x()) / 4, (fontSize.height() * pos.y()) / 8 );
}

QSize RCScanner::toPixel( const QSize & size )
{
    QSize fontSize = getFontSize(font);
    return QSize( (fontSize.width() * size.width()) / 4.0 + 0.5, (fontSize.height() * size.height()) / 8.0 + 0.5 );
}

void RCScanner::setupWidgetData( const UIElementData& uiElementData, ObjectDataWP objData )
{
    auto widgetData = dynamic_cast<WidgetData*>( objData.lock().get() );
    if ( ! widgetData ) return;

    widgetData->setName( uiElementData.id );
    widgetData->setPos( toPixel(uiElementData.pos) );
    widgetData->setSize( toPixel(uiElementData.size) );
}

void RCScanner::setupTextData( const ControlData& ctrlData, ObjectDataWP objData )
{
    auto textData = dynamic_cast<TextData*>( objData.lock().get() );
    if ( ! textData ) return;

    QString text = ctrlData.text;
    text.replace( "\\n", "<br />" );
    textData->setText( text );

    auto alignent = [&]() -> Qt::AlignmentFlag {
        switch ( ctrlData.ctrlType ) {
        case Control::CTEXT: return Qt::AlignHCenter;
        case Control::RTEXT: return Qt::AlignRight;
        default            : return Qt::AlignLeft;
        };
    };
    textData->setAlignment( alignent() );
}

void RCScanner::setupEditData( const ControlData& ctrlData, ObjectDataWP objData )
{
    auto editData = dynamic_cast<EditData*>( objData.lock().get() );
    if ( ! editData ) return;

    editData->SetMultiLine( ctrlData.style.contains(Styles::edit[Styles::ED_MULTILINE]) );
}

void RCScanner::setupComboBoxData( const ControlData& ctrlData, ObjectDataWP objData )
{
    auto cmbData = dynamic_cast<ComboBoxData*>( objData.lock().get() );
    if ( ! cmbData ) return;

    cmbData->setItemCount( ctrlData.virtualHeight.toInt() / COMBOBOX_HEIGHT - 1 );
}

void RCScanner::setupButtonData( const ControlData& ctrlData, ObjectDataWP objData )
{
    auto btnData = dynamic_cast<ButtonData*>( objData.lock().get() );
    if ( ! btnData ) return;

    btnData->setText( ctrlData.text );

    auto pushBtnData = dynamic_cast<PushButtonData*>( objData.lock().get() );
    if ( pushBtnData ) {
        pushBtnData->setIsDefault( ctrlData.ctrlType == Control::DEFPUSHBUTTON );
    }

    auto chkBoxData  = dynamic_cast<CheckBoxData*>( objData.lock().get() );
    if ( chkBoxData ) {
        chkBoxData->setIsChecked(false); // <2DO>
    }

    auto rdBtnData  = dynamic_cast<RadioButtonData*>( objData.lock().get() );
    if ( rdBtnData ) {
        rdBtnData->setIsChecked(false); // <2DO>
    }
}

void RCScanner::setupGroupBoxData( const ControlData& ctrlData, ObjectDataWP objData )
{
    auto grpBoxData = dynamic_cast<GroupBoxData*>( objData.lock().get() );
    if ( ! grpBoxData ) return;

    grpBoxData->setTitle( ctrlData.text );
}

ObjectDataSP RCScanner::createWidget( const ControlData& ctrlData )
{
    auto objData = WidgetData::create( ctrlData.type );

    setupWidgetData( ctrlData, objData );
    setupTextData( ctrlData, objData );
    setupEditData( ctrlData, objData );
    setupComboBoxData( ctrlData, objData );
    setupButtonData( ctrlData, objData );
    setupGroupBoxData( ctrlData, objData );

    return objData;
}

ObjectDataSP RCScanner::createDialog( const MfcDialogData& dlgData )
{
    auto objData = std::make_shared<DialogData>();

    setupWidgetData( dlgData, objData );

    auto& dialogData = dynamic_cast<DialogData&>( *objData );
    dialogData.setCaption( dlgData.title );
    dialogData.setFont( dlgData.font );

    return objData;
}

