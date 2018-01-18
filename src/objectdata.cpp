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

#include <assert.h>

#include <QFontMetrics>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QListView>
#include <QTableView>
#include <QTextEdit>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QMenuBar>
#include <QScrollBar>
#include <QDialog>

#include "objectdata.h"
#include "dialogpreview.h"

namespace
{
    template <class T>
    void setTextAndAllignment( const TextData * data, QObject * obj )
    {
        auto widget = dynamic_cast<T*>( obj );
        if ( widget )
        {
            widget->setText( data->getText() );
            widget->setAlignment( data->getAlignment() );
        }
    }
}

/*////////////////////////////////////////////////////////////////////
// ObjectDataBase                                                   */

ObjectDataBase::ObjectDataBase()
    : name( "DefaultName" )
    , parent( nullptr )
{
}

ObjectDataBase::~ObjectDataBase()
{
}

void ObjectDataBase::setName( const QString& name )
{
    this->name = name;
}

const QString& ObjectDataBase::getName() const
{
    return name;
}

void ObjectDataBase::setParent( ObjectDataBase * parent )
{
    if ( this->parent == parent )
        return;

    if ( parent != nullptr ) {
        parent->removeChild( shared_from_this() );
    }

    this->parent = parent;

    if ( this->parent != nullptr ) {
        this->parent->addChild( shared_from_this() );
    }
}

ObjectDataBase * ObjectDataBase::getParent() const
{
    return parent;
}

void ObjectDataBase::addChild( ObjectDataWP child )
{
    auto childSP = child.lock();
    if ( childSP ) {
        if ( ! children.contains(childSP) ) {
            children.append( childSP );
            childSP->setParent( this );
        }
    }
}

void ObjectDataBase::removeChild( ObjectDataWP child )
{
    auto childSP = child.lock();
    if ( childSP ) {
        if ( children.contains(childSP) ) {
            children.removeOne( childSP );
            childSP->setParent( nullptr );
        }
    }
}

QObject * ObjectDataBase::createQObject( QObject * parent ) const
{
    QObject * obj = createNewQObject( parent );
    initQObject( obj );
    return obj;
}

void ObjectDataBase::initQObject( QObject * obj ) const
{
    obj->setObjectName( name );

    foreach (auto child, children) {
        child->createQObject( obj );
    }
}

/*////////////////////////////////////////////////////////////////////
// ObjectData                                                       */

ObjectData::ObjectData()
    : ObjectDataBase()
{
}

ObjectData::~ObjectData()
{
}

const QFont& ObjectData::getFont() const
{
    return parent->getFont();
}

QSize ObjectData::getFontSize() const
{
    return parent->getFontSize();
}

QObject * ObjectData::createNewQObject( QObject * parent ) const
{
    return new QObject( parent );
}

/*////////////////////////////////////////////////////////////////////
// WidgetData                                                       */

WidgetData::WidgetData()
    : ObjectData()
{}

WidgetData::~WidgetData()
{}

ObjectDataSP WidgetData::create( Control::WIDGET type )
{
    ObjectDataSP rv;
    switch ( type ) {
    case Control::QWIDGET:
        rv = std::make_shared<WidgetData>();
        break;
    case Control::QLABEL:
        rv = std::make_shared<TextData>();
        break;
    case Control::QLINEEDIT:
    case Control::QTEXTEDIT:
        rv = std::make_shared<EditData>();
        break;
    case Control::QPUSHBUTTON:
            rv = std::make_shared<PushButtonData>();
            break;
    case Control::QGROUPBOX:
            rv = std::make_shared<GroupBoxData>();
            break;
    case Control::QCHECKBOX:
            rv = std::make_shared<CheckBoxData>();
            break;
    case Control::QRADIOBUTTON:
            rv = std::make_shared<RadioButtonData>();
            break;
    case Control::QCOMBOBOX:
            rv = std::make_shared<ComboBoxData>();
            break;
    case Control::QLISTVIEW:
            rv = std::make_shared<ListViewData>();
            break;
    case Control::QTABLEVIEW:
            rv = std::make_shared<TableViewData>();
            break;
    case Control::QDATETIMEEDIT:
            rv = std::make_shared<DateTimeEditData>();
            break;
    case Control::QMENUBAR:
            rv = std::make_shared<MenuBarData>();
            break;
    case Control::QSCROLLBAR:
    case Control::QIMAGE:
        // <2DO> implement
        // falltru
    default:
        rv = std::make_shared<ErrorWidgetData>();
    }

    return rv;
}

void WidgetData::setPos( const QPoint& pos )
{
    pos_ = pos;
}

const QPoint& WidgetData::getPos() const
{
    return pos_;
}

void WidgetData::setSize( const QSize& size )
{
    size_ = size;
}

const QSize& WidgetData::getSize() const
{
    return size_;
}

QObject * WidgetData::createNewQObject( QObject * parent ) const
{
    return new QWidget( dynamic_cast<QWidget*>(parent) );
}

