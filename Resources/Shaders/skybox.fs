#version 460

in vec2 texCords;

out vec4 fragColor;

uniform sampler2D tex;

void main() {
	fragColor = texture(tex, texCords);
};