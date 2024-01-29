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

#ifndef __DIALOGLISTMODEL_H_
#define __DIALOGLISTMODEL_H_

#pragma once

#include <vector>
#include <QAbstractTableModel>

#include "objectdata.h"

class DialogData;
class ConverterMainWindow;

class DialogListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DialogListModel(ConverterMainWindow *parent);
    virtual ~DialogListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setDialogData(const std::vector<ObjectDataSP> dialogData);
    void clearData();

    void showDialog(const QModelIndex &index);
    void saveDialog(const QModelIndex &index);

private:
    std::vector<ObjectDataSP> dialogData;

    ConverterMainWindow * mainWin();
};

#endif // __DIALOGLISTMODEL_H_
