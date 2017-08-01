#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

out vec4 vColor;

void main() {
  gl_Position = projectionMatrix * modelMatrix * vec4(position, 1.0);
  vColor = vec4(color, 1.0);
}
