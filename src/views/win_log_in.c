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

void get_log(GtkWidget * widget, GtkWidget **array){
  GtkWidget *entry_id = array[0];
  GtkWidget *entry_pass = array[1];

  GObject *btn_connexion = gtk_builder_get_object(MAIN_BUILDER , "btn_account");
  
  const gchar *a, *b;
  a = gtk_entry_get_text(GTK_ENTRY (entry_id));
  b = gtk_entry_get_text(GTK_ENTRY (entry_pass));
  if (log_in(a, b) == 1){
    
    gtk_button_set_label(GTK_BUTTON(btn_connexion) , "yepee");
  }
  else 
  gtk_button_set_label(GTK_BUTTON(btn_connexion), "Nope.");
  (void) widget;
}
void win_log_in(GtkWidget *widget){

  GtkWidget **array;
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget *label;

  array = malloc(3 * sizeof(GtkWidget));
  grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "grid"));
  label = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "label"));

  gtk_widget_destroy(GTK_WIDGET(label));
  gtk_grid_remove_column(GTK_GRID(grid), 2);
  gtk_grid_insert_column(GTK_GRID(grid), 2);
  
  grid_content = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(grid), grid_content, 2,0,1,1);

  entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid_content), entry, 1,2,1,1);
  array[0] = entry;
  entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid_content), entry, 1,3,1,1);
  array[1] = entry;
  label = gtk_label_new(NULL);
  gtk_grid_attach(GTK_GRID(grid_content), label, 2,3,1,1);
  array[2] = label;
  button = gtk_button_new_with_label("Connexion");
  gtk_grid_attach(GTK_GRID(grid_content), button, 1,4,1,1);
  label = gtk_label_new("Username");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1);
  label = gtk_label_new("Password");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,3,1,1);

  g_signal_connect(button, "clicked", G_CALLBACK(get_log), array);
  
  (void)widget;
  gtk_widget_show_all(grid_content);
}

void modify_log_text(){

}