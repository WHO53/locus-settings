#include "main.h"
#include <stdio.h>

void touch(int32_t id, double x, double y, int state) {
    // Check if the touch state is down
    if (state == 0) {
        // If app state is 0, check for box touches
        if (app.state == 0) {
            double y_ranges[6][2];
            for (int i = 0; i < 6; i++) {
                y_ranges[i][0] = (app.height * 0.10) + i * (app.height / 10 + app.height / 100);
                y_ranges[i][1] = y_ranges[i][0] + (app.height / 10);
            }
            if (y >= y_ranges[0][0] && y <= y_ranges[0][1]) {
                locus_set_draw_callback(&app, draw_wifi_panel);
                app.redraw = 1;
                app.state = 1;
                printf("Box 1 has been touched!\n");
            } 
            else if (y >= y_ranges[1][0] && y <= y_ranges[1][1]) {
                printf("Box 2 has been touched!\n");
            } 
            else if (y >= y_ranges[2][0] && y <= y_ranges[2][1]) {
                printf("Box 3 has been touched!\n");
            } 
            else if (y >= y_ranges[3][0] && y <= y_ranges[3][1]) {
                printf("Box 4 has been touched!\n");
            } 
            else if (y >= y_ranges[4][0] && y <= y_ranges[4][1]) {
                printf("Box 5 has been touched!\n");
            } 
            else if (y >= y_ranges[5][0] && y <= y_ranges[5][1]) {
                locus_set_draw_callback(&app, draw_about_panel);
                app.redraw = 1;
                app.state = 6;
                printf("Box 6 has been touched!\n");
            }
        } 
        // If app state is not 0, check for the back button
        else {
            if (x >= app.width / 50 && x <= (app.width / 50) + (app.height * .03 ) && y >= app.width * .05 && y <= (app.width * .05) + (app.height * 0.03)) {
                locus_set_draw_callback(&app, draw_panel);
                app.redraw = 1;
                app.state = 0;
                printf("back!\n");
            }
        }
    }
    // Check for state == 1 and print messages if conditions are met
    if (app.state == 1) {
        if (x >= app.width * 0.04 && x <= app.width * 0.14 && y >= app.height * .01 && y <= app.height * 0.13) {
            printf("wifi toggle\n");            
        } else if (x >= (app.width * 0.96) - (app.height * 0.03) && x <= app.width * 0.96 && y >= app.height * .1 && y <= app.height * .13) {
            printf("refresh\n");            
        }
    }
}
