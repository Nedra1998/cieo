#include "graphics.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/core.hpp"
#include "stl.hpp"

inline float frand() { return rand() / static_cast<float>(RAND_MAX); }

int main(int argc, char *argv[]) {
  graphics::open("Cieo", 500, 500);

  auto obj = graphics::construct("../stl/Stanford_Bunny_sample.stl");
  obj->scale({0.01, 0.01, 0.01});

  glm::vec3 pos = {0.0, 0.0, 5.0};
  glm::vec3 up = {0.0, 1.0, 0.0};
  graphics::set_view(pos, {0.0, 0.0, 0.0}, up);
  graphics::set_light({10.0, 5.0, 10.0}, {1.0, 1.0, 1.0});
  while (graphics::is_open()) {
    graphics::update();

    if (graphics::is_pressed(GLFW_KEY_RIGHT)) {
      glm::vec3 right = glm::normalize(glm::cross(-pos, up));
      pos += 0.1f * right;
      graphics::set_view(pos, {0.0, 0.0, 0.0}, up);
    } else if (graphics::is_pressed(GLFW_KEY_LEFT)) {
      glm::vec3 right = glm::normalize(glm::cross(-pos, up));
      pos -= 0.1f * right;
      graphics::set_view(pos, {0.0, 0.0, 0.0}, up);
    }
    if (graphics::is_pressed(GLFW_KEY_UP)) {
      pos += 0.1f * up;
      graphics::set_view(pos, {0.0, 0.0, 0.0}, up);
    } else if (graphics::is_pressed(GLFW_KEY_DOWN)) {
      pos -= 0.1f * up;
      graphics::set_view(pos, {0.0, 0.0, 0.0}, up);
    }
    if (graphics::is_pressed(GLFW_KEY_C)) {
      graphics::set_light({10.0, 5.0, 10.0}, {frand(), frand(), frand()});
    }
    if (graphics::is_pressed(GLFW_KEY_Q)) {
      graphics::should_close();
    }
  }
  graphics::close();
  return 0;
}
