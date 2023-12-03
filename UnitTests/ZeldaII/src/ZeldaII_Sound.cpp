#include "../ZeldaII.h"
#include "../../../Engine/paths.h"
#include <iostream>
#include <map>
#include <allegro5/allegro_audio.h>


#define FREQUENCY 44100
#define DEPTH ALLEGRO_AUDIO_DEPTH_FLOAT32
#define CHAN_CONFIG ALLEGRO_CHANNEL_CONF_2
ALLEGRO_SAMPLE *levelsound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *levelsoundInstance = nullptr;
ALLEGRO_SAMPLE *AttackSound = nullptr;
ALLEGRO_SAMPLE_INSTANCE *AttackSoundInstance = nullptr;

ALLEGRO_MIXER *Levelmixer = nullptr;
ALLEGRO_MIXER *SFXmixer = nullptr;
ALLEGRO_MIXER *MasterMixer = nullptr;
ALLEGRO_VOICE *voice = nullptr;

void ZeldaII_Sound() {
    if (levelsound == nullptr) {
        levelsound = al_load_sample(ZELDA_II_PALACE_INTRO_MUSIC);
        levelsoundInstance = al_create_sample_instance(levelsound);
    }
    if (AttackSound == nullptr) {
        AttackSound = al_load_sample(ATTACK_SOUND);
        AttackSoundInstance = al_create_sample_instance(AttackSound);
    }
    if(Levelmixer == nullptr)
        Levelmixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);

    if(SFXmixer == nullptr)
        SFXmixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);

    if(MasterMixer == nullptr){
        MasterMixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);
        al_attach_mixer_to_mixer(Levelmixer,MasterMixer );
        al_attach_mixer_to_mixer(SFXmixer,MasterMixer );
    }
    if(voice  == nullptr){
        voice = al_create_voice(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16,CHAN_CONFIG);
        al_attach_mixer_to_voice(MasterMixer, voice);
        al_set_sample(levelsoundInstance, levelsound);
        al_attach_sample_instance_to_mixer(levelsoundInstance, Levelmixer);
        al_set_sample_instance_playmode(levelsoundInstance, ALLEGRO_PLAYMODE_LOOP);
        al_play_sample_instance(levelsoundInstance);
    }

    if(inputs.at("A")){
        PlayAttackSound();
    }




}

void TitleScreenSound(){}

void PlayAttackSound(){
    al_set_sample(AttackSoundInstance, AttackSound);
    al_attach_sample_instance_to_mixer(AttackSoundInstance, SFXmixer);
    al_set_sample_instance_playmode(AttackSoundInstance, ALLEGRO_PLAYMODE_ONCE);
    al_play_sample_instance(AttackSoundInstance);
}