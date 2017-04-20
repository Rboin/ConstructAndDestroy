//
// Created by robin on 4/19/17.
//

#include <QGraphicsScene>
#include <QGraphicsView>
#include "world_panel.h"
#include "view/game_view.h"
#include "vector.h"

WorldPanel::WorldPanel(vec2 &size, vec2 &position) : Component(size, position) {
    _game_view = new GameView(size, position);
    _game_view->setParent(this);
}
