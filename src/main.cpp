#include "graphics.hpp"

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/core.hpp"
#include "stl.hpp"

constexpr static float speed = 0.05f;
constexpr static float rspeed = 0.01f;

inline float frand() { return rand() / static_cast<float>(RAND_MAX); }

int main(int argc, char *argv[]) {
  graphics::open("Cieo", 500, 500);

  auto obj = graphics::construct("../stl/Stanford_Bunny_sample.stl");
  obj->scale({0.01, 0.01, 0.01});
  obj->rotate(-M_PI / 2.0f, {1.0, 0.0, 0.0});

  glm::vec3 pos = {0.0, 0.0, 5.0};
  glm::vec3 cof = {0.0, 0.0, 0.0};
  glm::vec3 up = {0.0, 1.0, 0.0};
  graphics::set_view(pos, {0.0, 0.0, 0.0}, up);
  graphics::set_light({10.0, 5.0, 10.0}, {1.0, 1.0, 1.0});
  while (graphics::is_open()) {
    graphics::update();
    if (graphics::is_pressed(GLFW_KEY_D)) {
      auto diff = glm::normalize(glm::cross(cof - pos, up));
      pos += speed * diff;
      cof += speed * diff;
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_A)) {
      auto diff = glm::normalize(glm::cross(cof - pos, up));
      pos -= speed * diff;
      cof -= speed * diff;
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_W)) {
      auto diff = glm::normalize(cof - pos);
      pos += speed * diff;
      cof += speed * diff;
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_S)) {
      auto diff = glm::normalize(cof - pos);
      pos -= speed * diff;
      cof -= speed * diff;
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_E)) {
      auto diff = glm::normalize(up);
      pos += speed * diff;
      cof += speed * diff;
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_Q)) {
      auto diff = glm::normalize(up);
      pos -= speed * diff;
      cof -= speed * diff;
      graphics::set_view(pos, cof, up);
    }

    if (graphics::is_pressed(GLFW_KEY_L)) {
      glm::mat4 trans = glm::rotate(glm::mat4(1.0f), -rspeed, up);
      cof = pos + glm::vec3(trans * glm::vec4(cof - pos, 0.0f));
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_J)) {
      glm::mat4 trans = glm::rotate(glm::mat4(1.0f), rspeed, up);
      cof = pos + glm::vec3(trans * glm::vec4(cof - pos, 0.0f));
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_I)) {
      glm::mat4 trans = glm::rotate(glm::mat4(1.0f), rspeed,
                                    glm::normalize(glm::cross(cof - pos, up)));
      cof = pos + glm::vec3(trans * glm::vec4(cof - pos, 0.0f));
      up = trans * glm::vec4(up, 0.0f);
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_K)) {
      glm::mat4 trans = glm::rotate(glm::mat4(1.0f), -rspeed,
                                    glm::normalize(glm::cross(cof - pos, up)));
      cof = pos + glm::vec3(trans * glm::vec4(cof - pos, 0.0f));
      up = trans * glm::vec4(up, 0.0f);
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_O)) {
      glm::mat4 trans =
          glm::rotate(glm::mat4(1.0f), rspeed, glm::normalize(cof - pos));
      cof = pos + glm::vec3(trans * glm::vec4(cof - pos, 0.0f));
      up = trans * glm::vec4(up, 0.0f);
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_U)) {
      glm::mat4 trans =
          glm::rotate(glm::mat4(1.0f), -rspeed, glm::normalize(cof - pos));
      cof = pos + glm::vec3(trans * glm::vec4(cof - pos, 0.0f));
      up = trans * glm::vec4(up, 0.0f);
      graphics::set_view(pos, cof, up);
    }

    if (graphics::is_pressed(GLFW_KEY_C)) {
      graphics::set_light({10.0, 5.0, 10.0}, {frand(), frand(), frand()});
    } else if (graphics::is_pressed(GLFW_KEY_R)) {
      pos = {0.0, 0.0, 5.0};
      cof = {0.0, 0.0, 0.0};
      up = {0.0, 1.0, 0.0};
      graphics::set_view(pos, cof, up);
    } else if (graphics::is_pressed(GLFW_KEY_ESCAPE)) {
      graphics::should_close();
    }
  }
  graphics::close();
  return 0;
}
