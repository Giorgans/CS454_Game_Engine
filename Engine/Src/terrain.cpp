//
// Created by Georgios Zervos on 18/11/21.
//
#include "../Include/terrain.h"
#define TILESET_PATH "/Users/george/CLionProjects/CS454-Super-Mario-Game/UnitTests/UnitTest1/Media/overworld_tileset_grass.png"
#define CSV_PATH  "/Users/george/CLionProjects/CS454-Super-Mario-Game/UnitTests/UnitTest1/Media/map2_Tile Layer 1.csv"

#define DISPLAY_W 640
#define DISPLAY_H 480

#define TILE_PIXEL_W 16
#define TILE_PIXEL_H 16

#define TOTAL_TILES_X DIPLAY_W/TILE_PIXEL_W
#define TOTAL_TILES_Y DISPLAY_H/TILE_PIXEL_H

ALLEGRO_BITMAP *ReadTextMap(){
    ALLEGRO_BITMAP *tileset = NULL;
    ALLEGRO_BITMAP *map = NULL;


    al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

    tileset = al_load_bitmap(TILESET_PATH);
    if(!tileset) return NULL;


    std::vector<std::vector<std::string>> csv_tiles;
    std::vector<std::string> row;
    std::string line, word;


    std::fstream csv (CSV_PATH, std::ios::in);
    if(csv.is_open())
    {
        while(getline(csv, line))
        {
            row.clear();

            std::stringstream str(line);

            while(getline(str, word, ','))
                row.push_back(word);
            csv_tiles.push_back(row);
        }
    }
    else   std::cout << "Could not open the file\n";

    map = al_create_bitmap(csv_tiles.size()*TILE_PIXEL_W,csv_tiles[0].size()*TILE_PIXEL_H);
    //al_set_target_bitmap(map);

    int x = 0,y = 0;
    for( int i=0 ; i<csv_tiles.size() ; i++ )
    {
        for( int j=0 ; j<csv_tiles[i].size() ; j++ )
        {
            for ( int k = 0 ; k < std::stoi(csv_tiles[i][j]) ; k++){
                if( x == al_get_bitmap_width(tileset) ){
                    x = 0;
                    y += TILE_PIXEL_H;
                }
                x += TILE_PIXEL_W;
            }
            al_draw_bitmap_region(tileset,x,y,16,16,j*TILE_PIXEL_W,i*TILE_PIXEL_H,0);

            x=0;y=0;
        }
    }

    return map;
}
