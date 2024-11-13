#include <gtk/gtk.h>

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
GtkWidget *window;
GtkWidget *label;

window = gtk_application_window_new(app);
gtk_window_set_default_size(GTK_WINDOW(window), 200, 100); // Set window size
gtk_window_set_title(GTK_WINDOW(window), "My Calculator"); // Set window title

label = gtk_label_new("Hello World");
gtk_container_add(GTK_CONTAINER(window), label); // Add label to window

gtk_widget_show_all(window); // Show all widgets including the label
}

// This is the main function - the entry point of our program
// argc: counts how many arguments were passed when running the program
// argv: array of strings containing those arguments
int
main (int    argc,
      char **argv)
{
    // Declare a pointer to store our GTK application
    GtkApplication *app;
    // Variable to store the exit status of our program
    int status;

    // Create a new GTK application
    // "org.gtk.example" is the application ID (like a unique name)
    // G_APPLICATION_DEFAULT_FLAGS means use normal default settings
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);

    // Connect a signal (like an event listener)
    // When the app is "activated" (started), run the function named 'activate'
    // G_CALLBACK is used to convert the function into the right format
    // NULL means we're not passing any extra data to the activate function
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    // Actually run the application
    // G_APPLICATION(app) converts our GTK app into a basic application type
    // Returns an exit status code (0 usually means success)
    status = g_application_run (G_APPLICATION (app), argc, argv);

    // Clean up the memory used by our app
    g_object_unref (app);

    // Return the status code to the operating system
    return status;
}