//~~~~~~~~~INCLUDES~~~~~~~~~~~~
  #include "../../headers/all.h"


//~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~~
extern GtkBuilder* MAIN_BUILDER;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;
extern MYSQL* CONNECTOR_DB;

void win_new_product(){
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *button;
  GtkWidget *label;

  grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));


  if (ORDER_DATA.CURRENT_GRID != NULL)
    {
      gtk_widget_destroy(ORDER_DATA.CURRENT_GRID);
    }
    else{
      gtk_grid_remove_column(GTK_GRID(grid), 1);
      gtk_grid_insert_column(GTK_GRID(grid), 1);
    }
  
  grid_content = gtk_grid_new();
  ORDER_DATA.CURRENT_GRID = grid_content;
  gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,2,2);

  label = gtk_label_new(_("product_added"));
  gtk_grid_attach(GTK_GRID(grid_content), label, 0 ,0,2,1);

  button = gtk_button_new_with_label(_("add new"));
  gtk_grid_attach(GTK_GRID(grid_content), button, 0, 1 ,2,1);

  g_signal_connect(button, "clicked", G_CALLBACK(win_add_product_admin), NULL);

  gtk_widget_show_all(grid_content);

}


void get_product(GtkWidget *widget, GtkWidget **array){
  
  const gchar *a, *b, *c;
  GtkWidget *entry = array[0];
  GtkWidget *combo = array[1];
  GtkWidget *price = array[2];

  a = gtk_entry_get_text(GTK_ENTRY (entry));
  b = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo));
  c = gtk_entry_get_text(GTK_ENTRY(price));
  (void)widget; //Equivaut a windget = widget
  
  add_product(a,b,c);
  win_new_product();
}

void win_add_product(const gchar *store){

    GtkWidget **array;
    GtkWidget *combo;
    GtkWidget *entry;

    GtkWidget *grid;
    GtkWidget *grid_content;
    GtkWidget *button;
    GtkWidget *label;

    if(USER_DATA.IS_CONNECTED){
    array = malloc(4 * sizeof(GtkWidget));
    check_malloc(array);
    
    grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
    
    if (ORDER_DATA.CURRENT_GRID != NULL)
    {
      gtk_widget_destroy(ORDER_DATA.CURRENT_GRID);
    }
    else{
      gtk_grid_remove_column(GTK_GRID(grid), 1);
      gtk_grid_insert_column(GTK_GRID(grid), 1);
    }
    
    grid_content = gtk_grid_new();
    ORDER_DATA.CURRENT_GRID = grid_content;
    gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,2,3);

    button = gtk_button_new_with_label(_("add"));
    entry = gtk_entry_new();
    combo = gtk_combo_box_text_new();

    label = gtk_label_new(_("product_name"));
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);
    label = gtk_label_new(_("category"));
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,1,1,1);

    fill_combobox_cat(GTK_COMBO_BOX_TEXT(combo));
    
    gtk_grid_attach(GTK_GRID(grid_content), button, 1,3,1,1);
    gtk_grid_attach(GTK_GRID(grid_content), entry, 1,0,1,1);
    gtk_grid_attach(GTK_GRID(grid_content), combo, 1,1,1,1);

    array[0] = entry;

    label = gtk_label_new(_("product_price"));
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1 );
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_content), entry, 1,2,1,1);


    array[1] = combo; 
    array[2] = entry;
    g_signal_connect (button, "clicked", G_CALLBACK (get_product) , array);
    gtk_widget_show_all(grid_content);
    (void)store;
  }
  else{ 
    print_error();
  }
}

void sql_add_category(const gchar *cat, const gchar *store){
  char start[80];
  int id_store = atoi(store);
  sprintf(start, "insert into category values (NULL, '%s', %d)", cat, id_store);
  if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
  } 
}

void add_category(GtkWidget *widget, GtkWidget **array){
  GtkWidget *entry = array[0];
  GtkWidget *store_n = array[1];
  char **id_store;
  char tmp[3];
  const gchar *category, *store;
  category = gtk_entry_get_text(GTK_ENTRY(entry));
  store = gtk_label_get_text(GTK_LABEL(store_n));
  id_store = get_id(store);
  strcpy(tmp, id_store[0]);
  sql_add_category(category, tmp);
  win_new_product();
  (void) widget;
}

void win_add_category(const gchar *store){
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *label;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget **array;

  array = malloc(2*sizeof(GtkWidget));

  grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
  if (ORDER_DATA.CURRENT_GRID != NULL)
    {
      gtk_widget_destroy(ORDER_DATA.CURRENT_GRID);
    }
    else{
      gtk_grid_remove_column(GTK_GRID(grid), 1);
      gtk_grid_insert_column(GTK_GRID(grid), 1);
    }
  
  grid_content = gtk_grid_new();
  ORDER_DATA.CURRENT_GRID = grid_content;
  gtk_grid_attach(GTK_GRID(grid), grid_content, 1, 0, 3, 3);

  label = gtk_label_new(_("name"));
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);

  entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid_content), entry, 0,1,1,1);
  array[0] = entry;

  label = gtk_label_new(store);
  array[1] = label;

  button = gtk_button_new_with_label(_("add"));
  gtk_grid_attach(GTK_GRID(grid_content), button, 1,1,1,1);

  g_signal_connect(button, "clicked", G_CALLBACK(add_category), array);

  gtk_widget_show_all(grid_content);


}

void product_cat(GtkWidget *widget, GtkWidget **array){
  GtkWidget *store = array[0];
  GtkWidget *chose = array[1];

  const gchar *stooore;
  const gchar *choose;

  stooore = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(store));
  choose = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(chose));

  if(!strcmp(choose, "Produit")){
    win_add_product(stooore);
  }
  else {
    win_add_category(stooore);
  }
  (void)widget;
}


void win_add_product_admin(GtkWidget *widget){
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *label;
  GtkWidget *button;
  GtkWidget *combo;
  GtkWidget **array;

  array = malloc(2*sizeof(GtkWidget));

  grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
  if (ORDER_DATA.CURRENT_GRID != NULL)
    {
      gtk_widget_destroy(ORDER_DATA.CURRENT_GRID);
    }
    else{
      gtk_grid_remove_column(GTK_GRID(grid), 1);
      gtk_grid_insert_column(GTK_GRID(grid), 1);
    }

    if (ORDER_DATA.GRID_RESULTS != NULL){
      gtk_widget_destroy(ORDER_DATA.GRID_RESULTS);
    }
  
  grid_content = gtk_grid_new();
  ORDER_DATA.CURRENT_GRID = grid_content;
  gtk_grid_attach(GTK_GRID(grid), grid_content, 1, 0, 3, 3);

  label = gtk_label_new(_("store"));
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);

  label = gtk_label_new(_("type"));
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,1,1,1);

  combo = gtk_combo_box_text_new();
  fill_combobox_store(GTK_COMBO_BOX_TEXT(combo));
  gtk_grid_attach(GTK_GRID(grid_content), combo, 1,0,1,1);
  array[0] = combo;

  combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), "1", _("category"));
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), "2", _("product"));
  gtk_grid_attach(GTK_GRID(grid_content), combo, 1,1,1,1);
  array[1] = combo;

  button = gtk_button_new_with_label(_("next"));
  gtk_grid_attach(GTK_GRID(grid_content), button, 1,2,1,1);

  g_signal_connect(button, "clicked", G_CALLBACK(product_cat), array);

  gtk_widget_show_all(grid_content);
  (void) widget;

}


