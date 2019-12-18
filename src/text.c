#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}


int main( int   argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *check;
    gint tmp_pos;

    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 200, 100);
    gtk_window_set_title (GTK_WINDOW (window), "GTK Entry");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event", G_CALLBACK (gtk_widget_destroy), window);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate", G_CALLBACK (enter_callback), entry);

    //Placeholder
    gtk_entry_set_text (GTK_ENTRY (entry), "hello");

    tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(entry));

    gtk_editable_insert_text (GTK_EDITABLE (entry), " world", -1, &tmp_pos);

    //We don't know
    //gtk_editable_select_region (GTK_EDITABLE (entry), 0, gtk_entry_get_text_length(GTK_ENTRY(entry)));

    //Ajoute l'input au groupe vbox et l'affiche
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

  
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox); 

      /* il existe un stock de button*/                             
    button = gtk_button_new_from_stock (GTK_STOCK_OPEN);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
    gtk_widget_set_can_default (button, TRUE);
    gtk_widget_grab_default (button);
    gtk_widget_show (button);
    
    gtk_widget_show (window);

    gtk_main();

    return 0;
}