#include <gtk/gtk.h>

// struct Notification {
//   gint width;
//   gint height;
//   struct Notification* next;
// };

// static struct Notification* first_notification = NULL;

void on_size_allocate(GtkWidget* window) {
  gint width, height;
  gint margin = 10;
  gint titlebar = 20;
  GdkRectangle window_rectangle;
  gtk_window_get_size (GTK_WINDOW (window), &width, &height);
  printf("Size of widget %dx%d\n", width, height);

  printf("%d\n", gtk_widget_get_allocated_height(window));

  GdkDisplay* display = gdk_display_get_default();
  GdkMonitor *monitor = gdk_display_get_primary_monitor (display);
  GdkRectangle monitor_rectangle;

  gdk_monitor_get_geometry (monitor, &monitor_rectangle);
  printf("monitor x: %d, y: %d, width: %d, height: %d\n", monitor_rectangle.x, monitor_rectangle.y, monitor_rectangle.width, monitor_rectangle.height);
  printf("placing at x: %d y: %d\n", monitor_rectangle.x + monitor_rectangle.width - width - margin,  monitor_rectangle.y + margin + titlebar);
  gtk_window_move (GTK_WINDOW (window), monitor_rectangle.x + monitor_rectangle.width - width - margin,  monitor_rectangle.y + margin + titlebar);
}

void add_notification(const gchar* content) {
  GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkWidget* label = gtk_label_new (content);
  gtk_container_add (GTK_CONTAINER (window), label);

  gtk_window_set_decorated (GTK_WINDOW (window), TRUE);
  gtk_window_set_title (GTK_WINDOW (window), "Notification");
  //gtk_window_set_gravity (GTK_WINDOW (window), GDK_GRAVITY_STATIC);

  // DOCK is very cool and will create an actual dock on i3
  gtk_window_set_type_hint (GTK_WINDOW (window), GDK_WINDOW_TYPE_HINT_UTILITY);

  g_signal_connect(window, "size_allocate", G_CALLBACK(on_size_allocate), window);

  // struct Notification* notification = {}
  // if (first_notification == NULL) {

  // }

  gtk_widget_show_all (window);
}

//https://www.freedesktop.org/wiki/Specifications/wm-spec/ not supported by i3wm
//https://specifications.freedesktop.org/notification-spec/notification-spec-latest.html
//https://github.com/i3/i3/issues/1335
//https://github.com/i3/i3/issues/1341
//https://github.com/i3/i3/pull/3184
int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
  add_notification("This is the body of the notification....");
  gtk_main();
  return 0;
}