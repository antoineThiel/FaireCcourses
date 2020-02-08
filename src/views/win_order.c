//~~~~~~INCLUDES~~~~~~~~~~~
    #include "../../headers/all.h"

//~~~~~~GLOBALS~~~~~~~~~~~~

extern GtkBuilder *MAIN_BUILDER;
extern MYSQL *CONNECTOR_DB;
extern SESSION USER_DATA;


//SQL recupère panier
MYSQL_RES* get_results(){
    
    MYSQL_RES *results;

    char *start;
    start = malloc(sizeof(char)*60);
    check_malloc(start);

    strcpy(start, "select * from product_order where id_order = ");
    sprintf(start, "%s %s", start, USER_DATA.ORDER_NUMBER);

    if (mysql_query(CONNECTOR_DB, start)) {
        fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }
    results = mysql_store_result(CONNECTOR_DB);
    free(start);
    return results;
}


u_int64_t get_num_rows(MYSQL_RES *results){
    u_int64_t num;
    num = mysql_num_rows(results);
    return num; 
}

char **show_full_list(MYSQL_RES *results){
    MYSQL_ROW row;
    row = mysql_fetch_row(results);
    return row;
}

void win_show_order(GtkWidget *widget){

    (void)widget;
    if(USER_DATA.IS_CONNECTED && USER_DATA.ORDER_STARTED){
        GtkWidget *grid_content;
        GtkWidget *grid;
        GtkWidget *label;
        MYSQL_RES *results;
        u_int64_t num_rows;
        char** cart;
        char line[20];
        int height;
        grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "grid"));
        label = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "label"));
        grid_content = gtk_grid_new();
        gtk_grid_remove_column(GTK_GRID(grid), 2);
        gtk_grid_insert_column(GTK_GRID(grid), 2);
        gtk_grid_attach(GTK_GRID(grid), grid_content, 2,0,1,1);

        label = gtk_label_new("Votre Panier : ");
        gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1);
        results = get_results();
        num_rows = get_num_rows(results);
        cart = show_full_list(results);
        for (u_int64_t i = 0; i < num_rows; i++){
            sprintf(line, "article n° %lu", i);
            height = (3+i);
            label = gtk_label_new(line);
            gtk_grid_attach(GTK_GRID(grid_content), label, 3,height,1,1);
            label = gtk_label_new(cart[i]);
            height = (4+i);
            gtk_grid_attach(GTK_GRID(grid_content), label, 4,height,1,1);
        }
        gtk_widget_show_all(grid_content);


    }
    else{
        print_error();
    }

}