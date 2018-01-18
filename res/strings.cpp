#include "<!HEADERFILE!>"

QString MfCStrings::getString( enum ID id )
{
    switch( id )
    {
<!CASESTATEMENTS!>
    
    default:
        return 0;
    }
}
