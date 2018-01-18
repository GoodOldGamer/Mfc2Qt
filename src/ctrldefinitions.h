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

#ifndef __CTRLDEFINITIONS_H__
#define __CTRLDEFINITIONS_H__

#pragma once

#include <QMap>
#include <QPoint>
#include <QSize>
#include <QFont>

namespace Styles
{
    enum Qt
    {
        NOQTPROPERTY = -1,
        ALLWAYSDONE = -2
    };

    enum EDITCONTROL
    {
        ED_MULTILINE,
        ED_UPPERCASE,
        ED_LOWERCASE,
        ED_PASSWORD,
        ED_AUTOVSCROLL,
        ED_AUTOHSCROLL,
        ED_NOHIDESEL,
        ED_OEMCONVERT,
        ED_READONLY,
        ED_WANTRETURN,
        ED_LEFT,
        ED_CENTER,
        ED_NUMBER,
        ED_RIGHT,
        ED_COUNT
    };

    extern const char * edit[];


    enum QEDITCONTROL
    {
        QED_MULTILINE       = ED_MULTILINE,     // need to decide between QLineEdit or QTextEdit
        QED_UPPERCASE       = NOQTPROPERTY,     // use ui->textbox1.setText(arg1.toUpper());
        QED_LOWERCASE       = NOQTPROPERTY,     // like UPPERCASE
        QED_PASSWORD        = NOQTPROPERTY,     // use QLineEdit::setEchoMode
        QED_AUTOVSCROLL     = ALLWAYSDONE,
        QED_AUTOHSCROLL     = ALLWAYSDONE,
        QED_NOHIDESEL       = NOQTPROPERTY,
        QED_OEMCONVERT      = NOQTPROPERTY,
        QED_READONLY        = ED_READONLY,
        QED_WANTRETURN      = NOQTPROPERTY,
        QED_LEFT            = ED_LEFT,
        QED_CENTER          = ED_CENTER,
        QED_RIGHT           = ED_RIGHT,
        QED_NUMBER          = NOQTPROPERTY
    };

    enum BUTTONCONTROL
    {
        BC_STATE3,
        BC_AUTO3STATE,
        BC_AUTOCHECKBOX,
        BC_AUTORADIOBUTTON,
        BC_BITMAP,
        BC_BOTTOM,
        BC_CENTER,
        BC_CHECKBOX,
        BC_COMMANDLINK,
        BC_DEFCOMMANDLINK,
        BC_DEFPUSHBUTTON,
        BC_DEFSPLITBUTTON,
        BC_GROUPBOX,
        BC_ICON,
        BC_FLAT,
        BC_LEFT,
        BC_LEFTTEXT,
        BC_MULTILINE,
        BC_NOTIFY,
        BC_OWNERDRAW,
        BC_PUSHBUTTON,
        BC_PUSHLIKE,
        BC_RADIOBUTTON,
        BC_RIGHT,
        BC_RIGHTBUTTON,
        BC_SPLITBUTTON,
        BC_TEXT,
        BC_TOP,
        BC_TYPEMASK,
        BC_USERBUTTON, //obsolete
        BC_VCENTER,
        BC_COUNT
    };

    enum QBUTTONCONTROL
    {
        QBC_STATE3              = BC_STATE3,
        QBC_AUTO3STATE          = BC_AUTO3STATE,
        QBC_AUTOCHECKBOX        = BC_AUTOCHECKBOX,
        QBC_AUTORADIOBUTTON     = BC_AUTORADIOBUTTON,
        QBC_BITMAP              = NOQTPROPERTY,
        QBC_BOTTOM              = BC_BOTTOM,
        QBC_CENTER              = BC_CENTER,        // horizontally
        QBC_CHECKBOX            = BC_CHECKBOX,
        QBC_COMMANDLINK         = BC_COMMANDLINK,
        QBC_DEFCOMMANDLINK      = BC_DEFCOMMANDLINK,
        QBC_DEFPUSHBUTTON       = BC_DEFPUSHBUTTON,
        QBC_DEFSPLITBUTTON      = BC_DEFSPLITBUTTON,
        QBC_GROUPBOX            = BC_GROUPBOX,
        QBC_ICON                = NOQTPROPERTY,     // do not know the Icon yet
        QBC_FLAT                = BC_FLAT,
        QBC_LEFT                = BC_LEFT,
        QBC_LEFTTEXT            = BC_LEFTTEXT,
        QBC_MULTILINE           = NOQTPROPERTY,
        QBC_NOTIFY              = ALLWAYSDONE,
        QBC_OWNERDRAW           = NOQTPROPERTY,
        QBC_PUSHBUTTON          = BC_PUSHBUTTON,
        QBC_PUSHLIKE            = BC_PUSHLIKE,
        QBC_RADIOBUTTON         = BC_RADIOBUTTON,
        QBC_RIGHT               = BC_RIGHT,
        QBC_RIGHTBUTTON         = BC_RIGHTBUTTON,
        QBC_SPLITBUTTON         = NOQTPROPERTY,     // no idea yet
        QBC_TEXT                = ALLWAYSDONE,
        QBC_TOP                 = BC_TOP,
        QBC_TYPEMASK            = NOQTPROPERTY,
        QBC_USERBUTTON          = NOQTPROPERTY,
        QBC_VCENTER             = BC_VCENTER
    };


