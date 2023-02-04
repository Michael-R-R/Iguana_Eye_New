[VERTEX]
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec4 aColor;
layout (location = 4) in vec3 aAtlas;
layout (location = 5) in mat4 aModel;

out vec4 vColor;

uniform mat4 uViewProjection;

void main()
{
	vColor = aColor;

	gl_Position = uViewProjection * aModel * vec4(aPos, 1.0);
}

[FRAGMENT]
#version 430 core

in vec4 vColor;

out vec4 FragColor;

void main()
{
	FragColor = vColor;
}
