#include "core.hpp"

#include <memory>

#include "gl.hpp"
#include "gl_window.hpp"
#include "shaders.hpp"

void glfw_error_callback(int error_code, const char *description) {
  std::fprintf(stderr, "GLFW ERROR [%d]: %s\n", error_code, description);
}
void glfw_framebuffer_size_callback(GLFWwindow *, int w, int h) {
  glViewport(0, 0, w, h);
}

bool graphics::open(const std::string &title,
                    const std::array<std::size_t, 2> &size) {
  if (!glfwInit())
    return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  window = glfwCreateWindow(size[0], size[1], title.c_str(), NULL, NULL);
  if (window == nullptr) {
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }
  glViewport(0, 0, size[0], size[1]);
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  const char *vertex_shader_source = vertex_glsl;
  const char *fragment_shader_source = fragment_glsl;

  int success;
  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(vertex, sizeof(info_log), NULL, info_log);
    std::fprintf(stderr, "Failed to compile vertex shader: \"%s\"\n", info_log);
  }
  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(fragment, sizeof(info_log), NULL, info_log);
    std::fprintf(stderr, "Failed to compile fragment shader: \"%s\"\n", info_log);
  }
  shader_id = glCreateProgram();
  glAttachShader(shader_id, vertex);
  glAttachShader(shader_id, fragment);
  glLinkProgram(shader_id);
  glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(shader_id, sizeof(info_log), NULL, info_log);
    std::fprintf(stderr, "Failed to link shader program: \"%s\"\n", info_log);
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  glUseProgram(shader_id);

  return true;
}

bool graphics::close() {
  glfwDestroyWindow(window);
  glfwTerminate();
  return true;
}

bool graphics::update() {
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glfwSwapBuffers(window);
  return true;
}
bool graphics::should_close() { return glfwWindowShouldClose(window); }
