//
// Created by Sander on 20-3-2017.
//

#ifndef C_AND_D_PROJECT_RESOURCE_ENTITY_H
#define C_AND_D_PROJECT_RESOURCE_ENTITY_H

#include <string>
#include "static_entity.h"
#include "resource_type.h"

class ResourceEntity : public StaticEntity {
private:
    //Determines the kind of resource
    ResourceType _resource_type;
    //Amount of units the resource actually has
    float _units;
    //The max units a resource can have, this could be influenced by upgrades
    float _max_units;
    //The rate at which the units replenish, this could be influenced by upgrades
    float _replenish_rate;
    bool _depleted;
    std::string _texture;
    std::string _depleted_texture;
    std::string _current_texture;
public:
    ResourceEntity(vec2,float, ResourceType);

    ~ResourceEntity();

    void set_textures(std::string, std::string);
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
    float gather(float d_t);

    /*!
     * Adds a very small amount to the units
     */
    void replenish_resource(float d_t);

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
