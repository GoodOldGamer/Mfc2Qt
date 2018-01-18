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


#ifndef RCRAWDATA_H
#define RCRAWDATA_H

#pragma once

#include "ctrldefinitions.h"

class UIElementData
{
public:
    virtual ~UIElementData() {}

    QString     id;
    QPoint      pos;
    QSize       size;
};

class MfcDialogData : public UIElementData
{
public:
    QString     title;
    QFont       font;
    QString     type;
    QStringList ctrlDef;
};

class ControlData : public UIElementData
{
public:
    Control::WIDGET     type;
    Control::CONTROL    ctrlType;
    QString             text;
    QString             cctype;
    QString             style;
    QString             xstyle;
    QString             virtualHeight;
};

#endif // RCRAWDATA_H
