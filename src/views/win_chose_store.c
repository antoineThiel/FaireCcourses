//~~~~~~~~~INCLUDES~~~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

extern GtkBuilder* MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;

//SQL recupère id du magasin donné en parametre
char** get_id(const gchar *store){
    
    MYSQL_RES *result;
    MYSQL_ROW data;

    char *start;
    char quote[2]="\""; 
    //Rserve memory
    start = malloc(sizeof(char)*200);
    check_malloc(start);
    //initializing query
    strcpy(start, "select id from store where name =");
    strcat(start, quote);
    strcat(start, store);
    strcat(start, quote);

    if (mysql_query(CONNECTOR_DB, start)) {
      fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
      exit(1);
    }

    result = mysql_store_result(CONNECTOR_DB);
    data = mysql_fetch_row(result);
    

    mysql_free_result(result);
    free(start);
    return data;
    
}

//SQL Recupère id du produit donné en parametre
char** get_product_id(const gchar *product){
    
    MYSQL_RES *result;
    MYSQL_ROW data;

    char *start;
    char quote[2]="\""; 
    //Rserve memory
    start = malloc(sizeof(char)*200);
    check_malloc(start);
    
    //initializing query
    strcpy(start, "select id from product where name =");
    strcat(start, quote);
    strcat(start, product);
    strcat(start, quote);

    if (mysql_query(CONNECTOR_DB, start)) {
      fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
      exit(1);
    }

    result = mysql_store_result(CONNECTOR_DB);
    data = mysql_fetch_row(result);    

    mysql_free_result(result);
    free(start);
    return data;
    
}


//SQL Retour de recherche pour le mot clé entré
char** get_product_list(const gchar *product){

  MYSQL_RES *result;
  MYSQL_ROW data;
  char *start;
  char quote[2]="\""; 
  //Rserve memory
  start = malloc(sizeof(char)*200);
  check_malloc(start);
  
  //initializing query
  strcpy(start, "select name, category, price from product where name =");
  strcat(start, quote);
  strcat(start, product);
  strcat(start, quote);

  if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
  }

  result = mysql_store_result(CONNECTOR_DB);  
  data = mysql_fetch_row(result);
  
  mysql_free_result(result);
  free(start);
  return data;
}
  
char** get_max_id(){
  MYSQL_RES *results;
  MYSQL_ROW row;
  char *start;
  start = malloc(sizeof(char)*50);
  check_malloc(start);

  strcpy(start, "select max(id) from `order`");

  if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
  }
  results = mysql_store_result(CONNECTOR_DB);
  row = mysql_fetch_row(results);
  free(start);
  mysql_free_result(results);
  return row;

}

//SQL Creation nouvelle commande
void start_order(MYSQL_ROW data){
  char *start;
  //Rserve memory
  start = malloc(sizeof(char)*200);
  check_malloc(start);

  strcpy(start, "insert into `order` values(NULL,");
  strcat(start, data[0]);
  strcat(start, ", NULL, NULL)");
  if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
  }
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
void def_add_cart(gchar *id_order,char *id_product, const gchar *quantity){
  char *start;
  //Rserve memory
  start = malloc(sizeof(char)*200);
  check_malloc(start);

  //initializing query
  strcpy(start, "insert into product_order values(");
  strcat(start, id_order);
  strcat(start, ",");
  strcat(start, id_product);
  strcat(start, ",");
  strcat(start, quantity);
  strcat(start, ")");

  if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
  }
  free(start);
}

void see_order(const gchar *name, const gchar *ammount, const gchar *price, GtkWidget *grid){

  
  GtkWidget *label;

  label = gtk_label_new(name);
  gtk_grid_insert_row(GTK_GRID(grid), 2);
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);

  label = gtk_label_new(ammount);
  gtk_grid_attach(GTK_GRID(grid), label, 1,2,1,1);

  label = gtk_label_new(price);
  gtk_grid_insert_column(GTK_GRID(grid), 2);
  gtk_grid_attach(GTK_GRID(grid), label, 3, 2, 1, 1);
  gtk_widget_show_all(grid);

}


//Recupere nom produit, id produit, quantité
void add_to_cart(GtkWidget *widget, GtkWidget **array){

  const gchar *name;
  const gchar *quantity;
  const gchar *price;
  gchar **id_product;
  gchar **id_order;
  char temp[10];
  GtkWidget *product_name =  array[1];
  GtkWidget *price_product = array[3];
  price = gtk_label_get_text(GTK_LABEL(price_product));

  name = gtk_label_get_text(GTK_LABEL(product_name));
  id_product = get_product_id(name);

  strcpy(temp, id_product[0]);
  id_order = get_max_id();
  USER_DATA.ORDER_NUMBER = id_order[0];

  GtkWidget *ammount = array[0];
  quantity = gtk_label_get_text(GTK_LABEL(ammount));

  def_add_cart(id_order[0],temp, quantity);
  
  see_order(name, quantity, price, array[2]);

  widget = widget;

}

