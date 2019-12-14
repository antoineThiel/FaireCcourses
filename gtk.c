#include <gtk/gtk.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "headers/sql_fonctions.h"


void add_product( const gchar *param, const gchar *param2) {
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "project";
    char *start;
    char *param1;
    char input[50];
    char quote[2]="\"";

    //Rserve memory
    start = malloc(sizeof(char)*200);
    
    //initializing query
    strcpy(start, "insert into product values(NULL");
    strcat(start, ",");
    strcat(start, quote);

    //Get name of the product
    

    //add quotes & comma
    strcat(start, param);
    strcat(start, quote);
    strcat(start, ",");
    strcat(start, quote);

    //Get the category
    //Finishing Query
    strcat(start, param2);
    strcat(start, quote);
    strcat(start, ")");

    //Initalizing connection with bdd
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    //Query to add a product
    if (mysql_query(conn, start)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    //Close connection
    mysql_close(conn);
    //Free memory
    free(start);
}

//Fonction pour récupérer le texte
void get_input2(GObject **tab){
  const gchar *trial, *trial2;
  trial = gtk_entry_get_text (GTK_ENTRY (tab[0]));
  trial2 = gtk_entry_get_text(GTK_ENTRY (tab[1]));
  add_product(trial, trial2);
}

int main (int argc, char *argv[]){

  GObject **gtkWidget_Array;
  GtkBuilder *builder;
  GObject *window;
  GObject *button;
  GObject *entry1;
  GObject *entry2;
  GError *error = NULL;
  const gchar *trial;
  gtk_init (&argc, &argv);

  gtkWidget_Array = malloc(2 * sizeof(GtkWidget*));

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