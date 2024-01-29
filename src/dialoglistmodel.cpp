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

#include "mainwindow.h"
#include "dialoglistmodel.h"

DialogListModel::DialogListModel(ConverterMainWindow *parent)
    :QAbstractTableModel(parent)
{
}

DialogListModel::~DialogListModel()
{
}

int DialogListModel::rowCount(const QModelIndex & /*parent*/) const
{
   return dialogData.size();
}

int DialogListModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant DialogListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= (int)dialogData.size())
       return QVariant();

    auto dlgData = dynamic_cast<DialogData*>(dialogData[index.row()].get());
    if (!dlgData) return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            return dlgData->getName();
        }
    }

    return QVariant();
}

void DialogListModel::setDialogData(std::vector<ObjectDataSP> dialogData)
{
    beginResetModel();
    this->dialogData = dialogData;
    endResetModel();
}

void DialogListModel::clearData()
 {
    beginResetModel();
    dialogData.clear();
    endResetModel();
 }

void DialogListModel::showDialog(const QModelIndex &index)
{
    if (index.row() < 0 || index.row() >= (int)dialogData.size())
        return;

    mainWin()->showPreviewDialog(dialogData[index.row()]);
}

void DialogListModel::saveDialog(const QModelIndex &index)
{
    if (index.row() < 0 || index.row() >= (int)dialogData.size())
        return;

    mainWin()->saveDialog(dialogData[index.row()]);
}

ConverterMainWindow * DialogListModel::mainWin()
{
    return dynamic_cast<ConverterMainWindow*>(parent());
}
