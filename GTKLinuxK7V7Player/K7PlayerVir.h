#ifndef K7PLAYERVIR_H
#define K7PLAYERVIR_H

#include <iostream>
#include <gtk/gtk.h>

using namespace std;

class K7PlayerVir{
public:virtual void SetInK7PlayerMain(GtkWidget *context, GtkWidget *labelTime, GtkWidget *labelCompleteTime, GtkWidget *seekBar)=0;
public:virtual string GetK7PlayerLib(string file, GtkWidget *titre, GtkWidget *context)=0;
public:virtual string K7GO(string action, string action2, string title, GtkWidget *context)=0;
};

#endif
