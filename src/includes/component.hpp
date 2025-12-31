#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

class component{
public:
    virtual void reset() = 0;
    virtual void update(double tick) = 0;
    virtual void render() = 0;
};

#endif // GAME_COMPONENT_H
