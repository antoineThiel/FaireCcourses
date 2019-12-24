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

void fill_combobox_cat(MYSQL *conn , GtkComboBoxText *combo){

  char *query = "SELECT * FROM category";
    MYSQL_RES *result;
    MYSQL_ROW data;

    if( !mysql_query(conn , query) ){

        result = mysql_store_result(conn);

        while( (data = mysql_fetch_row(result) ) != NULL){
            gtk_combo_box_text_append(combo , data[0] , data[1] );
        }

    }else{
        fprintf(stderr, "An error occured : \n%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_free_result(result);

}
//Fonction pour récupérer le texte (add_product);
static void get_product(GtkWidget *widget, conn_n_2_gtk_widget *array){
  
  const gchar *a, *b;
 // GtkWidget *entry = array->entry;
  //GtkWidget *combo = array->combo;

  a = gtk_entry_get_text(GTK_ENTRY (array->entry));
  b = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (array->combo));
  
  (void)widget; //Equivaut a windget = widget
  
  add_product(array->conn,a,b);
}
void get_log(GtkWidget * widget, GtkWidget **array){
  GtkWidget *entry_id = array[0];
  GtkWidget *entry_pass = array[1];
  GtkWidget *label = array[2];
  const gchar *a, *b;
  a = gtk_entry_get_text(GTK_ENTRY (entry_id));
  b = gtk_entry_get_text(GTK_ENTRY (entry_pass));
  if (log_in(a, b) == 1){
    //free(array);
    gtk_label_set_text(GTK_LABEL(label), "Connecté");
  }
  else 
  gtk_label_set_text(GTK_LABEL(label), "Echec");
  (void) widget;
}
void win_add_product(GtkWidget *widget, builder_and_conn *builders){

  //GtkWidget **gtkWidget_Array;
  //GtkWidget *combo;
  //GtkWidget *entry;

  conn_n_2_gtk_widget array;
  array.conn = builders->conn;

  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *button;
  GtkWidget *label;

  //gtkWidget_Array = malloc(2 * sizeof(GtkWidget));
  
  grid = GTK_WIDGET(gtk_builder_get_object(builders->builder, "grid"));
  label = GTK_WIDGET(gtk_builder_get_object(builders->builder, "label"));
  grid_content = gtk_grid_new();

  //gtk_widget_destroy(GTK_WIDGET(label));

// TODO
  gtk_grid_remove_column(GTK_GRID(grid), 2);
  gtk_grid_insert_column(GTK_GRID(grid), 2);
  gtk_grid_attach(GTK_GRID(grid), grid_content, 2,0,1,1);
  button = gtk_button_new_with_label("Ajouter");
  array.entry = gtk_entry_new();
  array.combo = gtk_combo_box_text_new();
  label = gtk_label_new("Nom du produit");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1);
  label = gtk_label_new("Categorie");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,3,1,1);
// ~~~~~~~~~~~~~  replace this code with an xml file insertion  

  fill_combobox_cat(builders->conn , GTK_COMBO_BOX_TEXT(array.combo));
  
  gtk_grid_attach(GTK_GRID(grid_content), button, 1,4,1,1);
  gtk_grid_attach(GTK_GRID(grid_content), array.entry, 1,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_content), array.combo, 1,3,1,1);

/*
  gtkWidget_Array[0] = entry;
  gtkWidget_Array[1] = combo; */

  g_signal_connect (button, "clicked", G_CALLBACK (get_product) , &array);
  (void)widget;
  gtk_widget_show_all(grid_content);
}
void win_log_in(GtkWidget *widget, builder_and_conn *builders){

  GtkWidget **array;
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget *label;

  array = malloc(3 * sizeof(GtkWidget));
  grid = GTK_WIDGET(gtk_builder_get_object(builders->builder, "grid"));
  label = GTK_WIDGET(gtk_builder_get_object(builders->builder, "label"));

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
void win_chose_store(){
  GtkBuilder *builder;
  GtkWidget *window;
  //GtkWidget *combo;

  builder = gtk_builder_new_from_file("glade/window_chose_store.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  //combo = GTK_WIDGET(gtk_builder_get_object(builder, "combobox_store"));
  //fill_combo_box_store();

  gtk_widget_show(window);
}
void win_show_order(){
  GtkBuilder *builder;
  GtkWidget *window;

  builder = gtk_builder_new_from_file("glade/window_show_order.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

  gtk_widget_show(window);
}
void event_handler(builder_and_conn *fundalentals){
  
  GtkWidget *window;
  GtkWidget *button;

  //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (fundalentals->builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  //Get the buttons and apply usefulnes
  button = GTK_WIDGET(gtk_builder_get_object(fundalentals->builder, "btn_add_product"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_add_product), fundalentals);

  button = GTK_WIDGET(gtk_builder_get_object(fundalentals->builder, "btn_account"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_log_in), fundalentals);

  button = GTK_WIDGET(gtk_builder_get_object(fundalentals->builder, "btn_store"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_chose_store), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(fundalentals->builder, "btn_order"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_show_order), NULL);


  button = GTK_WIDGET (gtk_builder_get_object(fundalentals->builder, "quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), window);

  gtk_widget_show(window);
}


int main (int argc, char *argv[]){


  builder_and_conn builders;

  gtk_init (&argc, &argv);


  PREPARE_CONNECTION(builders.conn);

  /* Construct a GtkBuilder instance and load our UI description */
  builders.builder = gtk_builder_new_from_file ("./glade/window_main.glade");

  event_handler(&builders);

  gtk_main ();

  mysql_close(builders.conn);


  return 0;
}

