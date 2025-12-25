#include "game.hpp"

// To generate dance
DANCE_MOVEMENTS movements_list[] = {
JUMP,
KICK_LEFT,
KICK_RIGHT,
FLIP,
SHUFFLE_FORWARD,
SHUFFLE_BACKWARD
};

DANCE_LEVELS levels_list[]{
EASY,
NORMAL,
HARD
};
int dance_binds[] = {GLFW_KEY_SPACE,
                     GLFW_KEY_A,
                     GLFW_KEY_D,
                     GLFW_KEY_E,
                     GLFW_KEY_W,
                     GLFW_KEY_S}; // Binds

dance_sequence game_core::generate_dance(DANCE_LEVELS level){
    dance_sequence buffer;
    buffer.level = level;

    for (int i = 0; i < level; i++){
        DANCE_MOVEMENTS movement;

        if (buffer.movements.empty()){
            movement = movements_list[randint(0,5)];
        }
        else if (buffer.movements.back() == JUMP){
            movement = movements_list[FLIP];
        }
        else if (buffer.movements.back() == FLIP){
            DANCE_MOVEMENTS buffer = movements_list[randint(0,5)];
            while (buffer == FLIP){
                buffer = movements_list[randint(0,5)];
            }
            movement = buffer;
        }
        else if (buffer.movements.back() == KICK_LEFT || buffer.movements.back() == KICK_RIGHT){
            movement = movements_list[randint(0,5)];
        }
        else if (buffer.movements.back() == SHUFFLE_BACKWARD || buffer.movements.back() == SHUFFLE_FORWARD){
            movement = movements_list[randint(1,2)];
        }

        // Debug output
        switch (movement){
        case JUMP:
            write_dbg("GAME:generate_dance", "Added JUMP to dance");
            break;
        case KICK_LEFT:
            write_dbg("GAME:generate_dance", "Added KICK_LEFT to dance");
            break;
        case KICK_RIGHT:
            write_dbg("GAME:generate_dance", "Added KICK_RIGHT to dance");
            break;
        case FLIP:
            write_dbg("GAME:generate_dance", "Added FLIP to dance");
            break;
        case SHUFFLE_FORWARD:
            write_dbg("GAME:generate_dance", "Added SHUFFLE_FORWARD to dance");
            break;
        case SHUFFLE_BACKWARD:
            write_dbg("GAME:generate_dance", "Added SHUFFLE_BACKWARD to dance");
            break;
        }
        buffer.movements.push_back(movement);
    }

    return buffer;
}

game_core::game_core(){
    write_dbg("GAME", "game launched");

    now_dance = generate_dance(levels_list[randint(0,2)]);

    // Initialisating all components
    warmup_component = new warmup();
    controls_component = new controls();
    scene_component = new scene();

    controls_component->speed = now_dance.beat_speed;
    warmup_component->timer_time = WARMUP_TIME;
}

void game_core::update(double tick){
    // Updating scene for first
    scene_component->update(tick);
    warmup_component->update(tick);
    controls_component->update(tick);

    string buffer = "Now score:" + to_string(score);
    write_dbg("GAME", buffer);
}
