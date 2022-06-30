#include <iostream>
#include <queue>
#include <random>
#include <math.h>
#include <fstream>

using namespace std;

namespace param {
    double t = 1000000; //время моделирования
    auto l = 0.9; // интенсивность входного потока
    auto m = 1; // интенсивность обслуживания
}

class msg {
public:
    double arr_t = 0; // время прибытия
    double recive_t = 0; // время доставки
    double service_t = 0;//время обслуживания

    msg(double time, double ser_t);
};

msg::msg(double time, double ser_t) {
    arr_t = time;
    service_t = ser_t;
}

double modeling() {
    queue<msg> q;
    double T = 0; // время прихода заявки
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    while (T < param::t) { // заполняем очередь сообщениями
        double x1 = dis(gen);
        double x2 = dis(gen);
        double y1 = -log(x1) / param::l; // время между приходами заявок
        double y2 = -log(x2) / param::m; // время обслуживания
        T += y1;
        q.push(msg(T, y2));
    }
    double dt = 0.01;
    int count = 0;
    double t_delay = 0; //время задержки
    for (double i = 0; i < param::t; i += dt) {
        if (i >= q.front().arr_t) {
            q.front().service_t -= dt;
            if (q.front().service_t <= 0) {
                count++;
                t_delay += i - q.front().arr_t;
                q.pop();
            }
        }
    }
    t_delay /= count; // среднее время задержки
    return t_delay;
}

double modeling_xx1() {
    queue<msg> q;
    double T = 0; // время прихода заявки
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    while (T < param::t) { // заполняем очередь сообщениями
        double x = dis(gen);
        double y1 = -log(x) / param::l; // время между приходами заявок
        double y2 = -log(x) / param::m; // время обслуживания
        T += y1;
        q.push(msg(T, y2));
    }
    double dt = 0.01;
    int count = 0;
    double t_delay = 0; //время задержки
    for (double i = 0; i < param::t; i += dt) {
        if (i >= q.front().arr_t) {
            q.front().service_t -= dt;
            if (q.front().service_t <= 0) {
                count++;
                t_delay += i - q.front().arr_t;
                q.pop();
            }
        }
    }
    t_delay /= count; // среднее время задержки
    return t_delay;
}

double modeling_yy1() {
    queue<msg> q;
    double T = 0; // время прихода заявки
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    while (T < param::t) { // заполняем очередь сообщениями
        double x = dis(gen);
        double y1 = -log(x) / param::l; // время между приходами заявок
        double y2 = -log(1 - x) / param::m; // время обслуживания
        T += y1;
        q.push(msg(T, y2));
    }
    double dt = 0.01;
    int count = 0;
    double t_delay = 0; //время задержки
    for (double i = 0; i < param::t; i += dt) {
        if (i >= q.front().arr_t) {
            q.front().service_t -= dt;
            if (q.front().service_t <= 0) {
                count++;
                t_delay += i - q.front().arr_t;
                q.pop();
            }
        }
    }
    t_delay /= count; // среднее время задержки
    return t_delay;
}

int main() {
    string filename1 = "mm1.dat";
    string filename2 = "xx1.dat";
    string filename3 = "yy1.dat";
    ofstream out1(filename1);
    ofstream out2(filename2);
    ofstream out3(filename3);

    for (double n = 0; n <= 0.96; n += 0.05) {
        param::l = n;
        double m = modeling();
        out1 << n << ' ' << m << endl;
        double m2 = modeling_xx1();
        out2 << n << ' ' << m2 << endl;
        double m3 = modeling_yy1();
        out3 << n << ' ' << m3 << endl;
    }
}
