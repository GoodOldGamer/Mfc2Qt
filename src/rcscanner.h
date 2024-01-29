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

#ifndef __RCSCANNER_H__
#define __RCSCANNER_H__

#pragma once

#include <QObject>

#include <QByteArray>
#include <QString>
#include <QSize>
#include <QPoint>
#include <QFont>
#include <QList>
#include <QFile>

#include "objectdata.h"
#include "resourcedata.h"
#include "rcrawdata.h"

class RCScanner : public QObject
{
    Q_OBJECT

public:
    enum ERRORCODE
    {
        ERR_SUCCESS,
        ERR_UKNOWNCONTROL,
        ERR_CANNOTOPENFILE
    };

    RCScanner( QObject * parent );
    virtual ~RCScanner();

    void readFile( const QString& filePath );

    QStringList getDialogIDs() const;
    ObjectDataSP getDialogData( const QString& dlgID );

    const QStringList& getImages() const;
    const QStringMap& getStringTable() const;

private:
    ObjectDataSP        dialog;

    QString             caption;
    QString             id;
    QSize               size;
    QPoint              pos;
    QFont               font;
    QString             type;
    ERRORCODE           errorCode;

    DlgDataMap          dialogGuis;
    QStringList         images;
    QStringMap          stringTable;

    MfcDialogData getMfcDialogData( const QString& dlgID ) const;

    bool isNewControl( const QString& line );

    void processGuidelines( QFile& rcFile );
    void processDialogLayout( QFile& rcFile );
    void processDlgInit( QFile& rcFile );
    void processDialog( QFile& rcFile );
    void processImage( QFile& rcFile );
    void processStringTable( QFile& rcFile );

    int calculateFontWeight( int ms_weight );
    ControlData getControlData( const QString& line );

    QPoint toPixel( const QPoint & pos );
    QSize toPixel( const QSize & size );

    void setupWidgetData( const UIElementData& uiElementData, ObjectDataWP objData );
    void setupTextData( const ControlData& ctrlData, ObjectDataWP objData );
    void setupEditData( const ControlData& ctrlData, ObjectDataWP objData );
    void setupComboBoxData( const ControlData& ctrlData, ObjectDataWP objData );
    void setupButtonData( const ControlData& ctrlData, ObjectDataWP objData );
    void setupGroupBoxData( const ControlData& ctrlData, ObjectDataWP objData );

    ObjectDataSP createWidget( const ControlData& ctrlData );
    ObjectDataSP createDialog( const MfcDialogData& dlgData );
};

#endif // __RCSCANNER_H__
