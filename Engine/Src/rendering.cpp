#include "../Include/rendering.h"


void Rendering() {





}


// Draws a part of bitmap to an area of another bitmap
void BitmapBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    al_set_target_bitmap(dest);
    al_draw_bitmap_region(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,0);
    al_unlock_bitmap(dest);
}


// Draws a part of bitmap to an area of another bitmap
void BitmapMaskedBlit(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point,ALLEGRO_COLOR color){
    al_set_target_bitmap(src);
    al_convert_mask_to_alpha(src,color);
    al_unlock_bitmap(src);

    al_set_target_bitmap(dest);
    al_draw_bitmap_region(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,0);
    al_unlock_bitmap(dest);
}

// Draws a scaled part of bitmap to an area of another bitmap
void BitmapBlitScaled(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    al_set_target_bitmap(dest);
    al_draw_scaled_bitmap(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,DISPLAY_W,DISPLAY_H,0);
    al_unlock_bitmap(dest);
}


// Draws a scaled part of bitmap to an area of another bitmap
void BitmapBlitScaledSprite(ALLEGRO_BITMAP *src,Rect src_rect,ALLEGRO_BITMAP *dest,Point dest_point){
    al_set_target_bitmap(dest);
    al_draw_scaled_bitmap(src,src_rect.x,src_rect.y,src_rect.w,src_rect.h,dest_point.x,dest_point.y,src_rect.w,32,0);
    al_unlock_bitmap(dest);
}
