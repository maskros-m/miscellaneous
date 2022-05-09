/************************************************
AUFGABENSTELLUNG

Programmieren Sie eine Stopp-Uhr mit folgenden Funktionen:

Ein Druck nach OBEN auf dem Joystick (p15) startet die Zeitnehmung, welche bis zum Beginn eines zweiten Drucks nach OBEN (egal wie lange dieser ist, soll das Niederdrücken des Tasters zählen) läuft. Danach wird die gemessene Zeit im Format "sss,xy" (mit sss in Sekunden, x Zehntelsekunden, y Hundertstelsekunden) ausgegeben.
Mit einem Druck nach unten (p12) kann die Messung jederzeit gestoppt und die Zeit resettiert werden
Während die Zeitnehmung läuft, soll die LED1 leuchten (und LED2 und 3 aus sein) - wenn die Uhr stoppt und einen Wert ungleich 0 hat, soll LED1 aus sein und LED2 leuchten.
Wenn die Uhr resettiert ist, soll LED3 leuchten.
GLEICHZEITIG soll die LED4 mit einer Frequenz von genau 2Hz blinken, ohne von den Stoppuhr-Funktionen gestört zu werden.

*************************************************/

#include "mbed.h"

DigitalOut led1(LED1), led2(LED2), led3(LED3), led4(LED4);
DigitalIn ctrlBtn(p15), resetBtn(p12);

Timer stopwatch;
int counter = 0;

void startTimer() {
    stopwatch.start();
    // printf("Button has been pressed %d times\n", counter);
    led1 = 1;
    led2 = 0;
    led3 = 0;
}

void stopTimer() {
    stopwatch.stop();
    printf("Elapsed time since last session: %.2f seconds\n", (double) stopwatch.read_ms() / 1000);
    led1 = 0;
    led2 = 1;
    led3 = 0;
}

void resetTimer() {
    stopwatch.stop();
    stopwatch.reset();
    printf("Stopwatch reset.\nCurrent time: %.2f seconds\n", (double) stopwatch.read_ms() / 1000);
    led3 = 1;
    led1 = 0;
    led2 = 0;
}

int main()
{
    while (true) {
        if (counter > 1 && ctrlBtn == 0) {
            stopTimer();
            counter = 0;
        }
        if (ctrlBtn == 1 && counter == 0) {
            printf("Start counting time\n");
        }
        if (ctrlBtn == 1) {
            ++counter;
            startTimer();
        }
        if (resetBtn == 1) {
            resetTimer();
        }    
        led4 = !led4;
        wait_us(500000);    
    }
}
