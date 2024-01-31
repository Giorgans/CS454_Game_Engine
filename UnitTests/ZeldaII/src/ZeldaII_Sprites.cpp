
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

void LinkEnemy(Sprite *enemy,Sprite *player){
    if((player->GetFilm()->GetID()==AttackLeft || player->GetFilm()->GetID()==AttackRight ||player->GetFilm()->GetID()==DownLeft ||player->GetFilm()->GetID()==DownRight) && player->GetFrame()==1) {
        enemy->SetStateID("Attacked");
        enemy->SetVisibility(false);
    }
}

void LinkElevatorAction(Sprite *link,Sprite *elevator){
    if(inputs["Down"]) {
        elevator->SetStateID("Down");
        link->SetStateID("Down");
    }
    if(inputs["Up"]) {
        elevator->SetStateID("Up");
        link->SetStateID("Up");
    }

    if(link->GetStateID()=="GoingUp"){
        elevator->SetStateID("GoingUp");
    }


    if(link->GetStateID()=="GoingDown"){
        elevator->SetStateID("GoingDown");
    }
}

void LinkKeyAction(Sprite *link,Sprite *key){
    if(inputs["A"]){
        key->SetVisibility(false);
        inputs["key"] = true;
    }
}

void LinkDoorAction(Sprite *link,Sprite *door){
    if(inputs["key"])
        door->SetStateID("Open");



}
void LinkBridgeAction(Sprite *link,Sprite *bridge){
    if(bridge->IsVisible()) {
        bridge->SetStateID("Fall");
        link->SetStateID("OnBridge");
    }
}



void createEnemiesAndObjects(){
    auto Link = SpriteManager::GetSingleton().GetDisplayList().at(1);
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
            else if(i == WOSU_ENEMY_TILE){
                auto wosu = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row),AnimationFilmHolder::GetHolder().Load(WosuLeft),"Wosu");
                wosu->SetFrame(0);
                wosu->SetVisibility(true);
                wosu->SetZorder(0);
                wosu->GetGravityHandler().gravityAddicted = true;
                SpriteManager::GetSingleton().Add(wosu);
                CollisionChecker::GetSingleton().Register(wosu,Link,LinkEnemy);
            }
            else if(i == BOT_TILE) {
                auto bot = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row), AnimationFilmHolder::GetHolder().Load(Bot), "Bot");
                bot->SetFrame(0);
                bot->SetVisibility(true);
                bot->SetZorder(0);
                bot->GetGravityHandler().gravityAddicted = true;
                bot->SetStateID("Inactive");
                SpriteManager::GetSingleton().Add(bot);
                CollisionChecker::GetSingleton().Register(bot,Link,LinkEnemy);
            }
            else if(i == STALFOS_TILE) {
                auto stalfos = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row), AnimationFilmHolder::GetHolder().Load(StalfosWalkingLeft), "Stalfos");
                stalfos->SetFrame(0);
                stalfos->SetVisibility(true);
                stalfos->SetZorder(0);
                stalfos->GetGravityHandler().gravityAddicted = true;
                SpriteManager::GetSingleton().Add(stalfos);
                CollisionChecker::GetSingleton().Register(stalfos,Link,LinkEnemy);
            }
            else if(i == KEY_TILE) {
                auto key = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row),AnimationFilmHolder::GetHolder().Load(Key),"Key");
                key->SetFrame(0);
                key->SetVisibility(true);
                key->SetZorder(0);
                key->GetGravityHandler().gravityAddicted = false;
                SpriteManager::GetSingleton().Add(key);
                auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
                CollisionChecker::GetSingleton().Register(link,key, LinkKeyAction);
            }
            else if(i == DOOR_TILE){
                auto door = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row),AnimationFilmHolder::GetHolder().Load(Door),"Door");
                door->SetFrame(0);
                door->SetVisibility(true);
                door->SetZorder(0);
                door->GetGravityHandler().gravityAddicted = false;
                SpriteManager::GetSingleton().Add(door);
                auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
                CollisionChecker::GetSingleton().Register(link,door, LinkDoorAction);
            }
            else if(i == CANDLE_TILE) {
                auto candle = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row),AnimationFilmHolder::GetHolder().Load(Candle),"Candle");
                candle->SetFrame(0);
                candle->SetVisibility(true);
                candle->SetZorder(0);
                candle->GetGravityHandler().gravityAddicted = false;
                SpriteManager::GetSingleton().Add(candle);
                auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
                CollisionChecker::GetSingleton().Register(link,candle, {});
            }
            else if(i == BRIDGE_TILE) {
                auto bridge = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row),AnimationFilmHolder::GetHolder().Load(FallingBridge),"Bridge");
                bridge->SetFrame(0);
                bridge->SetVisibility(true);
                bridge->SetZorder(0);
                bridge->GetGravityHandler().gravityAddicted = false;
                SpriteManager::GetSingleton().Add(bridge);
                auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
                CollisionChecker::GetSingleton().Register(link,bridge, LinkBridgeAction);
            }
            else if(i == FAIRY_TILE) {
                auto fairy = new Sprite(MUL_TILE_WIDTH(col), MUL_TILE_HEIGHT(row),AnimationFilmHolder::GetHolder().Load(Fairy),"Fairy");
                fairy->SetFrame(0);
                fairy->SetVisibility(true);
                fairy->SetZorder(0);
                fairy->GetGravityHandler().gravityAddicted = false;
                SpriteManager::GetSingleton().Add(fairy);
                auto link = SpriteManager::GetSingleton().GetDisplayList().at(1);
                CollisionChecker::GetSingleton().Register(link,fairy, {});
            }
            col++;
        }
        row++;
        col=0;
    }

}

