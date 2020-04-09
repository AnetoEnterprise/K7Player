#include <iostream>
#include <dlfcn.h>
#include "V7PlayerVir.h"

#include <gtk/gtk.h>

using namespace std;

static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
static void execF();

GtkWidget *main_window;
GtkWidget *labelTime = NULL;
GtkWidget *labelCompleteTime = NULL;
GtkWidget *titre;
GtkWidget *progressbar;
GtkAdjustment *adjust;

void *handle;
guint ctimer;
V7PlayerVir* ps;
typedef V7PlayerVir* create_t();
typedef void destroy_t(V7PlayerVir*);
create_t* openV7;
destroy_t* closeV7;














static void progressbar_change(GtkScaleButton *button, gdouble value, gpointer data){
gchar *text = NULL;
text = g_strdup_printf ("%f", value);

string vl=text;
string resVolume=ps->K7GO("PROGRESS", "" + vl + "", "K7Player Media", window);
cout << resVolume;
g_free (text), text = NULL;
}

static void value_change (GtkScaleButton *button, gdouble value, gpointer data){
GtkLabel *label = GTK_LABEL (data);
gchar *text = NULL;

text = g_strdup_printf ("%f", value);
gtk_label_set_text (label, text);

string vl=text;
string resVolume=ps->V7GO("VOLUME", "" + vl + "", "V7Player Media", main_window);
cout << resVolume;
g_free (text), text = NULL;
}

void ActionPlay(){
string resPlay=ps->V7GO("PLAY", "", "V7Player Media", main_window);
cout << resPlay;
}

void ActionPause(){
string resPause=ps->V7GO("PAUSE", "", "V7Player Media", main_window);
cout << resPause;
}

void ActionResume(){
string resPause=ps->V7GO("RESUME", "", "K7Player Media", main_window);
cout << resPause;
}

void ActionLoop(){
string resPause=ps->V7GO("LOOP", "true", "K7Player Media", main_window);
cout << resPause;
}

void ActionFullScreen(){
string resFullScreen=ps->V7GO("FULLSCREEN", "", "V7Player Media", main_window);
cout << resFullScreen;
}




     
int main (int argc, char **argv){
gtk_init (&argc, &argv);

GtkWidget *boxh;
GtkWidget *boxv;
GtkWidget *buttonPlay;
GtkWidget *buttonPause;
GtkWidget *buttonResume;
GtkWidget *buttonLoop;
GtkWidget *buttonFullScreen;
GtkWidget *buttonVolume = NULL;
GtkWidget *labelVolume = NULL;
                          
main_window =gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (main_window), "V7Player");
gtk_window_set_default_size (GTK_WINDOW (main_window), 500, 400);

boxh=gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
boxv=gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
gtk_widget_set_size_request(scrolled_window, 500, 380);

progressbar=gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, NULL);
buttonPlay = gtk_button_new_with_label ("PLAY");
buttonPause = gtk_button_new_with_label ("PAUSE");
buttonResume = gtk_button_new_with_label ("RESUME");
buttonLoop = gtk_button_new_with_label ("LOOP");
buttonFullScreen = gtk_button_new_with_label ("FULLSCREEN");
buttonVolume = gtk_volume_button_new();
labelVolume = gtk_label_new ("0");
labelTime = gtk_label_new ("0:00");
labelCompleteTime = gtk_label_new ("0:00");

g_signal_connect (buttonPlay, "clicked", G_CALLBACK (ActionPlay), NULL);
g_signal_connect (buttonPause, "clicked", G_CALLBACK (ActionPause), NULL);
g_signal_connect (buttonResume, "clicked", G_CALLBACK (ActionResume), NULL);
g_signal_connect (buttonLoop, "clicked", G_CALLBACK (ActionLoop), NULL);
g_signal_connect (buttonFullScreen, "clicked", G_CALLBACK (ActionFullScreen), NULL);
g_signal_connect (progressbar, "change-value", G_CALLBACK (progressbar_change), NULL);
g_signal_connect (G_OBJECT (buttonVolume), "value-changed", G_CALLBACK (value_change), labelVolume);

handle = dlopen("./K7PlayerLib/V7PlayerLib.so", RTLD_LAZY);
if (!handle){printf("%s", dlerror());}
openV7=(create_t*)dlsym(handle, "create");
closeV7=(destroy_t*)dlsym(handle, "destroy");
if (!openV7){cout << "%s" << dlerror();}
if (!closeV7){cout << "%s" << dlerror();}

ps = openV7();
string getV7=ps->GetV7PlayerLib("GET", "", titre, main_window, scrolled_window);
cout << getV7;
string resV7=ps->GetV7PlayerLib("file:///media/sf_E_DRIVE/Musique/SeanKingStone/Videos/sean_kingston_one_away_h264_15561.mp4", "USB", titre, main_window, scrolled_window);
cout << resV7;

gtk_container_add (GTK_CONTAINER (boxh), labelTime);
gtk_container_add (GTK_CONTAINER (boxh), buttonPlay);
gtk_container_add (GTK_CONTAINER (boxh), buttonPause);
gtk_container_add (GTK_CONTAINER (boxh), buttonResume);
gtk_container_add (GTK_CONTAINER (boxh), buttonLoop);
gtk_container_add (GTK_CONTAINER (boxh), labelCompleteTime);
gtk_container_add (GTK_CONTAINER (boxh), buttonFullScreen);
gtk_container_add (GTK_CONTAINER (boxh), buttonVolume);
gtk_container_add (GTK_CONTAINER (boxh), labelVolume);
gtk_container_add (GTK_CONTAINER (boxv), scrolled_window);
gtk_container_add (GTK_CONTAINER (boxv), progressbar);
gtk_container_add (GTK_CONTAINER (boxv), boxh);

gtk_container_add (GTK_CONTAINER (main_window), boxv);
g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
ctimer=g_timeout_add(1000, (GSourceFunc)execF, NULL);
gtk_widget_show_all (main_window);
gtk_main ();

return 0 ;
}







static void execF(){
//g_source_remove(ctimer);
ps->SetInV7PlayerMain(main_window, labelTime, labelCompleteTime, progressbar);
cout << "-------";
}



static void destroyWindowCb(GtkWidget* widget, GtkWidget* window){
closeV7(ps);
gtk_main_quit();
}
