#include "graphics.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stl.hpp"

int main(int argc, char *argv[]) {
  load_stl("../stl/Stanford_Bunny_sample.stl");
  graphics::open("Hello");
  // auto obj = graphics::create({{-0.5, -0.5, -0.5},
  //                              {-0.5, -0.5, 0.5},
  //                              {-0.5, 0.5, -0.5},
  //                              {-0.5, 0.5, 0.5},
  //                              {0.5, -0.5, -0.5},
  //                              {0.5, -0.5, 0.5},
  //                              {0.5, 0.5, -0.5},
  //                              {0.5, 0.5, 0.5}},
  //                             {{0, 1, 3},
  //                              {0, 3, 2},
  //                              {0, 5, 1},
  //                              {0, 4, 5},
  //                              {0, 2, 6},
  //                              {0, 6, 4},
  //                              {2, 3, 6},
  //                              {3, 7, 6},
  //                              {4, 7, 5},
  //                              {4, 6, 7},
  //                              {1, 7, 3},
  //                              {1, 5, 7}});
  while (graphics::is_open()) {
    graphics::update();
    // obj->trans = glm::translate(obj->trans, glm::vec3(0.0, 0.0, 1.0));
    // if (!graphics::is_recording())
    //   graphics::start_recording("frame-%05d.jpg");
  }
  // graphics::stop_recording();
  graphics::close();
  return 0;
}
