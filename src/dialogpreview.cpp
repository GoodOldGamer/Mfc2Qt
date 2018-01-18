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

#include <QXmlStreamReader>

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QListView>
#include <QTableView>
#include <QDateTimeEdit>
#include <QMenuBar>
#include <QGroupBox>

#include "dialogpreview.h"

DialogPreview::DialogPreview( QWidget * parent )
    : QDialog( parent, Qt::WindowFlags() )
{
}

void DialogPreview::closeEvent( QCloseEvent * event )
{
    setVisible(false);
    event->accept();
}

void DialogPreview::save( QFile & file )
{
    QXmlStreamWriter writer( &file );

    writer.setAutoFormatting( true );
    writer.writeStartDocument( "1.0", true );
    writer.setCodec( "UTF-8" );

    writer.writeStartElement( "ui" );
    writer.writeAttribute( "version", "4.0" );

    writer.writeTextElement( "class", this->objectName() );
    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QDialog" );
    writer.writeAttribute( "name", this->objectName() );

    writeGeometry( writer, geometry() );
    writeWindowTitle( writer, this->windowTitle() );

    foreach( QObject * child, children() )
    {
        addWidget( writer, qobject_cast<QWidget*>(child) );
    }

    // close all open elements and finish document
    writer.writeEndDocument();
}

void DialogPreview::writeGeometry( QXmlStreamWriter & writer, const QRect& rect )
{
    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "geometry" );

    writer.writeStartElement( "rect" );
    writer.writeTextElement( "x", QString::number( rect.x() ) );
    writer.writeTextElement( "y", QString::number( rect.y() ) );
    writer.writeTextElement( "width", QString::number( rect.width() ) );
    writer.writeTextElement( "height", QString::number( rect.height() ) );
    writer.writeEndElement(); //rect

    writer.writeEndElement(); //property
}

void DialogPreview::writeWindowTitle( QXmlStreamWriter & writer, const QString& title )
{
    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "windowTitle" );
    writer.writeTextElement( "string", title );
    writer.writeEndElement(); //property
}

