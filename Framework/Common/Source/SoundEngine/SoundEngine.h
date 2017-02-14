#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <string>
#include <irrKlang.h>
#include <map>

#include "../SingletonTemplate.h"

using std::string;
using std::map;
using std::pair;
using namespace::irrklang;

class SoundEngine : public Singleton<SoundEngine>
{
private:
	map<string, ISoundSource*> sources;
	map<string, ISound*> sounds;
	ISoundEngine* engine;

public:
	friend Singleton<SoundEngine>;

	SoundEngine();
	~SoundEngine();
	
	void AddSound(string name, string fileLoc, float volume = 1.f);
	void AddRepeatSound(string name, string fileLoc, float volume = 1.f);
	void Play(string name);
	void Pause(string name);
	void Remove(string name);
	void SetMasterVolume(float volume = 1.f);
	void ClearSounds();
};

#endif