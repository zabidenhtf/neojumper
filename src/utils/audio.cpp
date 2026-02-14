/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "utils/audio.hpp"
#include <climits>

AudioSystem *Audio;

/* SOUND SOURCE */
SoundSource::SoundSource(){
    Console.WriteDebug("AUDIO", "Created sound source");
}

void SoundSource::PlayGlobal(){
	// Creating AL source
    alGenSources(1, &Source);
	// Configurating source
    alSourcef(Source, AL_PITCH, 1.0f);
    alSourcef(Source, AL_GAIN, static_cast<float>(Audio->GetVolume())/100);
    alSourcei(Source, AL_SOURCE_RELATIVE, AL_TRUE); // Global sound
    alSource3f(Source, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSourcei(Source, AL_BUFFER, Data.Raw);
    alSourcePlay(Source); // Playing sound
	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);

	if (state == AL_PLAYING) {
	    Console.WriteDebug("AUDIO", "Playing " + Data.Path);
	}
}

void SoundSource::Play(vec3 Position){
	// Creating AL source
    alGenSources(1, &Source);
	// Configurating source
    alSourcef(Source, AL_PITCH, 1.0f);
    alSourcef(Source, AL_GAIN, static_cast<float>(Audio->GetVolume())/100);
    alSource3f(Source, AL_POSITION, Position.x, Position.y, Position.z);
    alSourcei(Source, AL_BUFFER, Data.Raw);
    alSourcePlay(Source); // Playing sound
	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);

	if (state == AL_PLAYING) {
	    Console.WriteDebug("AUDIO", "Playing " + Data.Path);
	}
}

/* AUDIO SYSTEM */
AudioSystem::AudioSystem(){
	SoundDevice = alcOpenDevice(nullptr); // Get sound device
	if (!SoundDevice){
		Console.WriteDebug("AUDIO", "Failed to find sound device");
	}

	SoundContext = alcCreateContext(SoundDevice, nullptr); // Creating context
	if (!SoundContext){
		Console.WriteDebug("AUDIO", "Failed to create sound context");
	}
	alcMakeContextCurrent(SoundContext);
	// Finding device
	const ALCchar* Name = NULL;
	if (alcIsExtensionPresent(SoundDevice, "ALC_ENUMERATE_ALL_EXT")){
		Name = alcGetString(SoundDevice, ALC_ALL_DEVICES_SPECIFIER);
	}
	if (!Name || alcGetError(SoundDevice) != AL_NO_ERROR){
		Name = alcGetString(SoundDevice, ALC_DEVICE_SPECIFIER);
	}

	string TextBuffer = "Opened " + string(Name) + " device";
	Console.WriteDebug("AUDIO", TextBuffer);
}