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

#ifndef __DIALOGPREVIEW_H__
#define __DIALOGPREVIEW_H__

#pragma once

#include <QDialog>
#include <QXmlStreamWriter>
#include <QFile>
#include <QCloseEvent>

#include "objectdata.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QTextEdit;
class QGroupBox;
class QCheckBox;
class QRadioButton;

class DialogPreview : public QDialog
{
public:
    DialogPreview( QWidget * parent );

    void save( QFile & file );

    QList<QWidget*> childrenFromRect( const QRect& rect );

protected:
    virtual void closeEvent( QCloseEvent * event ) override;

private:
    void createInternal( const ObjectDataSP& data );

    void writeGeometry( QXmlStreamWriter& writer, const QRect& rect );
    void writeWindowTitle( QXmlStreamWriter& writer, const QString& title );

    void addWidget( QXmlStreamWriter& writer, QWidget * widget );

    void addLabel( QXmlStreamWriter& writer, QLabel * label );
    void addButton( QXmlStreamWriter& writer, QPushButton * button );
    void addCheckBox( QXmlStreamWriter& writer, QCheckBox * button );
    void addRadioButton( QXmlStreamWriter& writer, QRadioButton * radioButton );
    void addLineEdit( QXmlStreamWriter& writer, QLineEdit * edit );
    void addTextEdit( QXmlStreamWriter& writer, QTextEdit * edit );
    void addNotImplementedLabel( QXmlStreamWriter& writer, QWidget * widget );
    void addErrorWidget( QXmlStreamWriter& writer, QWidget * widget );
    void addGroupBox( QXmlStreamWriter& writer, QGroupBox * groupbox );
    void prepareGroupBox( QGroupBox * groupbox );
};

#endif // __DIALOGPREVIEW_H__
