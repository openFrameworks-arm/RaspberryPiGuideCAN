attribute vec4 position;		// set automatically by OF

uniform mat4 modelViewMatrix;	// set automatically by OF
uniform mat4 projectionMatrix;	// set automatically by OF

void main()
{
	vec4 pos = projectionMatrix * modelViewMatrix * position;
	gl_Position = pos;

}