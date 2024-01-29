#include <allegro5/allegro_acodec.h>
#include "../Include/sound.h"

#define FREQUENCY 44100
#define DEPTH ALLEGRO_AUDIO_DEPTH_FLOAT32
#define CHAN_CONFIG ALLEGRO_CHANNEL_CONF_2

SoundManager& SoundManager::GetManager() {
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager() = default;


SoundManager::~SoundManager() {
    CleanUp();
}

void SoundManager::CleanUp() {

    for (auto& sound : sounds) {
        al_destroy_sample(sound.second);
    }
    for (auto& instance : soundInstances) {
        al_destroy_sample_instance(instance.second);
    }

}

void SoundManager::initialize() {
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10); //edw mporoume na valome mexri kai 10 samples na paizoun

    mixers[SFX] = al_create_mixer(FREQUENCY, DEPTH, CHAN_CONFIG);
    mixers[LEVEL] = al_create_mixer(FREQUENCY, DEPTH, CHAN_CONFIG);
    mixers[VOICE] = al_create_mixer(FREQUENCY, DEPTH, CHAN_CONFIG);

    ALLEGRO_MIXER* masterMixer = al_create_mixer(FREQUENCY, DEPTH, CHAN_CONFIG);
    for (auto& mixer : mixers) {
        if (!mixer.second || !al_attach_mixer_to_mixer(mixer.second, masterMixer)) {
            std::cerr << "Failed to attach mixer!\n";
        }
    }

    voice = al_create_voice(FREQUENCY, ALLEGRO_AUDIO_DEPTH_INT16, CHAN_CONFIG);
    if (!voice || !al_attach_mixer_to_voice(masterMixer, voice)) {
        std::cerr << "Failed to create or attach voice!\n";
    }
}


void SoundManager::loadSound(SoundCategory category, const std::string& soundName, const std::string& filePath) {
    ALLEGRO_SAMPLE* sample = al_load_sample(filePath.c_str());
    if (sample) {
        sounds[soundName] = sample;
        ALLEGRO_SAMPLE_INSTANCE* sampleInstance = al_create_sample_instance(sample);
        soundInstances[soundName] = sampleInstance;
        if (!al_attach_sample_instance_to_mixer(sampleInstance, mixers[category])) {
            std::cerr << "Failed to attach sample instance to mixer for sound: " << soundName << "\n";
        }
    } else {
        std::cerr << "Failed to load sound: " << filePath << "\n";
    }
}

void SoundManager::playSound(const std::string& soundName, bool loop) {
    auto it = soundInstances.find(soundName);
    if (it != soundInstances.end()) {
        al_set_sample_instance_playmode(it->second, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE);
        al_play_sample_instance(it->second);
    } else {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
}

void SoundManager::stopSound(const std::string& soundName) {
    auto it = soundInstances.find(soundName);
    if (it != soundInstances.end()) {
        al_stop_sample_instance(it->second);
    } else {
        std::cerr << "Sound not found: " << soundName << std::endl;
    }
}

void SoundManager::setVolume(SoundCategory category, float volume) {
    if (mixers.find(category) != mixers.end()) {
        al_set_mixer_gain(mixers[category], volume);
    } else {
        std::cerr << "Mixer not found for category!\n";
    }
}
