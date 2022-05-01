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
        printf("There are %d minutes left\n", i);
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

/* OUTPUT:
Timer has been set to 25
Boiling point of 121 degrees has been reached
Pressure has reached 30
Timer has been set to 25
There is 25 minutes left
There is 24 minutes left
There is 23 minutes left
There is 22 minutes left
There is 21 minutes left
There is 20 minutes left
There is 19 minutes left
There is 18 minutes left
There is 17 minutes left
There is 16 minutes left
There is 15 minutes left
There is 14 minutes left
There is 13 minutes left
There is 12 minutes left
There is 11 minutes left
There is 10 minutes left
There is 9 minutes left
There is 8 minutes left
There is 7 minutes left
There is 6 minutes left
There is 5 minutes left
There is 4 minutes left
There is 3 minutes left
There is 2 minutes left
There is 1 minutes left
There is 0 minutes left
Food is ready.
- What is "Timer has been set to 25" doing way up there?
*/
