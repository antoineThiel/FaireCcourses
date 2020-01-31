//~~~~~~INCLUDES~~~~~~~~~~~
    #include "../../headers/all.h"

//~~~~~~GLOBALS~~~~~~~~~~~~

extern GtkBuilder *MAIN_BUILDER;
extern SESSION USER_DATA;


void win_show_order(GtkWidget *widget){

    (void)widget;
    if(USER_DATA.IS_CONNECTED){
        //DO SOMETHING
    }
    else{
        g_print("You need to log first \n");
    }

}