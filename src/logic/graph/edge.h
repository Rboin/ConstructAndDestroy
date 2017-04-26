//
// Created by Sander on 2-3-2017.
//

#ifndef C_AND_D_PROJECT_EDGE_H
#define C_AND_D_PROJECT_EDGE_H

class Edge {
protected:
    int from;
    int to;
    float cost;
    bool active;
public:
    Edge(int, int, float);

    Edge(int, int);

    int get_from();
    int get_to();
    int get_cost();
    bool is_active();
    void set_active(bool);
};

#endif //C_AND_D_PROJECT_EDGE_H
