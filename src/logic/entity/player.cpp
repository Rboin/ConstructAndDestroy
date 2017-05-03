#include "player.h"
#include "entity/moving/moving_entity.h"

Player::Player() {
    this->resources = Resources();
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
    float leftOffset = start_x;
    float rightOffset = end_x;
    float topOffset = start_y;
    float botOffset = end_y;

    //Case: Reversed selection. from Right to left
    if(start_x > end_x){
        leftOffset = end_x;
        rightOffset = start_x;
    }

    //Case: Upwards selection. From bot to top.
    if(start_y > end_y){
        topOffset = end_y;
        botOffset = start_y;
    }



    for(int i = 0; i < this->units.size();i++){

        float x = this->units[i]->get_position().x;
        float y = this->units[i]->get_position().y;

        if(x >= leftOffset && x <= rightOffset && y >= topOffset && y <= botOffset){
            this->units[i]->select();
            this->units[i]->take_possession();
            this->selected_units.push_back(this->units[i]);
        }
    }
}


void Player::clear_selected_units() {
    for(int i = 0; i < this->selected_units.size(); i++){
        this->selected_units[i]->deselect();
        this->selected_units[i]->exorcise();
    }
    this->selected_units.clear();
}