#ifndef CONSTRUCT_AND_DESTROY_RESOURCES_H
#define CONSTRUCT_AND_DESTROY_RESOURCES_H
class Resources {
public:
    float gold;
    float wood;
    float stone;

    Resources();
    Resources(float gold, float wood, float stone);
    virtual ~Resources();
    
};
#endif //CONSTRUCT_AND_DESTROY_RESOURCES_H
