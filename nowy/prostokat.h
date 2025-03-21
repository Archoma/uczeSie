#pragma once
void przesunDo(int x, int y);
class Prostokat {
    public:
        Prostokat(int x, int y, int w, int h, int dir, double spd) : 
            x(x), y(y), w(w), h(h),
            direction(dir), speed(spd),
            realX(x), realY(y) {}
            
        void draw();
        void move(int direction, double speed);
    private:
        int x, y, w, h;
        int direction, speed;
        double realX, realY;
};