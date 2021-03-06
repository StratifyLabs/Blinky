// COPYING: Copyright 2011-2021 Stratify Labs, Inc
#include <stdio.h>
#include <unistd.h>

#include <chrono.hpp>
#include <hal.hpp>
#include <sys.hpp>
#include <var.hpp>

#include "sl_config.h"

static void print_usage();

class Options {
public:
  Options(const Cli &cli) {
    if (const auto pin_arg = cli.get_option("pin");
        pin_arg.is_empty() == false) {
      m_pin = pin_arg;
    }

    if (const auto period_arg = cli.get_option("period");
        period_arg.is_empty() == false) {
      m_period = period_arg.to_integer() * 1_milliseconds;
    } else {
      m_period = 500_milliseconds;
    }
  }

private:
  API_AC(Options, PathString, pin);
  API_AC(Options, MicroTime, period);
};

int main(int argc, char *argv[]) {

  Cli cli(argc, argv);
  Options options(cli);

  if (cli.get_option("help") == "true") {
    print_usage();
    exit(0);
  }

  if (cli.get_option("version") == "true") {
    printf("Blinky version " SL_CONFIG_VERSION_STRING);
    exit(0);
  }

  if( options.pin().is_empty() ){
    printf("Error: you must specify the pin to flash the LED\n");
    print_usage();
    exit(1);
  }

  Pin pin(Pin::from_string(options.pin()));
  if (pin.is_error()) {
    printf("failed to use pin %s for LED\n", options.pin().cstring());
    exit(1);
  }

  printf("flashing LED on pin %s every %d ms\n", options.pin().cstring(),
         options.period().milliseconds());
  pin.set_output();

  while (1) {
    pin.set_value(true)
        .wait(options.period() / 2)
        .set_value(false)
        .wait(options.period() / 2);
  }

  return 0;
}

void print_usage() {
  printf("Usage: Blinky --pin=<port.pin> --period=<milliseconds>");
}
