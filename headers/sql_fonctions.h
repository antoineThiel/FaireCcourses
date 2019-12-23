int log_in(const gchar *id, const gchar *pass);
MYSQL* prepare_conn(MYSQL *conn);
void add_product(MYSQL *conn ,  const gchar *param, const gchar *param2) ;
MYSQL_ROW* select_cat_options( MYSQL *conn);
