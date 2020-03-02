#include "stl.hpp"

#include <cstring>
#include <string>
#include <vector>

#include <glm/glm.hpp>

void load_stl_ascii(FILE *fp) {
  // TODO: Ascii STL file format
}
void load_stl_binary(FILE *fp) {
  // Header
  char header[80];
  fread(header, sizeof(char), 80, fp);
  // number_of_triangles
  std::uint32_t num_tris;
  fread(&num_tris, sizeof(std::uint32_t), 1, fp);

  std::vector<glm::vec3> normals(num_tris);
  std::vector<glm::vec3> verticies(num_tris * 3);

  for (std::uint32_t tri = 0; tri < num_tris; ++tri) {
    float xyz[3];
    fread(&xyz, sizeof(float), 3, fp);
    normals.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    fread(&xyz, sizeof(float), 3, fp);
    verticies.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    fread(&xyz, sizeof(float), 3, fp);
    verticies.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    fread(&xyz, sizeof(float), 3, fp);
    verticies.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
    std::uint16_t attr;
    fread(&attr, sizeof(std::uint16_t), 1, fp);
    if (glm::any(glm::isnan(normals.back()))) {
      // TODO: Compute normal manually if it is nan
    }
  }

  std::fclose(fp);
}

void load_stl(const std::string &filename) {
  FILE *fp = std::fopen(filename.c_str(), "r");
  if (fp == nullptr) {
    std::fprintf(stderr, "Failed to open file: %s\n", filename.c_str());
    return;
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
