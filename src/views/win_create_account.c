//~~~~~~~~~INCLUDES~~~~~~~~~~~~~
  #include "../../headers/all.h"

//~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~

extern GtkBuilder* MAIN_BUILDER;
extern MYSQL* CONNECTOR_DB;
extern SESSION USER_DATA;
extern ORDER ORDER_DATA;

void create_account(const gchar *username, const gchar *password){
    char start[255];
    sprintf(start, "insert into customer values(NULL, '%s', '%s', 0, 0)", username, password);
    if (mysql_query(CONNECTOR_DB, start)) {
        fprintf(stderr, "%s\n", mysql_error(CONNECTOR_DB));
        exit(1);
    }
}

void verif_creation(GtkWidget *widget, GtkWidget **logs){
    const gchar *username;
    const gchar *password;
    GtkWidget *entry_name = logs[0];
    GtkWidget *entry_pass = logs[1];

    username = gtk_entry_get_text(GTK_ENTRY(entry_name));
    password = gtk_entry_get_text(GTK_ENTRY(entry_pass));
    
    create_account(username, password);
    
    win_log_in(NULL);
    (void) widget;
}

void win_create_account(GtkWidget *widget){
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *button;
    GtkWidget *entry;
    GtkWidget *entry1;
    GtkWidget *grid_content;
    GtkWidget **logs;

    logs = malloc(2*sizeof(GtkWidget));

    event_handler();

    grid = GTK_WIDGET(gtk_builder_get_object(MAIN_BUILDER, "base_grid"));

    gtk_grid_remove_column(GTK_GRID(grid), 2);
    grid_content = gtk_grid_new();
    ORDER_DATA.CURRENT_GRID = grid_content;
    gtk_grid_attach(GTK_GRID(grid), grid_content, 1,0,5,5);

    label = gtk_label_new("Username :");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,0,1,1);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_content), entry, 1,0,1,1);

    logs[0] = entry;

    label = gtk_label_new("Password : ");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,1,1,1);

    entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_content), entry1, 1,1,1,1);

    logs[1] = entry1;

    label = gtk_label_new("Age (Pour des raisons statistiques): ");
    gtk_grid_attach(GTK_GRID(grid_content), label, 0,2,1,1);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid_content), entry, 1,2,1,1);

    button = gtk_button_new_with_label("Confirmer la création");
    gtk_grid_attach(GTK_GRID(grid_content), button, 0, 3, 2, 1);



    g_signal_connect(button, "clicked", G_CALLBACK(verif_creation), logs);
    
    gtk_widget_show_all(grid_content);
    widget = widget;
}