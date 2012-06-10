// code by Caleb Booker, Aug 10 2009
// courtesy of Clever Zebra
//
// NO rights reserved - use this code any way you want.

default
{
    state_entry()
    {

    }
    
    touch_start(integer total_number)
    {
        string strDescText = llGetObjectDesc();
        string strNameText = llGetObjectName();
        llLoadURL(llDetectedKey(0), strNameText, strDescText);
    }
}