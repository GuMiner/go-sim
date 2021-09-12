#version 400 core

out vec4 color;

void main(void)
{
    // The entire view range spans from 0 to 1 in the depth coord.
    color = vec4(vec3(gl_FragCoord.z), 1.0);
}