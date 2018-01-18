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

#include "ctrldefinitions.h"

const char* Styles::edit[] = {
    "ES_MULTILINE",
    "ES_UPERCASE",
    "ES_LOWERCASE",
    "ES_PASSWORD",
    "ES_OEMCONVERT",
    "ES_AUTOVSCROLL",
    "ES_AUTOHSCROLL",
    "ES_NOHIDESEL",
    "ES_READONLY",
    "ES_WANTRETURN",
    "ES_LEFT",
    "ES_CENTER",
    "ES_NUMBER",
    "ES_RIGHT",
    nullptr
};

const char * Styles::button[] = {
    "BS_3STATE",
    "BS_AUTO3STATE",
    "BS_AUTOCHECKBOX",
    "BS_AUTORADIOBUTTON",
    "BS_BITMAP",
    "BS_BOTTOM",
    "BS_CENTER",
    "BS_CHECKBOX",
    "BS_COMMANDLINK",
    "BS_DEFCOMMANDLINK",
    "BS_DEFPUSHBUTTON",
    "BS_DEFSPLITBUTTON",
    "BS_GROUPBOX",
    "BS_ICON",
    "BS_FLAT",
    "BS_LEFT",
    "BS_LEFTTEXT",
    "BS_MULTILINE",
    "BS_NOTIFY",
    "BS_OWNDERDRAM",
    "BS_PUSHBUTTON",
    "BS_PUSHLIKE",
    "BS_RADIOBUTTON",
    "BS_RIGHT",
    "BS_RIGHTBUTTON",
    "BS_SPLITBUTTON",
    "BS_TEXT",
    "BS_TOP",
    "BS_TYPEMASK",
    "BS_USERBUTTON",
    "BS_VCENTER",
    nullptr
};

const char * Styles::combobox[] = {
    "CBS_AUTOHSCROLL",
    "CBS_DISABLENOSCROLL",
    "CBS_DROPDOWN",
    "CBS_DROPDOWNLIST",
    "CBS_HASSTRINGS",
    "CBS_LOWERCASE",
    "CBS_NOINTEGRALHEIGHT",
    "CBS_OEMCONVERT",
    "CBS_OWNERDRAWFIXED",
    "CBS_OWNERDRAWVARIABLE",
    "CBS_SIMPLE",
    "CBS_SORT",
    "CBS_UPPERCASE",
    nullptr
};

const char * Styles::listbox[] = {
    "LBS_COMBOBOX",
    "LBS_EXTENDEDSEL",
    "LBS_HASSTRINGS",
    "LBS_MULTICOLUMN",
    "LBS_MULTIPLESEL",
    "LBS_NODATA",
    "LBS_NOINTEGRALHEIGHT",
    "LBS_NOREDRAW",
    "LBS_NOSEL",
    "LBS_NOTIFY",
    "LBS_OWNERDRAWFIXED",
    "LBS_OWNERDRAWVARIABLE",
    "LBS_SORT",
    "LBS_STANDARD",
    "LBS_USETABSTOPS",
    "LBS_WANTKEYBOARDINPUT",
    nullptr
};

const char * Styles::scrollbar[] = {
    "SBS_BOTTOMALIGN",
    "SBS_HORZ",
    "SBS_LEFTALIGN",
    "SBS_RIGHTALIGN",
    "SBS_SIZEBOX",
    "SBS_SIZEBOXBOTTOMRIGHTALIGN",
    "SBS_SIZEBOXTOPLEFTALIGN",
    "SBS_SIZEGRIP",
    "SBS_TOPALIGN",
    "SBS_VERT",
    nullptr
};

