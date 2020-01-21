void fill_combobox_cat(GtkComboBoxText *combo);
void fill_combobox_store(GtkComboBoxText *combo);

struct SESSION{
    int IS_CONNECTED; // initially disconnected
    char* CURRENT_SHOP;
};

typedef struct SESSION SESSION;


void session_init(SESSION* data);
