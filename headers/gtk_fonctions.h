//
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

struct SESSION{
    int IS_CONNECTED; // initially disconnected
    int ADMIN; //allows =/= rights
    int ID_CUSTOMER;
};

struct ORDER{
    char* CURRENT_SHOP;
    char* ORDER_NUMBER;
    double TOTAL_PRICE;
    GtkWidget *CURRENT_GRID;
    GtkWidget *PRICE;
};

typedef struct SESSION SESSION;
typedef struct ORDER ORDER;


void session_init(SESSION* data);
void order_init(ORDER* data);
