#ifndef GRAPHICS_OBJ_HPP
#define GRAPHICS_OBJ_HPP

#include "gl.hpp"
#include "gl_window.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <memory>
#include <vector>

namespace graphics {
struct Obj : std::enable_shared_from_this<Obj> {

  Obj() : tri_count(0), color(1.0), trans(1.0) {}

  /**
   * @brief Number of triangles in the object
   */
  std::size_t tri_count;
  /**
   * @brief The color to render the object as
   */
  glm::vec3 color;
  /**
   * @brief The transformation matrix for the object
   */
  glm::mat4 trans;
  /**
   * @brief Internal OpenGL things
   */
  GLuint VBO, VAO, EBO;

  /**
   * @brief Internal rendering call
   */
  inline void draw() const {
    glUseProgram(shader);
    shader_set("uColor", color);
    shader_set("uModel", trans);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, tri_count * 3, GL_UNSIGNED_INT, 0);
  }

  /**
   * @brief Sets the color of an object
   *
   * @param rgb `rgb` color of the object
   *
   * @return A pointer to the modified object
   */
  inline std::shared_ptr<Obj> set_color(glm::vec3 rgb) {
    color = rgb;
    return shared_from_this();
  }
  /**
   * @brief Reset the transformation of an object.
   *
   * @return A pointer to the modified object.
   */
  inline std::shared_ptr<Obj> reset() {
    trans = glm::mat4(1.0);
    return shared_from_this();
  }
  /**
   * @brief Translates an object
   *
   * @param xyz Comopnents to translate the object by
   *
   * @return A pointer to the modified object.
   */
  inline std::shared_ptr<Obj> translate(glm::vec3 xyz) {
    trans = glm::translate(trans, xyz);
    return shared_from_this();
  }
  /**
   * @brief Rotates an object
   *
   * @param angle Angle to rotate the object by
   * @param axis The axis to rotate about
   *
   * @return A pointer to the modified object
   */
  inline std::shared_ptr<Obj> rotate(float angle, glm::vec3 axis) {
    trans = glm::rotate(trans, angle, axis);
    return shared_from_this();
  }
  /**
   * @brief Scales an object
   *
   * @param xyz Amount to scale the object in each direction.
   *
   * @return A pointer to the modifed object.
   */
  inline std::shared_ptr<Obj> scale(glm::vec3 xyz) {
    trans = glm::scale(trans, xyz);
    return shared_from_this();
  }
};
extern std::map<std::string, std::shared_ptr<Obj>> objects;

/**
 * @brief Constructs a new object to be rendered
 *
 * @param name The name of the object
 * @param verts A vector of each vertex, with repetition
 * @param norms A vector of the normal for each vertex
 *
 * @return A pointer to the newly created object.
 */
std::shared_ptr<Obj> construct(const std::string &name,
                               const std::vector<glm::vec3> &verts,
                               const std::vector<glm::vec3> &norms);
/**
 * @brief Constructs a new object to be rendered
 *
 * @param file The `stl` file to load the object from.
 *
 * @return A pointer to the newly created object.
 */
std::shared_ptr<Obj> construct(const std::string &file);
} // namespace graphics

#endif // GRAPHICS_OBJ_HPP