    extern const char * button[];

    enum COMBOBOX
    {
        CB_AUTOHSCROLL,
        CB_DISABLENOSCROLL,
        CB_DROPDOWN,
        CB_HASSTRINGS,
        CB_LOWERCASE,
        CB_NOINTEGRALHEIGHT,
        CB_OEMCONVERT,
        CB_OWNERDRAWFIXED,
        CB_OWNERDRAWVARIABLE,
        CB_SIMPLE,
        CB_SORT,
        CB_UPPERCASE,
        CB_COUNT
    };

    enum QCOMBOBOX
    {
        QCB_AUTOHSCROLL             = ALLWAYSDONE,
        QCB_DISABLENOSCROLL         = CB_DISABLENOSCROLL,
        QCB_DROPDOWN                = ALLWAYSDONE,
        QCB_HASSTRINGS              = NOQTPROPERTY,
        QCB_LOWERCASE               = NOQTPROPERTY, //see EditControl for more information
        QCB_NOINTEGRALHEIGHT        = ALLWAYSDONE,
        QCB_OEMCONVERT              = NOQTPROPERTY,
        QCB_OWNERDRAWFIXED          = NOQTPROPERTY,
        QCB_OWNERDRAWVARIABLE       = NOQTPROPERTY,
        QCB_SIMPLE                  = NOQTPROPERTY,
        QCB_SORT                    = CB_SORT,
        QCB_UPPERCASE               = NOQTPROPERTY // see EDITCONTROL for more information
    };

    extern const char * combobox[];

    enum LISTBOX
    {
        LB_COMBOBOX,
        LB_DISABLENOSCROLL,
        LB_EXTENDEDSEL,
        LB_HASSTRINGS,
        LB_MULTICOLUMN,
        LB_MULTIPLESEL,
        LB_NODATA,
        LB_NOINTEGRALHEIGHT,
        LB_NOREDRAW,
        LB_NOSEL,
        LB_NOTIFY,
        LB_OWNERDRAWFIXED,
        LB_OWNERDRAWVARIABLE,
        LB_SORT,
        LB_STANDARD,
        LB_USETABSTOPS,
        LB_WANTKEYBOARDINPUT,
        LB_COUNT
    };

    enum QLISTBOX
    {
        QLB_COMBOBOX                = NOQTPROPERTY,
        QLB_DISABLENOSCROLL         = LB_DISABLENOSCROLL,
        QLB_EXTENDEDSEL             = LB_EXTENDEDSEL,
        QLB_HASSTRINGS              = NOQTPROPERTY,
        QLB_MULTICOLUMN             = LB_MULTICOLUMN,
        QLB_MULTIPLESEL             = LB_MULTIPLESEL,
        QLB_NODATA                  = NOQTPROPERTY,
        QLB_NOINTEGRALHEIGHT        = NOQTPROPERTY,
        QLB_NOREDRAW                = NOQTPROPERTY,
        QLB_NOSEL                   = LB_NOSEL,
        QLB_NOTIFY                  = ALLWAYSDONE,
        QLB_OWNERDRAWFIXED          = NOQTPROPERTY,
        QLB_OWNERDRAWVARIABLE       = NOQTPROPERTY,
        QLB_SORT                    = LB_SORT,
        QLB_STANDARD                = ALLWAYSDONE,
        QLB_USETABSTOPS             = LB_USETABSTOPS,
        QLB_WANTKEYBOARDINPUT       = NOQTPROPERTY
    };

