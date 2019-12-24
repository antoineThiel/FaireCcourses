int log_in(const gchar *id, const gchar *pass);
MYSQL* prepare_conn(MYSQL *conn);
void add_product(MYSQL* ,  const gchar* , const gchar*) ;
void select_cat_options( MYSQL* , GtkComboBoxText* );
