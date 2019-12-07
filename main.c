/* Simple C program that connects to MySQL Database server*/
#include <mysql.h>
#include <stdio.h>

int main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = "localhost";
   char *user = "root";
   char *password = "root"; /* set me first */
   char *database = "project";

   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   send SQL query 
   if (mysql_query(conn, "select * from product")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   

   res = mysql_use_result(conn);
   
   output table name 
   printf("MySQL Tables in mysql database:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);

   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
   return 0;
}