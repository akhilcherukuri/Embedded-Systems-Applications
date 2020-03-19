#include <stddef.h>

#include "can_bus.h"
#include "can_bus_initializer.h"

static void handle_can_bus_off() { can__reset_bus(can1); }
void init_can_driver(void) {
  can__init(can1, 100, 100, 100, handle_can_bus_off, NULL);
  can__bypass_filter_accept_all_msgs();
  can__reset_bus(can1);
}