#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;
layout(location = 3) in vec2 vertexTexCoord;

// Output data ; will be interpolated for each fragment.
out vec3 vertexPosition_cameraspace;
out vec3 fragmentColor;
out vec3 vertexNormal_cameraspace;
out vec2 texCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 MV_inverse_transpose;
uniform bool lightEnabled;

void main(){
	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
	
	if(lightEnabled == true)
	{
		// Vector position, in camera space
		vertexPosition_cameraspace = ( MV * vec4(vertexPosition_modelspace, 1) ).xyz;
		
		// Vertex normal, in camera space
		// Use MV if ModelMatrix does not scale the model ! Use its inverse transpose otherwise.
		vertexNormal_cameraspace = ( MV_inverse_transpose * vec4(vertexNormal_modelspace, 0) ).xyz;
	}
	// The color of each vertex will be interpolated to produce the color of each fragment
	fragmentColor = vertexColor;
	// A simple pass through. The texCoord of each fragment will be interpolated from texCoord of each vertex
	texCoord = vertexTexCoord;
}

