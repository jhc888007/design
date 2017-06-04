#include <iostream>
#include <algorithm>
#include <vector>

class Observer {
public:
    virtual void onChange(int param) = 0;
};

class Model {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setBpm(int bpm) = 0;
    virtual int getBpm() = 0;
    virtual void registerObserver(Observer *o) = 0;
    virtual void removeObserver(Observer *o) = 0;
};

class BpmModel: public Model {
    int _bpm;
    bool _turned_on;
    std::vector<Observer *> _observer_v;
public:
    BpmModel(): _bpm(0), _turned_on(false) {}

    void on() {
        if (_turned_on) {
            std::cout << "Already turned on" << std::endl;
            return ;
        }
        _turned_on = true;
        std::cout << "BpmModel turned on" << std::endl;
    }
    void off() {
        if (!_turned_on) {
            std::cout << "Already turned off" << std::endl;
            return ;
        }
        _turned_on = false;
        std::cout << "BpmModel turned off" << std::endl;
    }
    void setBpm(int bpm) {
        _bpm = bpm;
        notifyObserver();
    }
    int getBpm() {
        return _bpm;
    }
    void registerObserver(Observer *o) {
        _observer_v.push_back(o);
    }
    void removeObserver(Observer *o) {
        for (auto it = _observer_v.begin(); it != _observer_v.end(); it++)
            if (*it == o) {
                _observer_v.erase(it);
                return;
            }
        return;
    }
    void notifyObserver() {
        for_each(_observer_v.begin(), _observer_v.end(), [this](Observer *o)->void{o->onChange(this->_bpm);});
    }
};

class Controller: public Observer {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void set(int param) = 0;
    virtual void onChange(int param) { std::cout << "Nothing happend" << std::endl; }
};

class Object: public Observer {
    int _x;
    int _y;
    int _size_x;
    int _size_y;
    std::vector<int> _pic_v;
    int _pic;
protected:
    inline int getX() const { return _x; }
    inline void setX(int x) { _x = x; }
    inline int getY() const { return _y; }
    inline void setY(int y) { _y = y; }
    inline int getPic() const { return _pic; }
    inline void setPic(int pic) { _pic = pic; _size_x = 10; _size_y = 10; }
public:
    Object(int x, int y, std::vector<int> pic_v): _x(x), _y(y) {
        _pic_v.assign(pic_v.begin(), pic_v.end());
        _pic = _pic_v.size() == 0 ? 0 : _pic_v[0];
        _size_x = 10;
        _size_y = 10;
    }
    virtual ~Object() = 0;

    virtual void onChange(int param) { std::cout << "Nothing happened" << std::endl; }
    virtual void onClick(Controller *c) { std::cout << "Nothing happened" << std::endl; }

    bool judgeArea(int x, int y) const {
        if (x >= _x && x <= _x + _size_x && y >= _y && y < _y + _size_y)
            return true;
        return false;
    }
};

Object::~Object() {}

class Button: public Object {
public:
    Button(int x, int y, std::vector<int> pic_v): Object(x, y, pic_v) {}
};

class StartButton: public Button {
public:
    StartButton(int x, int y, std::vector<int> pic_v): Button(x, y, pic_v) {}
    void onClick(Controller *c) {
        if (!c) return ;
        c->on();
    }
};

class StopButton: public Button {
public:
    StopButton(int x, int y, std::vector<int> pic_v): Button(x, y, pic_v) {}
    void onClick(Controller *c) {
        if (!c) return ;
        c->off();
    }
};

class ForwardButton: public Button {
public:
    ForwardButton(int x, int y, std::vector<int> pic_v): Button(x, y, pic_v) {}
    void onClick(Controller *c) {
        if (!c) return ;
        c->forward();
    }
};

class BackwardButton: public Button {
public:
    BackwardButton(int x, int y, std::vector<int> pic_v): Button(x, y, pic_v) {}
    void onClick(Controller *c) {
        if (!c) return ;
        c->backward();
    }
};

class SetButton: public Button {
public:
    SetButton(int x, int y, std::vector<int> pic_v): Button(x, y, pic_v) {}
    int getParam() {
        return 20;
    }
    void onClick(Controller *c) {
        if (!c) return ;
        c->set(getParam());
    }
};

class Bar: public Object {
public:
    Bar(int x, int y, std::vector<int> pic_v): Object(x, y, pic_v) {}
    void onChange(int param) {
        std::cout << "Bar show " << param << std::endl;
    }
};

class View: public Object {
    std::vector<Object*> _object_v;
    Controller *_controller;
public:
    View(int x, int y, std::vector<int> pic_v): Object(x, y, pic_v), _controller(NULL) {}
    void setController(Controller *c) { _controller = c; }
    inline Controller *getController() { return _controller; }
    void add(Object *ob) { _object_v.push_back(ob); }
    void onClick(int x, int y) {
        if (NULL == getController()) return ;
        for (auto ob:_object_v) {
            if (ob->judgeArea(x, y)) {
                ob->onClick(getController());
                break;
            }
        }
    }
    void onChange(int param) {
        for (auto ob:_object_v) {
            ob->onChange(param);
        }
    }
};

class WiredController: public Controller {
    Model *_model;
public:
    WiredController(Model *m): _model(m) {}
    void on() {
        _model->on();
    }
    void off() {
        _model->off();
    }
    void forward() {
        int p = _model->getBpm();
        _model->setBpm(p+1);
    }
    void backward() {
        int p = _model->getBpm();
        if (p > 0)
            _model->setBpm(p-1);
    }
    void set(int param) {
        if (param > 0)
            _model->setBpm(param);
    }
};

int main() {
    View v(5, 5, {1});
    BpmModel m;
    WiredController c(&m);
    v.setController(&c);
    v.add(new StartButton(5, 5, {1}));
    v.add(new StopButton(25, 5, {1}));
    v.add(new ForwardButton(45, 5, {1}));
    v.add(new BackwardButton(65, 5, {1}));
    v.add(new SetButton(85, 5, {1}));
    v.add(new Bar(5, 20, {1}));
    m.registerObserver(&v);
    m.registerObserver(&c);
    v.onClick(5, 5);
    v.onClick(86, 5);
    v.onClick(30, 5);
    return 0;
}


