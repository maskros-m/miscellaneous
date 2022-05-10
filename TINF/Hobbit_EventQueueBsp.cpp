#include "mbed.h"

EventQueue quiver; // Setting up an EventQueue. The arrows act as pending events, waiting to be fired
Thread battle;

int SmaugLife = 20; // Dragon's health


void shootArrow(int injuries) {
    SmaugLife -= injuries;
    printf("Arrow shot. Smaug's health left: %d\n", SmaugLife);
}

void endBattle() {
    SmaugLife = 20; 
    wait_us(50000); 
    quiver.break_dispatch();
    battle.terminate();
    battle.join();
    printf("Smaug has been slain. Hail to thee, mighty Warrior!\n");
}

void startBattle() {
    battle.start(callback(&quiver, &EventQueue::dispatch_forever)); // start battle thread with its underlying event queue
    quiver.call_every(2000,shootArrow, 5); // draw an arrow from quiver every 2 seconds and shoot
}

int main() {
    printf("Smaug is coming!\n");
    printf("All to arms! Protect Lake Town!\n");
    startBattle();

    while (true) {
        if (SmaugLife <= 0) {
            endBattle();
        }
    }
}
