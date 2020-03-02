#include "shader.hpp"

#include "gl.hpp"
#include "gl_window.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "shaders.hpp"

bool graphics::load_shaders() {
  int success;
  char buf[512];
  GLuint vs, fs;
  const char *vs_src = vertex_glsl;
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vs_src, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
    std::fprintf(stderr, "Failed to compile Vertex Shader: %s\n", buf);
    return false;
  }

  const char *fs_src = fragment_glsl;
  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fs_src, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
    std::fprintf(stderr, "Failed to compile Fragment Shader: %s\n", buf);
    return false;
  }

  graphics::shader = glCreateProgram();
  glAttachShader(graphics::shader, vs);
  glAttachShader(graphics::shader, fs);
  glLinkProgram(graphics::shader);
  glGetProgramiv(graphics::shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(graphics::shader, sizeof(buf), NULL, buf);
    std::fprintf(stderr, "Failed to link Shader: %s\n", buf);
    return false;
  }
  glDeleteShader(vs);
  glDeleteShader(fs);
  return true;
}

void graphics::shader_set(const std::string &name, const glm::vec3 &v) {
  glUniform3fv(glGetUniformLocation(graphics::shader, name.c_str()), 1,
               glm::value_ptr(v));
}
void graphics::shader_set(const std::string &name, const glm::mat4 &v) {
  glUniformMatrix4fv(glGetUniformLocation(graphics::shader, name.c_str()), 1,
                     GL_FALSE, glm::value_ptr(v));
}
