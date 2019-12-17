#include <gtk/gtk.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/sql_fonctions.h"

//Fonction pour récupérer le texte
void get_input2(GtkWidget *widget, GtkWidget **array){
  
  GtkWidget *entry = array[0];
  GtkWidget *entry2 = array[1];
  const gchar *a, *b;
  a = gtk_entry_get_text(GTK_ENTRY (entry));
  b = gtk_entry_get_text(GTK_ENTRY (entry2));
  add_product(a, b);
}

int main (int argc, char *argv[]){

  GObject **gtkWidget_Array;
  GtkBuilder *builder;
  GObject *window;
  GObject *button;
  GObject *entry1;
  GObject *entry2;
  GObject *combo;
  GError *error = NULL;
  gtk_init (&argc, &argv);
  gtkWidget_Array = malloc(2 * sizeof(GtkWidget));

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "builder.ui", &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    } 

  //Destroying the window 
  window = gtk_builder_get_object (builder, "window");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  
  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  combo = gtk_builder_get_object (builder, "comboboxtex_options");

  //Retrieving the entry from the builder
  entry1 = gtk_builder_get_object (builder, "entry1");
  entry2 = gtk_builder_get_object (builder, "entry2");

  gtkWidget_Array[0] = entry1;
  gtkWidget_Array[1] = entry2;


  //Add the add-product fonction to the button 1
  button = gtk_builder_get_object (builder, "button1");

  //Bouton clické
  g_signal_connect (button, "clicked", G_CALLBACK (get_input2) , gtkWidget_Array);

  //g_signal_connect (button, "clicked", G_CALLBACK (get_input2), entry2);

  
  gtk_main ();

  return 0;
}