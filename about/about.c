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
#define RADIUS 15 // Rounded corner radius
#define SHADOW_OFFSET 4

// Function to get the OS release details
void get_os_release(char *pretty_name) {
    FILE *fp = fopen("/etc/os-release", "r");
    if (fp != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "PRETTY_NAME=\"%[^\"]\"", pretty_name) == 1) {
                break;
            }
        }
        fclose(fp);
    } else {
        strcpy(pretty_name, "Unknown OS");
    }
}

// Function to get the hostname
void get_hostname(char *hostname) {
    gethostname(hostname, 256);
}

// Function to get kernel version
void get_kernel_version(char *kernel_version) {
    struct utsname buffer;
    if (uname(&buffer) == 0) {
        strcpy(kernel_version, buffer.release);
    } else {
        strcpy(kernel_version, "Unknown Kernel");
    }
}

static void draw_text_left(cairo_t *cr, int x, int y, const char *text) {
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.95);  // Light text color
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.03);

    cairo_move_to(cr, x + TEXT_PADDING, y + (BOX_HEIGHT / 2) + 8);
    cairo_show_text(cr, text);
    cairo_stroke(cr);
}

static void draw_back_arrow(cairo_t *cr, int x, int y) {
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.8);  // Lighter arrow color
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.03);

    cairo_move_to(cr, x + TEXT_PADDING, y);
    cairo_show_text(cr, "<");
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

void draw_about_panel(cairo_t *cr, int width, int height) {
    // Draw background
    cairo_set_source_rgba(cr, 0.05, 0.05, 0.1, 1);  // Slightly lighter black
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    // Get system information
    char pretty_name[256], kernel_version[256], hostname[256];
    get_os_release(pretty_name);
    get_kernel_version(kernel_version);
    get_hostname(hostname);

    int x = 0;
    int y = 0;

    // Draw back arrow at the top left
    draw_back_arrow(cr, x, y + BOX_PADDING * 5);

    // Draw "About" title
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.95);  // Light text
    cairo_select_font_face(cr, "Monofur Nerd Font", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, app.height * 0.05);
    cairo_move_to(cr, TEXT_PADDING * 4, app.height * 0.05);
    cairo_show_text(cr, "About");

    // Display system information
    const char *info[] = {
        "Username: user",
        pretty_name,
        kernel_version,
        hostname
    };

    // Draw each info item
    for (int i = 0; i < sizeof(info) / sizeof(info[0]); i++) {
        y = (app.height * .10) + i * (BOX_HEIGHT + BOX_PADDING);

        draw_text_box(cr, x, y);
        draw_text_left(cr, x, y, info[i]);
    }
}
