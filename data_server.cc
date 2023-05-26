#include "process_reader.h"

int main() {
  ProcessReader *reader = new ProcessReader();
  while (true) {
    reader->UpdateUserPosition();
  }
}