#ifndef GRAPHICS_SHADER_HPP_
#define GRAPHICS_SHADER_HPP_

#include <glm/glm.hpp>
#include <string>

namespace graphics {
bool load_shaders();
void shader_set(const std::string &name, const glm::vec3 &v);
void shader_set(const std::string &name, const glm::mat4 &v);
} // namespace graphics

#endif // GRAPHICS_SHADER_HPP_
