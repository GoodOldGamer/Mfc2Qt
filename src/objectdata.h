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

#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#pragma once

#include <memory>

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QList>

#include "ctrldefinitions.h"

typedef std::shared_ptr<class ObjectDataBase> ObjectDataSP;
typedef std::weak_ptr<class ObjectDataBase> ObjectDataWP;

class ObjectDataBase : public std::enable_shared_from_this<ObjectDataBase>
{
public:
    ObjectDataBase();
    virtual ~ObjectDataBase();

    void setName( const QString& name );
    const QString& getName() const;

    virtual const QFont& getFont() const = 0;
    virtual QSize getFontSize() const = 0;

    void setParent( ObjectDataBase * parent );
    ObjectDataBase * getParent() const;

    void addChild( ObjectDataWP child );
    void removeChild( ObjectDataWP child );

    QObject * createQObject( QObject * parent ) const;

protected:
    QString                 name;

    ObjectDataBase *        parent;
    QList<ObjectDataSP>     children;

    virtual QObject * createNewQObject( QObject * parent ) const = 0;
    virtual void initQObject( QObject * obj ) const;
};

class ObjectData : public ObjectDataBase
{
public:
    ObjectData();
    virtual ~ObjectData();

    virtual const QFont& getFont() const override;
    virtual QSize getFontSize() const override;

protected:
    virtual QObject * createNewQObject( QObject * parent ) const override;
};

class WidgetData : public ObjectData
{
public:
    WidgetData();
    virtual ~WidgetData();

    static ObjectDataSP create( Control::WIDGET type );

    void setPos( const QPoint& pos );
    const QPoint& getPos() const;

    void setSize( const QSize& size );
    const QSize& getSize() const;

    // <2DO> set style

protected:
    QPoint  pos_;
    QSize   size_;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class TextData : public WidgetData
{
public:
    TextData();
    virtual ~TextData();

    void setText( const QString& text );
    const QString& getText() const;

    void setAlignment( Qt::AlignmentFlag alignment );
    Qt::AlignmentFlag getAlignment() const;

protected:
    QString             text;
    Qt::AlignmentFlag   alignment;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class EditData : public TextData
{
public:
    EditData();
    virtual ~EditData();

    void SetMultiLine( bool multiLine );
    bool IsMultiLine() const;

protected:
    bool isMultiLine;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class ButtonData : public WidgetData
{
public:
    ButtonData();
    virtual ~ButtonData();

    void setText( const QString& text );
    const QString& getText() const;

protected:
    QString text_;

    virtual void initQObject( QObject * obj ) const override;
};

class PushButtonData : public ButtonData
{
public:
    PushButtonData();
    virtual ~PushButtonData();

    void setIsDefault( bool isDefault );
    bool getIsDefault() const;

protected:
    bool isDefault;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class CheckBoxData : public ButtonData
{
public:
    CheckBoxData();
    virtual ~CheckBoxData();

    void setIsChecked( bool isChecked );
    bool getIsChecked() const;

protected:
    bool isChecked;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class RadioButtonData : public ButtonData
{
public:
    RadioButtonData();
    virtual ~RadioButtonData();

    void setIsChecked( bool isChecked );
    bool getIsChecked() const;

protected:
    bool isChecked;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class GroupBoxData : public WidgetData
{
public:
    GroupBoxData();
    virtual ~GroupBoxData();

    void setTitle( const QString& title );
    const QString& getTitle() const;

protected:
    QString title;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class ComboBoxData : public WidgetData
{
public:
    ComboBoxData();
    virtual ~ComboBoxData();

    void setItemCount( int itemCount );
    int getItemCount() const;

protected:
    int itemCount;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

class ListViewData : public WidgetData
{
public:
    ListViewData();
    virtual ~ListViewData();

protected:
    virtual QObject * createNewQObject( QObject * parent ) const override;
};

class TableViewData : public WidgetData
{
public:
    TableViewData();
    virtual ~TableViewData();

protected:
    virtual QObject * createNewQObject( QObject * parent ) const override;
};

class DateTimeEditData : public WidgetData
{
public:
    DateTimeEditData();
    virtual ~DateTimeEditData();

protected:
    virtual QObject * createNewQObject( QObject * parent ) const override;
};

class MenuBarData : public WidgetData
{
public:
    MenuBarData();
    virtual ~MenuBarData();

protected:
    virtual QObject * createNewQObject( QObject * parent ) const override;
};

class ErrorWidgetData : public WidgetData
{
public:
    ErrorWidgetData();
    virtual ~ErrorWidgetData();

protected:
    virtual void initQObject( QObject * obj ) const override;
};

class DialogData : public WidgetData
{
public:
    DialogData();
    virtual ~DialogData();

    void setCaption( const QString& caption );
    const QString& getCaption() const;

    void setFont( const QFont& font );
    virtual const QFont& getFont() const override;
    virtual QSize getFontSize() const override;

protected:
    QString         caption;
    QFont           font;
    mutable QSize   fontSize;

    virtual QObject * createNewQObject( QObject * parent ) const override;
    virtual void initQObject( QObject * obj ) const override;
};

#endif // OBJECTDATA_H
