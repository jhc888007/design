#include <iostream>

using namespace std;

class FlyBehavior {
public:
    virtual void fly() = 0;
};

class QuackBehavior {
public:
    virtual void quack() = 0;
};

class Duck {
protected:
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;
public:
    Duck() {};
    virtual void display() = 0;
    void performFly() { //为什么要进行封装？
        flyBehavior->fly(); //为什么这里具体行为不是类似于Behave一类的名称？
    }
    void performQuack() {
        quackBehavior->quack(); //为什么这里具体行为不是类似于Behave一类的名称？
    }
    void swim() {
        cout << "All ducks float" << endl;
    }
};

class FlyWithWings: public FlyBehavior {
public:
    void fly() {
        cout << "Fly with wings" << endl;
    }
};

class FlyNoWay: public FlyBehavior {
public:
    void fly() {
        cout << "Can't fly" << endl;
    }
};

class Quack: public QuackBehavior {
public:
    void quack() {
        cout << "Quack, Quack" << endl;
    }
};

class MuteQuack: public QuackBehavior {
public:
    void quack() {
        cout << "Silence" << endl;
    }
};

class Squeak: public QuackBehavior {
public:
    void quack() {
        cout << "Squeak, Squeak" << endl;
    }
};

class MiniDuckSimulator: public Duck {
public:
    MiniDuckSimulator() {
        flyBehavior = new FlyWithWings();
        quackBehavior = new Quack();
    }
    void display() {
        cout << "Mini duck show" << endl;
    }
};

int main() {
    MiniDuckSimulator duck;
    duck.display();
    duck.performQuack();
    duck.performFly();
    duck.swim();
}


