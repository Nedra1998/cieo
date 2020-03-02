#ifndef GRAPHICS_CORE_HPP_
#define GRAPHICS_CORE_HPP_

#include <string>

#include <glm/glm.hpp>

namespace graphics {
bool open(const std::string &name, const std::size_t &w = 500,
          const std::size_t &h = 500);
bool close();

void clear_rgb(const glm::vec3& color);

bool is_open();
bool update();
} // namespace graphics

#endif // GRAPHICS_CORE_HPP_
