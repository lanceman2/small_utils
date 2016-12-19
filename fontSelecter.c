#include <gtk/gtk.h>

int main(int argc, char **argv)
{
  if(argc > 1) {
      printf("  Usage: %s\n"
        "\n"
        "  Display a GTK+3 font_chooser widget\n",
        argv[0]);
      return 1;
  }

  GtkWidget *w, *win;

  gtk_init(&argc, &argv);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  w = gtk_font_chooser_widget_new();
  gtk_container_add(GTK_CONTAINER(win), w);
  g_signal_connect(G_OBJECT(win), "delete-event", 
                    G_CALLBACK (gtk_main_quit), NULL);
  gtk_widget_show_all(GTK_WIDGET(win));

  gtk_main ();

  return 0;
}
