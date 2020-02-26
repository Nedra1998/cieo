#include "graphics.hpp"

int main(int argc, char *argv[]) { 
  graphics::open("Hello");
  while(!graphics::should_close()){
    graphics::update();
  }
  graphics::close();
  return 0; }
