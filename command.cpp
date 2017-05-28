#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Command {
public:
    virtual void execute() = 0;
};

class Light {
public:
    void on() {
        cout << "Light on" << endl;
    }
    void off() {
        cout << "Light off" << endl;
    }
};

class LightOnCommand: public Command {
    Light *_light;
public:
    LightOnCommand(Light *l) {
        _light = l;
    }
    void execute() {
        _light->on();
    }
};

class GarageDoor {
public:
    void open() {
        cout << "Garage door open" << endl;
    }
    void close() {
        cout << "Garage door close" << endl;
    }
};

class GarageDoorOpenCommand: public Command {
    GarageDoor *_garage_door;
public:
    GarageDoorOpenCommand(GarageDoor *g) {
        _garage_door = g;
    }
    void execute() {
        _garage_door->open();
    }
};

class RemoteControl {
    enum {
        MAX_BUTTONS = 7,
    };
    Command *_commands[MAX_BUTTONS];
    int _last_button;

public:
    RemoteControl() {
        _last_button = MAX_BUTTONS+1;
        memset(_commands, 0, sizeof(_commands));
        cout << "RemoteControl._commands.size():" << sizeof(_commands) << endl;
    }
    void setCommand(Command *c, int i) {
        if (i >= MAX_BUTTONS || i < 0) return;
        _commands[i] = c;
    }
    void sendCommand(int i) {
        if (i >= MAX_BUTTONS || i < 0 || _commands[i] == 0) return;
        _commands[i]->execute();
        _last_button = i;
    }
    void repeatCommand() {
        if (_last_button >= MAX_BUTTONS || _last_button < 0 || _commands[_last_button] == 0) return;
        _commands[_last_button]->execute();
    }
};

int main() {
    RemoteControl *remote = new RemoteControl();
    Light *light = new Light();
    LightOnCommand *lightOn = new LightOnCommand(light);
    remote->setCommand(lightOn, 1);
    remote->sendCommand(1);
    GarageDoor *garage_door = new GarageDoor();
    GarageDoorOpenCommand *garage_door_open = new GarageDoorOpenCommand(garage_door);
    remote->setCommand(garage_door_open, 2);
    remote->sendCommand(2);
    remote->repeatCommand();
    return 0;
}



