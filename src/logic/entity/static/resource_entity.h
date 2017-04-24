//
// Created by Sander on 20-3-2017.
//

#ifndef C_AND_D_PROJECT_RESOURCE_ENTITY_H
#define C_AND_D_PROJECT_RESOURCE_ENTITY_H


#include "static_entity.h"
#include "resource_type.h"

class ResourceEntity : public StaticEntity {
private:
    //Determines the kind of resource
    ResourceType resource_type;
    //Amount of units the resource actually has
    float _units;
    //The max units a resource can have, this could be influenced by upgrades
    float _max_units;
    //The rate at which the units replenish, this could be influenced by upgrades
    float _replenish_rate;
    bool _depleted;
    TextureTypes _texture;
    TextureTypes _depleted_texture;

    TextureTypes _current_texture;
public:
    ResourceEntity(const mesh*,vec2,float, ResourceType, TextureTypes, TextureTypes);
    ResourceEntity(const mesh*,vec2,float, ResourceType, TextureTypes);

    /*!
     * @return resource type
     */
    ResourceType get_resource_type();

    /*!
     * @return units
     */
    int get_units();

    /*!
     * Extracts from units and returns that same number.
     * @return
     */
    float gather();

    /*!
     * Adds a very small amount to the units
     */
    void replenish_resource();

    /*!
     * @return true if the resource depleted
     */
    bool is_depleted();

    /*!
     * Updates the texture when needed to the correct texture.
     */
    void update_texture();
};


#endif //C_AND_D_PROJECT_RESOURCE_ENTITY_H
