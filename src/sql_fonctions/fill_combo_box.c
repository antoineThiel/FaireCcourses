#define SERVER "localhost"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "project"

#define PREPARE_CONNECTION(connector) connector = mysql_init(NULL);\
                                      if (!mysql_real_connect(connector, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {\
                                          fprintf(stderr, "%s\n", mysql_error(connector));\
                                          exit(1);\
                                      }
#include <gtk/gtk.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/sql_fonctions.h"
#include "../headers/gtk_fonctions.h"

void fill_combobox_cat(GtkComboBoxText *combo){

  char *query = "SELECT * FROM category";
    MYSQL_RES *result;
    MYSQL_ROW data;
    MYSQL* conn;
    PREPARE_CONNECTION(conn);

    if( !mysql_query(conn , query) ){

        result = mysql_store_result(conn);

        while( (data = mysql_fetch_row(result) ) != NULL){
            gtk_combo_box_text_append(combo , data[0] , data[1] );
        }

    }else{
        fprintf(stderr, "An error occured : \n%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_free_result(result);
    mysql_close(conn);

}

void fill_combobox_store(GtkComboBoxText *combo){
    char *query="select * from store order by name asc";
    MYSQL_RES *result;
    MYSQL_ROW data;
    MYSQL* conn;
    PREPARE_CONNECTION(conn);

    if( !mysql_query(conn , query) ){

        result = mysql_store_result(conn);

        while( (data = mysql_fetch_row(result) ) != NULL){
            gtk_combo_box_text_append(combo , data[0] , data[1] );
        }

    }else{
        fprintf(stderr, "An error occured : \n%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_free_result(result);
    mysql_close(conn);
}