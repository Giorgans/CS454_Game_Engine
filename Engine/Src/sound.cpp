//
// Created by Georgios Zervos on 23/1/23.
//
#include "../Include/sound.h"
#define FREQUENCY 44100
#define DEPTH ALLEGRO_AUDIO_DEPTH_FLOAT32
#define CHAN_CONFIG ALLEGRO_CHANNEL_CONF_2
ALLEGRO_SAMPLE *levelsound = NULL;
ALLEGRO_SAMPLE_INSTANCE *levelsoundInstance = NULL;
ALLEGRO_MIXER *mixer = NULL;
ALLEGRO_AUDIO_STREAM *stream;
ALLEGRO_VOICE *voice = NULL;
void Sound() {
    if (levelsound == NULL) {
        levelsound = al_load_sample(level);
        levelsoundInstance = al_create_sample_instance(levelsound);
    }
    if(mixer == NULL){
        mixer = al_create_mixer(FREQUENCY,DEPTH, CHAN_CONFIG);
    }
    if(voice  == NULL){
        voice = al_create_voice(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16,CHAN_CONFIG);
        al_attach_mixer_to_voice(mixer, voice);
        al_set_sample(levelsoundInstance, levelsound);
        al_attach_sample_instance_to_mixer(levelsoundInstance, mixer);
        al_set_sample_instance_playmode(levelsoundInstance, ALLEGRO_PLAYMODE_LOOP);
        al_play_sample_instance(levelsoundInstance);
    }
}