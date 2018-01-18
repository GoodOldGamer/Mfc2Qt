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

#include <QApplication>
#include <QMouseEvent>
#include <QDialog>
#include <QIcon>

#include "dialoglistmodel.h"
#include "dialoglistdelegate.h"

namespace
{
    const int buttonSize = 26;

    template <typename T>
    bool inRange(T min, T max, T value)
    {
        return (value >= min && value <= max);
    }
} // unnamed namespace

DialogListDelegate::DialogListDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void DialogListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &item, const QModelIndex &index) const
{
    if (index.column() == 1)
    {
        QStyleOptionButton button;
        button.rect = QRect(item.rect.topLeft(),QSize(buttonSize,buttonSize));
        button.icon = QIcon(":/img/VIEW_DLG_ICO");
        button.iconSize = QSize(buttonSize - 2,buttonSize - 2);
        button.state = QStyle::State_Enabled;

        QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter );
        return;
    }
    if (index.column() == 2)
    {
        QStyleOptionButton button;
        button.rect = QRect(item.rect.topLeft(),QSize(buttonSize,buttonSize));
        button.icon = QIcon(":/img/SAVE_ICO");
        button.iconSize = QSize(buttonSize - 2,buttonSize - 2);
        button.state = QStyle::State_Enabled;

        QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter );
        return;
    }

    QStyledItemDelegate::paint(painter, item, index);
}

QSize DialogListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint( option, index );
    if ( inRange(1,2,index.column()) )
    {
        size.setWidth(buttonSize);
        size.setHeight(buttonSize);
    }
    return size;
}

bool DialogListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &item, const QModelIndex &index)
{
    if (index.column() == 1)
    {
        if( event->type() == QEvent::MouseButtonRelease )
        {
            auto btnPos = item.rect.topLeft();
            auto mouseEvent = dynamic_cast<QMouseEvent&>(*event);
            if ( inRange(btnPos.x(), btnPos.x() + buttonSize, mouseEvent.x()) && inRange(btnPos.y(), btnPos.y() + buttonSize, mouseEvent.y()))
            {
                auto dlgListModel = dynamic_cast<DialogListModel*>(model);
                if (dlgListModel)
                {
                    dlgListModel->showDialog(index);
                }
            }
        }
        return true;
    }
    if (index.column() == 2)
    {
        if( event->type() == QEvent::MouseButtonRelease )
        {
            auto btnPos = item.rect.topLeft();
            auto mouseEvent = dynamic_cast<QMouseEvent&>(*event);
            if ( inRange(btnPos.x(), btnPos.x() + buttonSize, mouseEvent.x()) && inRange(btnPos.y(), btnPos.y() + buttonSize, mouseEvent.y()))
            {
                auto dlgListModel = dynamic_cast<DialogListModel*>(model);
                if (dlgListModel)
                {
                    dlgListModel->saveDialog(index);
                }
            }
        }
        return true;
    }

    return QStyledItemDelegate::editorEvent(event, model, item, index);
}

