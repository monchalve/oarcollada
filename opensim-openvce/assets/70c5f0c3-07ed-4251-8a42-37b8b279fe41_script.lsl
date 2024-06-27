// window script to set transparency between 0 and 1 in 5 steps
// use ll
default {

    touch_start(integer total_number) {
        llOwnerSay("Use the controller to switch transparency.");
    }
    
    link_message(integer sender_num, integer num, string str, key id) {
        if(str == "transp") {
            llSetAlpha((0.25 * (float)num), ALL_SIDES); // set entire prim 100% visible.
        }
    }
    
}
 