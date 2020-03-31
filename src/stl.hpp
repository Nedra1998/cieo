#ifndef STL_HPP_
#define STL_HPP_

#include <array>
#include <glm/glm.hpp>
#include <string>
#include <vector>

/**
 * @brief Loads STL file format
 *
 * Currently only binary STL files are supported.
 *
 * @param filename The STL file to load, this can be either the relative path or
 * the full path
 *
 * @return An array with the first element being a vector of the verticies, and
 * the second being a vector of the normals at each vertex.
 *
 * @note In the returned arrays, the same vertex may appear multiple times, with
 * different normals.
 */
std::array<std::vector<glm::vec3>, 2> load_stl(const std::string &filename);

#endif // STL_HPP_
