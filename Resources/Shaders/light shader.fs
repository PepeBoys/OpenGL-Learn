#version 460 core

out vec4 pColor;

uniform vec4 objectColor;

void main() {
	pColor = objectColor;
};