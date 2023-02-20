[VERTEX]
#version 430 core

layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0);
}

[FRAGMENT]
#version 430 core

out vec4 FragColor;

uniform vec4 uColor;

void main()
{
	FragColor = uColor;
}
