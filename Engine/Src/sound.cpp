//
// Created by Georgios Zervos on 23/1/23.
//
#include "../Include/sound.h"
#include "../Include/timing.h"
#include "../paths.h"
#include <map>
extern std::map<std::string,bool> inputs;

#define FREQUENCY 44100
#define DEPTH ALLEGRO_AUDIO_DEPTH_FLOAT32
#define CHAN_CONFIG ALLEGRO_CHANNEL_CONF_2
ALLEGRO_SAMPLE *levelsound = NULL;
ALLEGRO_SAMPLE_INSTANCE *levelsoundInstance = NULL;
ALLEGRO_SAMPLE *AttackSound = NULL;
ALLEGRO_SAMPLE_INSTANCE *AttackSoundInstance = NULL;

ALLEGRO_MIXER *Levelmixer = NULL;
ALLEGRO_MIXER *SFXmixer = NULL;
ALLEGRO_MIXER *MasterMixer = NULL;
ALLEGRO_VOICE *voice = NULL;
uint64_t lastAttack=0;

void Sound() {
/*
    if (levelsound == NULL) {
        levelsound = al_load_sample(LEVEL_MUSIC_PATH);
        levelsoundInstance = al_create_sample_instance(levelsound);
    }
    if (AttackSound == NULL) {
        AttackSound = al_load_sample(ATTACK_SOUND);
        AttackSoundInstance = al_create_sample_instance(AttackSound);
    }
    if(Levelmixer == NULL)
        Levelmixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);

    if(SFXmixer == NULL)
        SFXmixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);

    if(MasterMixer == NULL){
        MasterMixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);
        al_attach_mixer_to_mixer(Levelmixer,MasterMixer );
        al_attach_mixer_to_mixer(SFXmixer,MasterMixer );
    }
    if(voice  == NULL){
        voice = al_create_voice(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16,CHAN_CONFIG);
        al_attach_mixer_to_voice(MasterMixer, voice);
        al_set_sample(levelsoundInstance, levelsound);
        al_attach_sample_instance_to_mixer(levelsoundInstance, Levelmixer);
        al_set_sample_instance_playmode(levelsoundInstance, ALLEGRO_PLAYMODE_LOOP);
        al_play_sample_instance(levelsoundInstance);
    }
    if(inputs.at("A") && (GetSystemTime()-lastAttack >=300) ){
        PlayAttackSound();
        lastAttack = GetSystemTime();
    }

*/
}

void PlayAttackSound(){
    al_set_sample(AttackSoundInstance, AttackSound);
    al_attach_sample_instance_to_mixer(AttackSoundInstance, SFXmixer);
    al_set_sample_instance_playmode(AttackSoundInstance, ALLEGRO_PLAYMODE_ONCE);
    al_play_sample_instance(AttackSoundInstance);

}