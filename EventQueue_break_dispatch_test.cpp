/************************************************************************
An example featuring dispatch_forever(), break_dispatch() and event() 
methods from EventQueue class (mbed).

Heavily referenced from 
https://os.mbed.com/users/mapellil/code/mbed-os-example-blinky//file/3701a2e4ec3d/main.cpp/
With modifications to the ThreadBodyFunc () (here's the callInfo() function)

Works with mbed5 specifications from Keil Studio.
Works with HTerm.
Output has been tested.
*************************************************************************/

#include "mbed.h"
#include "mbed_events.h"
#include <stdio.h>
#include <stdlib.h>

InterruptIn joystick(p14);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
BusOut flash(p23, p25);

/* Creates a class. All objects belonging to this class will have access to all methods and variables in it.
Prevent unauthorised access to methods defined here by objects outside of this class. */
class callSystem {
	public:
		Thread callThread;
		EventQueue callQueue;
		int _count;
	
  /* Needs to ask Kummer. When this function is executed, it breaks the cascade if statements in callInfo() */
	void toggleLed(DigitalOut& ledId) {
		ledId = !ledId;
		wait(500);
		ledId = !ledId;
	}
	
	void callInfo() {
		unsigned timestamp = equeue_tick();
    
    // generates a random callCode with every call to the function
		srand((unsigned) timestamp);
		int callCode = rand() % 3;

		printf("Incoming call's timestamp: %dms, call origin = %d\n", timestamp, callCode);
        _count++;
        if (callCode == 0) { printf("(inland call)\n"); flash = !flash; }
        else if (callCode == 1) { printf("(international call)\n"); flash = !flash; }
        else if (callCode == 2) { printf("(internal emergency call)\n"); led3 = !led3; }
		
	}
	
	void clockIn() {
		printf("Starting taking incoming calls at Thread %d\n", (unsigned int) callThread.get_id());
		_count = 0;
    // Starts a thread with an event queue bound to it
		callThread.start(callback(&callQueue, &EventQueue::dispatch_forever));
		callThread.set_priority(osPriorityRealtime);
    
    // detects interrupt signals from joystick, which triggers the creation of events and binds those events to the established queue
    // events are put into queue but they are fired (executed) immediately.
		joystick.fall(callQueue.event(this, &callSystem::callInfo));
	}
	
	void clockOut() {
		printf("Clocking out...\n");
		_count = 0;
		callQueue.break_dispatch();
		callThread.terminate();
		callThread.join();
		printf("Clocked out. No longer accepting calls.\n");
	}
};

int main() {
	callSystem Operator1;
	printf("Operator1 reports clocking in.\n");
	Operator1.clockIn();
	
	while(1) {
		Thread::yield;
		if (Operator1._count > 5) {
			Operator1.clockOut();
		}
	}
}
