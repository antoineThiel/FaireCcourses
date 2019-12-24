#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../headers/sql_fonctions.h"

void add_product(MYSQL *conn ,  const gchar *param, const gchar *param2) {
    
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
    if (mysql_query(conn, start)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    free(start);

    
}

void select_cat_options( MYSQL *conn , GtkComboBoxText *selector){

    char *query = "SELECT * FROM category";
    MYSQL_RES *result;
    MYSQL_ROW data;

    if( !mysql_query(conn , query) ){

        result = mysql_store_result(conn);

        while( (data = mysql_fetch_row(result) ) != NULL){
            gtk_combo_box_text_append(selector , data[0] , data[1] );
            printf("%s" , data[1]);
        }

    }else{
        fprintf(stderr, "An error occured : \n%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_free_result(result);
}