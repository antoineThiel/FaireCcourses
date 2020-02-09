//~~~~~~~~~INCLUDES~~~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

extern GtkBuilder* MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;

MYSQL_RES* get_list(const gchar *category){
    char start[90];
    MYSQL_RES* results;
    sprintf(start, "select name, price from product where id_store = %d and category = '%s'", ORDER_DATA.CURRENT_SHOP, category);
    if (mysql_query(CONNECTOR_DB, start)) {
        fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }
    return results = mysql_store_result(CONNECTOR_DB);
}

void be4results(GtkWidget *widget, GtkWidget *cat){

    GtkWidget *label;
    const gchar *category = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cat));
    MYSQL_RES* results = get_list(category);
    u_int64_t size = mysql_num_rows(results);
    if (size > 0)
    {    
        char** data = mysql_fetch_row(results);
        for (u_int64_t i = 0; i < size ; i++)
        {
            label = gtk_label_new(data[0]);
            gtk_grid_attach(GTK_GRID(ORDER_DATA.CURRENT_GRID), label, 1,3,1,1);
            label = gtk_label_new(data[1]);
            gtk_grid_attach(GTK_GRID(ORDER_DATA.CURRENT_GRID), label, 2, 3, 1, 1);
        }
    }
    gtk_widget_show_all(ORDER_DATA.CURRENT_GRID);
    (void)widget;
}

void chose_cat(GtkWidget *widget, GtkWidget *combo){
    GtkWidget *cat;
    GtkWidget *label;
    GtkWidget *button;
    char** id_store;
    char tmp[5];
    const gchar *store = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    id_store = get_id(store);
    strcpy(tmp, id_store[0]);
    ORDER_DATA.CURRENT_SHOP = atoi(tmp);
    cat = gtk_combo_box_text_new();
    fill_combobox_cat(GTK_COMBO_BOX_TEXT(cat));
    gtk_grid_attach(GTK_GRID(ORDER_DATA.CURRENT_GRID), cat, 1,1,1,1);
    label = gtk_label_new("Category : ");
    gtk_grid_attach(GTK_GRID(ORDER_DATA.CURRENT_GRID), label, 0,1,1,1);
    button = gtk_button_new_with_label("Valider");
    gtk_grid_attach(GTK_GRID(ORDER_DATA.CURRENT_GRID), button, 1,2,1,1);

    g_signal_connect(button, "clicked", G_CALLBACK(be4results), cat);
    gtk_widget_show_all(ORDER_DATA.CURRENT_GRID);
    (void) widget;

}


void win_see_product(GtkWidget *widget){
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *button;
    GtkWidget *grid_content;
    GtkWidget *combo;

    grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));

    if (ORDER_DATA.CURRENT_GRID != NULL)
    {
        gtk_widget_destroy(ORDER_DATA.CURRENT_GRID);
    }
    

    grid_content = gtk_grid_new();
    ORDER_DATA.CURRENT_GRID = grid_content;
    gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,5,5);

    label = gtk_label_new("Magasin :");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);

    combo = gtk_combo_box_text_new();
    fill_combobox_store(GTK_COMBO_BOX_TEXT(combo));
    gtk_grid_attach(GTK_GRID(grid_content), combo, 1,0,1,1);

    button = gtk_button_new_with_label("Valider");
    gtk_grid_attach(GTK_GRID(grid_content), button, 2,0,1,1);

    g_signal_connect(button, "clicked", G_CALLBACK(chose_cat), combo);
    gtk_widget_show_all(grid_content);
    (void) widget;
}