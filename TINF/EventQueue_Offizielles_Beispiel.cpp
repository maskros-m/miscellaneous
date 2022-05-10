#include "mbed.h"
#include <stdio.h>


BusOut myled(p23, p24, p25);
EventQueue quiver;
Thread battle;
DigitalIn hitBelly(p14);
int SmaugLife = 20;


void shootArrow(int injuries) {
    SmaugLife -= injuries;
    printf("Arrow shot. Smaug's health left: %d\r\n", SmaugLife);
}

void endBattle() {
    SmaugLife = 20;
    quiver.break_dispatch();
    battle.terminate();
    battle.join();
    printf("Smaug has been slayed. Hail to thee, mighty Warrior!\n");
}

void startBattle() {
    battle.start(callback(&quiver, &EventQueue::dispatch_forever));
    quiver.call_every(1500,shootArrow, 5);
}

int main() {
    printf("Battle starts\n");
    startBattle();

    while (true) {
        while(hitBelly) {
            if (!hitBelly) {
                endBattle();
                break;
            }
        }
        // if (SmaugLife <= 0) {
        //     endBattle();
        // }
        myled = !myled; wait_us(900000);
    }
}
