#include <gtk/gtk.h>

static gchar buffer[256];
static GtkWidget *window;
static GtkWidget *darea;
static guint id_signal;

static gboolean time_handler(GtkWidget *widget)
{    
    time_t curtime;
    struct tm *loctime;
    curtime = time(NULL);
    loctime = localtime(&curtime);
    strftime(buffer, 256, "%T", loctime);
    //发射信号    
    g_signal_emit_by_name (window, "custom-signal", buffer);
    return TRUE;
}

static void gtk_custom_signal_callback(gpointer instance, gpointer arg1, gpointer user_data)
{    
    gtk_window_set_title(GTK_WINDOW(window), (gchar *)arg1);    
    g_printf("in gtk_custom_signal_callback.\n");
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER (window), darea);

    g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 170, 100);
    gtk_window_set_title(GTK_WINDOW(window), "timer");

    g_timeout_add(1000, (GSourceFunc) time_handler, (gpointer) window); //建立定时器
#if 1    
    //建立信号
    id_signal = g_signal_new ("custom-signal", //最好用 - 分隔符
                  G_TYPE_OBJECT,
                  G_SIGNAL_RUN_LAST,
                  0,
                  NULL, //callback 成功后 收尾的处理. 可以为 NULL, NULL
                  NULL, //callback 的 user_data
                  g_cclosure_marshal_VOID__POINTER, //g_cclosure_marshal_VOID__POINTER----------typedef void (*callback) (gpointer instance, gpointer arg1, gpointer user_data);
                  G_TYPE_NONE, //返回类型
                  1, //参数个数
                  G_TYPE_POINTER//参数类型
                  );
#else
    id_signal = g_signal_new ("custom-signal",
                  G_TYPE_OBJECT,
                  G_SIGNAL_RUN_LAST,
                  0,
                  NULL, NULL,
                  g_cclosure_marshal_VOID__VOID, //g_closure_marshal_VOID_VOID说明该signal的回调函数为以下的callback类型：typedef void (*callback) (gpointer instance, gpointer user_data);
                  G_TYPE_NONE, //返回类型
                  0 //参数个数
                  //参数类型
                  );
#endif    
    //绑定信号
    gulong id_handler = g_signal_connect_object(window, "custom-signal",G_CALLBACK(gtk_custom_signal_callback), window, G_CONNECT_AFTER);
    g_printf("bind signal return. %ld.\n", id_handler);
    
    gtk_widget_show_all(window);
    time_handler(window);
    gtk_main();
    return 0;
}
