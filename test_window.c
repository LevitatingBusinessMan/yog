#include <gtk/gtk.h>
//https://www.freedesktop.org/wiki/Specifications/wm-spec/ not supported by i3wm
//https://specifications.freedesktop.org/notification-spec/notification-spec-latest.html
int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
  GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkWidget* label = gtk_label_new ("This is the body of the notification....");
  gtk_container_add (GTK_CONTAINER (window), label);

  gint window_width = 200;
  gint window_height = 50;
  gint margin = 10;

  gtk_window_set_default_size (GTK_WINDOW (window), window_width, window_height);
  gtk_window_set_decorated (GTK_WINDOW (window), TRUE);
  gtk_window_set_title (GTK_WINDOW (window), "Notification");
  //gtk_window_set_gravity (GTK_WINDOW (window), GDK_GRAVITY_STATIC);

  GdkScreen* screen = gdk_screen_get_default ();
  GdkDisplay* display = gdk_display_get_default();
  GdkMonitor *monitor = gdk_display_get_primary_monitor (display);
  GdkRectangle geometry;

  gdk_monitor_get_geometry (monitor, &geometry);

  gtk_window_get_size (GTK_WINDOW (window), &window_width, &window_height);
  
  printf("%dx%d\n", window_width, window_height);

  gtk_window_move (GTK_WINDOW (window), geometry.x + geometry.width - window_width - margin, margin);

  // DOCK is very cool and will create an actual dock on i3
  gtk_window_set_type_hint (GTK_WINDOW (window), GDK_WINDOW_TYPE_HINT_UTILITY);

  gtk_widget_show_all (window);
  
  gtk_main();
  return 0;
}