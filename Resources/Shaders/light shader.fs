#version 460

out vec4 pColor;

uniform vec4 objectColor;

void main() {
	pColor = objectColor;
};