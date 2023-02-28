[VERTEX]
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aOffset; // instanced

uniform vec2 uScale;

void main()
{
	float x = (aPos.x * uScale.x) + aOffset.x;
	float y = (aPos.y * uScale.y) + aOffset.y;

	gl_Position = vec4(x, y, 0.0, 1.0);
}

[FRAGMENT]
#version 430 core

out vec4 fColor;

void main()
{
	fColor = vec4(0.0, 0.0, 1.0, 1.0);
}