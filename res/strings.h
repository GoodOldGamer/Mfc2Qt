#ifndef <!INCLUDEGUARD!>
#define <!INCLUDEGUARD!>

#pragma once

#include <QString>

namespace MfCStrings
{
    enum ID
    {
        <!ENUMID!>
    };

    QString getString( enum ID id );
}

#endif // <INCLUDEGUARD>