void WidgetData::initQObject( QObject * obj ) const
{
    ObjectData::initQObject( obj );

    auto widget = dynamic_cast<QWidget*>( obj );
    if ( widget ) {
        widget->setGeometry( getPos().x(), getPos().y(), getSize().width(), getSize().height() );
    }
}

/*////////////////////////////////////////////////////////////////////
// LabelData                                                        */

TextData::TextData()
    : WidgetData()
    , alignment( Qt::AlignLeft )
{}

TextData::~TextData()
{}

void TextData::setText( const QString& text )
{
    this->text = text;
}

const QString& TextData::getText() const
{
    return text;
}

void TextData::setAlignment( Qt::AlignmentFlag alignment )
{
    this->alignment = alignment;
}

Qt::AlignmentFlag TextData::getAlignment() const
{
    return alignment;
}

QObject * TextData::createNewQObject( QObject * parent ) const
{
    return new QLabel( dynamic_cast<QWidget*>(parent) );
}

void TextData::initQObject( QObject * obj ) const
{
    WidgetData::initQObject( obj );

    setTextAndAllignment<QLabel>( this, obj );
}

/*////////////////////////////////////////////////////////////////////
// EditData                                                         */

EditData::EditData()
    : TextData()
    , isMultiLine( false )
{}

EditData::~EditData()
{}

void EditData::SetMultiLine( bool multiLine )
{
    isMultiLine = multiLine;
}

bool EditData::IsMultiLine() const
{
    return isMultiLine;
}

QObject * EditData::createNewQObject( QObject * parent ) const
{
    bool isLineEdit = true; // <2DO> select via style
    if ( isLineEdit ) {
        return new QLineEdit( dynamic_cast<QWidget*>(parent) );
    }
    else {
        return new QTextEdit( dynamic_cast<QWidget*>(parent) );
    }
}

void EditData::initQObject( QObject * obj ) const
{
    WidgetData::initQObject( obj );

    bool isLineEdit = true; // <2DO> select via style
    if ( isLineEdit ) {
        setTextAndAllignment<QLineEdit>( this, obj );
    }
    else {
        setTextAndAllignment<QTextEdit>( this, obj );
    }
}

/*////////////////////////////////////////////////////////////////////
// ButtonData                                                       */

ButtonData::ButtonData()
    : WidgetData()
{}

ButtonData::~ButtonData()
{}

void ButtonData::setText( const QString& text )
{
    text_ = text;
}

const QString& ButtonData::getText() const
{
    return text_;
}

void ButtonData::initQObject( QObject * obj ) const
{
    WidgetData::initQObject( obj );

    auto button = dynamic_cast<QAbstractButton*>( obj );
    if ( button )
    {
        button->setText( text_ );
    }
}

/*////////////////////////////////////////////////////////////////////
// PushButtonData                                                   */

PushButtonData::PushButtonData()
    : ButtonData()
    , isDefault( false )
{}

PushButtonData::~PushButtonData()
{}

void PushButtonData::setIsDefault( bool isDefault )
{
    this->isDefault = isDefault;
}

bool PushButtonData::getIsDefault() const
{
    return isDefault;
}

QObject * PushButtonData::createNewQObject( QObject * parent ) const
{
    return new QPushButton( dynamic_cast<QWidget*>(parent) );
}

void PushButtonData::initQObject( QObject * obj ) const
{
    ButtonData::initQObject( obj );

    auto button = dynamic_cast<QPushButton*>( obj );
    if ( button )
    {
        button->setDefault( isDefault );
    }
}

/*////////////////////////////////////////////////////////////////////
// CheckBoxData                                                        */

CheckBoxData::CheckBoxData()
    : ButtonData()
    , isChecked( false )
{}

CheckBoxData::~CheckBoxData()
{}

void CheckBoxData::setIsChecked( bool isChecked )
{
    this->isChecked = isChecked;
}

bool CheckBoxData::getIsChecked() const
{
    return isChecked;
}

QObject * CheckBoxData::createNewQObject( QObject * parent ) const
{
    return new QCheckBox( dynamic_cast<QWidget*>(parent) );
}

void CheckBoxData::initQObject( QObject * obj ) const
{
    ButtonData::initQObject( obj );

    auto chkBox = dynamic_cast<QCheckBox*>( obj );
    if ( chkBox )
    {
        chkBox->setChecked( isChecked );
    }
}

/*////////////////////////////////////////////////////////////////////
// RadioButtonData                                                  */

RadioButtonData::RadioButtonData()
    : ButtonData()
    , isChecked( false )
{}

RadioButtonData::~RadioButtonData()
{}

void RadioButtonData::setIsChecked( bool isChecked )
{
    this->isChecked = isChecked;
}

bool RadioButtonData::getIsChecked() const
{
    return isChecked;
}

QObject * RadioButtonData::createNewQObject( QObject * parent ) const
{
    return new QRadioButton( dynamic_cast<QWidget*>(parent) );
}

void RadioButtonData::initQObject( QObject * obj ) const
{
    ButtonData::initQObject( obj );

    auto rButton = dynamic_cast<QRadioButton*>( obj );
    if ( rButton )
    {
        rButton->setChecked( isChecked );
    }
}

