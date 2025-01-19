#pragma once
#include "asset_manager.h"

namespace nashira {
	class AudioManager
	{
	private:
		static AudioManager* sInstance;
		AssetManager* mAssetManager;
	public:

		static AudioManager* Instance();
		static void Release();

		void PlayMusic(std::string filename, int loops = -1);
		void PauseMusic();
		void ResumeMusic();

		void PlaySFX(std::string filename, int loops = false, int channel = 0);

	private:

		AudioManager();
		~AudioManager();
	};
}