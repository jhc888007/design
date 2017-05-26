#include <iostream>
#include <vector>

using namespace std;

class Observer {
public:
    virtual void update(int temp, int humi, int pres) = 0;
};

class DisplayElement {
public:
    virtual void display() = 0;
};

class Subject {
public:
    virtual void registerObserver(Observer *ob) = 0;
    virtual void removeObserver(Observer *ob) = 0;
    virtual void notifyObservers() = 0;
};

class WeatherData: public Subject {
    int _temp;
    int _humi;
    int _pres;
    bool _changed;
    typedef vector<Observer *> Observers;
    Observers _observers;
    int getTemperature() {
        return 1;
    }
    int getHumidity() {
        return 2;
    }
    int getPressure() {
        return 3;
    }
public:
    WeatherData() {
        _temp = 0;
        _humi = 0;
        _pres = 0;
        _changed = true;
    }
    void registerObserver(Observer *ob) {
        _observers.push_back(ob);
    }
    void removeObserver(Observer *ob) {
        for (Observers::iterator it = _observers.begin(); it != _observers.end();) {
            if (*it == ob)
                _observers.erase(it);
            else
                it++;
        }
    }
    void notifyObservers() {
        if (!_changed) return;
        for (Observers::iterator it = _observers.begin(); it != _observers.end(); it++) {
            (*it)->update(_temp, _humi, _pres);
        }
        _changed = false;
    }
    void meausurementChanged() {
        int temp = getTemperature();
        int humi = getHumidity();
        int pres = getPressure();
        if (temp == _temp && humi == _humi && _pres == pres)
            return ;
        _temp = temp;
        _humi = humi;
        _pres = pres;
        _changed = true;
    }
};

class CurrentConditionsDisplay: public Observer, public DisplayElement {
    int _temp;
    int _humi;
    Subject *_weatherData;
public:
    CurrentConditionsDisplay(Subject *weatherData) {
        _weatherData = weatherData;
        _weatherData->registerObserver(this);
    }
    void update(int temp, int humi, int pres) {
        _temp = temp;
        _humi = humi;
        display();
    }
    void display() {
        cout << "Current show" << endl;
    }
};

class StatisticsDisplay: public Observer, public DisplayElement {
    int _pres;
    Subject *_weatherData;
public:
    StatisticsDisplay(Subject *weatherData) {
        _weatherData = weatherData;
        _weatherData->registerObserver(this);
    }
    void update(int temp, int humi, int pres) {
        _pres = pres;
        display();
    }
    void display() {
        cout << "Statistic show" << endl;
    }
};

class ForecastDisplay: public Observer, public DisplayElement {
    Subject *_weatherData; //保存，可以用来去注册
public:
    ForecastDisplay(Subject *weatherData) {
        _weatherData = weatherData;
        _weatherData->registerObserver(this);
    }
    ~ForecastDisplay() {
        _weatherData->removeObserver(this);
    }
    void update(int temp, int humi, int pres) {
        display();
    }
    void display() {
        cout << "Forecast show" << endl;
    }
};

class ThirdPartyDisplay: public Observer, public DisplayElement {
public:
    void update(int temp, int humi, int pres) {
        //
        display();
    }
    void display() {
        cout << "Third Party show" << endl;
    }
};

int main() {
    WeatherData wd;
    CurrentConditionsDisplay cd(&wd);
    StatisticsDisplay cs(&wd);
    ForecastDisplay cf(&wd);

    wd.meausurementChanged();
    wd.notifyObservers();
    wd.meausurementChanged();
    wd.notifyObservers();

    return 0;
}


