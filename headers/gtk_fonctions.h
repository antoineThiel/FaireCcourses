typedef struct builder_and_conn builder_and_conn;

struct builder_and_conn{
    
    GtkBuilder *builder;
    MYSQL* conn;

};

void fill_combobox_cat(MYSQL *conn , GtkComboBoxText *combo);

typedef struct conn_n_2_gtk_widget conn_n_2_gtk_widget;

struct conn_n_2_gtk_widget{
    
    GtkWidget *entry;
    GtkWidget *combo;
    //MYSQL* conn;
};

