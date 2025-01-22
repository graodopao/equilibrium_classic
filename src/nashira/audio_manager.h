#pragma once
#include "asset_manager.h"

namespace nashira {
	class AudioManager
	{
	private:
		static AudioManager* s_instance;
		AssetManager* m_asset_manager;
	public:

		static AudioManager* instance();
		static void release();

		void play_music(const std::string &filename, int loops = -1) const;

		static void pause_music();

		static void resume_music();

		void play_sfx(const std::string &filename, int loops = false, int channel = 0) const;

	private:

		AudioManager();
		~AudioManager();
	};
}