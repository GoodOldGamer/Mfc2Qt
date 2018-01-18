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

#ifndef __RESOURCEDATA_H_
#define __RESOURCEDATA_H_

#pragma once

#include <QMap>

#include "rcrawdata.h"

typedef QMap<QString,QString> QStringMap;
typedef QStringMap ImagesMap;
typedef QMap<QString,MfcDialogData> DlgDataMap;

class ResourceData
{
public:
    ResourceData();

protected:
    DlgDataMap  dialogGuis;
    ImagesMap   images;
    QStringMap  strings;
};


#endif // __RESOURCEDATA_H_
