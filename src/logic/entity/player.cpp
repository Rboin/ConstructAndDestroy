#include "entity/state/state_machine.h"
#include "player.h"
#include "entity/moving/moving_entity.h"
#include "../globals.cpp"


Player::Player(int id) {
    _id = id;

    state_machine = new StateMachine<Player>(this);
}

void Player::update() {
    state_machine->update();
}

Player::~Player() {
}


void Player::select_units_in_rectangle(float start_x, float start_y, float end_x, float end_y) {

    //first up deselect all currently selected units
    clear_all_selections();

    // The values below are needed to decide where the rectangle is.
    // we need to know which of the floats represents the left, right, top and bot border of the rectangle
    // so that we can determine whether a position is inside or outside the selection.

    //Case: Standard selection. From Top Left to right bottom.
    float leftOffset = start_x;
    float rightOffset = end_x;
    float topOffset = start_y;
    float botOffset = end_y;

    //Case: Reversed selection. from Right to left
    if (start_x > end_x) {
        leftOffset = end_x;
        rightOffset = start_x;
    }

    //Case: Upwards selection. From bot to top.
    if (start_y > end_y) {
        topOffset = end_y;
        botOffset = start_y;
    }


    for (int i = 0; i < this->units.size(); i++) {
        if (units[i]->get_player()->get_id() == player_id) {
            float x = this->units[i]->get_position().x;
            float y = this->units[i]->get_position().y;

            if (x >= leftOffset && x <= rightOffset && y >= topOffset && y <= botOffset) {

                this->units[i]->select();
                this->units[i]->take_possession();
                this->selected_units.push_back(this->units[i]);
            }
        }
    }
}


void Player::select_one_unit(vec2 pos) {


    //first up deselect all currently selected units
    clear_all_selections();

    //Create offsets of a rectangle. This is done because the image of a unit is also a rectangle but its position
    // is the top left corner of the rectangle. So we create a rectangle and look for the first unit found in the
    // created rectangle. Values where determined by testing alot.
    float leftOffset = pos.x - 45;
    float rightOffset = pos.x;
    float topOffset = pos.y -45;
    float botOffset = pos.y;


    for (int i = 0; i < this->units.size(); i++) {

        float x = this->units[i]->get_position().x;
        float y = this->units[i]->get_position().y;

        if (x >= leftOffset && x <= rightOffset && y >= topOffset && y <= botOffset) {
            this->units[i]->select();
            this->units[i]->take_possession();
            this->selected_units.push_back(this->units[i]);

            // exit for loop after selecting one unit.
            break;
        }
    }


}

void Player::select_building(vec2 pos) {
    float leftOffset = pos.x - 45;
    float rightOffset = pos.x;
    float topOffset = pos.y -45;
    float botOffset = pos.y;

    for (int i = 0; i < this->buildings.size(); i++) {
        float x = this->buildings[i]->get_position().x;
        float y = this->buildings[i]->get_position().y;

        if (x >= leftOffset && x <= rightOffset && y >= topOffset && y <= botOffset) {
            this->buildings[i]->select();
            this->selected_building = this->buildings[i];
            // exit for loop after selecting one unit.
            break;
        }
    }
}


void Player::clear_all_selections() {
    for (int i = 0; i < this->selected_units.size(); i++) {
        this->selected_units[i]->deselect();
        this->selected_units[i]->exorcise();
    }
    this->selected_units.clear();
}

int Player::get_id() {
    return _id;
}

