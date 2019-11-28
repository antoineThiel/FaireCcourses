#include <mysql.h>
#include <stdio.h>
#include <string.h>

char* get_input(char* param){
    fgets(param, 50, stdin);
    strtok(param, "\n");
    return param;
}

int main() {
    MYSQL *conn;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "project";
    char *start;
    char *param;
    char input[50];
    char quote[2]="\"";
    char param2[50];

    //Rserve memory
    start = malloc(sizeof(char)*200);
    
    //initializing query
    strcpy(start, "insert into product values(NULL");
    strcat(start, ",");
    strcat(start, quote);

    //Get name of the product
    printf("\nQuel est le nom du produit que vous souhaitez ajouter ?");
    param = get_input(input);

    //add quotes & comma
    strcat(start, param);
    strcat(start, quote);
    strcat(start, ",");
    strcat(start, quote);

    //Get the category
    printf("\nDe quelle catégorie fait il partie ?");
    param = get_input(input);

    //Finishing Query
    strcat(start, param);
    strcat(start, quote);
    strcat(start, ")");

    //Initalizing connection with bdd
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    //Query to add a product
    if (mysql_query(conn, start)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    //Close connection
    mysql_close(conn);
    //Free memory
    free(start);

    return 0;
    }