#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "headers/sql_fonctions.h"

char* get_input(char* param){
    fgets(param, 50, stdin);
    strtok(param, "\n");
    return param;
}

void add_product(const gchar* param, const gchar* param2) {
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "project";
    char *start;
    const gchar *entry_text;
    char input[50];
    char quote[2]="\"";

    //Rserve memory
    start = malloc(sizeof(char)*200);
    
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
    printf("\nDe quelle catégorie fait il partie ?");
    param = get_input(input);

    //Finishing Query
    strcat(start, param2);
    strcat(start, quote);
    strcat(start, ")");

    //Initalizing connection with bdd
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

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