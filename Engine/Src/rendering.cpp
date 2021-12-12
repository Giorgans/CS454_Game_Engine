//
// Created by Georgios Zervos on 8/12/21.
//
#include "../Include/rendering.h"

#define KEY_COLOR al_map_rgb(148,148,255)
#define FPS 60

#define TERRAIN_W 3376
#define TERRAIN_H 480
#define BACKGROUND_W TERRAIN_W
#define BACKGROUND_H TERRAIN_H

void Rendering(void){
    ALLEGRO_BITMAP *background = al_create_bitmap(BACKGROUND_W,BACKGROUND_H);
    ALLEGRO_BITMAP *terrain = al_create_bitmap(TERRAIN_W,TERRAIN_H);;
    al_clear_to_color(KEY_COLOR);
    al_flip_display();

}

