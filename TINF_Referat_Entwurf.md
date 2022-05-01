## Beispiel 1: 
Ein Schnellkochtopf wird eingeschaltet (Modus: ON) und nach einer bestimmten Dauer, wird sein Timer gestellt und der ausgewählt Koch-Modus geschaltet.

Das automatische Stellen des Timers kann man als Event 1 (zur EventQueue a gehört) nennen.
Sobald der Timer gestellt wird, bedeutet es:
- Der Druck im Schnellkochtopf 30psi erreicht (Event 2 - zur EventQueue b gehört)
- Das Wasser seinen Siedepunkt (121 Grad) erreicht (Event 3 - zur EventQueue c gehört).

Event b und c sind die Folge von a und werden deswegen mit a durch "chaining Event" verbunden, damit sie ausgeführt werden können.

Die Funktion von chaining Event kann auch wie folgt geschrieben werden:
```cpp
int main () {

	// Event queue a mit event a wird erzeugt
	EventQueue timerOn;
	timerOn.call(setCountdown, COUNTDOWN_VALUE);

	// EventQueue 2 mit event b wird erzeugt
	EventQueue pressureMonitor; 
	enoughPressure.call(maintainPressure, PSI_VALUE);

	// EventQueue 3 mit event c wird erzeugt
	EventQueue boilingPoint; 
	boilingPoint.call(letSimmer, C_DEGREE_VALUE); 

	boilingPoint.chain(&timerOn); // wenn timerOn Event erkennt wird, wird der Code für boilingPoint auch ausgeführt.

	pressureMonitor.chain(&timerOn); // wenn timerOn Event erkennt wird, wird der Code für pressureMonitor auch ausgeführt.

	timerOn.dispatch_once();
	return 0;
}
```

das heißt, wenn Event timerOn is erkennt, behandelt der Schnellkochtopf drei Events (von drei EventQueues) durch die folgende Interrupts:
- Countdown wird erstellt (z.B. für 25 Minuten).
- Siedepunkt wird erhalt (z.B. auf 121 Grad).
- Druck wird auch erhalt (z.B. auf 30psi).

## Beispiel 2:
*(Ein verständlicheres Beispiel von chaining EventQueues, aber es hat weniger mit Mikrocontroller zu tun)*

Wenn man den Browser Chrome öffnet, wird eine EventQueue für Chrome erstellt, die die mit Chrome verbunden Events behandelt.

Außerdem hat man auch ein Antiviren-Software installiert. Sobald der Browser Chrome geöffnet wird, wird auch das Antiviren-Software aktiviert und dadurch seine eigene EventQueue erstellt.

Das heißt, die EventQueue vom Antiviren-Software wird mit der von Chrome verbunden. Wenn Chromes EventQueue 'dispatched' oder ausgeführt wird, wird auch die vom Antiviren-Software ausgeführt.
