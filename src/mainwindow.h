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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#pragma once

#include "ui_mainwindow.h"
#include "dialogpreview.h"
#include "dialoglistmodel.h"

class RCScanner;

typedef std::map<QString, DialogPreview*> DialogCache;

class ConverterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ConverterMainWindow();
    virtual ~ConverterMainWindow();

    void showPreviewDialog(ObjectDataWP dlgDataPtr);
    void saveDialog(ObjectDataWP dlgDataPtr);

private slots:
    void readResourceFile();
    void parseRCFile();

    void about();
    void help();

    void selectResourceFile();
    void selectOutputDir();

private:
    Ui::Mfc2Qt              ui;

    QString                 cppStrings;
    QString                 headerStrings;
    QString                 qrcFile;

    DialogCache             dialogCache;
    DialogListModel *       dialogsModel;
    QStringList             dialogImages;
    QMap<QString,QString>   dialogStrings;

    DialogPreview * createDialog(ObjectDataWP dlgDataPtr);
};

#endif // __MAINWINDOW_H__
