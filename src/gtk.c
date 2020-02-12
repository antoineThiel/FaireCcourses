//~~~~~~~~~~~~~INCLUDES~~~~~~~~~
  #include "../headers/all.h"

MYSQL* CONNECTOR_DB;
GtkBuilder* MAIN_BUILDER;

SESSION USER_DATA;
ORDER ORDER_DATA;

void launcher(){

  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *button;

  builder = gtk_builder_new_from_file("glade/launcher.glade");
   //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_account"));
  g_signal_connect (button, "clicked", G_CALLBACK (win_start), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_account"));
  g_signal_connect (button, "clicked", G_CALLBACK (win_create_account), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_quit"));
  g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show(window);
}

void event_handler(){
  
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *admin;
  GtkWidget *custo;
  admin = gtk_label_new("admin");
  custo = gtk_label_new("custo");

  //Destroying the window 
  window = GTK_WIDGET(gtk_builder_get_object (MAIN_BUILDER, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_account"));
  g_signal_connect (button, "clicked", G_CALLBACK(win_log_in),NULL );

  if (USER_DATA.IS_CONNECTED){
    if(USER_DATA.ADMIN){
    //Get the buttons and apply usefulnes
    button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_add_product"));
    g_signal_connect (button, "clicked", G_CALLBACK(win_add_product_admin), NULL);

    button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_see_product"));
    g_signal_connect(button, "clicked", G_CALLBACK(win_see_product_1), admin);
    }else {
      button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_add_product"));
      gtk_widget_hide(button);
      button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_see_product"));
      gtk_widget_hide(button);
    }
  button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_store"));
  g_signal_connect(button, "clicked", G_CALLBACK(win_see_product_1), custo);
  }

  button = GTK_WIDGET (gtk_builder_get_object(MAIN_BUILDER, "quit"));
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), window);




  gtk_widget_show(window);
}

int main (int argc, char *argv[]){


  PREPARE_CONNECTION(CONNECTOR_DB);
  session_init(&USER_DATA);
  order_init(&ORDER_DATA);
  gtk_init (&argc, &argv);
  /* Construct a GtkBuilder instance and load our UI description */
  MAIN_BUILDER = gtk_builder_new_from_file ("./glade/window_main.glade");
  
  //pour fix les pb de double en sql
  setlocale(LC_NUMERIC, "en_US.UTF-8");

  //Choix de la langue (fr : fr_FR.UTF-8 et messages_fr, en : en_US.UTF-8 et messages_en)

  setlocale(LC_MESSAGES, "en_US.UTF-8");
  bindtextdomain("messages_en", "trans");
  textdomain("messages_en");

  launcher();
  
  gtk_main ();

  generateSchema();
  
  mysql_close(CONNECTOR_DB);
  return 0;
}


void session_init(SESSION* data){
  data->IS_CONNECTED = 0;
}

void order_init(ORDER* data){
  data->CURRENT_GRID = NULL;
  data->PRICE = 0;
}