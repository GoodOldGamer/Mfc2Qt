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

#ifndef __RCWRITER_H_
#define __RCWRITER_H_

#pragma once

#include <QString>
#include <QStringList>
#include <QMap>

namespace RCWriter
{
    void writeQtRcFile( const QString& outputDir, const QString& filename, const QStringList& icons );
    void writeStringFile( const QString& outputDir, const QString& cppfile, const QString& headerfile, const QMap<QString,QString>& strings );
}

#endif //__RCWRITER_H_
