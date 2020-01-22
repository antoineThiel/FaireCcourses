//~~~~~~INCLUDES~~~~~~~~~~~
#include <gtk/gtk.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/sql_fonctions.h"
#include "../../headers/gtk_fonctions.h"
#include "../../headers/views.h"

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