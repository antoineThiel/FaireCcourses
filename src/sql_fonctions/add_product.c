#define SERVER "localhost"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "project"
#define PREPARE_CONNECTION(connector) connector = mysql_init(NULL);\
                                      if (!mysql_real_connect(connector, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {\
                                          fprintf(stderr, "%s\n", mysql_error(connector));\
                                          exit(1);\
                                      }

#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../headers/sql_fonctions.h"

void add_product(const gchar *param, const gchar *param2) {
    
    MYSQL* conn;
    PREPARE_CONNECTION(conn);
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
    mysql_close(conn);    
}