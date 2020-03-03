#ifndef STL_HPP_
#define STL_HPP_

#include <array>
#include <glm/glm.hpp>
#include <string>
#include <vector>

std::array<std::vector<glm::vec3>, 2> load_stl(const std::string &filename);

#endif // STL_HPP_
