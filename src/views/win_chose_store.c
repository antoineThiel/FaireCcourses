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

  //Recupérer la selection du select et lancer une fonction pour commencer les courses ?
  //Ouvrir une nouvelle fenetre avec une barre de recherche et une liste sur la gauche avec un panier qui s'agrandit
  //au fur et a mesure que l'utilisateur rajoute des produits ? :)

  gtk_widget_show_all(grid_content);
  (void)widget;
}