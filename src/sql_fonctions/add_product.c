//~~~~~~~~~~~INCLUDES~~~~~~~~~~~
    #include "../../headers/all.h"
//~~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

extern MYSQL* CONNECTOR_DB;
extern GtkBuilder* MAIN_BUILDER;
extern ORDER ORDER_DATA;

void add_product(const gchar *param, const gchar *param2, const gchar *param3) {
    
    char *start;
    char quote[2]="\""; 
    //Rserve memory
    start = malloc(sizeof(char)*200);
    check_malloc(start);
    
    //initializing query
    strcpy(start, "insert into product values(NULL");
    strcat(start, ",");
    strcat(start, quote);    

    //add quotes & comma
    strcat(start, param);
    strcat(start, quote);
    strcat(start, ",");
    strcat(start, quote);

    //Get the category
    //Finishing Query
    strcat(start, param2);
    strcat(start, quote);
    strcat(start, ",");
    strcat(start, param3);
    sprintf(start, "%s, %d)", start, ORDER_DATA.CURRENT_SHOP);

    //Query to add a product
    if (mysql_query(CONNECTOR_DB, start)) {
        fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }

    free(start);  
}