//void fill_combobox_cat(MYSQL_ROW *data);

typedef struct builder_and_conn builder_and_conn;

struct builder_and_conn{
    
    GtkBuilder *builder;
    MYSQL* conn;

};