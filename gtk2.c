#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}
static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *grid;
  GtkWidget *button_box;
  GtkWidget *entry;
  //Création de la fenêtre
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_container_set_border_width (GTK_CONTAINER (window) ,10);

  //Grid added that contains our buttons
  grid = gtk_grid_new();
  gtk_container_add( GTK_CONTAINER (window), grid);


  /*Button box (container) added & added to the window
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box); */

  entry = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 2, 2,1);
  gtk_entry_set_text(entry, "bonjour");

  //Label added to the button
  button = gtk_button_new_with_label ("Ajouter");

  //place the first buuton in the grid cell (0,0)
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);
  
  //2nd button
  button = gtk_button_new_with_label ("Retirer");
  gtk_grid_attach (GTK_GRID (grid), button, 1,0,1,1);

  //3rd button
  button = gtk_button_new_with_label ("quit");
  //Function of the button added
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 0,1,2,1);

  //Affichage du total
  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}