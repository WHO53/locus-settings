#include <locus.h>
#include <cairo.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <unistd.h>
#include "../main.h"

#define BOX_WIDTH app.width
#define BOX_HEIGHT app.height / 10
#define BOX_PADDING app.height / 100
#define TEXT_PADDING app.width / 50
#define ARROW_PADDING app.width / 10
#define TOGGLE_WIDTH (app.width * 0.10)
#define TOGGLE_HEIGHT (app.height * 0.03)
#define TOGGLE_RADIUS (TOGGLE_HEIGHT / 2)
#define RADIUS (app.height * 0.015)
#define SHADOW_OFFSET (app.height * 0.01)
#define REFRESH_ICON_SIZE (app.height * 0.03)

static int wifi_enabled = 1;

static void draw_toggle_switch(cairo_t *cr, int x, int y, int enabled) {
    cairo_set_line_width(cr, 2);
    if (enabled) {
        cairo_set_source_rgb(cr, 0.1, 0.1, 0.6);
    } else {
        cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
    }
    
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + TOGGLE_HEIGHT/2, y + TOGGLE_HEIGHT/2, TOGGLE_HEIGHT/2, M_PI/2, -M_PI/2);
    cairo_arc(cr, x + TOGGLE_WIDTH - TOGGLE_HEIGHT/2, y + TOGGLE_HEIGHT/2, TOGGLE_HEIGHT/2, -M_PI/2, M_PI/2);
    cairo_close_path(cr);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 1, 1, 1);
    if (enabled) {
        cairo_arc(cr, x + TOGGLE_WIDTH - TOGGLE_HEIGHT/2, y + TOGGLE_HEIGHT/2, TOGGLE_HEIGHT/2 - 2, 0, 2 * M_PI);
    } else {
        cairo_arc(cr, x + TOGGLE_HEIGHT/2, y + TOGGLE_HEIGHT/2, TOGGLE_HEIGHT/2 - 2, 0, 2 * M_PI);
    }
    cairo_fill(cr);
}

static void draw_refresh_icon(cairo_t *cr, int x, int y) {
    double radius = REFRESH_ICON_SIZE / 3.0;
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.8);
    cairo_set_line_width(cr, 2);

    cairo_arc(cr, x + REFRESH_ICON_SIZE/2, y + REFRESH_ICON_SIZE/2, radius, -M_PI/4, 3*M_PI/2);
    
    cairo_move_to(cr, x + REFRESH_ICON_SIZE/2 + radius * cos(3 * -M_PI/4), 
                     y + REFRESH_ICON_SIZE/2 + radius * sin(-M_PI/4));
    cairo_rel_line_to(cr, 5, -5);
    cairo_move_to(cr, x + REFRESH_ICON_SIZE/2 + radius * cos(-M_PI/4),
                     y + REFRESH_ICON_SIZE/2 + radius * sin(-M_PI/4));
    cairo_rel_line_to(cr, -5, -5);
    
    cairo_stroke(cr);
}

static void draw_text_left(cairo_t *cr, int x, int y, const char *text) {
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.95);
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.03);
    cairo_move_to(cr, x + TEXT_PADDING, y + (BOX_HEIGHT / 2) + 8);
    cairo_show_text(cr, text);
    cairo_stroke(cr);
}

static void draw_back_arrow(cairo_t *cr, int x, int y) {
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.8);
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.03);
    cairo_move_to(cr, x + TEXT_PADDING, y);
    cairo_show_text(cr, "<");
    cairo_stroke(cr);
}

static void draw_text_box(cairo_t *cr, int x, int y) {
    cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
    cairo_rectangle(cr, x + SHADOW_OFFSET, y + SHADOW_OFFSET, BOX_WIDTH, BOX_HEIGHT);
    cairo_fill(cr);
    
    cairo_set_source_rgba(cr, 0.15, 0.15, 0.2, 1);
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + BOX_WIDTH - RADIUS, y + RADIUS, RADIUS, -0.5 * M_PI, 0);
    cairo_arc(cr, x + BOX_WIDTH - RADIUS, y + BOX_HEIGHT - RADIUS, RADIUS, 0, 0.5 * M_PI);
    cairo_arc(cr, x + RADIUS, y + BOX_HEIGHT - RADIUS, RADIUS, 0.5 * M_PI, M_PI);
    cairo_arc(cr, x + RADIUS, y + RADIUS, RADIUS, M_PI, 1.5 * M_PI);
    cairo_close_path(cr);
    cairo_fill(cr);
}

void draw_wifi_panel(cairo_t *cr, int width, int height) {
    cairo_set_source_rgba(cr, 0.05, 0.05, 0.1, 1);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    int x = 0;
    int y = 0;

    draw_back_arrow(cr, x, y + BOX_PADDING * 5);

    cairo_set_source_rgb(cr, 0.9, 0.9, 0.95);
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.05);
    cairo_move_to(cr, TEXT_PADDING * 4, app.height * 0.05);
    cairo_show_text(cr, "WI-FI");

    draw_toggle_switch(cr, TEXT_PADDING * 2, app.height * 0.1, wifi_enabled);

    draw_refresh_icon(cr, BOX_WIDTH - TEXT_PADDING * 2 - REFRESH_ICON_SIZE, 
                     app.height * 0.1);

    const char *networks[] = {
        "Network 1",
        "Network 2",
        "Network 3",
        "Network 4",
        "Network 5"
    };

    for (int i = 0; i < sizeof(networks) / sizeof(networks[0]); i++) {
        y = (app.height * 0.15) + i * (BOX_HEIGHT + BOX_PADDING);
        draw_text_box(cr, x, y);
        draw_text_left(cr, x, y, networks[i]);
    }
}
