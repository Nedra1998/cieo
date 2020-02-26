#ifndef CIEO_GRAPHICS_OBJECT_HPP_
#define CIEO_GRAPHICS_OBJECT_HPP_

#include <glm/glm.hpp>
#include <vector>

#include "gl.hpp"

namespace graphics {
class Object {
public:
  Object(const std::vector<glm::vec3> &verticies,
         std::vector<glm::vec3> &normals,
         const std::vector<unsigned int> &indicies);

  void draw(const GLuint &shader);

  std::vector<glm::vec3> verticies;
  std::vector<glm::vec3> normals;
  std::vector<unsigned int> indicies;

private:
  void construct_mesh();

  unsigned int VAO, VBO, EBO;
};
} // namespace graphics

#endif // CIEO_GRAPHICS_OBJECT_HPP_
