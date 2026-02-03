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

SoundData AudioSystem::LoadSound(string Path){
	// SO BIG THANKS FOR codetechandtutorials github user!
	ALenum err, format;
	ALuint buffer;
	SoundData SoundRetBuffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t num_frames;
	ALsizei num_bytes;

	/* Open the audio file and check that it's usable. */
	sndfile = sf_open(Path.c_str(), SFM_READ, &sfinfo);
	if (!sndfile)
	{
		Console.WriteDebug("AUDIO", "Could not open audio in " + Path);
	}
	if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
	{
		Console.WriteDebug("AUDIO", "Bad sample count");
		sf_close(sndfile);
	}

	/* Get the sound format, and figure out the OpenAL format */
	format = AL_NONE;
	if (sfinfo.channels == 1)
		format = AL_FORMAT_MONO16;
	else if (sfinfo.channels == 2)
		format = AL_FORMAT_STEREO16;
	else if (sfinfo.channels == 3)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT2D_16;
	}
	else if (sfinfo.channels == 4)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT3D_16;
	}
	if (!format)
	{
		Console.WriteDebug("AUDIO", "Unsupported channel count");
		sf_close(sndfile);
	}

	/* Decode the whole audio file to a buffer. */
	membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

	num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	if (num_frames < 1)
	{
		free(membuf);
		sf_close(sndfile);
		Console.WriteDebug("AUDIO", "Failed to read samples");
	}
	num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

	/* Buffer the audio data into a new buffer object, then free the data and
	 * close the file.
	 */
	buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

	free(membuf);
	sf_close(sndfile);

	/* Check if an error occured, and clean up if so. */
	err = alGetError();
	if (err != AL_NO_ERROR)
	{
		Console.WriteDebug("AUDIO", "OpenAL Error: " + string(alGetString(err)));
		if (buffer && alIsBuffer(buffer))
			alDeleteBuffers(1, &buffer);
	}

	SoundRetBuffer.Path = Path;
	SoundRetBuffer.Raw = buffer;  // add to the list of known buffers

	return SoundRetBuffer;
}