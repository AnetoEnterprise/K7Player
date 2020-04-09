#include <iostream>
#include <dlfcn.h>
#include "K7PlayerVir.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

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
K7PlayerVir* ps;
typedef K7PlayerVir* create_t();
typedef void destroy_t(K7PlayerVir*);
create_t* openK7;
destroy_t* closeK7;







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
string resVolume=ps->K7GO("VOLUME", "" + vl + "", "K7Player Media", main_window);
cout << resVolume;
g_free (text), text = NULL;
}

void ActionPlay(){
string resPlay=ps->K7GO("PLAY", "", "K7Player Media", main_window);
cout << resPlay;
}

void ActionPause(){
string resPause=ps->K7GO("PAUSE", "", "K7Player Media", main_window);
cout << resPause;
}

void ActionResume(){
string resPause=ps->K7GO("RESUME", "", "K7Player Media", main_window);
cout << resPause;
}

void ActionLoop(){
string resPause=ps->K7GO("LOOP", "true", "K7Player Media", main_window);
cout << resPause;
}




     
int main (int argc, char **argv){
gtk_init (&argc, &argv);

GtkWidget *boxh;
GtkWidget *boxv;
GtkWidget *buttonPlay;
GtkWidget *buttonPause;
GtkWidget *buttonResume;
GtkWidget *buttonLoop;
GtkWidget *buttonVolume = NULL;
GtkWidget *labelVolume = NULL;
                          
main_window =gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (main_window), "K7Player");
GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
gtk_window_set_default_size (GTK_WINDOW (main_window), 500, 70);
boxh=gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
boxv=gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

progressbar=gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, NULL);
buttonPlay = gtk_button_new_with_label ("PLAY");
buttonPause = gtk_button_new_with_label ("PAUSE");
buttonResume = gtk_button_new_with_label ("RESUME");
buttonLoop = gtk_button_new_with_label ("LOOP");
buttonVolume = gtk_volume_button_new();
labelVolume = gtk_label_new ("0");
labelTime = gtk_label_new ("0:00");
labelCompleteTime = gtk_label_new ("0:00");


g_signal_connect (buttonPlay, "clicked", G_CALLBACK (ActionPlay), NULL);
g_signal_connect (buttonPause, "clicked", G_CALLBACK (ActionPause), NULL);
g_signal_connect (buttonResume, "clicked", G_CALLBACK (ActionResume), NULL);
g_signal_connect (buttonLoop, "clicked", G_CALLBACK (ActionLoop), NULL);
g_signal_connect (progressbar, "change-value", G_CALLBACK (progressbar_change), NULL);
g_signal_connect (G_OBJECT (buttonVolume), "value-changed", G_CALLBACK (value_change), labelVolume);

handle = dlopen("./K7PlayerLib/K7PlayerLib.so", RTLD_LAZY);
if (!handle){printf("%s", dlerror());}
openK7=(create_t*)dlsym(handle, "create");
closeK7=(destroy_t*)dlsym(handle, "destroy");
if (!openK7){cout << "%s" << dlerror();}
if (!closeK7){cout << "%s" << dlerror();}

ps = openK7();
string getK7=ps->GetV7PlayerLib("GET", "", titre, main_window, scrolled_window);
cout << getK7;
string resK7=ps->GetK7PlayerLib("file:///media/sf_E_DRIVE/Musique/SeanKingStone/Audios/sean_kingston_one_away_mp3_15549.mp3", "USB", titre, main_window);
cout << resK7;

gtk_container_add (GTK_CONTAINER (boxh), labelTime);
gtk_container_add (GTK_CONTAINER (boxh), buttonPlay);
gtk_container_add (GTK_CONTAINER (boxh), buttonPause);
gtk_container_add (GTK_CONTAINER (boxh), buttonResume);
gtk_container_add (GTK_CONTAINER (boxh), buttonLoop);
gtk_container_add (GTK_CONTAINER (boxh), labelCompleteTime);
gtk_container_add (GTK_CONTAINER (boxh), buttonVolume);
gtk_container_add (GTK_CONTAINER (boxh), labelVolume);
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
ps->SetInK7PlayerMain(main_window, labelTime, labelCompleteTime, progressbar);
cout << "-------";
}



static void destroyWindowCb(GtkWidget* widget, GtkWidget* window){
closeK7(ps);
gtk_main_quit();
}
