#version 330 core

layout(location = 0) in vec2 quadXY;
layout(location = 1) in vec2 quadUV;
layout(location = 2) in vec3 col0;
layout(location = 3) in vec3 col1;
layout(location = 4) in vec3 col2;
layout(location = 5) in vec4 color;
layout(location = 6) in vec4 texUV;
layout(location = 7) in vec2 size;

uniform mat3 worldProj;
uniform mat3 cameraProj;

out vec2 fragUV;
out vec4 fragColor;

void main() {
    mat3 transform = mat3(col0, col1, col2);
    vec3 position = transform * vec3(quadXY * size, 1.0);
    vec3 view = cameraProj * position;
    vec3 final = worldProj * view;

    gl_Position = vec4(final.xy, 0.0, 1.0);
    fragUV = texUV.xy + quadUV * texUV.zw;
    fragColor = color;
}