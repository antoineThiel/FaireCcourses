#include <gtk/gtk.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/sql_fonctions.h"

//Fonction pour récupérer le texte (add_product);
void get_product(GtkWidget *widget, GtkWidget **array){
  
  GtkWidget *entry = array[0];
  GtkWidget *combo = array[1];
  const gchar *a, *b;
  a = gtk_entry_get_text(GTK_ENTRY (entry));
  b = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo));
  add_product(a,b);
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
}

char db_fill_store(){
  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;
  int num_fields;

    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "project";
    char *start;
    char quote[2]="\"";

    start = malloc(sizeof(char)*200);
    strcpy(start, "SELECT name FROM `project`.`store` order by name asc;");
    // Connect to database
    if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
     //Query to get all stores
    if (mysql_query(conn, start)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
      for (int i = 0; i < num_fields; i++)
      {
        printf("%s ", row[i] ? row [i] : "NULL");
      }

      printf("\n");
      
    }
    mysql_free_result(result);
    mysql_close(conn);
}

void fill_combo_box_store(){
  db_fill_store();
}

void win_add_product(){

  GtkWidget **gtkWidget_Array;
  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *combo;
  GtkWidget *entry;

  gtkWidget_Array = malloc(2 * sizeof(GtkWidget));

  builder = gtk_builder_new_from_file("glade/window_add.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  button = GTK_WIDGET(gtk_builder_get_object (builder, "btn_add"));
  combo = GTK_WIDGET(gtk_builder_get_object (builder, "combobox_cat"));
  entry = GTK_WIDGET(gtk_builder_get_object (builder, "entry1"));


  gtkWidget_Array[0] = entry;
  gtkWidget_Array[1] = combo;

  g_signal_connect (button, "clicked", G_CALLBACK (get_product) , gtkWidget_Array);

  button = GTK_WIDGET (gtk_builder_get_object(builder, "btn_quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_widget_show(window);
}

void win_log_in(){
  GtkWidget **array;
  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget *label;

  array = malloc(3 * sizeof(GtkWidget));
  builder = gtk_builder_new_from_file("glade/window_log_in.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
  array[0] = entry;
  entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry_pass"));
  array[1] = entry;
  label = GTK_WIDGET(gtk_builder_get_object(builder, "is_log"));
  array[2] = label;
  button = GTK_WIDGET(gtk_builder_get_object(builder,"login"));
  g_signal_connect(button, "clicked", G_CALLBACK(get_log), array);
  button = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

  gtk_widget_show(window);
}
void win_chose_store(){
  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *combo;

  builder = gtk_builder_new_from_file("glade/window_chose_store.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  combo = GTK_WIDGET(gtk_builder_get_object(builder, "combobox_store"));
  fill_combo_box_store();

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

  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *button;

  gtk_init (&argc, &argv);
  //gtkWidget_Array = malloc(2 * sizeof(GtkWidget));

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new_from_file ("glade/window_main.glade");

  //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  //Get the buttons and apply usefulnes
  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_product"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_add_product), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_account"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_log_in), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_store"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_chose_store), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_order"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_show_order), NULL);


  button = GTK_WIDGET (gtk_builder_get_object(builder, "quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), window);

  gtk_widget_show(window);
  gtk_main ();

  return 0;
}