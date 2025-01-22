#include "audio_manager.h"
using namespace nashira;

AudioManager *AudioManager::s_instance = nullptr;

AudioManager *AudioManager::instance() {
    if (s_instance == nullptr) {
        s_instance = new AudioManager();
    }

    return s_instance;
}

void AudioManager::release() {
    delete s_instance;
    s_instance = nullptr;
}

AudioManager::AudioManager() {
    m_asset_manager = AssetManager::instance();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("Mixer initialization error: %s\n", Mix_GetError());
    }
}

AudioManager::~AudioManager() {
    m_asset_manager = nullptr;
    Mix_Quit();
}

void AudioManager::play_music(const std::string &filename, const int loops) const {
    Mix_PlayMusic(m_asset_manager->get_music(filename), loops);
}

void AudioManager::pause_music() {
    if (Mix_PlayingMusic() != 0) {
        Mix_PauseMusic();
    }
}

void AudioManager::resume_music() {
    if (Mix_PausedMusic() != 0) {
        Mix_ResumeMusic();
    }
}

void AudioManager::play_sfx(const std::string &filename, const int loops, const int channel) const {
    Mix_PlayChannel(channel, m_asset_manager->get_sfx(filename), loops);
}
