//~~~~~~~~~~~INCLUDES~~~~~~~~~~~
    #include "../../headers/all.h"
//~~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

extern MYSQL* CONNECTOR_DB;
extern GtkBuilder* MAIN_BUILDER;

void add_product(const gchar *param, const gchar *param2) {
    
    char *start;
    // char *param1;
    // char input[50];
    char quote[2]="\""; 
    //Rserve memory
    start = malloc(sizeof(char)*200);
    
    //initializing query
    strcpy(start, "insert into product values(NULL");
    strcat(start, ",");
    strcat(start, quote);

    //Get name of the product
    

    //add quotes & comma
    strcat(start, param);
    strcat(start, quote);
    strcat(start, ",");
    strcat(start, quote);

    //Get the category
    //Finishing Query
    strcat(start, param2);
    strcat(start, quote);
    strcat(start, ")");

    //Query to add a product
    if (mysql_query(CONNECTOR_DB, start)) {
        fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }

    free(start);
    mysql_close(CONNECTOR_DB);    
}