#include "message_processor.h"

static bool message_analyse(message_s *message) {
  bool symbol_found = false;
  if (message->data[0] == '$') {
    symbol_found = true;
  } else if (message->data[0] == '#') {
    symbol_found = true;
  } else {
    symbol_found = false;
  }
  return symbol_found;
}

bool message_processor(void) {
  bool symbol_found = false;
  message_s message;
  memset(&message, 0, sizeof(message));

  const static size_t max_messages_to_process = 3;
  for (size_t message_count = 0; message_count < max_messages_to_process; message_count++) {
    if (!message__read(&message)) {
      break;
    } else if (message_count < 2) {
      continue;
    } else {
      symbol_found = message_analyse(&message);
    }
  }
  return symbol_found;
}
