#include "core.hpp"

#include "gl.hpp"
#include "gl_window.hpp"
#include "obj.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void glfw_error_callback(int error_code, const char *description) {
  std::fprintf(stderr, "GLFW (%d): %s\n", error_code, description);
}
void glfw_framebuffer_size_callback(GLFWwindow *, int w, int h) {
  glViewport(0, 0, w, h);
}

bool graphics::open(const std::string &name, const std::size_t &w,
                    const std::size_t &h) {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
  if (window == NULL) {
    return false;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return false;
  }
  glViewport(0, 0, w, h);
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  if (!load_shaders())
    return false;

  set_view({0.0, 0.0, -3.0}, {0.0, 0.0, 10.0}, {0.0, 1.0, 0.0});
  set_light({10.0, 0.0, 0.0}, {1.0, 1.0, 1.0});
  set_fov(45);

  return true;
}
bool graphics::close() {
  glfwDestroyWindow(window);
  glfwTerminate();
  return true;
}

void graphics::clear_rgb(const glm::vec3 &color) {
  glClearColor(color.r, color.g, color.b, 1.0f);
}
void graphics::set_view(const glm::vec3 &pos, const glm::vec3 &look,
                        const glm::vec3 &up) {
  glm::mat4 view = glm::lookAt(pos, look, up);
  glUseProgram(shader);
  shader_set("uView", view);
  shader_set("uViewPos", pos);
}
void graphics::set_fov(const float &fov) {
  glm::mat4 view = glm::perspective(glm::radians(fov), 1.0f, 0.1f, 100.0f);
  glUseProgram(shader);
  shader_set("uProjection", view);
}
void graphics::set_light(const glm::vec3& pos, const glm::vec3& color){
  glUseProgram(shader);
  shader_set("uLightPos", pos);
  shader_set("uLightColor", color);
}

bool graphics::is_open() { return !glfwWindowShouldClose(window); }
bool graphics::update() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto &obj : objects) {
    obj->draw();
  }

  glfwSwapBuffers(window);
  glfwPollEvents();
  return true;
}
