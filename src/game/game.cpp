/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "game.hpp"

#include "utils/data.hpp"

// To generate dance
DANCE_MOVEMENTS MovementsList[] = {
KICK_LEFT_FORWARD,
KICK_RIGHT_FORWARD,
KICK_LEFT_BACKWARD,
KICK_RIGHT_BACKWARD,
STAND_LEFT,
STAND_RIGHT,
FLIP
};

DANCE_LEVELS LevelsList[]{
EASY,
NORMAL,
HARD
};
int DanceBinds[] = {
                     GLFW_KEY_Q, // KICK_LEFT_FORWARD
                     GLFW_KEY_E, // KICK_RIGHT_FORWARD
                     GLFW_KEY_Z, // KICK_LEFT_BACKWARD
                     GLFW_KEY_C, // KICK_RIGHT_BACKWARD
                     GLFW_KEY_A, // STAND_LEFT
                     GLFW_KEY_D,  // STAND_RIGHT
                     GLFW_KEY_SPACE // FLIP
                     }; // Binds

// Dance patterns
vector<DANCE_MOVEMENTS> PatternJumpLeftSide = {KICK_LEFT_FORWARD, KICK_LEFT_FORWARD, KICK_RIGHT_FORWARD, KICK_RIGHT_BACKWARD, STAND_LEFT}; // On keyboard Q Q E C A
vector<DANCE_MOVEMENTS> PatternFlipLeftSide = {KICK_LEFT_FORWARD, KICK_LEFT_FORWARD, FLIP}; // On keyboard Q Q Space

// Melodies (now only 1 for test)
SoundSource Melody;

// Generate dance
DanceSequence GameCore::GenerateDance(DANCE_LEVELS level){
    DanceSequence Buffer;
    Buffer.Level = level;

    // For level patterns count cloning patterns
    for (int i = 0; i < level; i++){
        DANCE_MOVEMENTS Movement;
        // Selector
        int d = RandomInt(0,1);
        if (d == 0){
            for (int x = 0; x<PatternJumpLeftSide.size(); x++){
                Movement = PatternJumpLeftSide[x];
                Buffer.Movements.push_back(Movement);
                // Debug output
                switch (Movement){
                    case KICK_LEFT_FORWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_LEFT_FORWARD to dance");
                        break;
                    case KICK_RIGHT_FORWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_RIGHT_FORWARD to dance");
                        break;
                    case KICK_LEFT_BACKWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_LEFT_BACKWARD to dance");
                        break;
                    case KICK_RIGHT_BACKWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_RIGHT_BACKWARD to dance");
                        break;
                    case STAND_LEFT:
                        Console.WriteDebug("GAME:generate_dance", "Added STAND_LEFT to dance");
                        break;
                    case STAND_RIGHT:
                        Console.WriteDebug("GAME:generate_dance", "Added STAND_RIGHT to dance");
                        break;
                    case FLIP:
                        Console.WriteDebug("GAME:generate_dance", "Added FLIP to dance");
                        break;
                }
                Buffer.MovementsCount ++;
            }
        }
        else{
             for (int x = 0; x<PatternFlipLeftSide.size(); x++){
                Movement = PatternFlipLeftSide[x];
                Buffer.Movements.push_back(Movement);
                // Debug output
                switch (Movement){
                    case KICK_LEFT_FORWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_LEFT_FORWARD to dance");
                        break;
                    case KICK_RIGHT_FORWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_RIGHT_FORWARD to dance");
                        break;
                    case KICK_LEFT_BACKWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_LEFT_BACKWARD to dance");
                        break;
                    case KICK_RIGHT_BACKWARD:
                        Console.WriteDebug("GAME:generate_dance", "Added KICK_RIGHT_BACKWARD to dance");
                        break;
                    case STAND_LEFT:
                        Console.WriteDebug("GAME:generate_dance", "Added STAND_LEFT to dance");
                        break;
                    case STAND_RIGHT:
                        Console.WriteDebug("GAME:generate_dance", "Added STAND_RIGHT to dance");
                        break;
                    case FLIP:
                        Console.WriteDebug("GAME:generate_dance", "Added FLIP to dance");
                        break;
                }
                Buffer.MovementsCount ++;
            }
        }
        
    }

    return Buffer;
}

GameCore::GameCore(){
    Console.WriteDebug("GAME", "game launched");

    // Initialisating all components
    Warmup = new GameWarmup();
    Controls = new GameControls();
    Message = new GameMessage();
    Hud = new GameHud();
}

// Reseting all game stuff
void GameCore::Reset(){
    // Resetings game params
    Score = 0;
    GameStarted = false;
    NowDance = GenerateDance(LevelsList[RandomInt(0,2)]);
    // Reseting components
    Warmup->Reset();
    Controls->Reset();
    Message->Reset();
    Hud->Reset();
    // Adding melody
    Melody.Data = Data->GetSoundByID(INGAME_MELODY1);
    Melody.PlayGlobal();
    // Configuring components
    Controls->Speed = NowDance.BeatSpeed;
    Warmup->WarmupTime = WARMUP_TIME;
}

void GameCore::Update(float Tick){
    Warmup->Update(Tick);
    Controls->Update(Tick);
    Message->Update(Tick);
    Hud->Update(Tick);
}
