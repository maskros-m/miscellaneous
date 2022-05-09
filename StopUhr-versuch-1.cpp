/************************************************
AUFGABENSTELLUNG

Programmieren Sie eine Stopp-Uhr mit folgenden Funktionen:

Ein Druck nach OBEN auf dem Joystick (p15) startet die Zeitnehmung, welche bis zum Beginn eines zweiten Drucks nach OBEN (egal wie lange dieser ist, soll das Niederdrücken des Tasters zählen) läuft. Danach wird die gemessene Zeit im Format "sss,xy" (mit sss in Sekunden, x Zehntelsekunden, y Hundertstelsekunden) ausgegeben.
Mit einem Druck nach unten (p12) kann die Messung jederzeit gestoppt und die Zeit resettiert werden
Während die Zeitnehmung läuft, soll die LED1 leuchten (und LED2 und 3 aus sein) - wenn die Uhr stoppt und einen Wert ungleich 0 hat, soll LED1 aus sein und LED2 leuchten.
Wenn die Uhr resettiert ist, soll LED3 leuchten.
GLEICHZEITIG soll die LED4 mit einer Frequenz von genau 2Hz blinken, ohne von den Stoppuhr-Funktionen gestört zu werden.

*************************************************/

