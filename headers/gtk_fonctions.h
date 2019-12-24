typedef struct builder_and_conn builder_and_conn;

struct builder_and_conn{
    
    GtkBuilder *builder;
    MYSQL* conn;

};

void fill_combobox_cat(MYSQL *conn , GtkComboBoxText *combo);
