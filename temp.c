#include "headers/all.h"


MYSQL* CONNECTOR_DB;
GtkBuilder* MAIN_BUILDER;

SESSION USER_DATA;


int main(){
  FILE_representation tmp = read_config("shops_config/model.model");
  __uint16_t* market_graph;

  market_graph = createGraph(&tmp);
  
  
  file_rep_destroy(&tmp);
  free(market_graph);

  return 0;
}