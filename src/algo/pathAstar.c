//INCLUDES
    #include "../../headers/all.h"
//

//GLOBALS
    __uint16_t MARKET_ENTRANCE;
    __uint16_t MARKET_EXIT;
    list_ids* REQUIRED_SHELFS; 


    extern SESSION USER_DATA;
    extern MYSQL* CONNECTOR_DB;

//
FILE_representation read_config(const char* filepath){
    FILE_representation config = file_rep_init();
    FILE* file = fopen(filepath  , "rb");
    check_fopen(file);

    config = get_config(file);
    config.shop_file = file;
    file_rep_aisle_init(&config);

    fill_shop_model(&config);

    // get_file_rep(&config);

    fclose(file);
    return config;
}

FILE_representation get_config(FILE* pf){

    FILE_representation config;
    char info[10];
    char dimensions[5];
    __uint8_t /* size_height = 0 , */ size_width = 0;


    fread(info , sizeof(char) , 10 , pf);

    while( !is_whitespace(info[size_width]) && size_width < 8 ){
        size_width++;

    };


    config.width = atoi(strncpy(dimensions , info , size_width) );
    // config.width = atoi(info+size_width);

    // info = info + size_width+1; //moving next search to the char after the whitespace

    // while( !is_whitespace(info[size_width + 1 +size_height]) && size_height < 8){
    //     size_height++;
    // }

    // config.height = atoi(strncpy(dimensions , info + size_height , size_height) );

    config.height = atoi(info+size_width);

    return config;

}

void fill_shop_model(FILE_representation* infos){

    __uint8_t* oneline = malloc(sizeof(__uint8_t) * infos->width);
    check_malloc(oneline);

    __uint8_t pos_debut = get_file_debt(infos->shop_file);

    fseek(infos->shop_file , pos_debut , SEEK_SET);

    for(__uint8_t rows = 0 ; rows < infos->height ; rows++){

        fread(oneline , sizeof(__uint8_t) , infos->width+1 , infos->shop_file );  // width+1 to include the newline char
        // printf("%s\n" , oneline);
        for(__uint8_t cols = 0 ; cols < infos->width ; cols++){
            if( (infos->aisle[rows * infos->width + cols] = oneline[cols] - '0' ) > 1 ){
                infos->checkpoints_max++;
            }
        }

    }
    free(oneline);
}


FILE_representation file_rep_init(){
    FILE_representation returned= {0,0,NULL,NULL,0};
    return returned;
}

void file_rep_aisle_init(FILE_representation* rep){

    size_t size = rep->height * rep->width;
    rep->aisle = malloc(sizeof(__uint8_t) * size );
    check_malloc(rep->aisle);

    *rep->aisle = (__uint8_t){0};
    /* for(__uint8_t pos = 0 ; pos < size ; pos++){
        rep->aisle[pos] = 0;
    } */
    /* for(__uint8_t y = 0 ; y < rep->height ; y++){
        for( __uint8_t x = 0 ; x < rep->width ; x++){
            rep->aisle[y* rep->width + x] = 0 ;
        }
    } */

}

void get_file_rep(FILE_representation* f){
    printf("height : %lu width : %lu shop : %p  checkpoints : %u\n\n" , f->height , f->width , f->shop_file , f->checkpoints_max);
    /*printf("first %p last : %p\n", &f->aisle[0] , &f->aisle[f->height*f->width]);*/
    for(size_t y = 0 ; y < f->height ; y++){
        for(size_t x = 0 ; x < f->width ; x++){
            printf("%hhu  ", f->aisle[y*f->width+x]);
        }
        printf("\n");
    }
}

void file_rep_destroy(FILE_representation* f){
    free(f->aisle);
    // printf("aisle vide");
}

__uint8_t get_file_debt(FILE* pf){

    char config[20]; // assuming that 2 numbers + 2 \n won't reach over 20chars of space ^^
    __uint8_t nl_counter = 0;
    fseek(pf , 0 , SEEK_SET);

    fread(config , sizeof(char) , 20 , pf);

    for(__uint8_t pos = 0 ; pos < 20 ; pos++){
        if(is_whitespace(config[pos])){
            // ++nl_counter == 2 ? return pos : continue;
            nl_counter++;
            if(nl_counter == 3)return pos+1; // pos+1 because we skip the actual \n
        }
    }

    return 0;
}

void free_graph(Graph* market_graph){
    free(market_graph->arrayChecks);
    free(market_graph->distance_array);
}


