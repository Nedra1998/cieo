#include "core.hpp"

#include "gl.hpp"
#include "gl_window.hpp"
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
  return load_shaders();
}
bool graphics::close() {
  glfwDestroyWindow(window);
  glfwTerminate();
  return true;
}

void graphics::clear_rgb(const glm::vec3 &color) {
  glClearColor(color.r, color.g, color.b, 1.0f);
}

bool graphics::is_open() { return !glfwWindowShouldClose(window); }
bool graphics::update() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glfwSwapBuffers(window);
  return true;
}