    extern const char * listbox[];

    enum SCROLLBAR
    {
        SB_BOTTOMALIGN,
        SB_HORIZ,
        SB_LEFTALIGN,
        SB_RIGHTALIGN,
        SB_SIZEBOX,
        SB_SIZEBOXBOTTOMRIGHTALIGN,
        SB_SIZEBOXTOPLEFTALIGN,
        SB_SIZEGRIP,
        SB_TOPALIGN,
        SB_VERTI,
        SB_COUNT
    };

    enum QSCROLLBAR
    {
        QSB_BOTTOMALIGN                 = NOQTPROPERTY,
        QSB_HORZ                        = SB_HORIZ,
        QSB_LEFTALIGN                   = NOQTPROPERTY,
        QSB_RIGHTALIGN                  = NOQTPROPERTY,
        QSB_SIZEBOX                     = NOQTPROPERTY,
        QSB_SIZEBOXBOTTOMRIGHTALIGN     = NOQTPROPERTY,
        QSB_SIZEBOXTOPLEFTALIGN         = NOQTPROPERTY,
        QSB_SIZEGRIP                    = NOQTPROPERTY,
        QSB_TOPALIGN                    = NOQTPROPERTY,
        QSB_VERT                        = SB_VERTI
    };

    extern const char * scrollbar[];

    enum STATIC
    {
        ST_BITMAP,
        ST_BLACKFRAME,
        ST_BLACKRECT,
        ST_CENTER,
        ST_CENTERIMAGE,
        ST_EDITCONTROL,
        ST_ENDELLIPSIS,
        ST_ENHMETAFILE,
        ST_ETCHEDFRAME,
        ST_ETCHEDHORZ,
        ST_ETCHEDVERT,
        ST_GRAYFRAME,
        ST_GRAYRECT,
        ST_ICON,
        ST_LEFT,
        ST_LEFTNOWORDWRAP,
        ST_NOPREFIX,
        ST_NOTIFY,
        ST_OWNERDRAW,
        ST_PATHELLIPSIS,
        ST_REALSIZECONTROL,
        ST_RIGHT,
        ST_RIGHTJUST,
        ST_SIMPLE,
        ST_SUNKEN,
        ST_TYPEMASK,
        ST_WHITEFRAME,
        ST_WHITERECT,
        ST_WORDELLIPSIS,
        ST_COUNT
    };

    enum QSTATIC
    {
        QST_BITMAP              = NOQTPROPERTY,
        QST_BLACKFRAME          = ST_BLACKFRAME,
        QST_BLACKRECT           = ST_BLACKRECT,
        QST_CENTER              = ST_CENTER,
        QST_CENTERIMAGE         = NOQTPROPERTY,
        QST_EDITCONTROL         = NOQTPROPERTY,
        QST_ENDELLIPSIS         = NOQTPROPERTY,
        QST_ENHMETAFILE         = NOQTPROPERTY, //???
        QST_ETCHEDFRAME         = NOQTPROPERTY,
        QST_ETCHEDHORZ          = NOQTPROPERTY,
        QST_ETCHEDVERT          = NOQTPROPERTY,
        QST_GRAYFRAME           = ST_GRAYFRAME,
        QST_GRAYRECT            = ST_GRAYRECT,
        QST_ICON                = NOQTPROPERTY, // do not know the icon yet
        QST_LEFT                = ST_LEFT,
        QST_LEFTNOWORDWRAP      = ST_LEFTNOWORDWRAP,
        QST_NOPREFIX            = ALLWAYSDONE,  //EXCEPT there is a connection between a label and an other widget
        QST_NOTIFY              = ALLWAYSDONE,
        QST_OWNERDRAW           = NOQTPROPERTY,
        QST_PATHELLIPSIS        = NOQTPROPERTY,
        QST_REALSIZECONTROL     = ST_REALSIZECONTROL,
        QST_RIGHT               = ST_RIGHT,
        QST_RIGHTJUST           = NOQTPROPERTY,
        QST_SIMPLE              = ST_SIMPLE,
        QST_TYPEMASK            = NOQTPROPERTY,
        QST_WHITEFRAME          = ST_WHITEFRAME,
        QST_WHITERECT           = ST_WHITERECT,
        QST_WORDELLIPSIS        = NOQTPROPERTY
    };

