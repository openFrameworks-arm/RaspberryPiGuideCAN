attribute vec4 position;		// set automatically by OF 
attribute vec4 color;			// set automatically by OF 
attribute vec4 normal;			// set automatically by OF 
attribute vec2 texcoord;		// set automatically by OF 

uniform mat4 modelViewMatrix;	// set automatically by OF 
uniform mat4 projectionMatrix;	// set automatically by OF 

uniform float time;

void main()
{
	vec4 pos = projectionMatrix * modelViewMatrix * position;
	gl_Position = pos;
}