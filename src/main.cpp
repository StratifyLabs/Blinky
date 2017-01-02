#include <stdio.h>
#include <unistd.h>


//see http://stratifylabs.co/StratifyLib/html/annotated.html for docs
#include <stfy/hal.hpp>
#include <stfy/var.hpp>
#include <stfy/sys.hpp>


static void print_usage();

int main(int argc, char * argv[]){

	pio_t blink_port;
	Cli cli(argc, argv);
	cli.set_version("1.1");
	cli.set_publisher("Stratify Labs, Inc");

	if( cli.is_option("--version") || cli.is_option("-v") ){
		cli.print_version();
		exit(1);
	}

	if( cli.is_option("--help") || cli.is_option("-h") ){
		print_usage();
	}


	if( cli.size() == 1 ){
		//first get the LED info from the board
		Core core(0);
		mcu_board_config_t config;

		core.open();
		core.get_mcu_board_config(config);
		core.close();

		blink_port = config.led;

	} else {
		blink_port = cli.pio_at(1);
	}

	if( blink_port.port == 255 ){
		printf("Failed to find pin\n");
		exit(1);
	}

	printf("Blinky is on port %d.%d\n", blink_port.port, blink_port.pin);

	Pin pin(blink_port.port, blink_port.pin);
	pin.init(Pin::OUTPUT);

	while(1){
		pin = true;
		Timer::wait_msec(250);
		pin = false;
		Timer::wait_msec(250);
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
