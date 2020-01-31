//~~~~~~~~~~~~~~~INCLUDES~~~~~~~~
    #include "../../headers/all.h"


//~~~~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~~~
extern MYSQL* CONNECTOR_DB;
extern GtkBuilder* MAIN_BUILDER;

void fill_combobox_cat(GtkComboBoxText *combo){

  char *query = "SELECT * FROM category";
    MYSQL_RES *result;
    MYSQL_ROW data;
    if( !mysql_query(CONNECTOR_DB , query) ){

        result = mysql_store_result(CONNECTOR_DB);

        while( (data = mysql_fetch_row(result) ) != NULL){
            gtk_combo_box_text_append(combo , data[0] , data[1] );
        }

    }else{
        fprintf(stderr, "An error occured : \n%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }

    mysql_free_result(result);

}

void fill_combobox_store(GtkComboBoxText *combo){
    char *query="select * from store order by name asc";
    MYSQL_RES *result;
    MYSQL_ROW data;

    if( !mysql_query(CONNECTOR_DB , query) ){

        result = mysql_store_result(CONNECTOR_DB);

        while( (data = mysql_fetch_row(result) ) != NULL){
            gtk_combo_box_text_append(combo , data[0] , data[1] );
        }

    }else{
        fprintf(stderr, "An error occured : \n%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }

    mysql_free_result(result);
}