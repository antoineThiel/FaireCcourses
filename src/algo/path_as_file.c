//~~~~~~~~~INCLUDES~~~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

// extern GtkBuilder* MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;


void ppm_file_from_stepArray(const FILE_representation* origin , __uint16_t* stepArray){
    FILE* new_file = fopen("result.ppm" , "wb");
    pixel_t pixel_tmp = {0,0,0};
    char config[30];

    sprintf(config , "P6\n%lu %lu\n255\n", origin->width , origin->height);

    fwrite(config , sizeof(char) , strlen(config) , new_file );

    for(size_t i = 0 ; i < origin->height ; i++){

        for(size_t j = 0 ; j < origin->width ; j++){
            // //recuperer pixel du tableau , (3x byte) --> ecrire 3 bytes dans fichier
            // pixel_tmp = ppm_get_pixel_at(origin , j , i);
            // fwrite(&pixel_tmp , sizeof(__uint8_t) , 3 , new_file);

            //ecrire le pixel contenu dans le tableau de pixel ,( réutiliser le TOS?)
        }
    }

    fclose(new_file);
}