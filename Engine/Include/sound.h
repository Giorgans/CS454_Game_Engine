#ifndef CS454_SUPER_MARIO_GAME_SOUND_H
#define CS454_SUPER_MARIO_GAME_SOUND_H

#include <iostream>
#include <string>
#include <map>
#include <allegro5/allegro_audio.h>

class SoundManager {
public:
    enum SoundCategory { SFX, LEVEL, VOICE };

    static SoundManager& getInstance();

    void loadSound(SoundCategory category, const std::string& soundName, const std::string& filePath);
    void playSound(const std::string& soundName, bool loop = false);
    void stopSound(const std::string& soundName);
    void setVolume(SoundCategory category, float volume);
    void initialize(); // Initialize mixers and voice

    SoundManager(SoundManager const&) = delete;
    void operator=(SoundManager const&) = delete;

private:
    SoundManager();
    ~SoundManager();

    std::map<std::string, ALLEGRO_SAMPLE*> sounds;
    std::map<std::string, ALLEGRO_SAMPLE_INSTANCE*> soundInstances;
    std::map<SoundCategory, ALLEGRO_MIXER*> mixers;
    ALLEGRO_VOICE *voice = nullptr;
};

#endif
