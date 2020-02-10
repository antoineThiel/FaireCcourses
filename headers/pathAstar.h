typedef struct FILE_representation{

    //qty of bits / line
    size_t width;
    //qty of lines
    size_t height; 

    FILE* shop_file;

    __uint8_t* aisle;

    __uint16_t checkpoints_max;

}FILE_representation;

typedef struct checkpoint{
    __uint16_t pos_x;
    __uint16_t pos_y; 
}checkpoint;

typedef struct Graph{
    __uint16_t* distance_array;
    __uint16_t width_of_it;
    checkpoint* arrayChecks;
}Graph;

FILE_representation read_config(const char* filepath);

//returns a struct FILE_rep from file , with struct.width and height fields filled
FILE_representation get_config(FILE* pf);

void fill_shop_model(FILE_representation* infos);

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

//generates a graph from a 2D "map"
Graph* createGraph(FILE_representation* file_rep);

//returns distance (in ~~blocs) between 2 chechpoints given
__uint16_t distance_between(checkpoint first , checkpoint second);

//returns 1D array of sorted shelfs to go to
__int32_t* createStepsArray(Graph* graph);

//return index from graph.checkpoint where distance is min
__uint16_t search_index_of_min_in_line(Graph* graph , __uint16_t line , __int32_t* already_checked);

//frees needed fields of Graph
void free_graph(Graph* market_graph);


 
