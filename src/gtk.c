#include <gtk/gtk.h> // add gtk.h to pc libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/views.h"

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "project"
#define PREPARE_CONNECTION(connector) connector = mysql_init(NULL);\
                                      if (!mysql_real_connect(connector, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {\
                                          fprintf(stderr, "%s\n", mysql_error(connector));\
                                          exit(1);\
                                      }

#include <mysql.h>

//Fonction pour récupérer le texte (add_product);
void event_handler(GtkBuilder *builder){
  
  GtkWidget *window;
  GtkWidget *button;

  //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  //Get the buttons and apply usefulnes
  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_product"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_add_product), builder);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_account"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_log_in),builder );

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_store"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_chose_store), builder);


/*
  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_order"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_show_order), builder);
*/

  button = GTK_WIDGET (gtk_builder_get_object(builder, "quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), window);




  gtk_widget_show(window);
}
MYSQL* CONNECTOR_DB;


int main (int argc, char *argv[]){

  GtkBuilder *builder;

  PREPARE_CONNECTION(CONNECTOR_DB);
  gtk_init (&argc, &argv);
  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new_from_file ("./glade/window_main.glade");
  
  event_handler(builder);
  
  gtk_main ();
  
  return 0;
}

