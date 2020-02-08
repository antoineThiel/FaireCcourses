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
    char* CURRENT_SHOP;
    int ORDER_STARTED; //Check if the order is started duh
    char* ORDER_NUMBER;
    int ADMIN; //allows =/= rights
    GtkWidget *CURRENT_GRID;
};

typedef struct SESSION SESSION;


void session_init(SESSION* data);
