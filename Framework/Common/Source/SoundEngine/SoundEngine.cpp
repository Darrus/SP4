#include "SoundEngine.h"
#include <iostream>


SoundEngine::SoundEngine()
{
	engine = createIrrKlangDevice();
}

SoundEngine::~SoundEngine()
{
	ClearSounds();
	engine->drop();
	//if (engine)
		//delete engine;
	engine = nullptr;
}

void SoundEngine::AddSound(string name, string fileLoc, float volume)
{
	if (sources.find(name) == sources.end())
	{	
		ISoundSource* source = engine->addSoundSourceFromFile(fileLoc.c_str());
		source->setDefaultVolume(volume);
		sources.insert(pair<string, ISoundSource*>(name, source));
	}
	else
	{
		std::cout << "File already exist!" << std::endl;
	}
}

void SoundEngine::AddRepeatSound(string name, string fileLoc, float volume)
{
	if (sounds.find(name) == sounds.end())
	{
		ISound* sound = engine->play2D(fileLoc.c_str(), true, true);
		sound->setVolume(volume);
		sounds.insert(pair<string, ISound*>(name, sound));
	}
	else
	{
		std::cout << "File already exist!" << std::endl;
	}
}

void SoundEngine::Play(string name)
{
	map<string, ISoundSource*>::iterator sourceIt = sources.find(name);
	if (sourceIt != sources.end())
	{
		engine->play2D(sourceIt->second);
		return;
	}

	map<string, ISound*>::iterator it = sounds.find(name);
	if (it != sounds.end())
	{
		if (it->second->getIsPaused())
			it->second->setIsPaused(false);
		
		it->second->setPlayPosition(0);
		return;
	}

	std::cout << "Error playing" << name << " sound. Check filename." << std::endl;
}

void SoundEngine::Pause(string name)
{
	map<string, ISound*>::iterator it = sounds.find(name);
	if (it != sounds.end())
		it->second->setIsPaused(true);
	else
		std::cout << "Error stopping " << name << " sound. Check filename." << std::endl;
}

void SoundEngine::Remove(string name)
{
	bool check = false;
	map<string, ISoundSource*>::iterator sourceIt = sources.find(name);
	if (sourceIt != sources.end())
	{
		engine->removeSoundSource(sourceIt->second);
		if (sourceIt->second)
			sourceIt->second->drop();
		sources.erase(sourceIt);
		check = true;
	}

	map<string, ISound*>::iterator it = sounds.find(name);
	if (it != sounds.end())
	{
		engine->removeSoundSource(it->second->getSoundSource());
		if (it->second)
			it->second->drop();
		sounds.erase(it);
		check = true;
	}

	if (!check)
		std::cout << "Error removing " << name << " sound. Check filename." << std::endl;
}

void SoundEngine::ClearSounds()
{
	for (map<string, ISound*>::iterator it = sounds.begin(); it != sounds.end();)
	{
		if (it->second)
			it->second->drop();
		it = sounds.erase(it);
	}

	engine->removeAllSoundSources();

	for (map<string, ISoundSource*>::iterator it = sources.begin(); it != sources.end();)
	{
		it = sources.erase(it);
	}
}

void SoundEngine::SetMasterVolume(float volume)
{
	engine->setSoundVolume(volume);
}