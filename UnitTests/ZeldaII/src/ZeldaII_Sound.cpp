#include "../ZeldaII.h"
#include "../../../Engine/paths.h"
#include <iostream>
#include <map>
#include <allegro5/allegro_audio.h>


#define FREQUENCY 44100
#define DEPTH ALLEGRO_AUDIO_DEPTH_FLOAT32
#define CHAN_CONFIG ALLEGRO_CHANNEL_CONF_2
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

void ZeldaII_Sound() {

    if (!LevelSound) {
        LevelSound = al_load_sample(LEVEL_MUSIC_PATH);
        LevelSoundInstance = al_create_sample_instance(LevelSound);
    }
    if (!TitleSound) {
        TitleSound = al_load_sample(TITLE_MUSIC_PATH);
        TitleSoundInstance = al_create_sample_instance(TitleSound);
    }
    if (!AttackSound) {
        AttackSound = al_load_sample(ATTACK_SOUND);
        AttackSoundInstance = al_create_sample_instance(AttackSound);
    }
    if(!Levelmixer)
        Levelmixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);

    if(!SFXmixer)
        SFXmixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);

    if(!MasterMixer){
        MasterMixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);
        al_attach_mixer_to_mixer(Levelmixer,MasterMixer );
        al_attach_mixer_to_mixer(SFXmixer,MasterMixer );
    }
    if(!voice){
        voice = al_create_voice(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16,CHAN_CONFIG);
        al_attach_mixer_to_voice(MasterMixer, voice);
    }

    if(inputs.at("A")){
        PlayAttackSound();
    }

    if(inputs.at("enter")){
        PlayLevelSound();
    }

    if(!PlayedOnce){
        PlayTitleScreenSound();
        PlayedOnce= true;
    }

}

void PlayTitleScreenSound(){
    al_set_sample(TitleSoundInstance, TitleSound);
    al_attach_sample_instance_to_mixer(TitleSoundInstance, Levelmixer);
    al_set_sample_instance_playmode(TitleSoundInstance, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(TitleSoundInstance);
}

void PlayLevelSound() {
    if (al_get_sample_instance_playing(TitleSoundInstance)) {
        al_stop_sample_instance(TitleSoundInstance);
    }
    al_set_sample(LevelSoundInstance, LevelSound);
    al_attach_sample_instance_to_mixer(LevelSoundInstance, Levelmixer);
    al_set_sample_instance_playmode(LevelSoundInstance, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(LevelSoundInstance);
}


void PlayAttackSound(){
    al_set_sample(AttackSoundInstance, AttackSound);
    al_attach_sample_instance_to_mixer(AttackSoundInstance, SFXmixer);
    al_set_sample_instance_playmode(AttackSoundInstance, ALLEGRO_PLAYMODE_ONCE);
    al_play_sample_instance(AttackSoundInstance);
}