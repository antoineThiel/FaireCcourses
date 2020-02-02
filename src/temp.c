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

  widget = widget; // if we don't, it's not compiling (variable not used...)
}
void fill_combobox_cat(builder_and_conn *data){

  GtkWidget* select_cat_btn;

  select_cat_btn = GTK_WIDGET(gtk_builder_get_object(data->builder , "combobox_cat") );

  select_cat_options(data->conn , GTK_COMBO_BOX_TEXT(select_cat_btn) );

}
//Fonction pour récupérer le texte (add_product);
void get_product(GtkWidget *widget, GtkWidget **array){
  
  GtkWidget *entry = array[0];
  GtkWidget *combo = array[1];
  const gchar *a, *b;
  a = gtk_entry_get_text(GTK_ENTRY (entry));
  b = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo));
  printf("%s, %s", a, b);
  (void)widget;
  //add_product(a,b);
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

  GtkWidget **gtkWidget_Array;
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *button;
  GtkWidget *combo;
  GtkWidget *entry;
  GtkWidget *label;

  gtkWidget_Array = malloc(2 * sizeof(GtkWidget));
  
  grid = GTK_WIDGET(gtk_builder_get_object(builders->builder, "grid"));
  label = GTK_WIDGET(gtk_builder_get_object(builders->builder, "label"));
  grid_content = gtk_grid_new();
  gtk_widget_destroy(GTK_WIDGET(label));
  gtk_grid_remove_column(GTK_GRID(grid), 2);
  gtk_grid_insert_column(GTK_GRID(grid), 2);
  gtk_grid_attach(GTK_GRID(grid), grid_content, 2,0,1,1);
  button = gtk_button_new_with_label("Ajouter");
  entry = gtk_entry_new();
  combo = gtk_combo_box_text_new();
  label = gtk_label_new("Nom du produit");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1);
  label = gtk_label_new("Categorie");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,3,1,1);
  
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(combo), NULL, "Fruit");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(combo), NULL, "Boisson");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(combo), NULL, "Bonbon");
  
  gtk_grid_attach(GTK_GRID(grid_content), button, 1,4,1,1);
  gtk_grid_attach(GTK_GRID(grid_content), entry, 1,2,1,1);
  gtk_grid_attach(GTK_GRID(grid_content), combo, 1,3,1,1);


  gtkWidget_Array[0] = entry;
  gtkWidget_Array[1] = combo;

  g_signal_connect (button, "clicked", G_CALLBACK (get_product) , gtkWidget_Array);
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


int main (int argc, char *argv[]){


  builder_and_conn builders;
  GtkWidget *window;
  GtkWidget *button;

  gtk_init (&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builders.builder = gtk_builder_new_from_file ("./glade/window_main.glade");

  //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (builders.builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  //Get the buttons and apply usefulnes
  button = GTK_WIDGET(gtk_builder_get_object(builders.builder, "btn_add_product"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_add_product), &builders);

  button = GTK_WIDGET(gtk_builder_get_object(builders.builder, "btn_account"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_log_in), &builders);

  button = GTK_WIDGET(gtk_builder_get_object(builders.builder, "btn_store"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_chose_store), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(builders.builder, "btn_order"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_show_order), NULL);


  button = GTK_WIDGET (gtk_builder_get_object(builders.builder, "quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), window);

  gtk_widget_show(window);
  gtk_main ();

  return 0;
}


int main (int argc, char *argv[]){


  builder_and_conn gtkWidget_Array;

  GtkWidget *window;
  GObject *button;

  
  PREPARE_CONNECTION(gtkWidget_Array.conn);

  gtk_init (&argc, &argv);
  /* Construct a GtkBuilder instance and load our UI description */
  gtkWidget_Array.builder = gtk_builder_new_from_file ("./glade/window_main.glade");

  window = GTK_WIDGET(gtk_builder_get_object (gtkWidget_Array.builder, "window"));
  //Event Destroying the window 
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);


  //Add the add-product fonction to the button 1
  button = gtk_builder_get_object (gtkWidget_Array.builder, "btn_add");

  fill_combobox_cat(&gtkWidget_Array);

  //Bouton clické
  g_signal_connect (button, "clicked", G_CALLBACK (get_input2), &gtkWidget_Array  );

  gtk_widget_show(window);
  gtk_main ();


  mysql_close(gtkWidget_Array.conn);
  return 0;
}