[VERTEX]
#version 430 core

layout (location = 0) in vec3 aPos;

out vec4 vColor;

void main()
{
	if(aPos.x == 0.0)
		vColor = vec4(0.0, 1.0, 0.0, 1.0);
	else if(aPos.y == 0.0)
		vColor = vec4(1.0, 0.0, 0.0, 1.0);
	else
		vColor = vec4(1.0, 1.0, 1.0, 1.0);

	gl_Position = vec4(aPos, 1.0);
}

[FRAGMENT]
#version 430 core

in vec4 vColor;

out vec4 FragColor;

void main()
{
	FragColor = vColor;
}
