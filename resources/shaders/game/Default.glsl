[VERTEX]
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in mat4 aModel;

uniform mat4 uViewProjection;

void main()
{
	gl_Position = uViewProjection * aModel * vec4(aPos, 1.0);
}

[FRAGMENT]
#version 430 core

out vec4 fColor;

void main()
{
	fColor = vec4(0.2, 0.2, 0.2, 1.0);
}
