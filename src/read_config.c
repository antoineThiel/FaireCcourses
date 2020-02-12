#include "../headers/all.h"


char** launcher_config(void){
    FILE* config_file = fopen("config/config.txt" , "rb");
    check_fopen(config_file);

    char infos[1000];
    char** parameters = malloc(3 * sizeof(char*));
    check_malloc(parameters);


    // char* img_debt = NULL , *img_end = NULL;
    char* lang_pos = NULL;

    for(int i = 0 ; i < 3 ; i++){
        parameters[i] = malloc(sizeof(char)* 30);
        check_malloc(parameters[i]);
    }

    fseek(config_file , 0 , SEEK_SET);
    fread(infos , sizeof(char) , 500 , config_file);

    lang_pos = strstr(infos , ":ON");

    // parameters[ENCODING] = strcmp(lang_pos - 2 , "fr" ) == 0 ? "fr_FR.UTF-8" : "en_US.UTF-8";
    
    if( strncmp(lang_pos - 2 , "fr" , 2 ) == 0){
        parameters[ENCODING] = "fr_FR.UTF-8";
        parameters[MESSAGE] = "messages_fr";
    }
    else{
        parameters[ENCODING] = "en_US.UTF-8";
        parameters[MESSAGE] = "messages_en";
    }

    // img_debt = strstr(infos , "src:");
    // // img_end = strchr(img_debt , "\n");

    // strcpy(parameters[MESSAGE] , img_debt+4);
    // img_end = strchr(parameters[MESSAGE] , '\n');

    // (void)img_end;

    fclose(config_file);
    return parameters;

}