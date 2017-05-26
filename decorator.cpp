#include <iostream>

using namespace std;

class Beverage {
protected:
    string _description;
public:
    virtual string getDescription() {
        return _description;
    }
    virtual double cost() = 0;
};

class CondimentDecorator: public Beverage {
protected:
    Beverage *_content;
public:
    virtual string getDescription() = 0;
};

class Espresso: public Beverage {
public:
    Espresso() {
        _description = "Espresso";
    }
    double cost() {
        return 1.99;
    }
};

class HouseBlend: public Beverage {
public:
    HouseBlend() {
        _description = "House Blend Coffee";
    }
    double cost() {
        return 0.89;
    }
};

class Mocka: public CondimentDecorator {
public:
    Mocka(Beverage *b) {
        _content = b;
    }
    string getDescription() {
        return _content->getDescription() + ", Mocha";
    }
    double cost() {
        return _content->cost() + 0.2;
    }
};

class Whip: public CondimentDecorator {
public:
    Whip(Beverage *b) {
        _content = b;
    }
    string getDescription() {
        return _content->getDescription() + ", Whip";
    }
    double cost() {
        return _content->cost() + 0.13;
    }
};

int main() {
    Espresso esp;
    Mocka m1(&esp);
    Mocka m2(&m1);
    Whip w(&m2);
    cout << w.getDescription() << endl;
    cout << w.cost() << endl;
}


