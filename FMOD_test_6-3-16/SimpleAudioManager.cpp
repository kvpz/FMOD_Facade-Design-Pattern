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

/*
	Many features used will work properly only if we update the
	system object.
*/
void SimpleAudioManager::Update(float elapsed) {
	system->update();
}
																
/*
	Note that there is a tradeoff between streaming or loading a sound file.
	Loading: con: all of its data is uncompressed and stored in
			memory
		pro: the computer can play it without much effort. 
	Streaming: 
		pro: barely uses memory
		con: the computer has to access the disk constantly and decode on the fly. 
	Another difference (in FMOD, at least) is that when you stream a sound, you
	can only have one instance of it playing at any time. This limitation exists
	because there is only one decode buffer per stream. Therefore, for sound 
	effects that have to be played multiple times simultaneously, you have to
	either load them into memory, or open up concurrent streams. 

	Streaming is great for music, voice cues, and ambient tracks.
	Loading is best for most sound effects.
*/
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
/*
	The fourh parameter of playSound can be &channel. Seen in AudioManager.cpp.		
*/
void SimpleAudioManager::Play(const std::string& path) {
	// Search for a matching sound in the map
	SoundMap::iterator sound = sounds.find(path);

	// Ignore call if no sound was found 
	if (sound == sounds.end()) return;

	// otherwise play the sound
	system->playSound(FMOD_CHANNEL_FREE, sound->second, false, 0);
}

