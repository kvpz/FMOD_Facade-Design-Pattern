#include "SimpleAudioManager.h"

SimpleAudioManager::SimpleAudioManager() {
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);
}

SimpleAudioManager::~SimpleAudioManager() {
	// Release every sound object and clear the map
	SoundMap::iterator iter;
	
	for (iter = sounds.begin(); iter != sounds.end(); ++iter)
		iter->second->release();
	sounds.clear();
	
	// Release the system object
	system->release();
	system = 0;
}

void SimpleAudioManager::Update(float elapsed) {
	system->update();
}

void SimpleAudioManager::LoadOrStream(const std::string& path, bool stream) {
	// Ignore call if sound is already loaded
	if (sounds.find(path) != sounds.end()) return;

	// Load (or stream) file into a sound object
	FMOD::Sound* sound;
	if (stream)
		system->createStream(path.c_str(), FMOD_DEFAULT, 0, &sound);
	else
		system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);

	// Store the sound object in the map using the path as key
	sounds.insert(std::make_pair(path, sound));
}

void SimpleAudioManager::Load(const std::string& path) {
	LoadOrStream(path, false);
}

void SimpleAudioManager::Stream(const std::string& path) {
	LoadOrStream(path, true);
}

void SimpleAudioManager::Play(const std::string& path) {
	// Search for a matching sound in the map
	SoundMap::iterator sound = sounds.find(path);

	// Ignore call if no sound was found 
	if (sound == sounds.end()) return;

	// otherwise play the sound
	system->playSound(FMOD_CHANNEL_FREE, sound->second, false, 0);
}

