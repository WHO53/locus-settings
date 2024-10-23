#include <locus.h>
#include <cairo.h>
#include "main.h"

Locus app;

int main() {
    locus_init(&app, 100, 100);
    app.state = 0;
    locus_create_window(&app, "locus-settings");
    locus_set_draw_callback(&app, draw_panel);
    locus_set_touch_callback(&app, touch);
    locus_run(&app);
    locus_cleanup(&app);
    return 0;
}
