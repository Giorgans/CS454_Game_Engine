#ifndef CS454_GAME_ENGINE_RENDERING_H
#define CS454_GAME_ENGINE_RENDERING_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "sprite.h"
#include "../paths.h"

void Rendering();


/***************************************
 *  Generic Rendering Functions       *
 **************************************/

void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
void BitmapBlitScaled(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);
void BitmapMaskedBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point,ALLEGRO_COLOR color);
void BitmapBlitScaledSprite(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point);


#endif //CS454_GAME_ENGINE_RENDERING_H
