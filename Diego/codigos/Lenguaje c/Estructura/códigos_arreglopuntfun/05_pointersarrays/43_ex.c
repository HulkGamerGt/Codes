
// function pointer

#include <stdio.h>

// Defining a function
void hello() { printf("Hello World"); }

// The main code
int main() {
  // Declaring a function pointer
  void (*ptr)() = &hello;

  // Calling function using the
  // function poiter
  (*ptr)();

  return 0;
}