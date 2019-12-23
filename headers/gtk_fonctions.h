typedef struct builder_and_conn builder_and_conn;

struct builder_and_conn{
    
    GtkBuilder *builder;
    MYSQL* conn;


};