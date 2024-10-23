#include <locus.h>
#include <cairo.h>
#include "main.h"
#include "panel.h"

#define BOX_WIDTH app.width
#define BOX_HEIGHT app.height / 10
#define BOX_PADDING app.height / 100
#define TEXT_PADDING app.width / 50
#define ARROW_PADDING app.width / 10
#define RADIUS 15 // Rounded corner radius
#define SHADOW_OFFSET 4

static void draw_text_left(cairo_t *cr, int x, int y, const char *text) {
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.95);  // Light text color
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.03);

    cairo_move_to(cr, x + TEXT_PADDING, y + (BOX_HEIGHT / 2) + 8);
    cairo_show_text(cr, text);
    cairo_stroke(cr);
}

static void draw_arrow_right(cairo_t *cr, int x, int y) {
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.8);  // Lighter arrow color
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.03);

    cairo_move_to(cr, x + BOX_WIDTH - ARROW_PADDING, y + (BOX_HEIGHT / 2) + 8);
    cairo_show_text(cr, ">");
    cairo_stroke(cr);
}

static void draw_text_box(cairo_t *cr, int x, int y) {
    // Draw shadow
    cairo_set_source_rgba(cr, 0, 0, 0, 0.2);  // Subtle shadow color
    cairo_rectangle(cr, x + SHADOW_OFFSET, y + SHADOW_OFFSET, BOX_WIDTH, BOX_HEIGHT);
    cairo_fill(cr);

    // Draw box with rounded corners
    cairo_set_source_rgba(cr, 0.15, 0.15, 0.2, 1);  // Dark background color
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + BOX_WIDTH - RADIUS, y + RADIUS, RADIUS, -0.5 * M_PI, 0);
    cairo_arc(cr, x + BOX_WIDTH - RADIUS, y + BOX_HEIGHT - RADIUS, RADIUS, 0, 0.5 * M_PI);
    cairo_arc(cr, x + RADIUS, y + BOX_HEIGHT - RADIUS, RADIUS, 0.5 * M_PI, M_PI);
    cairo_arc(cr, x + RADIUS, y + RADIUS, RADIUS, M_PI, 1.5 * M_PI);
    cairo_close_path(cr);
    cairo_fill(cr);
}

void draw_panel(cairo_t *cr, int width, int height) {
    // Draw background
    cairo_set_source_rgba(cr, 0.05, 0.05, 0.1, 1);  // Slightly lighter black
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    int x = 0;

    // "Settings" title at the top, following iOS style
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.95);  // Light text
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.05);
    cairo_move_to(cr, TEXT_PADDING, app.height * 0.05);
    cairo_show_text(cr, "Settings");

    const char *settings[] = {
        "WiFi",
        "Bluetooth",
        "Display",
        "Apps",
        "Battery",
        "About"
    };

    // Draw each setting item
    for (int i = 0; i < sizeof(settings) / sizeof(settings[0]); i++) {
        int y = (app.height * .10) + i * (BOX_HEIGHT + BOX_PADDING);

        draw_text_box(cr, x, y);
        draw_text_left(cr, x, y, settings[i]);
        draw_arrow_right(cr, x, y);
    }
}