const char * Styles::label[] = {
    "SS_BITMAP",
    "SS_BLACKFRAME",
    "SS_BLACKRECT",
    "SS_CENTER",
    "SS_CENTERIMAGE",
    "SS_EDITCONTROL",
    "SS_ENDELLIPSIS",
    "SS_ENHEMATFILE",
    "SS_ETCHEDFRAME",
    "SS_ETCHEDHORZ",
    "SS_ETCHEDVERT",
    "SS_GRAYFRAME",
    "SS_GRAYRECT",
    "SS_ICON",
    "SS_LEFT",
    "SS_LEFTNOWORDWRAP",
    "SS_NOPREFIX",
    "SS_NOTIFY",
    "SS_OWNDERDRAW",
    "SS_PATHELLIPSIS",
    "SS_REALSIZECONTROL",
    "SS_REALSIZEIMAGE",
    "SS_RIGHT",
    "SS_RIGHTJUST",
    "SS_SIMPLE",
    "SS_SUNKEN",
    "SS_TYPEMASK",
    "SS_WHITEFRAME",
    "SS_WHITERECT",
    "SS_WORDELLIPSIS",
    nullptr
};

const char * Styles::window[] = {
    "WS_BORDER",
    "WS_CAPTION",
    "WS_CHILD",
    "WD_CHILDWINDOW",
    "WS_CLIPCHILDREN",
    "WS_CLIPSIBLINGS",
    "WS_DIASBLED",
    "WS_DLGFRAME",
    "WD_GROUP",
    "WS_HSCROLL",
    "WS_ICONIC",
    "WS_MAXIMIZE",
    "WS_MAXIMIZEBOX",
    "WS_MINIMIZE",
    "WS_OERLLAPPED",
    "WS_OVERLAPPEDWINDOW",
    "WS_POPUP",
    "WS_POPUPWINDOW",
    "WS_SIZEBOX",
    "WS_SYSMENU",
    "WS_TABSTOP",
    "WS_THICKFRAME",
    "WS_TILED",
    "WS_TILEDWINDOW",
    "WS_VISIBLE",
    "WS_VSCROLL",
    nullptr
};

const char * Styles::windowex[] = {
    "WS_EX_ACCEPTFILES",
    "WS_EX_APPWINDOW",
    "WS_EX_CLIENTEDGE",
    "WS_EX_COMPOISTED",
    "WS_EX_CONTEXTHELP",
    "WS_EX_CONTROLPARENT",
    "WS_EX_DLGMODALFRAME",
    "WS_EX_LAYERED",
    "WS_EX_LAYOUTRTL",
    "WS_EX_LEFT",
    "WS_EX_LEFTSCROLLBAR",
    "WS_EX_LTRREADING",
    "WS_EX_MDICHILD",
    "WS_EX_NOACTIVATE",
    "WS_EX_NOINHERITLAYOUT",
    "WS_EX_NOPARENTNOTIFY",
    "WS_EX_NOREDIRECTIONBITMAP",
    "WS_EX_OVERLAPPEDWINDOW",
    "WS_EX_PALETTEWINDOW",
    "WS_EX_RIGHT",
    "WS_EX_RIGHTSCROLLBAR",
    "WS_EX_RTLREADING",
    "WS_EX_STATICEDGE",
    "WS_EX_TOOLWINDOW",
    "WS_EX_TOPMOST",
    "WS_EX_TRANSPARENT",
    "WS_EX_WINDOWEDGE",
    nullptr
};

const char* Control::controls[] = {
    "ICON",
    "LTEXT",
    "EDITTEXT",
    "RTEXT",
    "PUSHBUTTON",
    "PUSHBOX",
    "DEFPUSHBUTTON",
    "GROUPBOX",
    "CTEXT",
    "CHECKBOX",
    "RADIOBUTTON",
    "CONTROL",
    "COMBOBOX",
    "LISTBOX",
    "SCROLLBAR",
    nullptr
};

const char* Control::widget[] = {
    "QLabel",
    "QLineEdit",
    "QPushButton",
    "QGroupBox",
    "QCheckBox",
    "QComboBox",
    "QListWidget",
    "QTextEdit",
    "QWidget",
    nullptr
};
