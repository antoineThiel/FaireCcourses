//~~~~~~~~~~~~~INCLUDES~~~~~~~~~
#include <gtk/gtk.h> // add gtk.h to pc libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/views.h"
#include "../headers/gtk_fonctions.h"
#include <mysql.h>

//~~~~~~~~~~~~DEFINES~~~~~~~~~~~~
#define SERVER "localhost"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "project"
#define PREPARE_CONNECTION(connector) connector = mysql_init(NULL);\
                                      if (!mysql_real_connect(connector, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {\
                                          fprintf(stderr, "%s\n", mysql_error(connector));\
                                          exit(1);\
                                          }



//~~~~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MYSQL* CONNECTOR_DB;
GtkBuilder* MAIN_BUILDER;

SESSION USER_DATA;

void event_handler(){
  
  GtkWidget *window;
  GtkWidget *button;

  //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (MAIN_BUILDER, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  //Get the buttons and apply usefulnes
  button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_add_product"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_add_product), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_account"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_log_in),NULL );

  button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_store"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_chose_store), NULL);


  button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_order"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_show_order), MAIN_BUILDER);


  button = GTK_WIDGET (gtk_builder_get_object(MAIN_BUILDER, "quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), window);




  gtk_widget_show(window);
}

int main (int argc, char *argv[]){


  PREPARE_CONNECTION(CONNECTOR_DB);
  session_init(&USER_DATA);
  gtk_init (&argc, &argv);
  /* Construct a GtkBuilder instance and load our UI description */
  MAIN_BUILDER = gtk_builder_new_from_file ("./glade/window_main.glade");
  
  event_handler();
  
  gtk_main ();
  
  return 0;
}


void session_init(SESSION* data){
  data->IS_CONNECTED = 0;
}