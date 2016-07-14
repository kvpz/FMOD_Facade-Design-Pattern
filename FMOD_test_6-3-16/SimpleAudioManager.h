/*
	Project 1 found in the book Getting Started with C++ Audio Programming
	for Game Development

	This class is a wrapper for the underlying FMOD system. This abstraction
	is called "facade design pattern", i.e. only exposing the operations that
	are needed as provided by an underlying system.

	The purpose of "#pragma once" is to cause the current source file to 
	inlclude the file only once in a single compilation. It works the same
	way as #ifndef #define include guards but much safer and possibly efficient.


*/
#pragma once
#include <string>
#include <map>
#include <fmod.hpp>

typedef std::map<std::string, FMOD::Sound*> SoundMap;

class SimpleAudioManager {
public:
	SimpleAudioManager();
	~SimpleAudioManager();
	void Update(float elapsed);
	void Load(const std::string& path);
	void Stream(const std::string& path);
	void Play(const std::string& path);
private:
	void LoadOrStream(const std::string& path, bool stream);
	FMOD::System* system;
	SoundMap sounds;	
};