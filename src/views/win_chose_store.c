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


//SQL recupère id du magasin donné en parametre
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

//SQL Recupère id du produit donné en parametre
char** get_product_id(const gchar *product){
    
    MYSQL* conn;
    MYSQL_RES *result;
    MYSQL_ROW data;

    PREPARE_CONNECTION(conn);
    char *start;
    char quote[2]="\""; 
    //Rserve memory
    start = malloc(sizeof(char)*200);
    
    //initializing query
    strcpy(start, "select id from product where name =");
    strcat(start, quote);
    strcat(start, product);
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


//SQL Retour de recherche pour le mot clé entré
char** get_product_list(const gchar *product){

  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW data;
  PREPARE_CONNECTION(conn);
  char *start;
  char quote[2]="\""; 
  //Rserve memory
  start = malloc(sizeof(char)*200);
  
  //initializing query
  strcpy(start, "select name from product where name =");
  strcat(start, quote);
  strcat(start, product);
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
  

//SQL Creation nouvelle commande
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

//Ajoute 1 au compteur a coté du produit
void increase(GtkWidget *widget, GtkWidget *label){

  const gchar *now;
  int temp;
  gchar then[50];
  now = gtk_label_get_text(GTK_LABEL(label));
  temp=atoi(now)+1;
  sprintf(then, "%d", temp);
  gtk_label_set_text(GTK_LABEL(label), then);
  widget = widget;
}

//Enleve 1 au compteur a coté du produit
void decrease(GtkWidget *widget, GtkWidget *label){

  const gchar *now;
  int temp;
  gchar then[50];
  now = gtk_label_get_text(GTK_LABEL(label));
  if(atoi(now) <= 0){
    temp=0;
  }
  else{
    temp=atoi(now)-1;
  }
  sprintf(then, "%d", temp);
  gtk_label_set_text(GTK_LABEL(label), then);
  widget = widget;
}

//SQL ajout au panier def - a fix
void def_add_cart(gchar *id_product, const gchar *quantity){
  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW data2;
  PREPARE_CONNECTION(conn);
  char *start;
  //Rserve memory
  start = malloc(sizeof(char)*200);

  strcpy(start, "select max(id) from order");
  if (mysql_query(conn, start)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  result = mysql_store_result(conn);
  data2 = mysql_fetch_row(result);
  
  //initializing query
  strcpy(start, "insert into product_order values(");
  strcat(start, data2[0]);
  strcat(start, ",");
  strcat(start, id_product);
  strcat(start, ",");
  strcat(start, quantity);
  strcat(start, ")");

  if (mysql_query(conn, start)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  mysql_close(conn);
  free(start);
}

//Recupere nom produit, id produit, quantité
void add_to_cart(GtkWidget *widget, GtkWidget **array){

  const gchar *name;
  const gchar *quantity;
  gchar **id_product;
  GtkWidget *product_name =  array[1];

  id_product = malloc(100);

  name = gtk_label_get_text(GTK_LABEL(product_name));
  printf("%s", name);
  id_product = get_product_id(name);
  printf("\n%s", id_product[0]);

  GtkWidget *ammount = array[0];
  quantity = gtk_label_get_text(GTK_LABEL(ammount));

  printf("\n%s", id_product[0]);
  def_add_cart(id_product[0], quantity);
  

  widget = widget;

}

//Affiche les resultats de recherche et la possibilité d'ajouter au panier
void display_search(GtkWidget *widget, GtkWidget **array){

  const gchar *a;
  gchar **data;
  GtkBuilder *builder = GTK_BUILDER(array[0]);
  GtkWidget *grid;
  GtkWidget *label;
  GtkWidget *label2;
  GtkWidget *button;
  GtkWidget **array2;

  array2 = malloc( 2* sizeof(GtkWidget));

  a = gtk_entry_get_text(GTK_ENTRY(array[1]));
  data = get_product_list(a);

  grid = GTK_WIDGET(gtk_builder_get_object(builder, "grid_results"));
  gtk_grid_insert_row (GTK_GRID(grid), 2);
  label = gtk_label_new(data[0]);
  gtk_grid_attach(GTK_GRID(grid),label, 0, 2, 1, 1);
  button = gtk_button_new_with_label("-");
  gtk_grid_attach(GTK_GRID(grid),button, 2, 2, 1, 1);
  label = gtk_label_new("1");
  g_signal_connect(button, "clicked", G_CALLBACK(decrease), label);
  gtk_grid_attach(GTK_GRID(grid),label, 3, 2, 1, 1);
  button = gtk_button_new_with_label("+");
  g_signal_connect(button, "clicked", G_CALLBACK(increase), label);
  gtk_grid_attach(GTK_GRID(grid),button, 4, 2, 1, 1);
  button = gtk_button_new_with_label("Ajouter");
  gtk_grid_attach(GTK_GRID(grid),button, 5, 2, 1, 1);
  label2 = gtk_label_new(data[0]);
  array2[0] = label;
  array2[1] = label2;
  g_signal_connect(button, "clicked", G_CALLBACK(add_to_cart), array2);
  


  gtk_widget_show_all(grid);
  widget = widget;
}

//Gère l'affiche de la nouvelle fenetre
void win_shopping(){
  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget **array;

  array = malloc (2 * sizeof(GtkWidget));
  builder = gtk_builder_new_from_file("./glade/window_shop.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  entry = GTK_WIDGET(gtk_builder_get_object(builder, "search_entry"));
  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_search"));

  array[0] = GTK_WIDGET(builder);
  array[1] = entry;
  g_signal_connect(button, "clicked", G_CALLBACK(display_search), array);


  gtk_widget_show_all(window);
}

//Recupère l'id du magasin selon le nom créé une commande et affiche la nouvelle fenetre
void get_store(GtkWidget *widget, GtkWidget *combo){
  const gchar *a;
  gchar **data;
  a=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
  data = get_id(a);
  start_order(data);
  win_shopping();
  widget = widget;
}


//Gere l'affichage du mod dans le builder principal
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