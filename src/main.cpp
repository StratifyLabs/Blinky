#include <stdio.h>
#include <unistd.h>


//see http://stratifylabs.co/StratifyLib/html/annotated.html for docs
#include <stfy/hal.hpp>
#include <stfy/var.hpp>
#include <stfy/sys.hpp>


int main(int argc, char * argv[]){

	//first get the LED info from the board
	Core core(0);
	mcu_board_config_t config;

	core.open();
	core.get_mcu_board_config(config);
	core.close();

	printf("Blinky is on %d.%d\n", config.led.port, config.led.pin);

	Pin pin(config.led.port, config.led.pin);
	pin.init(Pin::OUTPUT);

	while(1){
		pin = true;
		Timer::wait_msec(250);
		pin = false;
		Timer::wait_msec(250);
	}

	return 0;
}
