#include "stl.hpp"

#include <array>
#include <cstring>
#include <string>
#include <vector>

#include <glm/glm.hpp>

std::array<std::vector<glm::vec3>, 2> load_stl_ascii(FILE *fp) {
  // TODO: Ascii STL file format
  return {std::vector<glm::vec3>(), std::vector<glm::vec3>()};
}
std::array<std::vector<glm::vec3>, 2> load_stl_binary(FILE *fp) {
  // Header
  char header[80];
  fread(header, sizeof(char), 80, fp);
  // number_of_triangles
  std::uint32_t num_tris;
  fread(&num_tris, sizeof(std::uint32_t), 1, fp);

  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> verticies;

  for (std::uint32_t tri = 0; tri < num_tris; ++tri) {
    float xyz[3];
    fread(&xyz, sizeof(float), 3, fp);
    normals.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    normals.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    normals.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    fread(&xyz, sizeof(float), 3, fp);
    verticies.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    fread(&xyz, sizeof(float), 3, fp);
    verticies.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    fread(&xyz, sizeof(float), 3, fp);
    verticies.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    std::uint16_t attr;
    fread(&attr, sizeof(std::uint16_t), 1, fp);
  }

  glm::vec3 min_v(std::numeric_limits<float>::infinity()),
      max_v(-std::numeric_limits<float>::infinity());
  for (auto &pt : verticies) {
    min_v = glm::min(min_v, pt);
    max_v = glm::max(max_v, pt);
  }

  glm::vec3 center = (max_v + min_v) / 2.0f;

  for (auto &pt : verticies) {
    pt -= center;
  }

  std::fclose(fp);
  return {verticies, normals};
}

std::array<std::vector<glm::vec3>, 2> load_stl(const std::string &filename) {
  FILE *fp = std::fopen(filename.c_str(), "r");
  if (fp == nullptr) {
    std::fprintf(stderr, "Failed to open file: %s\n", filename.c_str());
    return std::array<std::vector<glm::vec3>, 2>();
  }
  char buf[255];
  size_t n = std::fscanf(fp, "%s", buf);
  if (n != 0 && std::strncmp(buf, "shape", 5) == 0) {
    return load_stl_ascii(fp);
  } else {
    std::fclose(fp);
    fp = std::fopen(filename.c_str(), "rb");
    return load_stl_binary(fp);
  }
}
