#include "../ZeldaII.h"
#include "../../../Engine/paths.h"
#include <iostream>
#include <map>
#include "../../../Engine/Include/sound.h"
#include <allegro5/allegro_audio.h>
#include "../../../Engine/Include/sprite.h"


ALLEGRO_SAMPLE *LevelSound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *LevelSoundInstance = nullptr;
ALLEGRO_SAMPLE *AttackSound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *AttackSoundInstance = nullptr;
ALLEGRO_SAMPLE *TitleSound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *TitleSoundInstance = nullptr;
ALLEGRO_MIXER *Levelmixer = nullptr;
ALLEGRO_MIXER *SFXmixer = nullptr;
ALLEGRO_MIXER *MasterMixer = nullptr;
ALLEGRO_VOICE *voice = nullptr;

bool PlayedOnce=false;
bool levelSoundPlayed = false;

uint64_t LastTime;
SoundManager& soundManager = SoundManager::GetManager();


void LoadSounds(){

    soundManager.initialize();

    if (!LevelSound) {
        soundManager.loadSound(SoundManager::LEVEL,"level", LEVEL_MUSIC_PATH);
    }

    if (!TitleSound) {
        soundManager.loadSound(SoundManager::LEVEL,"title", TITLE_MUSIC_PATH);
    }

    if (!AttackSound) {
        soundManager.loadSound(SoundManager::SFX,"attack",ATTACK_SOUND);
    }

    soundManager.setVolume(SoundManager::SFX,0.5);
    soundManager.setVolume(SoundManager::LEVEL,0.2);

}

void ZeldaII_Sound() {

    static bool wasPausedLastFrame = false;

    if(inputs["P"]) {
        if (!wasPausedLastFrame) {
            soundManager.setVolume(SoundManager::LEVEL,0);
            wasPausedLastFrame = true;
        }
    } else {
        soundManager.setVolume(SoundManager::LEVEL,0.2);
        wasPausedLastFrame = false;
    }


    if(inputs.at("A") && inputs.at("Down") && (GetGameTime() - LastTime)>(1000/6)){
        LastTime = GetGameTime();
        soundManager.stopSound("attack");
        soundManager.playSound("attack",false);
    }
    if(inputs.at("A") && (GetGameTime() - LastTime)>((1000/6)*3)){
        LastTime = GetGameTime();
        soundManager.stopSound("attack");
        soundManager.playSound("attack",false);
    }

    if(inputs.at("start") && !levelSoundPlayed){
        PlayLevelSound();
        levelSoundPlayed = true;
    }

    if(!PlayedOnce){
        PlayTitleScreenSound();
        PlayedOnce= true;
    }

}

void PlayTitleScreenSound(){
    soundManager.playSound("title",true);
}

void PlayLevelSound() {
    soundManager.stopSound("title");
    soundManager.playSound("level",true);
}