    extern const char * label[];

    enum WINDOW
    {
        W_BORDER,
        W_CAPTION,
        W_CHILD,
        W_CHILDWINDOW,
        W_CLIPCHILDREN,
        W_CLIPSIBLINGS,
        W_DISABLED,
        W_DLGFRAME,
        W_GROUP,
        W_HSCROLL,
        W_ICONIC,
        W_MAXIMIZE,
        W_MAXIMIZEBOX,
        W_MINIMIZE,
        W_MINIMIZEBOX,
        W_OVERLAPPED,
        W_OVERLAPPEDWINDOW,
        W_POPUP,
        W_POPUPWINDOW,
        W_SIZEBOX,
        W_SYSMENU,
        W_TABSTOP,
        W_THICKFRAME,
        W_TILED,
        W_TILEDWINDOW,
        W_VISIBLE,
        W_VSCROLL,
        W_COUNT
    };

    extern const char * window[];

    enum WINDOWEX
    {
        WEX_ACCEPTFILES,
        WEX_APPWINDOW,
        WEX_CLIENTEDGE,
        WEX_COMPOSITED,
        WEX_CONTEXTHELP,
        WEX_CONTROLPARENT,
        WEX_DLGMODALFRAME,
        WEX_LAYERED,
        WEX_LAYOUTRTL,
        WEX_LEFT,
        WEX_LEFTSCROLLBAR,
        WEX_LTRREADING,
        WEX_MDICHILD,
        WEX_NOACTIVATE,
        WEX_NOINHERITLAYOUT,
        WEX_NOPARENTNOTIFY,
        WEX_NOREDIRECTIONBITMAP,
        WEX_OVERLAPPEDWINDOW,
        WEX_PALETTEWINDOW,
        WEX_RIGHT,
        WEX_RIGHTSCROLLBAR,
        WEX_RTLREADING,
        WEX_STATICEDGE,
        WEX_TOOLWINDOW,
        WEX_TOPMOST,
        WEX_TRANSPARENT,
        WEX_WINDOWEDGE,
        WEX_COUNT
    };

    extern const char * windowex[];
}

namespace Control
{
    enum CONTROL
    {
        UNKNOWN = -1,
        ICON = 0,
        LTEXT,
        EDITTEXT,
        RTEXT,
        PUSHBUTTON,
        PUSHBOX,
        DEFPUSHBUTTON,
        GROUPBOX,
        CTEXT,
        CHECKBOX,
        RADIOBUTTON,
        CCONTROL,
        COMBOBOX,
        LISTBOX,
        SCROLLBAR,

        C_SENTINAL,
        C_FIRST = ICON,
        C_LAST  = C_SENTINAL - 1,
        C_COUNT = C_SENTINAL
    };

    inline CONTROL operator++( CONTROL & orig )
    {
        orig = static_cast<CONTROL>( orig + 1 );

        return orig;
    }

    inline CONTROL operator++(CONTROL& orig, int ) {
        CONTROL rVal = orig;

        ++orig;
        return rVal;
    }

    extern const char* controls[];

    inline int controlLen( CONTROL ctrl )
    {
        return strlen( controls[ctrl] );
    }

    enum WIDGET
    {
        QOBJECT = 0,
        QWIDGET,
        QLABEL,
        QLINEEDIT,
        QIMAGE,
        QPUSHBUTTON,
        QGROUPBOX,
        QCHECKBOX,
        QRADIOBUTTON,
        QCOMBOBOX,
        QLISTVIEW,
        QTABLEVIEW,
        QTEXTEDIT,
        QDATETIMEEDIT,
        QMENUBAR,
        QSCROLLBAR,
        ERRORWIDGET,

        W_SENTINAL,
        W_FIRST = QWIDGET,
        W_LAST = W_SENTINAL - 1,
        W_COUNT = W_SENTINAL
    };

    extern const char* widget[];

    inline int widgetLen( WIDGET w )
    {
        return strlen( widget[w] );
    }
}

#endif // __CTRLDEFINITIONS_H__
