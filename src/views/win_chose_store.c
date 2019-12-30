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
#include "../../headers/sql_fonctions.h"
#include "../../headers/gtk_fonctions.h"
#include "../../headers/views.h"


char** get_id(const gchar *store){
    
    MYSQL* conn;
    MYSQL_RES *result;
    MYSQL_ROW data;

    PREPARE_CONNECTION(conn);
    char *start;
    char quote[2]="\""; 
    //Rserve memory
    start = malloc(sizeof(char)*200);
    
    //initializing query
    strcpy(start, "select id from store where name =");
    strcat(start, quote);
    strcat(start, store);
    strcat(start, quote);

    if (mysql_query(conn, start)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
    }

    result = mysql_store_result(conn);
    data = mysql_fetch_row(result);
    

    mysql_close(conn);
    mysql_free_result(result);
    free(start);
    return data;
    
  }
  
  void start_order(MYSQL_ROW data){
    MYSQL* conn;
    PREPARE_CONNECTION(conn);
    char *start;
    //Rserve memory
    start = malloc(sizeof(char)*200);
    strcpy(start, "insert into `order` values(NULL,");
    strcat(start, data[0]);
    strcat(start, ", NULL, NULL)");
    if (mysql_query(conn, start)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
    }
        mysql_close(conn);
    free(start);
  }

  void get_store(GtkWidget *widget, GtkWidget *combo){
  const gchar *a;
  gchar **data;
  a=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
  data = get_id(a);
  start_order(data);


  widget = widget;
}

void win_chose_store(GtkWidget *widget, GtkBuilder *builder){
  GtkWidget *grid_content;
  GtkWidget *combo;
  GtkWidget *grid;
  GtkWidget *label;
  GtkWidget *button;

  grid = GTK_WIDGET(gtk_builder_get_object(builder, "grid"));
  label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
  grid_content = gtk_grid_new();
  gtk_grid_remove_column(GTK_GRID(grid), 2);
  gtk_grid_insert_column(GTK_GRID(grid), 2);
  gtk_grid_attach(GTK_GRID(grid), grid_content, 2,0,1,1);
  
  combo = gtk_combo_box_text_new();
  fill_combobox_store(GTK_COMBO_BOX_TEXT(combo));
  gtk_grid_attach(GTK_GRID(grid_content), combo, 1,2,1,1);
  label = gtk_label_new("Nom du magasin");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1);
  button = gtk_button_new_with_label("Commencer");
  gtk_grid_attach(GTK_GRID(grid_content), button, 1,3,1,1);


  g_signal_connect(button, "clicked", G_CALLBACK(get_store), combo);

  //Recupérer la selection du select et lancer une fonction pour commencer les courses ?
  //Ouvrir une nouvelle fenetre avec une barre de recherche et une liste sur la gauche avec un panier qui s'agrandit
  //au fur et a mesure que l'utilisateur rajoute des produits ? :)

  gtk_widget_show_all(grid_content);


  (void)widget;
}