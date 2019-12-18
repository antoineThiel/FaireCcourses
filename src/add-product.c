#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../headers/sql_fonctions.h"

void add_product(MYSQL *conn ,  const gchar *param, const gchar *param2) {
    
    char *start;
    char *param1;
    char input[50];
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

    //Close connection
    mysql_close(conn);
    //Free memory
    free(start);
}


void prepare_conn(MYSQL *conn){

    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "project";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

}