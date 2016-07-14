Part of the book Getting Started with C++ Audio Programming for Game Development

Project 1 - Building a Simple Audio Manager
The purpose of this project is to learn how to incorporate the facade
design pattern. This will simplify the use of underlying libraries. This
program only allows you to load and play one-shot sound effects with very 
little code.

Project 2 - AudioManager

	Using a channel pointer will allow you to 
	control the sound in many ways. This handle remains valid while the sound has 
	not finished playing, or until sound is explicitly stopped.
	channel->stop()
	channel->setPaused(true) // false to resume
	channel->getPaused(&paused) // bool paused;
	
	To seek the sound to a different position in the file:
	channel->setPosition(0, FMOD_TIMEUNIT_MS);

	To control number of times sound should loop:
	channel->setLoopCount(-1) // Repeat endlessly
	channel->setLoopCount(0)	// Play once then stop
	channel->setLoopCount(2)  // Play three times, then stop

	Controlling the volume:
	channel->setVolume(1.0f) // takes values from 0 to 1
	channel->setMute(true) 
	float levels[2] = {0.0f, 1.0f}
	channel->setInputChannelMix(levels, 2) // modify the volume of each channel separately

	Controlling the pitch:
	channel->setFrequency(261.626f);
	If getFrequency() is called on a channel with its original frequency, we actually get
	the sampling rate of the sound. That means that any frequency value we set must be relative
	to this value (i.e. any sound above the original sampling rate will increase sound pitch).
		- octave: distance between two consecutive notes with the same name.
		- semitone: the distance between any two adjavent notes.
		If you multiply/ divide frequency by 2 we get new frequency one octave higher/lower.
		If you multiply/ divide frequency by 2 1/2 we get new frequency one semitone higher/lower.
		float ChangeOctave(float frequency, float variation) {
			static float octave_ratio = 2.0f;
			return frequency * pow(octave_ratio, variation);
		}
		float ChangeSemitone(float frequency, float variation) {
			static float semitone_ratio = pow(2.0f, 1.0f/12.0f);
			return frequency * pos(semitone_ratio, variation);
		}
		Note: Changing the frequency fo the sound will have the side effect of speeding it up or
		slowing it down. There is a way to change the pitch without changing the speed using
		DSP effect.

		Controlling the panning:
		channel->setPan(-1.0f) // takes values from -1 to 1
		Panning works by modifying the volume of each ouput to give the illusion of position. The
		way FMOD calculates these values is different between mono and stereo. (power vs linear curve)

		Grouping channels together:
		FMOD::ChannelGroup* musicGroup;
		system->createChannelGroup("music", &musicGroup);
		channel->setChannelGroup(musicGroup); // add a channel to a group
		channelGroup->addGroup(anotherGroup); // add a group as a child of another
		- A global (master) channel group is where every channel is placed every time you play a sound
		FMOD::ChannelGroup* masterGroup; 
		system->getMasterChannelGroup(&masterGroup); 
		- It is good to create a channel group for each category of sounds & add all to master 
		channel group. This way there is control over all and individual categories.

		Controlling groups of channels:
		Most operations are the same as for individual channels, except for pitch which is now setPitch()
		and it can take any value between 0 and 10 and multiplies it by the current frequency.