void DialogPreview::addLabel( QXmlStreamWriter& writer, QLabel * label )
{
    if ( !label ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QLabel" );
    writer.writeAttribute( "name", label->objectName() );

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "text" );
    writer.writeTextElement( "string", label->text() );
    writer.writeEndElement(); //property

    writeGeometry( writer, label->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addButton( QXmlStreamWriter& writer, QPushButton * button )
{
    if ( !button ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QPushButton" );
    writer.writeAttribute( "name", button->objectName() );

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "text" );
    writer.writeTextElement( "string", button->text() );
    writer.writeEndElement(); //property

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "default" );
    writer.writeTextElement( "bool", button->isDefault() ? "true" : "false" );
    writer.writeEndElement(); //property

    writeGeometry( writer, button->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addCheckBox( QXmlStreamWriter& writer, QCheckBox * checkBox )
{
    if ( !checkBox ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QCheckBox" );
    writer.writeAttribute( "name", checkBox->objectName() );

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "text" );
    writer.writeTextElement( "string", checkBox->text() );
    writer.writeEndElement(); //property

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "checked" );
    writer.writeTextElement( "bool", checkBox->isChecked() ? "true" : "false" );
    writer.writeEndElement(); //property

    writeGeometry( writer, checkBox->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addRadioButton( QXmlStreamWriter& writer, QRadioButton * radioButton )
{
    if ( !radioButton ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QRadioButton" );
    writer.writeAttribute( "name", radioButton->objectName() );

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "text" );
    writer.writeTextElement( "string", radioButton->text() );
    writer.writeEndElement(); //property

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "checked" );
    writer.writeTextElement( "bool", radioButton->isChecked() ? "true" : "false" );
    writer.writeEndElement(); //property

    writeGeometry( writer, radioButton->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addLineEdit( QXmlStreamWriter& writer, QLineEdit * edit )
{
    if ( !edit ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QLineEdit" );
    writer.writeAttribute( "name", edit->objectName() );

    writeGeometry( writer, edit->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addTextEdit( QXmlStreamWriter& writer, QTextEdit * edit )
{
    if ( !edit ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QTextEdit" );
    writer.writeAttribute( "name", edit->objectName() );

    writeGeometry( writer, edit->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addNotImplementedLabel( QXmlStreamWriter& writer, QWidget * widget )
{
    if ( !widget ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QLabel" );
    writer.writeAttribute( "name", widget->objectName() );

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "text" );
    writer.writeTextElement( "string", QString("Not implemented: ").append(widget->metaObject()->className()) );
    writer.writeEndElement(); //property

    writeGeometry( writer, widget->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addErrorWidget( QXmlStreamWriter& writer, QWidget * widget )
{
    if ( !widget ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QWidget" );
    writer.writeAttribute( "name", widget->objectName() );

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "styleSheet" );
    writer.writeStartElement( "string" );
    writer.writeAttribute( "notr", "true" );
    writer.writeCharacters( "background-color:rgb(255,0,0);" );
    writer.writeEndElement(); //string
    writer.writeEndElement(); //property

    writeGeometry( writer, widget->geometry() );

    writer.writeEndElement(); //widget
}

void DialogPreview::addGroupBox( QXmlStreamWriter& writer, QGroupBox * groupbox )
{
    if ( !groupbox ) return;

    writer.writeStartElement( "widget" );
    writer.writeAttribute( "class", "QGroupBox" );
    writer.writeAttribute( "name", groupbox->objectName() );

    writer.writeStartElement( "property" );
    writer.writeAttribute( "name", "title" );
    writer.writeTextElement( "string", groupbox->title() );
    writer.writeEndElement(); //property

    writeGeometry( writer, groupbox->geometry() );

    foreach( QObject * child, groupbox->children() )
    {
        addWidget( writer, qobject_cast<QWidget*>(child) );
    }

    writer.writeEndElement(); //widget
}

void DialogPreview::prepareGroupBox( QGroupBox * groupbox )
{
    if ( !groupbox ) return;

    QList<QWidget*> children = this->childrenFromRect( groupbox->geometry() );
    foreach( QWidget * child, children )
    {
        child->setParent( groupbox );
        child->setGeometry( child->x() - groupbox->x(),
                            child->y() - groupbox->y(),
                            child->width(),
                            child->height() );
        child->show();
    }
}

QList<QWidget*> DialogPreview::childrenFromRect( const QRect& rect )
{
    QList<QWidget*> result;
    foreach( QObject * child, children() )
    {
        QWidget * widget = qobject_cast<QWidget*>( child );
        if ( !widget ) continue;

        if ( rect.contains(widget->x(), widget->y()) ||
             rect.contains(widget->x(), widget->y() + widget->height()) ||
             rect.contains(widget->x() + widget->width(), widget->y()) ||
             rect.contains(widget->x() + widget->width(), widget->y() + widget->height()) )
        {
            result.append( widget );
        }
    }

    return result;
}

void DialogPreview::addWidget( QXmlStreamWriter& writer, QWidget * widget )
{
    if (qobject_cast<QLabel*>(widget) != nullptr)
    {
        addLabel( writer, qobject_cast<QLabel*>(widget) );
    }
    else if (qobject_cast<QPushButton*>(widget) != nullptr)
    {
        addButton( writer, qobject_cast<QPushButton*>(widget) );
    }
    else if (qobject_cast<QCheckBox*>(widget) != nullptr)
    {
        addCheckBox( writer, qobject_cast<QCheckBox*>(widget) );
    }
    else if (qobject_cast<QRadioButton*>(widget) != nullptr)
    {
        addRadioButton( writer, qobject_cast<QRadioButton*>(widget) );
    }
    else if (qobject_cast<QLineEdit*>(widget) != nullptr)
    {
        addLineEdit( writer, qobject_cast<QLineEdit*>(widget) );
    }
    else if (qobject_cast<QTextEdit*>(widget) != nullptr)
    {
        addTextEdit( writer, qobject_cast<QTextEdit*>(widget) );
    }
    else if (qobject_cast<QListView*>(widget) != nullptr)
    {
        // <2DO>
        addNotImplementedLabel( writer, widget );
    }
    else if (qobject_cast<QTableView*>(widget) != nullptr)
    {
        // <2DO>
        addNotImplementedLabel( writer, widget );
    }
    else if (qobject_cast<QDateTimeEdit*>(widget) != nullptr)
    {
        // <2DO>
        addNotImplementedLabel( writer, widget );
    }
    else if (qobject_cast<QMenuBar*>(widget) != nullptr)
    {
        // <2DO>
        addNotImplementedLabel( writer, widget );
    }
    else if (qobject_cast<QGroupBox*>(widget) != nullptr)
    {
        addGroupBox( writer, qobject_cast<QGroupBox*>(widget) );
    }
    else
    {
        addErrorWidget( writer, widget );
    }
}