Graph* createGraph(FILE_representation* file_rep){

    Graph* graph = malloc(sizeof(Graph));
    check_malloc(graph);

    size_t graph_dimension = file_rep->checkpoints_max;

    graph->width_of_it = graph_dimension;
    size_t graph_size = file_rep->checkpoints_max * file_rep->checkpoints_max;

    checkpoint* arrayChecks = malloc(sizeof(checkpoint)* graph_dimension);
    size_t pos_to_push = 0;
    __uint16_t* distances_graph = malloc(sizeof(__uint16_t)* graph_size);
    check_malloc(distances_graph);

    for(size_t y = 0 ; y < file_rep->height ; y++){
        for(size_t x = 0 ; x < file_rep->width ; x++ ){

            if(file_rep->aisle[y*file_rep->width + x] >= 2){
                arrayChecks[pos_to_push].pos_x = x;
                arrayChecks[pos_to_push].pos_y = y;

                if(file_rep->aisle[y*file_rep->width + x] == 3){
                    MARKET_ENTRANCE = pos_to_push;
                }
                else if(file_rep->aisle[y*file_rep->width + x] == 4){
                    MARKET_EXIT = pos_to_push;
                }
                pos_to_push++;
            }
        }
    }
    for(size_t y = 0 ; y < graph_dimension ; y++){
        for(size_t x = 0 ; x < graph_dimension ; x++){            
            distances_graph[x*graph_dimension + y] = distance_between(arrayChecks[y] , arrayChecks[x]);

            // printf("%u\t", distances_graph[x* graph_dimension + y]);
        }
        // printf("\n");
    }
    graph->distance_array = distances_graph;
    graph->arrayChecks = arrayChecks;
    return graph;
}

__uint16_t distance_between(checkpoint first , checkpoint second){
    __uint16_t distance = 0;
    checkpoint copy = {abs(second.pos_x - first.pos_x) , abs(second.pos_y - first.pos_y)};
    while(copy.pos_x > 0 && copy.pos_y > 0){
        copy.pos_x--;
        copy.pos_y--;
        distance += 3;
    }
    distance += (copy.pos_x + copy.pos_y) *2;

    return distance;
}

__uint16_t search_index_of_min_in_line(Graph* graph , __uint16_t line , __int32_t* already_checked){

    __uint16_t min_dist = 65535; // MAX_OF_UINT_16 (thought of -1 but ???)^^
    __uint16_t index = 0 ;

    for(__uint16_t pos = 0 ; pos < graph->width_of_it ; pos++ ){

        //order of statement is pure algorithm/self appreciation deppending of data consumed
        if(graph->distance_array[line * graph->width_of_it + pos] > 0){
            if(graph->distance_array[line * graph->width_of_it + pos] < min_dist){
                if(already_visited( already_checked , pos , graph->width_of_it) || !already_visited(REQUIRED_SHELFS->id , pos , REQUIRED_SHELFS->length)){ //"index" already passed by : skip loop's round , no already passed by :
                    continue;
                }
                // else{
                //     min_dist = min_dist_tmp;
                //     index = index_tmp;
                // }
                min_dist = graph->distance_array[line * graph->width_of_it + pos];
                index = pos;

            }
        }

    }

    return index;
}


__int32_t* createStepsArray(Graph* graph){

    __int32_t* visited_shelf = malloc( (REQUIRED_SHELFS->length+2) * sizeof(__int32_t)); //avoid initializing it :)))
    check_malloc(visited_shelf);
    memset(visited_shelf , -1 , (REQUIRED_SHELFS->length+2) * sizeof(__int32_t) ) ;

    list_ids *required_shelf = get_category_list_from_cart();
    for(int i = 0 ; i < required_shelf->length ; i++){
        printf("requiredshelf %d  : shelf nb %d \n" , i , required_shelf->id[i]);
    }
    __uint16_t new_step ; //index to put new step in follow steps
    __uint16_t  current_line = MARKET_ENTRANCE ;

    //begining is obviously the entrance , and last... is the exit :)
    visited_shelf[0] = MARKET_ENTRANCE;
    visited_shelf[REQUIRED_SHELFS->length +1] = MARKET_EXIT;  // no -1 needed because [0] is filled // +1 because visitedshelf.length == requiredshelves.length + 2
    printf("\n");
    for( new_step = 1 ; new_step <= REQUIRED_SHELFS->length ; new_step++ ){

        visited_shelf[new_step] = search_index_of_min_in_line(graph , current_line , visited_shelf); // add closest point to visited cities
        current_line = visited_shelf[new_step];
        printf("%u \n" , current_line);
    }

    return visited_shelf;

}

bool already_visited(const __int32_t * visited_ones , __uint16_t shelf , __uint16_t size_array){
    for(__uint16_t i = 0 ; i < size_array ; i++){
        if(shelf == visited_ones[i]) return 1;
    }
    return 0;

}

void generateSchema(void){
    FILE_representation tmp = read_config("shops_config/model.model");
    Graph* market_graph;
    __int32_t* steps_needed = NULL;

    REQUIRED_SHELFS = get_category_list_from_cart();

    market_graph = createGraph(&tmp);
    file_rep_destroy(&tmp);


    steps_needed = createStepsArray(market_graph);

    steps_needed = realloc(steps_needed , sizeof(__int32_t) * REQUIRED_SHELFS->length);

    for(__uint16_t i = 0 ; i < REQUIRED_SHELFS->length + 2; i++){ //+2 : entrance and exit are not considered as REQUIRED_SHELVES
        printf("step %u : %u\n" , i , steps_needed[i]);
    }

    free_graph(market_graph);
    free(market_graph);

}
