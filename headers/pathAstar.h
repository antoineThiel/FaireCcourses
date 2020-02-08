typedef struct FILE_representation{

    //qty of bits / line
    size_t width;
    //qty of lines
    size_t height; 

    FILE* shop_file;

    __uint8_t* aisle;

}FILE_representation;


void read_config(const char* filepath);

//returns a struct FILE_rep from file , with struct.width and height fields filled
FILE_representation get_config(FILE* pf);

void fill_shop_model(FILE_representation* infos);

FILE_representation file_rep_init(void);

//prints all the fields of FILE_rep struct
void get_file_rep(FILE_representation* f);

//releases allocated memory of f
void file_rep_destroy(FILE_representation *f);

//fill file_rep aisle field all to 0
void file_rep_aisle_init(FILE_representation* rep);

//returns initialised FILE_rep with 0 for numeric fields and NULL for pointers
FILE_representation file_rep_init(void);

//returns pos of 1st byte defining the shop's aisles
__uint8_t get_file_debt(FILE* pf);
