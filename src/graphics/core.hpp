#ifndef CIEO_GRAPHICS_CORE_HPP_
#define CIEO_GRAPHICS_CORE_HPP_

#include <string>
#include <array>

namespace graphics {
bool open(const std::string &title = "CIEO",
          const std::array<std::size_t, 2> &size = {500, 500});
bool close();
bool update();
bool should_close();
} // namespace graphics

#endif // CIEO_GRAPHICS_CORE_HPP_
