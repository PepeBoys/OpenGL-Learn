#version 460

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCords;

out vec3 normal;
out vec3 fragPos;
out vec2 texCords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	normal = mat3(transpose(inverse(model))) * iNormal;
	texCords = iTexCords;
	fragPos = normalize(vec3(model * vec4(pos, 1.0f)));
};