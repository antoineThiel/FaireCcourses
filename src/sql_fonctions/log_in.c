//~~~~~~~~~~INCLUDES~~~~~~~~~~~~
    #include "../../headers/all.h"

//~~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~~~~~
extern MYSQL* CONNECTOR_DB;
extern GtkBuilder* MAIN_BUILDER;

int log_in(const gchar *id, const gchar *pass){
    
  MYSQL_RES *result;
  int num_fields;

  char *start;
  char quote[2]="\"";

  start = malloc(sizeof(char)*200);
  check_malloc(start);

  strcpy(start, "select * from customer where username=");
  strcat(start, quote);
  strcat(start, id);
  strcat(start, quote);
  strcat(start, "and password=");
  strcat(start, quote);
  strcat(start, pass);
  strcat(start, quote);


  //Query to check_log_in
  if (mysql_query(CONNECTOR_DB, start)) {
      fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
      exit(1);
  }

  result = mysql_store_result(CONNECTOR_DB);
  num_fields = mysql_num_rows(result);

  if(num_fields == 0){ // failed
    free(start);
    return 0;
  }
  
    free(start);

  return 1;

}