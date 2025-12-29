#ifndef SCENE_ENTITY_H
#define SCENE_ENTITY_H

class entity{
public:
    virtual void reset() = 0;
    virtual void update(double tick) = 0;
    virtual void render() = 0;
};

#endif // SCENE_ENTITY_H
