#define SERVER "localhost"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "project"

#define PREPARE_CONNECTION(connector) connector = mysql_init(NULL);\
                                      if (!mysql_real_connect(connector, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {\
                                          fprintf(stderr, "%s\n", mysql_error(connector));\
                                          exit(1);\
                                      }
                                 

#include <gtk/gtk.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/sql_fonctions.h"
#include "../headers/gtk_fonctions.h"


//get product info & add it to db
void get_product(GtkWidget *widget, builder_and_conn *data){
  
  const gchar *product, *category;

  GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object (data->builder, "entry1")) ;
  GtkWidget *combo = GTK_WIDGET(gtk_builder_get_object (data->builder, "combobox_cat" ));


  product = gtk_entry_get_text(GTK_ENTRY (entry));
  category = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo));
  add_product(data->conn , product , category);

  widget = widget; // if we don't, it's not compiling
}

void win_add_product(builder_and_conn *data){

  GtkBuilder *builder ;En
  GtkWidget *window;
  GtkWidget *button;
  
  
  
  builder = gtk_builder_new_from_file("./glade/window_add.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  button = GTK_WIDGET(gtk_builder_get_object (builder, "btn_add"));
  
  g_signal_connect (button, "clicked", G_CALLBACK (get_product) , );
  
  
  button = GTK_WIDGET (gtk_builder_get_object(builder, "btn_quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_widget_show(window);
}

int main (int argc, char *argv[]){

  builder_and_conn gtkWidget_Array;
  GtkWidget *window;
  GtkWidget *button;
  GtkBuilder *builder;
  
  PREPARE_CONNECTION(gtkWidget_Array.conn);

  gtk_init (&argc, &argv);
  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new_from_file ("./glade/window_main.glade");

  window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = GTK_WIDGET(gtk_builder_get_object (builder, "btn_add_product"));
  g_signal_connect (button, "clicked", G_CALLBACK (win_add_product), &gtkWidget_Array);

/*
  button = gtk_builder_get_object (gtkWidget_Array.builder, "btn_account");
  g_signal_connect (button, "clicked", G_CALLBACK (win_log_in), &gtkWidget_Array  );
  
  button = gtk_builder_get_object (gtkWidget_Array.builder, "btn_store");
  g_signal_connect (button, "clicked", G_CALLBACK (win_chose_store), &gtkWidget_Array  );
  
  button = gtk_builder_get_object (gtkWidget_Array.builder, "btn_order");
  g_signal_connect (button, "clicked", G_CALLBACK (win_show_order), &gtkWidget_Array  );

*/

  gtk_widget_show(window);
  gtk_main ();

  mysql_close(gtkWidget_Array.conn);
  return 0;
}