/* Probably not a good example but we all need to start somewhere */
/* Note to self: Timer might not be an event here */
#include "mbed.h"
#include "mbed_events.h"
#include <stdio.h>

DigitalOut led(LED1);
DigitalOut led2(LED2);

void enoughPressure (int psi) {
    for (int i = 0; i <= psi; i++) {
        wait_us(100000);
        if (i == psi)
            printf("Pressure has reached %d\n", i);
    }
}

void checkBoilingPoint (int degrees) {
    for (int i = 0; i <= degrees; i++) {
        wait_us(10000);
        if (i == degrees)
            printf("Boiling point of %d degrees has been reached\n", degrees);
    }
}

int setTimer (int starting_value) {
    printf("Timer has been set to %d\n", starting_value);
    return starting_value;
}

void countdown (int countdown_value) {
    for (int i = countdown_value; i >= 0; i--) {
        wait_us(100000);
        printf("There is %d minutes left\n", i);
        if (i == 0)
            printf("Food is ready.\n");
    }
}

int main()
{
    // Create some event queues with pending events
    EventQueue pressureMonitor;
    pressureMonitor.call(enoughPressure, 30);

    EventQueue boilingPoint;
    boilingPoint.call(checkBoilingPoint, 121);

    EventQueue timerOn;
    timerOn.call(setTimer, 25);
    timerOn.call(countdown, setTimer(25));

    // Chain c and b onto a's event queue. Both c and b will be dispatched
    // in the context of a's dispatch function.
    pressureMonitor.chain(&boilingPoint);
    timerOn.chain(&boilingPoint);

    // Dispatching a will in turn dispatch b and c, printing hello from
    // all three queues
    boilingPoint.dispatch();
}
