//~~~~~~INCLUDES~~~~~~~~~~~
    #include "../headers/all.h"


void print_error(){
    g_print("you need to log in first\n");
}

void check_malloc(void* p){
    if(p == NULL){
        printf("error when allocating memory...");
        exit(1);
    }
}
void check_fopen(FILE* pf){
    if( pf == NULL){
        printf("error when oppening file...");
        exit(1);
    }
}