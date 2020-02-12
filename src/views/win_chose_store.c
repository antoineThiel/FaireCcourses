//~~~~~~~~~INCLUDES~~~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

extern GtkBuilder* MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;

void unset(){
  ORDER_DATA.TOTAL_PRICE = 0;
  ORDER_DATA.PRICE = NULL;
  win_see_product(NULL);
}

void update_price_order(){
  char start[60];
  sprintf(start, "update `order` set price = %.2lf where id = %d", ORDER_DATA.TOTAL_PRICE, ORDER_DATA.ORDER_NUMBER);
  if (mysql_query(CONNECTOR_DB, start)) {
  fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
  exit(1);
  }
}

void update_id_customer(){
  char start[60];
  sprintf(start, "update `order` set id_customer = %d where id = %d", USER_DATA.ID_CUSTOMER, ORDER_DATA.ORDER_NUMBER);
  if (mysql_query(CONNECTOR_DB, start)) {
  fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
  exit(1);
  }
}

void update_order_customer(){
  char start[90];
  sprintf(start, "update customer set total_order = (select total_order where id = %d) +1 where id = %d", USER_DATA.ID_CUSTOMER, USER_DATA.ID_CUSTOMER);
  if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
  }
}

void validate_order(){
    
  update_price_order();
  update_id_customer();
  update_order_customer();

  gtk_widget_destroy(ORDER_DATA.CURRENT_GRID);
  gtk_widget_destroy(ORDER_DATA.GRID_RESULTS);
  gtk_widget_destroy(ORDER_DATA.BASKET);
  GtkWidget *button;
  GtkWidget *grid_content;
  GtkWidget *grid;
  grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
  grid_content = gtk_grid_new();
  ORDER_DATA.CURRENT_GRID = GTK_WIDGET(grid_content);
  gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,2,3);
  button = gtk_button_new_with_label(_("order_more"));
  gtk_grid_attach(GTK_GRID(grid_content), button, 1,1,1,1);

  g_signal_connect(button, "clicked", G_CALLBACK(unset), NULL);

  button = gtk_button_new_with_label(_("quit"));
  gtk_grid_attach(GTK_GRID(grid_content), button, 1, 3, 1, 1);

  g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(grid_content);


  generateSchema();
  //print_plan()
}
void set_label_price(){

  char text[20];
  sprintf(text, "Total : %.2lf €", ORDER_DATA.TOTAL_PRICE);
  gtk_label_set_text(GTK_LABEL(ORDER_DATA.PRICE), text);
}

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
void start_order(){
  char start[80];
  //Rserve memory
  sprintf(start, "insert into `order` values(NULL, 0, 0, %d)", ORDER_DATA.CURRENT_SHOP);
  if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
  }
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

void see_order(const gchar *name, const gchar *ammount){

  
  GtkWidget *label;



  if (!ORDER_DATA.BASKET_STAT)
  {

      GtkWidget *grid;
      grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
      gtk_grid_attach(GTK_GRID(grid), ORDER_DATA.BASKET, 25,0,4,10);
      gtk_grid_attach(GTK_GRID(ORDER_DATA.BASKET), ORDER_DATA.BASKET_NAME, 0,0,1,1);
      ORDER_DATA.BASKET_STAT =1;
  }
  if (!ORDER_DATA.TOTAL_PRICE !=0)
  {
      GtkWidget *button;
      button = gtk_button_new_with_label(_("valid"));
      gtk_grid_attach(GTK_GRID(ORDER_DATA.BASKET), button, 0,3,2,2);
      g_signal_connect(button, "clicked", G_CALLBACK(validate_order), NULL);
      gtk_grid_attach(GTK_GRID(ORDER_DATA.BASKET), ORDER_DATA.PRICE, 0,2,1,1);

  }
  label = gtk_label_new(name);
  gtk_grid_insert_row(GTK_GRID(ORDER_DATA.BASKET), 2);
  gtk_grid_attach(GTK_GRID(ORDER_DATA.BASKET), label, 0, 2, 1, 1);

  label = gtk_label_new(ammount);
  gtk_grid_attach(GTK_GRID(ORDER_DATA.BASKET), label, 1,2,1,1);
  gtk_widget_show_all(ORDER_DATA.BASKET);

}


