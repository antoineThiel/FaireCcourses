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


int log_in(const gchar *id, const gchar *pass);
void add_product(const gchar* param, const gchar* param2, const gchar* param3) ;
void get_product(GtkWidget *widget, GtkWidget **array);