//Affiche les resultats de recherche et la possibilité d'ajouter au panier
void display_search(GtkWidget *widget, GtkWidget **array){

  const gchar *a;
  gchar **data;
  GtkWidget *grid;
  GtkWidget *label;
  GtkWidget *label2;
  GtkWidget *label3;
  GtkWidget *button;
  GtkWidget **array2;

  array2 = malloc( 3* sizeof(GtkWidget));
  check_malloc(array2);

  a = gtk_entry_get_text(GTK_ENTRY(array[1]));
  data = get_product_list(a);
  if(data[0]==NULL){
      printf("empty");
  }
  else{

  //Grille + ajout ligne
  grid = GTK_WIDGET(array[0]);
  gtk_grid_remove_row(GTK_GRID(grid), 2);
  gtk_grid_remove_row(GTK_GRID(grid), 2);
  gtk_grid_remove_row(GTK_GRID(grid), 2);
  gtk_grid_insert_row (GTK_GRID(grid), 2);
  gtk_grid_insert_row (GTK_GRID(grid), 2);
  gtk_grid_insert_row (GTK_GRID(grid), 2);
  
  //Nom
  label = gtk_label_new(data[0]);
  gtk_grid_attach(GTK_GRID(grid),label, 0, 2, 1, 1);

  //Category
  label = gtk_label_new(data[1]);
  gtk_grid_attach(GTK_GRID(grid),label, 1, 2, 1, 1);

  //Price
  strcat(data[2], "€");
  label = gtk_label_new(data[2]);
  gtk_grid_attach(GTK_GRID(grid),label, 2, 2, 1, 1);
  
  
  //Quantity
  button = gtk_button_new_with_label("-");
  gtk_grid_attach(GTK_GRID(grid),button, 0, 3, 1, 1);
  label = gtk_label_new("1");
  g_signal_connect(button, "clicked", G_CALLBACK(decrease), label);
  gtk_grid_attach(GTK_GRID(grid),label, 1, 3, 1, 1);
  button = gtk_button_new_with_label("+");
  g_signal_connect(button, "clicked", G_CALLBACK(increase), label);
  gtk_grid_attach(GTK_GRID(grid),button, 2, 3, 1, 1);
  button = gtk_button_new_with_label("Ajouter");
  gtk_grid_attach(GTK_GRID(grid),button, 0, 4, 3, 1);
  
  
  label2 = gtk_label_new(data[0]);
  label3 = gtk_label_new(data[2]);
  array2[0] = label;  //Quantity
  array2[1] = label2; //Name
  array2[3] = label3; //Price
  array2[2] = array[2];   //grid_results
  g_signal_connect(button, "clicked", G_CALLBACK(add_to_cart), array2);
  


  gtk_widget_show_all(grid);
  }
  widget = widget;
}

//Gère l'affichage de la recherche des produits
void win_shopping(){
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *grid_results;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget **array;
  GtkWidget *label;

  array = malloc(3*sizeof(GtkWidget));

  grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
  
  gtk_widget_destroy(USER_DATA.CURRENT_GRID);
  gtk_grid_insert_column(GTK_GRID(grid), 1);
  
  grid_content = gtk_grid_new();
  USER_DATA.CURRENT_GRID = grid_content;
  gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,6,1);

  entry = gtk_entry_new();
  button = gtk_button_new_with_label("Search");
  gtk_grid_attach(GTK_GRID(grid_content), entry, 0, 0, 4, 1);
  gtk_grid_attach(GTK_GRID(grid_content), button, 4, 0, 1, 1);

  grid_results = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(grid), grid_results, 7, 0, 5, 1);
  label = gtk_label_new("Votre Panier : ");
  gtk_grid_attach(GTK_GRID(grid_results), label, 0, 0, 1, 1);

  gtk_widget_show_all(grid_content);
  gtk_widget_show_all(grid_results);
  
  
  array[0] = grid_content;
  array[1] = entry;
  array[2] = grid_results;
  g_signal_connect(button, "clicked", G_CALLBACK(display_search), array);

}

//Recupère l'id du magasin selon le nom, créé une commande et affiche la nouvelle fenetre
void get_store(GtkWidget *widget, GtkWidget *combo){
  const gchar *a;
  gchar **data;
  a=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
  data = get_id(a);
  start_order(data);
  USER_DATA.ORDER_STARTED = 1;
  win_shopping();
  widget = widget;
}


//Gere l'affichage du mod dans le MAIN_BUILDER principal
void win_chose_store(GtkWidget *widget){
  GtkWidget *grid_content;
  GtkWidget *grid;
  GtkWidget *combo;
  GtkWidget *label;
  GtkWidget *button;
  if(USER_DATA.IS_CONNECTED){
    grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));

    if (USER_DATA.CURRENT_GRID != NULL)
    {
      gtk_widget_destroy(USER_DATA.CURRENT_GRID);
    }
    else{
      gtk_grid_remove_column(GTK_GRID(grid), 1);
      gtk_grid_insert_column(GTK_GRID(grid), 1);
    }
    
    grid_content = gtk_grid_new();
    USER_DATA.CURRENT_GRID = grid_content;
    gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,3,1);

    combo = gtk_combo_box_text_new();
    fill_combobox_store(GTK_COMBO_BOX_TEXT(combo));
    gtk_grid_attach(GTK_GRID(grid_content), combo, 1,0,1,1);
    label = gtk_label_new("Nom du magasin");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);
    button = gtk_button_new_with_label("Commencer");
    gtk_grid_attach(GTK_GRID(grid_content), button, 2,0,1,1);

    gtk_widget_show_all(grid_content);

    g_signal_connect(button, "clicked", G_CALLBACK(get_store), combo);

    (void)widget;
  }
  else
  {
    print_error();
  }
  
}