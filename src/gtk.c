#include <gtk/gtk.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/sql_fonctions.h"

//Fonction pour récupérer le texte
void get_input2(GtkWidget *widget, GtkWidget **array){
  
  GtkWidget *entry = array[0];
  GtkWidget *combo = array[1];
  MYSQL *conn = array[2];

  const gchar *a, *b;
  a = gtk_entry_get_text(GTK_ENTRY (entry));
  b = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo));
  add_product(conn , a,b);
}

int main (int argc, char *argv[]){

  GObject **gtkWidget_Array;
  GtkBuilder *builder;
  GtkWidget *window;
  GObject *button;
  GObject *entry1;
  GObject *combo;
  GtkComboBoxText *select_cat_btn;

  MYSQL* conn; 

  prepare_conn(conn);

  gtk_init (&argc, &argv);
  gtkWidget_Array = malloc(3 * sizeof(GtkWidget)); // 3 = nb of parameters for our function

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new_from_file ("./glade/window_main.glade");

  //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  combo = gtk_builder_get_object (builder, "combobox_cat");

  //Retrieving the entry from the builder
  entry1 = gtk_builder_get_object (builder, "entry1");

  gtkWidget_Array[0] = entry1;
  gtkWidget_Array[1] = combo;
  gtkWidget_Array[2] = conn; 

  //Add the add-product fonction to the button 1
  button = gtk_builder_get_object (builder, "btn_add");

  // select_cat_btn = gtk_builder_get_object(builder , "combobox_cat");
  // fill_cat_options(builder , &select_cat_btn);

  //Bouton clické
  g_signal_connect (button, "clicked", G_CALLBACK (get_input2) , gtkWidget_Array);

  gtk_widget_show(window);
  gtk_main ();

  return 0;
}

// void fill_cat_option(GtkComboBoxText *select){

      

// }