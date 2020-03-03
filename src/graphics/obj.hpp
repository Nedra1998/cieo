#ifndef GRAPHICS_OBJ_HPP
#define GRAPHICS_OBJ_HPP

#include "gl.hpp"
#include "gl_window.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

namespace graphics {
struct Obj : std::enable_shared_from_this<Obj> {

  Obj() : tri_count(0), color(1.0), trans(1.0) {}

  std::size_t tri_count;
  glm::vec3 color;
  glm::mat4 trans;
  GLuint VBO, VAO, EBO;

  inline void draw() const {
    glUseProgram(shader);
    shader_set("uColor", color);
    shader_set("uModel", trans);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, tri_count * 3, GL_UNSIGNED_INT, 0);
  }

  inline std::shared_ptr<Obj> set_color(glm::vec3 rgb) {
    color = rgb;
    return shared_from_this();
  }
  inline std::shared_ptr<Obj> reset() {
    trans = glm::mat4(1.0);
    return shared_from_this();
  }
  inline std::shared_ptr<Obj> translate(glm::vec3 xyz) {
    trans = glm::translate(trans, xyz);
    return shared_from_this();
  }
  inline std::shared_ptr<Obj> rotate(float angle, glm::vec3 axis) {
    trans = glm::rotate(trans, angle, axis);
    return shared_from_this();
  }
  inline std::shared_ptr<Obj> scale(glm::vec3 xyz) {
    trans = glm::scale(trans, xyz);
    return shared_from_this();
  }
};
extern std::vector<std::shared_ptr<Obj>> objects;

std::shared_ptr<Obj> construct(const std::vector<glm::vec3> &verts,
                               const std::vector<glm::vec3> &norms);
} // namespace graphics

#endif // GRAPHICS_OBJ_HPP
