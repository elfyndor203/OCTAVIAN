#version 330 core

in vec2 fragUV;
in vec4 fragColor;

out vec4 outColor;

uniform sampler2D tex;

void main() {
	outColor = texture(tex, fragUV) * fragColor;
}