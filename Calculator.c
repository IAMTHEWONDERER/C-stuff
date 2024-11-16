#include <gtk/gtk.h>
#include <stdio.h>

// Function that handles the button click event
static void on_button_clicked(GtkWidget *button, gpointer data) {
    GtkWidget *entry = GTK_WIDGET(data);
    const char *input_text = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Button clicked: %s\n", input_text);
    GtkWidget *label = g_object_get_data(G_OBJECT(button), "label");
    gtk_label_set_text(GTK_LABEL(label), input_text);
}

// Function that handles the Enter key press event
static gboolean on_entry_key_press(GtkWidget *entry, GdkEventKey *event, gpointer data) {
    // Check if the pressed key is Enter
    if (event->keyval == GDK_KEY_Return || event->keyval == GDK_KEY_KP_Enter) {
        GtkWidget *button = GTK_WIDGET(data);
        g_signal_emit_by_name(button, "clicked"); // Simulate button click
        return TRUE; // Stop further handling of the key event
    }
    return FALSE; // Allow other key events to propagate
}

// Activate function
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget *label;
    GtkWidget *button;

    // Create main window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "INPUT AND OUTPUT");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    // Create a vertical box layout
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create the entry widget
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "ENTER TEXT PLEASE");
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);

    // Create the label widget
    label = gtk_label_new("OUTPUT");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

    // Create the button widget
    button = gtk_button_new_with_label("CLICK ME");
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    // Link the button and label for the click event
    g_object_set_data(G_OBJECT(button), "label", label);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);

    // Connect the entry key press event to the Enter handler
    g_signal_connect(entry, "key-press-event", G_CALLBACK(on_entry_key_press), button);

    // Show all widgets
    gtk_widget_show_all(window);
}

// Main function
int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
