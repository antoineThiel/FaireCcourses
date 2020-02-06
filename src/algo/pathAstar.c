#include "../../headers/all.h"

void read_config(const char* filepath){
    __uint8_t* shop;

    FILE* file = fopen(filepath , "rb");
    check_fopen(file);


    FILE_representation config = get_config(file);
    config.shop_file = file;


    // printf("%lu et  %lu \n" , config.height , config.width);

    shop = malloc(config.height * config.width);
    check_malloc(shop);

    fill_shop_model(shop , &config);

    free(shop);
    fclose(file);
}



FILE_representation get_config(FILE* pf){

    FILE_representation config;
    char info[10];
    char dimensions[5];
    __uint8_t size_height = 0 , size_width = 0;


    fread(info , sizeof(char) , 10 , pf);

    while(size_width++ , is_whitespace(info[size_width]));
    config.width = atoi(strncpy(dimensions , info , size_width) );

    // info = info + size_width+1; //moving next search to the char after the whitespace

    while(size_height++ , is_whitespace(info[size_width + 1 +size_height]));
    config.height = atoi(strncpy(dimensions , info , size_height) );

    return config;



}

void fill_shop_model(__uint8_t* array_market , FILE_representation* infos){

    __uint8_t* oneline = malloc(sizeof(bool) * infos->width);
    check_malloc(oneline);


    fseek(infos->shop_file , 0 , SEEK_SET);
    for(__uint8_t rows = 0 ; rows < infos->height ; rows++){
        fread(oneline , sizeof(__uint8_t) , infos->width , infos->shop_file );

        for(__uint8_t cols = 0 ; cols < infos->width ; cols++){
            array_market[rows * infos->width + cols] = oneline[cols] - atoi("0");
        }
        fseek(infos->shop_file , 1 , SEEK_CUR); //skipping newline char 
    }
}