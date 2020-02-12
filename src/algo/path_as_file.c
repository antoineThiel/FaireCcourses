//~~~~~~~~~INCLUDES~~~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

    extern MYSQL* CONNECTOR_DB;
    // extern SESSION USER_DATA;
    extern ORDER ORDER_DATA;
    extern list_ids* REQUIRED_SHELFS;

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

void file_ppm(FILE_representation* file_rep ,__int32_t* steps_needed , checkpoint* pos_shelves){
    // checkpoint tmp_coord;

    //setting used shelves to a noticeable value and linking shelves , entrance and exit are included
    for(__uint16_t pos = 0 ; pos <= REQUIRED_SHELFS->length ; pos++){
        trace_line_on_filerep(file_rep ,pos_shelves[steps_needed[pos]],
                                        pos_shelves[steps_needed[pos+1]],
                                        NOTICEABLE_VALUE+pos);
    
    }
    ppm_file_from_filerep(file_rep);
    get_file_rep(file_rep);
}

void trace_line_on_filerep(FILE_representation* file_rep , checkpoint origin , checkpoint end , __uint8_t value_to_set){

    __int8_t horizontal_move; // origin more or less right than end 
    __int8_t vertical_move; //
    
    checkpoint copy = origin;

    if( origin.pos_x > end.pos_x)
        horizontal_move = -1;
    else if (  origin.pos_x == end.pos_x)
        horizontal_move = 0;
    else
        horizontal_move = 1;

    if( origin.pos_y > end.pos_y)
        vertical_move = -1;
    else if (  origin.pos_y == end.pos_y)
        vertical_move = 0;
    else
        vertical_move = 1;

    // printf("origin : %hhu \\ %hhu   end : %hhu \\ %hhu\n" , origin.pos_x ,origin.pos_y , end.pos_x , end.pos_y);
    // printf("h : %hhd , v : %hhd \n" , horizontal_move , vertical_move);
    
    // while(origin.pos_x != end.pos_x && origin.pos_y != end.pos_y){
    //     origin.pos_x += horizontal_move;
    //     origin.pos_y += vertical_move;

    //     file_rep->aisle[origin.pos_y * file_rep->width + origin.pos_x] = value_to_set;
    // }

    //might not go through this one or the other one , because 1 statement was used to break the loop above (: 
    while (copy.pos_x != end.pos_x){
        copy.pos_x += horizontal_move;

        file_rep->aisle[copy.pos_y * file_rep->width + copy.pos_x] = value_to_set;
    }
    
    while(copy.pos_y != end.pos_y){
        copy.pos_y += vertical_move;
        file_rep->aisle[copy.pos_y * file_rep->width + copy.pos_x] = value_to_set;

    }
}


void ppm_file_from_filerep(const FILE_representation* origin){
    FILE* new_file = fopen("result.ppm" , "wb");
    check_fopen(new_file);

    pixel_t pixel_tmp = {0,0,0};
    char config[30];
    __uint8_t cell_content;
    fseek(new_file , 0 , SEEK_SET);

    sprintf(config , "P6\n%lu %lu\n255\n", origin->width * RATIO_IMG, origin->height * RATIO_IMG);

    fwrite(config , sizeof(char) , strlen(config) , new_file );

    for(size_t i = 0 ; i < origin->height ; i++){
        for(__int8_t loop1 = 0 ; loop1 < RATIO_IMG ; loop1++){

            for(size_t j = 0 ; j < origin->width ; j++){
                for(__int8_t loop2 = 0 ; loop2 < RATIO_IMG ; loop2++){
                    cell_content = origin->aisle[i * origin->width + j];

                    if(cell_content >= NOTICEABLE_VALUE){
                        pixel_tmp.red   = 20 * cell_content;
                        pixel_tmp.green = 12 * cell_content;
                        pixel_tmp.blue  = 50 * cell_content;
                    }
                    else{
                        pixel_tmp.red   = 255;
                        pixel_tmp.green = 255;
                        pixel_tmp.blue  = 255;
                    }


                    fwrite(&pixel_tmp , sizeof(u_int8_t) , 3 , new_file);
                }
            }
        }
    }

    fclose(new_file);
}
