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

#ifndef __RESSOURCEDEF_H__
#define __RESSOURCEDEF_H__

#pragma once

#define TRUE        1
#define FALSE       0

#define SDIALOG     "DIALOG"
#define SDIALOGEX   "DIALOGEX"

#define GUIDELINES  "GUIDELINES DESIGNINFO"
#define STRINGTABLE "STRINGTABLE"
#define SSTYLE      "STYLE"
#define SEXSTYLE    "EXSTYLE"
#define SCAPTION    "CAPTION"
#define SFONT       "FONT"
#define SBEGIN      "BEGIN"
#define SEND        "END"

#define XPOS        0
#define YPOS        1
#define WIDTHPOS    2
#define HEIGHTPOS   3

#define CAPTIONPOS  1

#define FONTSIZEPOS 0
#define FONTPOS     1
#define WEIGHTPOS   2
#define ITALICPOS   3
#define CHARSETPOS  4

namespace Position
{
    // Label, Button, GroupBox, CheckBox, RadioButton
    enum Control
    {
        CTL_ID,
        CTL_X,
        CTL_Y,
        CTL_WIDTH,
        CTL_HEIGHT,
        CTL_STYLE,
        CTL_XSTYLE,
    };

    // Icon, Edit, ComboBox, ListBox, Scrollbar
    enum ControlWText
    {
        CWT_TEXT,
        CWT_ID,
        CWT_X,
        CWT_Y,
        CWT_WIDTH,
        CWT_HEIGHT,
        CWT_STYLE,
        CWT_XSTYLE,
    };

    enum CustomControl
    {
        CCL_TEXT,
        CCL_ID,
        CCL_TYPE,
        CCL_STYLE,
        CCL_X,
        CCL_Y,
        CCL_WIDTH,
        CCL_HEIGHT,
        CCL_XSTYLE,
    };

}

#define CTL_STATIC          "Static"
#define CTL_BUTTON          "Button"
#define CTL_LISTVIEW        "SysListView32"
#define CTL_PROFUISDTP      "ProfUIS-DurationWnd"
#define CTL_PROFUISGRID     "ProfUIS-ScrollItemWindow"
#define CTL_PROFUISCTRLBAR  "ProfUIS-ControlBar"

#define CTS_AUTOCHECKBOX    "BS_AUTOCHECKBOX"
#define CTS_AUTORADIOBUTTON "BS_AUTORADIOBUTTON"

/* Font Weights */
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_DEMIBOLD         600
#define FW_BOLD             700
#define FW_BLACK            900
#define FW_MAX             1000
#define QT_MAX               99

#endif // __RESSOURCEDEF_H__
