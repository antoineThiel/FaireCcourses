//~~~~~~~~~~~INCLUDES~~~~~~~~~~~
    #include "../../headers/all.h"
//    
void read_config(const char* filepath){
    FILE_representation config = file_rep_init();
    FILE* file = fopen(filepath  , "rb");
    check_fopen(file);

    config = get_config(file);
    config.shop_file = file;
    file_rep_aisle_init(&config);

    fill_shop_model(&config);

    get_file_rep(&config);

    file_rep_destroy(&config);
    fclose(file);

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
        printf("%s\n" , oneline); 
        for(__uint8_t cols = 0 ; cols < infos->width ; cols++){
            infos->aisle[rows * infos->width + cols] = oneline[cols] - '0';
        }

    }

    free(oneline);
}


FILE_representation file_rep_init(){
    FILE_representation returned= {0,0,NULL,NULL};
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
/*     printf("height : %lu width : %lu shop : %p \n\n" , f->height , f->width , f->shop_file);
    printf("first %p last : %p\n", &f->aisle[0] , &f->aisle[f->height*f->width]);*/
    for(size_t y = 0 ; y < f->height ; y++){
        for(size_t x = 0 ; x < f->width ; x++){
            printf("%hhu  ", f->aisle[y*f->width+x]);
        }
        printf("\n");
    }
}

void file_rep_destroy(FILE_representation* f){
    free(f->aisle);
    printf("aisle vide");
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


void find_path_to_product(char* product){
    (void)product;
}