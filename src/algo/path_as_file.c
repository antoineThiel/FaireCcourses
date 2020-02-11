//~~~~~~~~~INCLUDES~~~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

// extern GtkBuilder* MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;


list_ids* get_product_list_from_cart(){
    char query[200];

    list_ids* returned = malloc(sizeof(list_ids));
    check_malloc(returned);

    __int32_t* product_ids;
    __uint16_t push = 0; // last pos to put new data to product_ids
    my_ulonglong cart_size = 0;
    MYSQL_RES* result_set;
    MYSQL_ROW db_line;

    sprintf(query , "SELECT id_product from product_order WHERE id_order = %d" , ORDER_DATA.ORDER_NUMBER);

    if(mysql_real_query(CONNECTOR_DB , query , strlen(query))){
        fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }
    result_set = mysql_store_result(CONNECTOR_DB);
    cart_size = mysql_num_rows(result_set);

    product_ids = malloc(sizeof(__uint16_t) * cart_size);

    while( (db_line = mysql_fetch_row(result_set)  ) != NULL){
        product_ids[push] = atoi(db_line[0]) ;
        push++;

        // printf("id vaut : %u \n" , product_ids[push-1]);
    }

    returned->id = product_ids;
    returned->length = cart_size;
    return returned;
}

list_ids* get_category_list_from_cart(){
    
    list_ids* product_ids = get_product_list_from_cart();

    list_ids* shelf_order = malloc(sizeof(list_ids));
    check_malloc(shelf_order);

    shelf_order->id = malloc(sizeof(__int32_t) * product_ids->length) ; // can't have MORE than `length` categories since we have `length` products
    check_malloc(shelf_order->id);

    __uint16_t last_pos = 0;

    char query[200];
    MYSQL_RES* result_set;
    MYSQL_ROW db_line;


    for(__uint16_t i =0 ; i < product_ids->length ; i++){

        sprintf(query , "SELECT shelf_order from shelf "
                            "WHERE category =  "
                            "(SELECT id from category "
                                "WHERE name = "
                                "(SELECT category from product WHERE id = %d LIMIT 1))" ,
                product_ids->id[i]);

        if( mysql_real_query(CONNECTOR_DB , query , strlen(query) )  ){
            fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
            exit(1);
        }
        result_set = mysql_store_result(CONNECTOR_DB);

        db_line = mysql_fetch_row(result_set);

        if(!already_visited(shelf_order->id , (__uint16_t)atoi(db_line[0]) , last_pos ) ) {

            shelf_order->id[last_pos] = atoi(db_line[0]);
            last_pos++;
        }
    }
    free(product_ids->id);
    free(product_ids);

    shelf_order->length = last_pos;

    return shelf_order;
}



