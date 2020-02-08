//~~~~~~INCLUDES~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~GLOBALS~~~~~~~~~~~~

extern GtkBuilder *MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;


char** get_id_customer(const gchar *name, const gchar *pass){
  MYSQL_RES *results;
  MYSQL_ROW row;

  char start[80];
  sprintf(start, "select id from customer where username = '%s' and password = '%s'", name, pass);

  if (mysql_query(CONNECTOR_DB, start)) {
  fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
  exit(1);
  }

  results = mysql_store_result(CONNECTOR_DB);
  row = mysql_fetch_row(results);
  mysql_free_result(results);
  return row;

}

void get_log(GtkWidget * widget, GtkWidget **array){
  GtkWidget *entry_id = array[0];
  GtkWidget *entry_pass = array[1];
  char** data;

  GObject *btn_connexion = gtk_builder_get_object(MAIN_BUILDER , "btn_account");
  
  const gchar *a, *b;
  a = gtk_entry_get_text(GTK_ENTRY (entry_id));
  b = gtk_entry_get_text(GTK_ENTRY (entry_pass));
  if ( (USER_DATA.IS_CONNECTED = log_in(a, b) ) ){

    data = get_id_customer(a, b);
    USER_DATA.ID_CUSTOMER = atoi(data[0]);
    gtk_widget_hide(GTK_WIDGET(btn_connexion));
    win_my_account(widget);
    
  }
  else 
  gtk_button_set_label(GTK_BUTTON(btn_connexion), "Nope.");
  (void) widget;
}
void win_log_in(GtkWidget *widget){

  GtkWidget **array;
  GtkWidget *grid;
  GtkWidget *grid_content;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget *label;

  array = malloc(3 * sizeof(GtkWidget));
  check_malloc(array);
  grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
  label = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "label"));

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
  
  entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid_content), entry, 1,0,1,1);
  array[0] = entry;
  
  entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid_content), entry, 1,1,1,1);
  array[1] = entry;
  
  button = gtk_button_new_with_label("Connexion");
  gtk_grid_attach(GTK_GRID(grid_content), button, 2,0,1,2);
  label = gtk_label_new("Username");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);
  label = gtk_label_new("Password");
  gtk_grid_attach(GTK_GRID(grid_content), label, 0,1,1,1);

  g_signal_connect(button, "clicked", G_CALLBACK(get_log), array);
  
  (void)widget;
  gtk_widget_show_all(grid_content);
}

void modify_log_text(){

}

void win_start(GtkWidget *widget){

  event_handler();
  win_log_in(NULL);
  widget = widget;
}