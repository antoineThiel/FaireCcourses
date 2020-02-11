typedef struct list_ids{
    __uint16_t* id;
    __uint16_t length;
}list_ids;

typedef struct pixel_t{
    __uint8_t red;
    __uint8_t green;
    __uint8_t blue;

}pixel_t;


void ppm_file_from_stepArray(const FILE_representation* origin , __uint16_t* stepArray);
list_ids* get_product_list_from_cart(void);
__uint16_t* get_category_list_from_cart(void);

