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
    void setFlyBehavior(FlyBehavior *fb) {
        if (flyBehavior) {
            delete flyBehavior;
            flyBehavior = 0;
        }
        flyBehavior = fb;
    }
    void performFly() { //为什么要进行封装？
        flyBehavior->fly(); //为什么这里具体行为不是类似于Behave一类的名称？
    }
    void setQuackBehavior(QuackBehavior *qb) {
        if (quackBehavior) {
            delete quackBehavior;
            quackBehavior = 0;
        }
        quackBehavior = qb;
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

class MallardDuck: public Duck {
public:
    MallardDuck() {
        flyBehavior = new FlyWithWings();
        quackBehavior = new Quack();
    }
    void display() {
        cout << "Mini duck show" << endl;
    }
};

void test1() {
    MallardDuck duck;
    duck.display();
    duck.performQuack();
    duck.performFly();
    duck.swim();
}

class ModelDuck: public Duck {
public:
    ModelDuck() {
        flyBehavior = new FlyNoWay();
        quackBehavior = new Quack();
    }
    void display() {
        cout << "Model duck show" << endl;
    }
};

class FlyRocketPowered: public FlyBehavior {
    void fly() {
        cout << "Fly Rocket" << endl;
    }
};

void test2() {
    ModelDuck duck;
    duck.performFly();
    duck.setFlyBehavior(new FlyRocketPowered());
    duck.performFly();
}

int main() {
    test1();
    test2();
}


