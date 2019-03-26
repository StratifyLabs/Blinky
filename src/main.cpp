#include <stdio.h>
#include <unistd.h>


//see http://docs.stratifylabs.co for docs
#include <sapi/hal.hpp>
#include <sapi/var.hpp>
#include <sapi/sys.hpp>

static void print_usage();

int main(int argc, char * argv[]){

	mcu_pin_t blink_port;
    Cli cli(argc, argv, SOS_GIT_HASH);
	cli.set_publisher("Stratify Labs, Inc");
	cli.handle_version();

	if( cli.is_option("--help") || cli.is_option("-h") ){
		print_usage();
	}

	blink_port.port = 255;
	blink_port.pin = 255;

	if( cli.size() > 1 ){
		blink_port = cli.pin_at(1);
	}

	if( blink_port.port == 255 ){
		//first get the LED info from the board
		Core core(0);
		mcu_board_config_t config;

		core.open();
		core.get_mcu_board_config(config);
		core.close();

		blink_port = config.led;

	}

	if( blink_port.port == 255 ){
		printf("Failed to find LED pin\n");
		exit(1);
	}

	printf("Blinky is on port %d.%d\n", blink_port.port, blink_port.pin);

	Pin pin(blink_port.port, blink_port.pin);
	pin.initialize(Pin::FLAG_SET_OUTPUT);


	while(1){
		pin.set_attributes(Pin::FLAG_SET_OUTPUT);
		pin = true;
		Timer::wait_milliseconds(250);
		pin = false;
		Timer::wait_milliseconds(250);
	}

	return 0;
}

void print_usage(){
	printf("Usage:\n");
	printf("Blink on the default LED supplied by kernel\n");
	printf("\tBlinky\n\n");
	printf("Blink on the port/pin combination specified\n");
	printf("\tBlinky [X.Y]\n\n");
	exit(0);
}