//Recupere nom produit, id produit, quantité
void add_to_cart(GtkWidget *widget, GtkWidget **array){

  const gchar *name;
  const gchar *quantity;
  const gchar *price;
  gchar **id_product;
  gchar **id_order;
  int tmp;
  char temp[10];
  GtkWidget *product_name =  array[1];
  GtkWidget *price_product = array[2];
  price = gtk_label_get_text(GTK_LABEL(price_product));

  name = gtk_label_get_text(GTK_LABEL(product_name));
  id_product = get_product_id(name);
  start_order();
  strcpy(temp, id_product[0]);
  id_order = get_max_id();
  tmp = atoi(id_order[0]);
  ORDER_DATA.ORDER_NUMBER = tmp;

  GtkWidget *ammount = array[0];
  quantity = gtk_label_get_text(GTK_LABEL(ammount));

  def_add_cart(id_order[0],temp, quantity);  
  see_order(name, quantity);
  ORDER_DATA.TOTAL_PRICE += (strtod(price, NULL)*strtod(quantity, NULL));
  set_label_price();
  widget = widget;

}

//Affiche les resultats de recherche et la possibilité d'ajouter au panier
void display_search(GtkWidget *widget, GtkWidget *cat){
 
  GtkWidget *label;
  GtkWidget *grid_results;
  GtkWidget *grid;
  GtkWidget **array;
  GtkWidget *button;
  array = malloc(4*sizeof(GtkWidget));
  const gchar *category = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cat));
  MYSQL_RES* results = get_list(category);
  u_int64_t size = mysql_num_rows(results);

  if (size > 0)
  {    
      if (ORDER_DATA.GRID_RESULTS != NULL)
      {
          gtk_widget_destroy(ORDER_DATA.GRID_RESULTS);
      }       
      grid_results= gtk_grid_new();
      ORDER_DATA.GRID_RESULTS = grid_results;
      grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
      gtk_grid_attach(GTK_GRID(grid), grid_results, 10,0,6,10);
      label = gtk_label_new(_("name"));
      gtk_grid_attach(GTK_GRID(grid_results), label, 0,0,1,1);
      label = gtk_label_new(_("price"));
      gtk_grid_attach(GTK_GRID(grid_results), label, 1,0,1,1);
      for (u_int64_t i = 0; i < size ; i++)
      {
          char** data = mysql_fetch_row(results);
          label = gtk_label_new(data[0]);
          array[1] = label;
          gtk_grid_attach(GTK_GRID(grid_results), label, 0,1+(int)i,1,1);
          char price[5];
          sprintf(price, "%s €", data[1]);
          
          label = gtk_label_new(price);
          array[2] = label;
          gtk_grid_attach(GTK_GRID(grid_results), label, 1,1+(int)i,1,1);
          //Quantity
          button = gtk_button_new_with_label("-");
          gtk_grid_attach(GTK_GRID(grid_results),button, 2, 1+(int)i, 1, 1);
          label = gtk_label_new("1");
          array[0]=label;
          g_signal_connect(button, "clicked", G_CALLBACK(decrease), label);
          gtk_grid_attach(GTK_GRID(grid_results),label, 3, 1+(int)i, 1, 1);
          button = gtk_button_new_with_label("+");
          g_signal_connect(button, "clicked", G_CALLBACK(increase), label);
          gtk_grid_attach(GTK_GRID(grid_results),button, 4, 1+(int)i, 1, 1);
          button = gtk_button_new_with_label(_("add"));
          gtk_grid_attach(GTK_GRID(grid_results),button, 5, 1+(int)i, 1, 1);
      }
  }
  g_signal_connect(button, "clicked", G_CALLBACK(add_to_cart), array);
  
  gtk_widget_show_all(ORDER_DATA.GRID_RESULTS);
  widget = widget;
}


