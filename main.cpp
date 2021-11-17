#include <iostream>
#include "app.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


int main(int argc, char **argv) {

    ALLEGRO_DISPLAY *display = NULL;

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(640, 480);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    //ALLEGRO_MAP *map = al_open_map("/UnitTests/UnitTest1/Media", "map2.tmx");
    //al_draw_map(map, 0, 0, 0); // (map, dx, dy, flags)


    //al_clear_to_color(al_map_rgb(0,0,0));

    while(true) al_rest(10.0);

    al_destroy_display(display);

    return 0;
}
