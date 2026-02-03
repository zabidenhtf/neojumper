/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#define WARMUP_TIME 4

// Components
#include "components/warmup.hpp"
#include "components/controls.hpp"
#include "components/message.hpp"
#include "components/hud.hpp"

#include "utils/system.hpp"
#include "utils/audio.hpp"

#include "includes.hpp"


enum DANCE_MOVEMENTS{
KICK_LEFT_FORWARD,
KICK_RIGHT_FORWARD,
KICK_LEFT_BACKWARD,
KICK_RIGHT_BACKWARD,
STAND_LEFT,
STAND_RIGHT,
FLIP
};

enum DANCE_LEVELS{ // Count of patterns
EASY=4,
NORMAL=6,
HARD=8
};

enum DANCE_SIDE{
	LEFT,
	RIGHT
};

extern int DanceBinds[]; //binds

struct DanceSequence{
vector<DANCE_MOVEMENTS> Movements;
DANCE_LEVELS Level;
int MovementsCount = 0;
double BeatSpeed = 0.6; // Speed of movements
};

// Melodies (now only 1 for test)
extern SoundSource Melody;

class GameCore{
public:
    void AddScore(int N){Score+N;}; // Add score
    int GetScore(){return Score;}; // Interface for score
    DanceSequence GenerateDance(DANCE_LEVELS level);
    GameCore();
    void Reset();
    void Update(float Tick);
    bool GameStarted; // If warmup ended it true
    DanceSequence NowDance; // Dance sequence now
    // Compontents
    GameWarmup *Warmup;
    GameControls *Controls;
    GameMessage *Message;
    GameHud *Hud;
private:
    int Score = 0;
};

extern GameCore *Game;
