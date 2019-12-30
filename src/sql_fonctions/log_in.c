 #include <stdio.h>
 #include <stdlib.h>
 #include <mysql.h>
 #include <string.h>
 #include <gtk/gtk.h>
 


int log_in(const gchar *id, const gchar *pass){
  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;
  int num_fields;

    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "project";
    char *start;
    char quote[2]="\"";

    start = malloc(sizeof(char)*200);

    strcpy(start, "select * from customer where username=");
    strcat(start, quote);
    strcat(start, id);
    strcat(start, quote);
    strcat(start, "and password=");
    strcat(start, quote);
    strcat(start, pass);
    strcat(start, quote);


    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    //Query to check_log_in
    if (mysql_query(conn, start)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    result = mysql_store_result(conn);
  num_fields = mysql_num_rows(result);
  if(num_fields == 0){
    //Close connection
    mysql_close(conn);
    //Free memory
    free(start);
    return 0;
  }
  
//Close connection
    mysql_close(conn);
    //Free memory
    free(start);

  return 1;

}