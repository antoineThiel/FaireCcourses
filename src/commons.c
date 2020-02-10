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

bool is_whitespace(const char letter){
    // whitespace? 1 : 0  (translation ;) )
    return strchr(" \t\n\v\f\r" , letter) != NULL ;
}

bool is_in(__uint16_t to_find , __int32_t* reference , __uint16_t width ){
    for(__uint16_t inside = 0 ; inside < width ; inside++){
        if( reference[inside] == to_find ){
            return 1;
        }
    }
    printf("ouiii\n");
    return 0; // not found
}