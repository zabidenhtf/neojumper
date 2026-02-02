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

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"

#include "audio.hpp"


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

extern int dance_binds[]; //binds

struct dance_sequence{
vector<DANCE_MOVEMENTS> movements;
DANCE_LEVELS level;
int movements_count = 0;
double beat_speed = 0.6; // Speed of movements
};

// Melodies (now only 1 for test)
extern SoundSource Melody;

// main core, there is all game content
class game_core{
public:
    dance_sequence generate_dance(DANCE_LEVELS level);
    game_core();
    void reset();
    void update(double tick);
    bool game_started;
    dance_sequence now_dance;
    int score = 0;

    game_warmup *warmup;
    game_controls *controls;
    game_message *message;
    game_hud *hud;
};

extern game_core *game;
