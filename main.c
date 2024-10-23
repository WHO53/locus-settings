#include <locus.h>
#include <cairo.h>
#include "main.h"

Locus app;

static void draw_main_panel(cairo_t *cr, int width, int height) {
    cairo_set_source_rgba(cr, 0, 0, 0, 1);
    cairo_rectangle(cr, 0, 0 , app.width, app.height);
    cairo_fill(cr);
}

int main(){
    locus_init(&app, 100, 100);
    locus_create_window(&app, "locus-settings");
    locus_set_draw_callback(&app, draw_main_panel);
    locus_run(&app);
    locus_cleanup(&app);
    return 0;
}

