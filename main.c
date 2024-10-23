#include <locus.h>
#include <cairo.h>
#include "main.h"
#include "panel.h"

Locus app;

int main(){
    locus_init(&app, 100, 100);
    locus_create_window(&app, "locus-settings");
    locus_set_draw_callback(&app, draw_panel);
    locus_run(&app);
    locus_cleanup(&app);
    return 0;
}

