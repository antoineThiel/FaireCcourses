//~~~~~~~~~INCLUDES~~~~~~~~~~~~
  #include "../../headers/all.h"


//~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~~
extern GtkBuilder* MAIN_BUILDER;
extern SESSION USER_DATA;


void get_product(GtkWidget *widget, GtkWidget **array){
  
  const gchar *a, *b;
  GtkWidget *entry = array[0];
  GtkWidget *combo = array[1];

  a = gtk_entry_get_text(GTK_ENTRY (entry));
  b = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo));
  
  (void)widget; //Equivaut a windget = widget
  
  add_product(a,b);
}

void win_add_product(GtkWidget *widget){

    GtkWidget **array;
    GtkWidget *combo;
    GtkWidget *entry;

    GtkWidget *grid;
    GtkWidget *grid_content;
    GtkWidget *button;
    GtkWidget *label;

    if(USER_DATA.IS_CONNECTED){
    array = malloc(2 * sizeof(GtkWidget));
    check_malloc(array);
    
    grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));
    
    if (USER_DATA.CURRENT_GRID != NULL)
    {
      gtk_widget_destroy(USER_DATA.CURRENT_GRID);
    }
    else{
      gtk_grid_remove_column(GTK_GRID(grid), 1);
      gtk_grid_insert_column(GTK_GRID(grid), 1);
    }
    
    grid_content = gtk_grid_new();
    USER_DATA.CURRENT_GRID = grid_content;
    gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,2,3);

    button = gtk_button_new_with_label("Ajouter");
    entry = gtk_entry_new();
    combo = gtk_combo_box_text_new();

    label = gtk_label_new("Nom du produit");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);
    label = gtk_label_new("Categorie");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,1,1,1);

    fill_combobox_cat(GTK_COMBO_BOX_TEXT(combo));
    
    gtk_grid_attach(GTK_GRID(grid_content), button, 1,2,1,1);
    gtk_grid_attach(GTK_GRID(grid_content), entry, 1,0,1,1);
    gtk_grid_attach(GTK_GRID(grid_content), combo, 1,1,1,1);

    array[0] = entry;
    array[1] = combo; 

    g_signal_connect (button, "clicked", G_CALLBACK (get_product) , array);
    (void)widget;
    gtk_widget_show_all(grid_content);
  }
  else{ 
    print_error();
  }
}


