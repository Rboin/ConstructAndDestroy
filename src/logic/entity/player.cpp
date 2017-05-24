#include <world/world.h>
#include "player.h"
#include "state/state_machine.h"
#include "entity/moving/moving_entity.h"


Player::Player(int id) {
    _id = id;
    selected_building = nullptr;
    state_machine = new StateMachine<Player>(this);
    resources = new Resources(0, 0, 0, 0);
    buildings = std::vector<BuildingEntity *>();
    units = std::vector<MovingEntity *>();
    selected_units = std::vector<MovingEntity *>();
    resources = new Resources(50, 50, 50, 50);
}

void Player::update() {
    state_machine->update();
}

Player::~Player() {
    delete selected_building;
}


void Player::select_units_in_rectangle(float start_x, float start_y, float end_x, float end_y) {

    //first up deselect all currently selected units
    clear_all_selections();

    // The values below are needed to decide where the rectangle is.
    // we need to know which of the floats represents the left, right, top and bot border of the rectangle
    // so that we can determine whether a position is inside or outside the selection.

    //Case: Standard selection. From Top Left to right bottom.
    float left_offset = start_x;
    float right_offset = end_x;
    float top_offset = start_y;
    float bot_offset = end_y;

    //Case: Reversed selection. from Right to left
    if (start_x > end_x) {
        left_offset = end_x;
        right_offset = start_x;
    }

    //Case: Upwards selection. From bot to top.
    if (start_y > end_y) {
        top_offset = end_y;
        bot_offset = start_y;
    }


    for (int i = 0; i < this->units.size(); i++) {
        float x = this->units[i]->get_position().x;
        float y = this->units[i]->get_position().y;

        if (x >= left_offset && x <= right_offset && y >= top_offset && y <= bot_offset) {
            this->units[i]->select();
            this->selected_units.push_back(this->units[i]);
        }

    }
}


void Player::select_one_unit(vec2 pos) {


    //first up deselect all currently selected units
    clear_all_selections();

    //Create offsets of a rectangle. This is done because the image of a unit is also a rectangle but its position
    // is the top left corner of the rectangle. So we create a rectangle and look for the first unit found in the
    // created rectangle. Values where determined by testing a lot.
    float left_offset = pos.x - 45;
    float right_offset = pos.x;
    float top_offset = pos.y - 45;
    float bot_offset = pos.y;


    for (int i = 0; i < this->units.size(); i++) {

        float x = this->units[i]->get_position().x;
        float y = this->units[i]->get_position().y;

        if (x >= left_offset && x <= right_offset && y >= top_offset && y <= bot_offset) {
            this->units[i]->select();
            this->selected_units.push_back(this->units[i]);

            // exit for loop after selecting one unit.
            break;
        }
    }
}

void Player::select_building(vec2 pos) {
    float left_offset = pos.x - 45;
    float right_offset = pos.x;
    float top_offset = pos.y - 45;
    float bot_offset = pos.y;

    for (int i = 0; i < this->buildings.size(); i++) {
        if (this->buildings[i] != NULL && this->buildings[i] != nullptr) {
            float x = this->buildings[i]->get_position().x;
            float y = this->buildings[i]->get_position().y;

            if (x >= left_offset && x <= right_offset && y >= top_offset && y <= bot_offset) {
                this->buildings[i]->select();
                this->selected_building = this->buildings[i];
                // exit for loop after selecting one unit.
                break;
            }
        }
    }
}


void Player::clear_all_selections() {
    for (int i = 0; i < this->selected_units.size(); i++) {
        this->selected_units[i]->deselect();
    }

    if (selected_building != nullptr) {
        selected_building->deselect();
        selected_building = nullptr;
    }

    this->selected_units.clear();
}

int Player::get_id() {
    return _id;
}

void Player::remove_entity(BaseEntity *e) {
    if (MovingEntity *moving_entity = dynamic_cast<MovingEntity *>(e)) {
        if (moving_entity == nullptr) {
            delete moving_entity;
        } else {
            remove_unit(moving_entity);
        }
    } else if (BuildingEntity *building_entity = dynamic_cast<BuildingEntity *>(e)) {
        if (building_entity == nullptr) {
            delete building_entity;
        } else {
            remove_building(building_entity);
        }
    }
}

void Player::remove_unit(MovingEntity *e) {
    for (std::vector<MovingEntity *>::iterator iter = units.begin(); iter != units.end(); ++iter) {
        if (*iter == e) {
            units.erase(iter);
            break;
        }
    }
}

void Player::remove_building(BuildingEntity *e) {
    for (std::vector<BuildingEntity *>::iterator iter = buildings.begin(); iter != buildings.end(); ++iter) {
        if (*iter == e) {
            buildings.erase(iter);
            break;
        }
    }
}

void Player::clear_units() {
    for (std::vector<MovingEntity *>::iterator iter = units.begin(); iter != units.end(); ++iter) {
        World::get_instance()->remove_entity((*iter));
    }
    units.clear();
}
