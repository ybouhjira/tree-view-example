#include <gtk/gtk.h>

static void init_list(GtkWidget *list)
{
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *nom, *prenom, *cne;
    GtkListStore *store;


    cne = gtk_tree_view_column_new_with_attributes("cne", renderer,
                                                      "text",
                                                      0, NULL);
    nom = gtk_tree_view_column_new_with_attributes("nom", renderer,
                                                      "text",
                                                      1, NULL);
    prenom = gtk_tree_view_column_new_with_attributes("prenom", renderer,
                                                      "text",
                                                      2, NULL);


    gtk_tree_view_append_column(GTK_TREE_VIEW(list), cne);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), nom);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), prenom);

    store = gtk_list_store_new(3, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    g_object_unref(store);
}

static void add_to_list(GtkWidget *list, const gchar *cne,
                        const gchar* nom, const gchar* prenom)
{
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model
                           (GTK_TREE_VIEW(list)));

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, cne, -1);
    gtk_list_store_set(store, &iter, 1, nom, -1);
    gtk_list_store_set(store, &iter, 2, prenom, -1);
}


void  on_changed(GtkWidget *widget, gpointer label)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *value;


    if (gtk_tree_selection_get_selected(
                GTK_TREE_SELECTION(widget), &model, &iter)) {

        gtk_tree_model_get(model, &iter, 0, &value,  -1);
        gtk_label_set_text(GTK_LABEL(label), value);
        g_free(value);
    }

}

int main (int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *list;

    GtkWidget *vbox;
    GtkWidget *label;
    GtkTreeSelection *selection;

    gtk_init(&argc, &argv);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 270, 250);
    gtk_window_set_title(GTK_WINDOW(window), "List View");

    list = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), TRUE);

    vbox = gtk_vbox_new(FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

    label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    init_list(list);
    add_to_list(list, "1257659734", "Bouhjira", "Youssef");
    add_to_list(list, "1257659734", "El Midaoui", "Ayoub");


    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(selection, "changed",
                     G_CALLBACK(on_changed), label);

    g_signal_connect(G_OBJECT (window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main ();

    return 0;
}
