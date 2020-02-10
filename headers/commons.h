void print_error(void);

//make sure memory given to the pointer is well allocated
void check_malloc(void*);

//make sure FILE pointer was correctly returned
void check_fopen(FILE* );

//return 1 if char sent is a whitespace , 0 otherwise
bool is_whitespace(const char letter);

//searches if `to_find` is present in `reference` array , of size `width`
bool is_in(__uint16_t to_find , __int32_t* reference , __uint16_t width );
