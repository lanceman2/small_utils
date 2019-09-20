#include <stdio.h>
#include <libgen.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
  if(argc > 1) {
      printf("  Usage: %s\n"
        "\n"
        "  Display a GTK+2 color_selection widget\n",
        argv[0]);
      return 1;
  }

  GtkWidget *colorWidget, *win;

 /* Initialize the widget set */
  gtk_init(&argc, &argv);

  colorWidget = gtk_color_selection_new();
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_container_add(GTK_CONTAINER(win), colorWidget);

  g_signal_connect(GTK_OBJECT(win), "delete-event", 
                    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_show_all(GTK_WIDGET(win));

  /* Enter the main event loop, and wait for user interaction */
  gtk_main ();

  return 0;
}
