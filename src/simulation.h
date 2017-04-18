//
// Created by robin on 3/19/17.
//

#ifndef C_AND_D_PROJECT_SIMULATION_H
#define C_AND_D_PROJECT_SIMULATION_H


class SimulationWindow;

template<typename T>
class EventHandler;

struct key_event_data;
struct mouse_event_data;

class Simulation {
private:
    SimulationWindow *_window;
    EventHandler<key_event_data> *_key_handler;
    EventHandler<mouse_event_data> *_mouse_handler;
public:
    Simulation(SimulationWindow *);

    ~Simulation();

    void set_key_handler(EventHandler<key_event_data> *);

    void set_mouse_handler(EventHandler<mouse_event_data> *);

    void loop();
};


#endif //C_AND_D_PROJECT_SIMULATION_H
