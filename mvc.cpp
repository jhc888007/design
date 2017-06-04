#include <iostream>
#include <vector>

class Object {
    int _x;
    int _y;
    int _size_x;
    int _size_y;
    std::vector<int> _pic_v;
    int _pic;
protected:
    int getX() const { return _x; }
    void setX(int x) { _x = x; }
    int getY() const { return _y; }
    void setY(int y) { _y = y; }
    int getPic() const { return _pic; }
    void setPic(int pic) { _pic = pic; _size_x = 10; _size_y = 10; }
public:
    Object(int x, int y, std::vector<int> pic_v): _x(x), _y(y) {
        _pic_v.assign(pic_v.begin(), pic_v.end());
        _pic = _pic_v.size() == 0 ? 0 : _pic_v[0];
        _size_x = 10;
        _size_y = 10;
    }
    virtual ~Object() = 0;

    virtual void onClick() { std::cout << "Nothing happened" << std::endl; }
    virtual void onChange(int param) { std::cout << "Nothing happened" << std::endl; }

    bool judgeArea(int x, int y) const {
        if (x > _x && x < _x + _size_x && y > _y && y < _y + _size_y)
            return true;
        return false;
    }
};

class Button: public Object {
public:
    Button(int x, int y, std::vector<int> pic_v): Object(x, y, pic_v) {}
};

class Bar: public Object {
public:
    Bar(int x, int y, std::vector<int> pic_v): Object(x, y, pic_v) {}
};

class Screen: public Object {
public:
    Screen(int x, int y, std::vector<int> pic_v): Object(x, y, pic_v) {}
};

class View: public Object {
    std::vector<Object*> _object_v;
public:
    View(int x, int y, std::vector<int> pic_v): Object(x, y, pic_v) {}
    void add(Object *ob) { _object_v.push_back(ob); }
    void onClick(int x, int y) {
        for (auto ob:_object_v) {
            if (ob->judgeArea(x, y)) {
                ob->onClick();
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

Object::~Object() {}

int main() {
    //Object b(5,5,{1});
    View v(5,5,{1});
    //v.onClick(1, 2);
    v.Object::onClick();
    v.onChange(1);
    return 0;
}


