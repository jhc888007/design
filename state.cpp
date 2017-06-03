#include <iostream>

/*typedef enum {
    STATE_A,
    STATE_B,
    STATE_C,
}STATE;
     
class BehaveBase {
public:
    void behave(STATE s) {
        if (s == STATE_A)
            state_func_A();
        else if (s == STATE_B)
            state_func_B();
        else
            state_func_C();
    }
    virtual void state_func_A() = 0;
    virtual void state_func_B() = 0;
    virtual void state_func_C() = 0;
};

class Behave1: public BehaveBase {
    void state_func_A() {
        std::cout << "1 A" << std::endl;
    }
    void state_func_B() {
        std::cout << "1 B" << std::endl;
    }
    void state_func_C() {
        std::cout << "1 C" << std::endl;
    }
};

class Behave2: public BehaveBase {
    void state_func_A() {
        std::cout << "2 A" << std::endl;
    }
    void state_func_B() {
        std::cout << "2 B" << std::endl;
    }
    void state_func_C() {
        std::cout << "2 C" << std::endl;
    }
};

class Machine {
    STATE _s;
    BehaveBase *b1;
    BehaveBase *b2;
public:
    Machine() {
        _s = STATE_A;
        b1 = new Behave1();
        b2 = new Behave2();
    }
    void behave1() {
        b1->behave(_s);
    }
    void behave2() {
        b2->behave(_s);
    }
};*/

class StateBase;

class Machine {
    StateBase *sA;
    StateBase *sB;
    StateBase *state;
public:
    Machine();
    void behave1();
    void behave2();
    void behave3();
    void setState(StateBase *s) { state = s; }
    StateBase *getStateA() { return sA; }
    StateBase *getStateB() { return sB; }
};

class StateBase {
protected:
    Machine *_machine;
public:
    virtual void behave1() = 0;
    virtual void behave2() = 0;
    virtual void behave3() = 0;
};

class StateA: public StateBase {
public:
    StateA(Machine *machine) {_machine = machine;}
    //StateA(Machine *machine): _machine(machine) {}; //ERROR!
    void behave1() {
        std::cout << "A 1" << std::endl;
        _machine->setState(_machine->getStateB());
    }
    void behave2() {
        std::cout << "A 2" << std::endl;
    }
    void behave3() {
        std::cout << "A 3" << std::endl;
    }
};

class StateB: public StateBase {
public:
    StateB(Machine *machine) {_machine = machine;}
    //StateB(Machine *machine): _machine(machine) {}; //ERROR!
    void behave1() {
        std::cout << "B 1" << std::endl;
    }
    void behave2() {
        std::cout << "B 2" << std::endl;
        _machine->setState(_machine->getStateA());
    }
    void behave3() {
        std::cout << "B 3" << std::endl;
        _machine->setState(_machine->getStateA());
    }
};

Machine::Machine() {
    sA = new StateA(this);
    sB = new StateB(this);
    state = sA;
}

void Machine::behave1() {
    state->behave1();
}

void Machine::behave2() {
    state->behave2();
}

void Machine::behave3() {
    state->behave3();
}
    
int main() {
    Machine m;
    m.behave1();
    m.behave2();
    m.behave1();
    m.behave3();
    return 0;
}
