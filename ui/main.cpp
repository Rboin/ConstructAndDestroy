//
// Created by robin on 4/19/17.
//


#include <QtWidgets/QApplication>
#include "component.h"

int main(int argc, char **argv) {
    QApplication application(argc, argv);
    Component window(200, 200);
    window.show();
    return application.exec();
}