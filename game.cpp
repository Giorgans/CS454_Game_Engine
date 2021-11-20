//
// Created by Georgios Zervos on 18/11/21.
//
#include "game.h"
#include "Engine/Include/terrain.h"
#include <allegro5/allegro_image.h>

#define DIPLAY_W 640
#define DISPLAY_H 480


void Game::MainLoop(){
    al_init();
    al_init_image_addon();
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *EventQueue;
    ALLEGRO_EVENT Event;

    display = al_create_display(DIPLAY_W, DISPLAY_H);
    al_set_target_backbuffer(display);
    EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_display_event_source(display));

    ALLEGRO_BITMAP *map = ReadTextMap();
    bool exit = false ;
    while(!exit)
    {
        al_draw_bitmap(al_get_target_bitmap(), 0, 0, 0);
        al_flip_display();

        al_wait_for_event(EventQueue, &Event);
        if(Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = true;
    }
    al_destroy_event_queue(EventQueue);
    al_destroy_bitmap(map);
}