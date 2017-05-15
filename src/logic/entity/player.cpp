#include "entity/state/state_machine.h"
#include "player.h"
#include "entity/moving/moving_entity.h"
#include "../globals.cpp"

Player::Player(int id) {
    _id = id;
    state_machine = new StateMachine<Player>(this);
    resources = new Resources(0, 0, 0, 0);
}

void Player::update() {
    state_machine->update();
}

Player::~Player() {
}


void Player::select_units_in_rectangle(float start_x, float start_y, float end_x, float end_y) {

    //first up deselect all currently selected units
    clear_selected_units();

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
    clear_selected_units();

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

void Player::clear_selected_units() {
    for (int i = 0; i < this->selected_units.size(); i++) {
        this->selected_units[i]->deselect();
    }
    this->selected_units.clear();
}

int Player::get_id() {
    return _id;

}