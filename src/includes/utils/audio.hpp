/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "utils/system.hpp"
#include "utils/data.hpp"
#include "includes.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#pragma once

using namespace glm;

class SoundSource{ // Source of sound
public:
	SoundSource(); // Constructor
    SoundData Data; // Raw stuff
	void PlayGlobal();
	void Play(vec3 Position);
	void Stop(){alSourceStop(Source);};
private:
    ALuint Source; // AL source
};

class AudioSystem{
public:
	AudioSystem(); // Constructor
	int GetVolume(){return SoundVolume;};
private:
	int SoundVolume; // Global sound volume
	ALCdevice* SoundDevice;
	ALCcontext* SoundContext;
};

extern AudioSystem *Audio; // Global audio pointer