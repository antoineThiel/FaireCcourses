typedef struct FILE_representation{

    //qty of bits / line
    size_t width;
    //qty of lines
    size_t height; 

    FILE* shop_file;

}FILE_representation;


void read_config(const char* filepath);
FILE_representation get_config(FILE* pf);

void fill_shop_model(__uint8_t* array_market , FILE_representation* info);
