#include <iostream>

using namespace std;

class Duck {
public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class MallardDuck: public Duck {
public:
    void quack() {
        cout << "Duck quack" << endl;
    }
    void fly() {
        cout << "Duck fly" << endl;
    }
};

class Turkey {
public:
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

class WildTurkey: public Turkey {
public:
    void gobble() {
        cout << "Turkey gobble" << endl;
    }
    void fly() {
        cout << "Turkey jump" << endl;
    }
};

class TurkeyDuckAdaptor: public Duck {
    Turkey *_turkey;
public:
    TurkeyDuckAdaptor(Turkey *t): _turkey(t) {}
    void quack() {
        _turkey->gobble();
    }
    void fly() {
        _turkey->fly();
        _turkey->fly();
        _turkey->fly();
        _turkey->fly();
    }
};

class DuckTurkeyAdaptor: public Turkey {
    enum {
        DUCK_TURKEY_LOOP_COUNT = 5,
    };
    Duck *_duck;
public:
    DuckTurkeyAdaptor(Duck *d): _duck(d) {}
    void gobble() {
        _duck->quack();
    }
    void fly() {
        static int count = DUCK_TURKEY_LOOP_COUNT;
        count++;
        if (count >= DUCK_TURKEY_LOOP_COUNT) {
            count = 0;
            _duck->fly();
        }
    }
};


int main() {
    Duck *d1 = new MallardDuck();
    d1->quack();
    d1->fly();

    Turkey *t1 = new WildTurkey();
    t1->gobble();
    t1->fly();

    Duck *d2 = new TurkeyDuckAdaptor(t1);
    d2->quack();
    d2->fly();

    Turkey *t2 = new DuckTurkeyAdaptor(d1);
    t2->gobble();
    t2->fly();
    t2->fly();
    t2->fly();
    t2->fly();
    t2->fly();
    t2->fly();
    t2->fly();
    
    return 0;
}

