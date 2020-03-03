#include "obj.hpp"

#include "gl.hpp"
#include "gl_window.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

namespace graphics {
std::vector<std::shared_ptr<Obj>> objects;

std::shared_ptr<Obj> construct(const std::vector<glm::vec3> &verts,
                               const std::vector<glm::vec3> &norms) {

  std::vector<float> inter;
  std::vector<unsigned> indicies;
  for (size_t i = 0; i < verts.size(); ++i) {
    inter.push_back(verts[i].x);
    inter.push_back(verts[i].y);
    inter.push_back(verts[i].z);
    inter.push_back(norms[i].x);
    inter.push_back(norms[i].y);
    inter.push_back(norms[i].z);
    indicies.push_back(i);
  }
  objects.push_back(std::make_shared<Obj>());
  auto obj = objects.back();
  obj->trans = glm::mat4(1.0);
  obj->tri_count = verts.size() / 3;
  glGenVertexArrays(1, &obj->VAO);
  glGenBuffers(1, &obj->VBO);
  glGenBuffers(1, &obj->EBO);
  glBindVertexArray(obj->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);
  glBufferData(GL_ARRAY_BUFFER, inter.size() * sizeof(float), inter.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned),
               indicies.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);
  return obj;
}
} // namespace graphics
