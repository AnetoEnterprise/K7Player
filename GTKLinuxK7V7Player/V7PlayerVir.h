#ifndef V7PLAYERVIR_H
#define V7PLAYERVIR_H

#include <iostream>
#include <gtk/gtk.h>

using namespace std;

class V7PlayerVir{
public:virtual void SetInV7PlayerMain(GtkWidget *context, GtkWidget *labelTime, GtkWidget *labelCompleteTime, GtkWidget *seekBar)=0;
public:virtual string GetV7PlayerLib(string file, GtkWidget *titre, GtkWidget *context, GtkWidget *box)=0;
public:virtual string V7GO(string action, string action2, string title, GtkWidget *context)=0;
};

#endif
