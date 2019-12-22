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


//Fonction pour récupérer le texte
void get_input2(GtkWidget *widget, builder_and_conn *data){

  const gchar *product, *category;

  GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object (data->builder, "entry1") );
  GtkWidget *combo = GTK_WIDGET(gtk_builder_get_object (data->builder, "combobox_cat") );


  product = gtk_entry_get_text(GTK_ENTRY (entry));
  category = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo));
  add_product(data->conn , product , category);

  widget = widget; // if we don't, it's not compiling
}

int main (int argc, char *argv[]){


  builder_and_conn gtkWidget_Array;

  GtkWidget *window;
  GObject *button;
  // GtkWidget *select_cat_btn;

  //MYSQL_ROW* result_array;
  
  PREPARE_CONNECTION(gtkWidget_Array.conn);

  gtk_init (&argc, &argv);
  /* Construct a GtkBuilder instance and load our UI description */
  gtkWidget_Array.builder = gtk_builder_new_from_file ("./glade/window_main.glade");

  window = GTK_WIDGET(gtk_builder_get_object (gtkWidget_Array.builder, "window"));
  //Event Destroying the window 
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);


  //Add the add-product fonction to the button 1
  button = gtk_builder_get_object (gtkWidget_Array.builder, "btn_add");

  //select_cat_btn = GTK_WIDGET(gtk_builder_get_object(builder , "combobox_cat") );
  //result_array = select_cat_options(conn);
  //fill_combobox_cat(result_array);

  //Bouton clické
  g_signal_connect (button, "clicked", G_CALLBACK (get_input2), &gtkWidget_Array  );

  gtk_widget_show(window);
  gtk_main ();


  mysql_close(gtkWidget_Array.conn);
  return 0;
}

// void fill_combobox_cat(MYSQL_ROW *data){
//   int test =1;

// }