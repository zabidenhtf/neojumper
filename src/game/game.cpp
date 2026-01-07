#include "game.hpp"

// To generate dance
DANCE_MOVEMENTS movements_list[] = {
KICK_LEFT_FORWARD,
KICK_RIGHT_FORWARD,
KICK_LEFT_BACKWARD,
KICK_RIGHT_BACKWARD,
STAND_LEFT,
STAND_RIGHT,
FLIP
};

DANCE_LEVELS levels_list[]{
EASY,
NORMAL,
HARD
};
int dance_binds[] = {
                     GLFW_KEY_Q, // KICK_LEFT_FORWARD
                     GLFW_KEY_E, // KICK_RIGHT_FORWARD
                     GLFW_KEY_Z, // KICK_LEFT_BACKWARD
                     GLFW_KEY_C, // KICK_RIGHT_BACKWARD
                     GLFW_KEY_A, // STAND_LEFT
                     GLFW_KEY_D,  // STAND_RIGHT
                     GLFW_KEY_SPACE // FLIP
                     }; // Binds

dance_sequence game_core::generate_dance(DANCE_LEVELS level){
    dance_sequence buffer;
    buffer.level = level;

    for (int i = 0; i < level; i++){
        DANCE_MOVEMENTS movement;

        if (buffer.movements.empty()){
            movement = movements_list[randint(0,6)];
        }
        
        // Debug output
        switch (movement){
        case KICK_LEFT_FORWARD:
            write_dbg("GAME:generate_dance", "Added KICK_LEFT_FORWARD to dance");
            break;
        case KICK_RIGHT_FORWARD:
            write_dbg("GAME:generate_dance", "Added KICK_RIGHT_FORWARD to dance");
            break;
        case KICK_LEFT_BACKWARD:
            write_dbg("GAME:generate_dance", "Added KICK_LEFT_BACKWARD to dance");
            break;
        case KICK_RIGHT_BACKWARD:
            write_dbg("GAME:generate_dance", "Added KICK_RIGHT_BACKWARD to dance");
            break;
        case STAND_LEFT:
            write_dbg("GAME:generate_dance", "Added STAND_LEFT to dance");
            break;
        case STAND_RIGHT:
            write_dbg("GAME:generate_dance", "Added STAND_RIGHT to dance");
            break;
        case FLIP:
            write_dbg("GAME:generate_dance", "Added FLIP to dance");
            break;
        }
        buffer.movements.push_back(movement);
    }

    return buffer;
}

game_core::game_core(){
    write_dbg("GAME", "game launched");

    // Initialisating all components
    warmup = new game_warmup();
    controls = new game_controls();
    message = new game_message();
    reset();
}

void game_core::reset(){
    score = 0;
    game_started = false;
    now_dance = generate_dance(levels_list[randint(0,2)]);
    warmup->reset();
    controls->reset();
    message->reset();
    controls->speed = now_dance.beat_speed;
    warmup->timer_time = WARMUP_TIME;
}

void game_core::update(double tick){
    // Updating scene for first
    warmup->update(tick);
    controls->update(tick);
    message->update(tick);

    string buffer = "Now score:" + to_string(score);
    write_dbg("GAME", buffer);
}
