#include <iostream>

using namespace std;

class Dough {
protected:
    Dough() {}
};

class Sauce {
protected:
    Sauce() {}
};

class IngredientFactory {
public:
    virtual Dough *createDough() = 0;
    virtual Sauce *createSauce() = 0;
};

class Pizza {
    friend class PizzaStore;
protected:
    string _name;
    Dough *_dough;
    Sauce *_sauce;
    int _count;
    IngredientFactory *_factory;

    virtual void prepare() = 0;
    virtual void bake() {
        cout << "Bake for 25 minutes" << endl;
    }
    virtual void cut() {
        cout << "Cutting pieces" << endl;
    }
    virtual void box() {
        cout << "Placing " << _name << " into box" << endl;
    }
public:
    Pizza(int c): _count(c) {}
    ~Pizza() {
        if (_dough != NULL) {
            delete _dough;
        }
        if (_sauce != NULL) {
            delete _sauce;
        }
    }
    string getName() {
        return _name;
    }
};

class PizzaStore {
protected:
    IngredientFactory *_factory;
public:
    virtual Pizza *createPizza(string type, int num) = 0;
    bool orderPizza(string type, int num) {
        IngredientFactory *factory;
        Pizza *p = createPizza(type, num);
        if (!p) return false;
        cout << "Pizza cooking, please wait for a moment" << endl;
        p->prepare();
        p->bake();
        p->cut();
        p->box();
        return true;
    }
};

class ThinCrustDough: public Dough {
public:
    ThinCrustDough() {cout << "ThinCrustDough create" << endl;}
};

class ThinDough: public Dough {
public:
    ThinDough() {cout << "ThinDough create" << endl;}
};

class MarinaraSauce: public Sauce {
public:
    MarinaraSauce() {cout << "MarinaraSauce create" << endl;}
};

class NYIngredientFactory: public IngredientFactory {
public:
    Dough *createDough() {return new ThinCrustDough;}
    Sauce *createSauce() {return new MarinaraSauce;}
};

class NYCheesePizza: public Pizza {
public:
    NYCheesePizza(int c, IngredientFactory *factory): Pizza(c) {
        _factory = factory;
        _name = "NYCheesePizza";
        cout << "NYCheesePizza created" << endl;
    }
    void prepare() {
        _dough = _factory->createDough();
        _sauce = _factory->createSauce();
    }
};

class NYClanPizza: public Pizza {
public:
    NYClanPizza(int c, IngredientFactory *factory): Pizza(c) {
        _factory = factory;
        _name = "NYClanPizza";
        cout << "NYClanPizza created" << endl;
    }
    void prepare() {
        _dough = _factory->createDough();
        _sauce = _factory->createSauce();
    }
};

class NYStylePizzaStore: public PizzaStore {
public:
    NYStylePizzaStore() {
        _factory = new NYIngredientFactory();
    }
    ~NYStylePizzaStore() {
        if (_factory)
            delete _factory;
    }
    Pizza *createPizza(string type, int num) {
        if (type == "cheese")
            return new NYCheesePizza(num, _factory);
        else if (type == "clan")
            return new NYClanPizza(num, _factory);
        else
            cout << "No this kind in our store: " << type << endl;
        return NULL;
    }
};

class LAIngredientFactory: public IngredientFactory {
public:
    Dough *createDough() {return new ThinDough;}
    Sauce *createSauce() {return new MarinaraSauce;}
};

class LACheesePizza: public Pizza {
public:
    LACheesePizza(int c, IngredientFactory *factory): Pizza(c) {
        _factory = factory;
        _name = "LACheesePizza";
        cout << "LACheesePizza created" << endl;
    }
    void prepare() {
        _dough = _factory->createDough();
        _sauce = _factory->createSauce();
    }
};

class LAClanPizza: public Pizza {
public:
    LAClanPizza(int c, IngredientFactory *factory): Pizza(c) {
        _factory = factory;
        _name = "LAClanPizza";
        cout << "LAClanPizza created" << endl;
    }
    void prepare() {
        _dough = _factory->createDough();
        _sauce = _factory->createSauce();
    }
};

class LAStylePizzaStore: public PizzaStore {
public:
    LAStylePizzaStore() {
        _factory = new LAIngredientFactory();
    }
    ~LAStylePizzaStore() {
        if (_factory)
            delete _factory;
    }
    Pizza *createPizza(string type, int num) {
        if (type == "cheese")
            return new LACheesePizza(num, _factory);
        else if (type == "clan")
            return new LAClanPizza(num, _factory);
        else
            cout << "No this kind in our store: " << type << endl;
        return NULL;
    }
};

int main() {
    PizzaStore *a = new NYStylePizzaStore();
    PizzaStore *b = new LAStylePizzaStore();
    a->orderPizza("cheese", 2);
    b->orderPizza("clan", 3);
    return 0;
}
 
