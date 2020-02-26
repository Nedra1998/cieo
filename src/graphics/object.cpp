#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>

#include "gl.hpp"

graphics::Object::Object(const std::vector<glm::vec3> &verticies,
                         std::vector<glm::vec3> &normals,
                         const std::vector<unsigned int> &indicies)
    : verticies(verticies), indicies(indicies) {
  construct_mesh();
}

void graphics::Object::draw(const GLuint &shader) {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void graphics::Object::construct_mesh() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  std::vector<glm::vec3> interleaved;
  for (unsigned int i = 0; i < verticies.size(); ++i) {
    interleaved.push_back(verticies[i]);
    interleaved.push_back(normals[i]);
  }

  glBufferData(GL_ARRAY_BUFFER, interleaved.size() * sizeof(glm::vec3),
               &interleaved[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int),
               &indicies[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2,
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2,
                        (void *)sizeof(glm::vec3));
  glBindVertexArray(0);
}
