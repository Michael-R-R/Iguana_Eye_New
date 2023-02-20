[VERTEX]
#version 430 core

out vec3 vNearPoint;
out vec3 vFarPoint;
out mat4 vView;
out mat4 vProj;

uniform mat4 uView;
uniform mat4 uProjection;

vec3 gridPlane[6] = vec3[]
(
	vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
	vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

vec3 unprojectPoint(float x, float y, float z, mat4 view, mat4 projection)
{
	mat4 viewInv = inverse(view);
	mat4 projInv = inverse(projection);
	vec4 unprojectedPoint = viewInv * projInv * vec4(x, y, z, 1.0);
	
	return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
	vView = uView;
	vProj = uProjection;

	vec3 point = gridPlane[gl_VertexID].xyz;
	vNearPoint = unprojectPoint(point.x, point.y, 0.0, uView, uProjection).xyz;
	vFarPoint = unprojectPoint(point.x, point.y, 1.0, uView, uProjection).xyz;
	
    gl_Position = vec4(point, 1.0);
}

[FRAGMENT]

#version 430 core

in vec3 vNearPoint;
in vec3 vFarPoint;
in mat4 vView;
in mat4 vProj;
out vec4 FragColor;

float nearClip = 0.1f;
float farClip = 2000.0f;

vec4 grid(vec3 fragPos3D, float scale)
{
	vec2 coord = fragPos3D.xz * scale; // Sets distance between lines
	vec2 derivative = fwidth(coord);
	vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
	float line = min(grid.x, grid.y);
	float minimumZ = min(derivative.y, 1);
	float minimumX = min(derivative.x, 1);
	vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));
	
	// Z axis
	if(fragPos3D.x > -1.0 * minimumX && fragPos3D.x < 1.0 * minimumX)
	{
		color = vec4(0.0, 0.0, 1.0, 1.0 - min(line, 1.0));
	}
	
	// X axis
	if(fragPos3D.z > -1.0 * minimumZ && fragPos3D.z < 1.0 * minimumZ)
	{
		color = vec4(1.0, 0.0, 0.0, 1.0 - min(line, 1.0));
	}
	
	return color;
}

float computeDepth(vec3 pos)
{
	// Get the clip-space coordinates
	vec4 clipSpacePos = vProj * vView * vec4(pos.xyz, 1.0);
	
	// Get the depth value in normalized device coordinates
	float clipSpaceDepth = clipSpacePos.z / clipSpacePos.w;
	
	// Compute the range based on gl_DepthRange settings
	float far = gl_DepthRange.far;
	float near = gl_DepthRange.near;

	// Compute depth
	float depth = (((far-near) * clipSpaceDepth) + near + far) / 2.0;

	return depth;
}

float computeLinearDepth(vec3 pos)
{
    vec4 clipSpacePos = vProj * vView * vec4(pos.xyz, 1.0);
    float clipSpaceDepth = (clipSpacePos.z / clipSpacePos.w) * 2.0 - 1.0;
    float linearDepth = (2.0 * nearClip * farClip) / (farClip + nearClip - clipSpaceDepth * (farClip - nearClip));
	
    return linearDepth / farClip; // normalize
}

void main()
{
    float x = -vNearPoint.y / (vFarPoint.y - vNearPoint.y);
    vec3 fragPos3D = vNearPoint + x * (vFarPoint - vNearPoint);
	
    gl_FragDepth = computeDepth(fragPos3D);
	
    float linearDepth = computeLinearDepth(fragPos3D);
    float fading = max(0, (0.5 - linearDepth));

    FragColor = (grid(fragPos3D, 1) +  grid(fragPos3D, 0.5)) *       float(x > 0); 
    FragColor.a *= fading;
}
