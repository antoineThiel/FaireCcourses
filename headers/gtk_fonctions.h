//~~~~~~~~~~~~DEFINES~~~~~~~~~~~~
    #define SERVER "localhost"
    #define USER "root"
    #define PASSWORD "root"
    #define DATABASE "project"
    #define PREPARE_CONNECTION(connector) connector = mysql_init(NULL);\
                                      if (!mysql_real_connect(connector, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {\
                                          fprintf(stderr, "%s\n", mysql_error(connector));\
                                          exit(1);\
                                          }
//


void fill_combobox_cat(GtkComboBoxText *combo);
void fill_combobox_store(GtkComboBoxText *combo);

void win_add_product(GtkWidget *widget);
void get_product(GtkWidget *widget, GtkWidget **array);
void win_show_order(GtkWidget *widget);

char** get_id(const gchar *store);
char** get_product_id(const gchar *product);
char** get_product_list(const gchar *product);
void start_order(MYSQL_ROW data);
void increase(GtkWidget *widget, GtkWidget *label);
void decrease(GtkWidget *widget, GtkWidget *label);
void def_add_cart(gchar *id_order,char *id_product, const gchar *quantity);
void add_to_cart(GtkWidget *widget, GtkWidget **array);
void display_search(GtkWidget *widget, GtkWidget **array);
void win_shopping(void);
void get_store(GtkWidget *widget, GtkWidget *combo);
void win_chose_store(GtkWidget *widget);

void get_log(GtkWidget * widget, GtkWidget **array);
void win_log_in(GtkWidget *widget);
void modify_log_text(void);




















struct SESSION{
    int IS_CONNECTED; // initially disconnected
    char* CURRENT_SHOP;
    int ORDER_STARTED; //Check if the order is started duh
    char* ORDER_NUMBER;
    int ADMIN; //allows =/= rights
    GtkWidget *CURRENT_GRID;
};

typedef struct SESSION SESSION;


void session_init(SESSION* data);
