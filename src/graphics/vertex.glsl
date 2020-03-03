#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  FragPos = vec3(uModel * vec4(aPos, 1.0));
  Normal = vec3((transpose(inverse(uModel))) * vec4(aNormal, 0.0));
  gl_Position = uProjection * uView * vec4(FragPos, 1.0);
}
