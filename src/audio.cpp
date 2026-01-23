/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "interface.hpp"

// Devices define
ALCdevice* sound_device;
ALCcontext* sound_context;

void audio::init(){
	sound_device = alcOpenDevice(nullptr); // Get sound device
	if (!sound_device){
		write_dbg("AUDIO", "Failed to find sound device");
	}

	sound_context = alcCreateContext(sound_device, nullptr); // Creating context
	if (!sound_context){
		write_dbg("AUDIO", "Failed to create sound context");
	}
	alcMakeContextCurrent(sound_context);
	// Finding device
	const ALCchar* name = NULL;
	if (alcIsExtensionPresent(sound_device, "ALC_ENUMERATE_ALL_EXT")){
		name = alcGetString(sound_device, ALC_ALL_DEVICES_SPECIFIER);
	}
	if (!name || alcGetError(sound_device) != AL_NO_ERROR){
		name = alcGetString(sound_device, ALC_DEVICE_SPECIFIER);
	}

	string text_buffer = "Opened " + string(name) + " device";
	write_dbg("AUDIO", text_buffer);
}

sound audio::load_sound(string filename){
	// SO BIG THANKS FOR codetechandtutorials github user!
	ALenum err, format;
	ALuint buffer;
	sound s_buffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t num_frames;
	ALsizei num_bytes;

	/* Open the audio file and check that it's usable. */
	sndfile = sf_open(filename.c_str(), SFM_READ, &sfinfo);
	if (!sndfile)
	{
		write_dbg("AUDIO", "Could not open audio in " + filename);
	}
	if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
	{
		write_dbg("AUDIO", "Bad sample count");
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
		write_dbg("AUDIO", "Unsupported channel count");
		sf_close(sndfile);
	}

	/* Decode the whole audio file to a buffer. */
	membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

	num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	if (num_frames < 1)
	{
		free(membuf);
		sf_close(sndfile);
		write_dbg("AUDIO", "Failed to read samples");
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
		write_dbg("AUDIO", "OpenAL Error: " + string(alGetString(err)));
		if (buffer && alIsBuffer(buffer))
			alDeleteBuffers(1, &buffer);
	}

	s_buffer.path = filename;
	s_buffer.sound_buffer = buffer;  // add to the list of known buffers

	return s_buffer;
}