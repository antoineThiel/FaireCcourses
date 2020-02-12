typedef struct list_ids{
    __int32_t* id;
    __uint16_t length;
}list_ids;

typedef struct pixel_t{
    __uint8_t red;
    __uint8_t green;
    __uint8_t blue;

}pixel_t;


void ppm_file_from_stepArray(const FILE_representation* origin , __uint16_t* stepArray);
list_ids* get_product_list_from_cart(void);
list_ids* get_category_list_from_cart(void);

void file_ppm(FILE_representation* file_rep , __int32_t* steps_needed , checkpoint* graph);

//modifies file_rep to likely generate the path 
void trace_line_on_filerep(FILE_representation* file_rep , checkpoint origin , checkpoint end , __uint8_t value_to_set);

//literally create the final file , fiou
void ppm_file_from_filerep(const FILE_representation* origin);


#define RATIO_IMG 15
#define NOTICEABLE_VALUE 10