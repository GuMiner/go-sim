#version 400 core

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

uniform vec3 colorOverride;

layout (location = 0) in vec3 position;

out vec3 fs_color;

// Basic renderer for voxels (no shading)
void main(void)
{
    fs_color = colorOverride;
    gl_Position = projection * camera * model * vec4(position, 1.0f);
}