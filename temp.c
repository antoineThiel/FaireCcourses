#include "headers/all.h"


MYSQL* CONNECTOR_DB;
GtkBuilder* MAIN_BUILDER;

SESSION USER_DATA;


int main(){
  FILE_representation tmp = read_config("shops_config/model.model");
  Graph* market_graph;
  __int32_t* steps_needed = NULL;
  
  market_graph = createGraph(&tmp);
  file_rep_destroy(&tmp);


  steps_needed = createStepsArray(market_graph);

  free(market_graph);
  free_graph(market_graph);

  for(__uint16_t i = 0 ; i < market_graph->width_of_it ; i++){
    printf("step %u : %u\n" , i , steps_needed[i]);
  }

  free(steps_needed);

  return 0;
}