#include "graphics.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stl.hpp"

int main(int argc, char *argv[]) {
  auto data = load_stl("../stl/Stanford_Bunny_sample.stl");
  graphics::open("Hello");
  // auto obj = graphics::construct(
  //     {{-0.5, -0.5, 0.0}, {0.5, -0.5, 0.0}, {0.0, 0.5, 0.0}},
  //     {{0.0, 0.0, -1.0}, {0.0, 0.0, -1.0}, {0.0, 0.0, -1.0}});
  // auto obj = graphics::construct({{-1.0, -1.0, -1.0},
  //                                 {1.0, -1.0, -1.0},
  //                                 {1.0, 1.0, -1.0},
  //                                 {-1.0, -1.0, -1.0},
  //                                 {1.0, 1.0, -1.0},
  //                                 {-1.0, 1.0, -1.0},
  //                                 {-1.0, -1.0, -1.0},
  //                                 {-1.0, -1.0, 1.0},
  //                                 {1.0, -1.0, 1.0},
  //                                 {-1.0, -1.0, -1.0},
  //                                 {1.0, -1.0, 1.0},
  //                                 {1.0, -1.0, -1.0}},
  //                                {{0.0, 0.0, -1.0},
  //                                 {0.0, 0.0, -1.0},
  //                                 {0.0, 0.0, -1.0},
  //                                 {0.0, 0.0, -1.0},
  //                                 {0.0, 0.0, -1.0},
  //                                 {0.0, 0.0, -1.0},
  //                                 {0.0, -1.0, 0.0},
  //                                 {0.0, -1.0, 0.0},
  //                                 {0.0, -1.0, 0.0},
  //                                 {0.0, -1.0, 0.0},
  //                                 {0.0, -1.0, 0.0},
  //                                 {0.0, -1.0, 0.0}});

  auto obj = graphics::construct(data[0], data[1]);
  obj->trans = glm::rotate(glm::scale(glm::mat4(1.0f), {0.01f, 0.01f, 0.01f}),
                           1.57075f, {-1.0f, 0.0f, 0.0f});
  float t = 0;
  while (graphics::is_open()) {
    graphics::update();
    graphics::set_view({5 * glm::sin(t), 0.0, 5 * glm::cos(t)}, {0.0, 0.0, 0.0},
                       {0.0, 1.0, 0.0});
    graphics::set_light({10 * glm::sin(2 * t), 1.0, 5 * glm::cos(2 * t)},
                        {glm::sin(2 * t) * 0.5 + 0.5, glm::sin(t) * 0.5 + 0.5,
                         glm::sin(3 * t) * 0.5 + 0.5});
    t += 0.01;
  }
  // graphics::stop_recording();
  graphics::close();
  return 0;
}
