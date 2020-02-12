
void fill_combobox_cat(GtkComboBoxText *combo);
void fill_combobox_store(GtkComboBoxText *combo);
void chose_cat(GtkWidget *widget, GtkWidget *combo);
// void win_add_product(GtkWidget *widget);
void get_product(GtkWidget *widget, GtkWidget **array);
void win_show_order(GtkWidget *widget);

char** get_id(const gchar *store);
char** get_product_id(const gchar *product);
char** get_product_list(const gchar *product);
void increase(GtkWidget *widget, GtkWidget *label);
void decrease(GtkWidget *widget, GtkWidget *label);
void def_add_cart(gchar *id_order,char *id_product, const gchar *quantity);
void add_to_cart(GtkWidget *widget, GtkWidget **array);
void display_search(GtkWidget *widget, GtkWidget *cat);
void win_shopping(void);
void get_store(GtkWidget *widget, GtkWidget *combo);
void win_chose_store(GtkWidget *widget);
MYSQL_RES* get_list(const gchar *category);
void get_log(GtkWidget * widget, GtkWidget **array);
void win_log_in(GtkWidget *widget);
void modify_log_text(void);
void win_see_product_1(GtkWidget *widget, GtkWidget *choice);
void validate_order();
void set_labels();
void set_img();
struct SESSION{
    int IS_CONNECTED; // initially disconnected
    int ADMIN; //allows =/= rights
    int ID_CUSTOMER;
};

struct ORDER{
    int CURRENT_SHOP;
    int ORDER_NUMBER;
    int TOTAL_PRICE;
    GtkWidget *CURRENT_GRID;
    GtkWidget *GRID_RESULTS;
    GtkWidget *BASKET;
    GtkWidget *PRICE;
    int SHOPPING;
    int BASKET_STAT;
    GtkWidget *BASKET_NAME;
};

typedef struct SESSION SESSION;
typedef struct ORDER ORDER;


void session_init(SESSION* data);
void order_init(ORDER* data);