/*////////////////////////////////////////////////////////////////////
// GroupBoxData                                                     */

GroupBoxData::GroupBoxData()
    : WidgetData()
{}

GroupBoxData::~GroupBoxData()
{}

void GroupBoxData::setTitle( const QString& title )
{
    this->title = title;
}

const QString& GroupBoxData::getTitle() const
{
    return title;
}

QObject * GroupBoxData::createNewQObject( QObject * parent ) const
{
    return new QGroupBox( dynamic_cast<QWidget*>(parent) );
}

void GroupBoxData::initQObject( QObject * obj ) const
{
    WidgetData::initQObject( obj );

    auto gbox = dynamic_cast<QGroupBox*>( obj );
    if ( gbox )
    {
        gbox->setTitle( title );

        // <2DO> add children
    }
}

/*////////////////////////////////////////////////////////////////////
// ComboBoxData                                                     */

ComboBoxData::ComboBoxData()
    : WidgetData()
    , itemCount( 0 )
{}

ComboBoxData::~ComboBoxData()
{}

void ComboBoxData::setItemCount( int itemCount )
{
    this->itemCount = itemCount;
}

int ComboBoxData::getItemCount() const
{
    return itemCount;
}

QObject * ComboBoxData::createNewQObject( QObject * parent ) const
{
    return new QComboBox( dynamic_cast<QWidget*>(parent) );
}

void ComboBoxData::initQObject( QObject * obj ) const
{
    WidgetData::initQObject( obj );

    auto cmbBox = dynamic_cast<QComboBox*>( obj );
    if ( cmbBox )
    {
        cmbBox->setMaxVisibleItems( itemCount );
    }
}

/*////////////////////////////////////////////////////////////////////
// ListViewData                                                     */

ListViewData::ListViewData()
    : WidgetData()
{}

ListViewData::~ListViewData()
{}

QObject * ListViewData::createNewQObject( QObject * parent ) const
{
    return new QListView( dynamic_cast<QWidget*>(parent) );
}

/*////////////////////////////////////////////////////////////////////
// TableViewData                                                    */

TableViewData::TableViewData()
    : WidgetData()
{}

TableViewData::~TableViewData()
{}

QObject * TableViewData::createNewQObject( QObject * parent ) const
{
    return new QTableView( dynamic_cast<QWidget*>(parent) );
}

/*////////////////////////////////////////////////////////////////////
// DateTimeEditData                                                 */

DateTimeEditData::DateTimeEditData()
    : WidgetData()
{}

DateTimeEditData::~DateTimeEditData()
{}

QObject * DateTimeEditData::createNewQObject( QObject * parent ) const
{
    return new QDateTimeEdit( dynamic_cast<QWidget*>(parent) );
}

/*////////////////////////////////////////////////////////////////////
// MenuBarData                                                      */

MenuBarData::MenuBarData()
    : WidgetData()
{}

MenuBarData::~MenuBarData()
{}

QObject * MenuBarData::createNewQObject( QObject * parent ) const
{
    return new QMenuBar( dynamic_cast<QWidget*>(parent) );
}

/*////////////////////////////////////////////////////////////////////
// ErrorWidgetData                                                  */

ErrorWidgetData::ErrorWidgetData()
    : WidgetData()
{}

ErrorWidgetData::~ErrorWidgetData()
{}

void ErrorWidgetData::initQObject( QObject * obj ) const
{
    WidgetData::initQObject( obj );

    auto widget = dynamic_cast<QWidget*>( obj );
    if ( widget )
    {
        widget->setStyleSheet( "background-color:rgb(255,0,0);" );
    }
}

/*////////////////////////////////////////////////////////////////////
// DialogData                                                       */

DialogData::DialogData()
    : WidgetData()
{
}

DialogData::~DialogData()
{
}

void DialogData::setCaption( const QString& caption )
{
    this->caption = caption;
}

const QString& DialogData::getCaption() const
{
    return caption;
}

void DialogData::setFont( const QFont& font )
{
    this->font = font;
    fontSize.setWidth( 0 );
    fontSize.setHeight( 0 );
}

const QFont& DialogData::getFont() const
{
    return font;
}

QSize DialogData::getFontSize() const
{
    if ( fontSize.isEmpty() )
    {
        QFontMetrics metrics( getFont() );

        // QFontMetrics::averageCharWidth doesn't deliver the right value, see https://support.microsoft.com/en-us/kb/145994
        int w = metrics.size( Qt::TextSingleLine, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" ).width();

        fontSize.setWidth( ( w / 26 + 1 ) / 2 );
        fontSize.setHeight( metrics.height() + 1 );
    }
    return fontSize;
}

QObject * DialogData::createNewQObject( QObject * parent ) const
{
    return new DialogPreview( dynamic_cast<QWidget*>(parent) );
}

void DialogData::initQObject( QObject * obj ) const
{
    WidgetData::initQObject( obj );

    auto dlg = dynamic_cast<QDialog*>( obj );
    if ( dlg ) {
        dlg->setWindowTitle(caption);
    }
}
