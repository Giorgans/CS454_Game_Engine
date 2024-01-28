
#include "../../../Engine/Include/sprite.h"



/***************************************
 *  Creating Sprites Functions        *
 *************************************/

void createTittleScreen(){
    auto *TitleScn = new Sprite(ZELDA_STARTING_LEVEL_STARTING_POINT_X,ZELDA_STARTING_LEVEL_STARTING_POINT_Y,AnimationFilmHolder::GetHolder().Load(TitleScreen),"TitleScreen");
    TitleScn->SetFrame(0);
    TitleScn->SetVisibility(true);
    TitleScn->SetZorder(1);
    SpriteManager::GetSingleton().Add(TitleScn);

}

void createLink() {
    auto *Link = new Sprite(LINK_STARTING_POINT_X,LINK_STARTING_POINT_Y,AnimationFilmHolder::GetHolder().Load(WalkingRight),"Link");
    Link->SetFrame(0);
    Link->SetVisibility(true);
    Link->SetZorder(0);
    Link->GetGravityHandler().gravityAddicted = true;
    SpriteManager::GetSingleton().Add(Link);
}

void LinkElevatorAction(Sprite *link,Sprite *elevator){
    if(inputs["Down"]) {
        elevator->SetStateID("Down");
        link->SetStateID("Down");
    }
}

void createEnemiesAndObjects(){
    std::string csv_value,line;
    Dim col=0,row=0;
    std::ifstream file;
    file.open(OBJECTS_CSV_FILE_PATH);
    if(!file.is_open()) assert(true);
    while(std::getline(file, line))
    {
        std::stringstream str(line);
        while(getline(str, csv_value, ',')){
            int i = std::stoi(csv_value);
            if(i == ELEVATOR_TILE){
                auto elevator = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row),AnimationFilmHolder::GetHolder().Load(Elevator),"Object");
                elevator->SetFrame(0);
                elevator->SetVisibility(true);
                elevator->SetZorder(0);
                elevator->GetGravityHandler().gravityAddicted = false;
                SpriteManager::GetSingleton().Add(elevator);
                auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
                CollisionChecker::GetSingleton().Register(link,elevator,LinkElevatorAction);
            }


            //
            col++;
        }
        row++;
        col=0;
    }

}

