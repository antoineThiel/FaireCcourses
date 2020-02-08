//~~~~~~~~~INCLUDES~~~~~~~~~~~~
  #include "../../headers/all.h"


//~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~~
extern GtkBuilder* MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;


char** get_infos(char* id){
    MYSQL_RES *results;
    MYSQL_ROW row;

    char start[100];
    sprintf(start, "select username, total_order, statut from customer where id = '%s'",id);
    if (mysql_query(CONNECTOR_DB, start)) {
    fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
    exit(1);
    }
        results = mysql_store_result(CONNECTOR_DB);
    row = mysql_fetch_row(results);
    mysql_free_result(results);
    return row;
}

void my_account(GtkWidget *widget){

    GtkWidget *label;
    GtkWidget *grid_content;
    GtkWidget *grid;
    char id[3];
    char** infos;

    grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "grid"));

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
    gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,2,5);

    label = gtk_label_new("Username :");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);

    sprintf(id, "%d", USER_DATA.ID_CUSTOMER);
    infos = get_infos(id);
    label = gtk_label_new(infos[0]);
    gtk_grid_attach(GTK_GRID(grid_content), label, 1,0,1,1);

    label = gtk_label_new("Nombre total de commande : ");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,1,1,1);

    label = gtk_label_new(infos[1]);
    gtk_grid_attach(GTK_GRID(grid_content), label, 1,1,1,1);

    label = gtk_label_new("Statut : ");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1);

    if (!strcmp(infos[2], "1")){
        label = gtk_label_new("Administrateur");
        USER_DATA.ADMIN = 1;
    }
    else{
        label = gtk_label_new("Client");
        USER_DATA.ADMIN = 0;
    }
    gtk_grid_attach(GTK_GRID(grid_content), label, 1,2,1,1);
    gtk_widget_show_all(grid_content);
    widget = widget;
}




void win_my_account(GtkWidget *widget){

    GtkWidget *grid;
    GtkWidget *button;

    grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "grid"));
    button = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "btn_account"));
    gtk_widget_destroy(button);
    button = gtk_button_new_with_label("Mon Compte");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(my_account), NULL);
    widget=widget;

    gtk_widget_show_all(grid);
    my_account(widget);
}

