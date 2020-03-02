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
} // namespace graphics
