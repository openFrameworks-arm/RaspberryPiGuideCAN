attribute vec4 position;		// set automatically by OF 
attribute vec4 color;			// set automatically by OF 
attribute vec4 normal;			// set automatically by OF 
attribute vec2 texcoord;		// set automatically by OF 

uniform mat4 modelViewMatrix;	// set automatically by OF 
uniform mat4 projectionMatrix;	// set automatically by OF 

// Uniforms --------------
uniform float u_maxHeight;

// Varyings --------------
varying float v_heightFrac;

// -------------------------------------------
void main()
{
	v_heightFrac = position.y / u_maxHeight;
	
	vec4 pos = projectionMatrix * modelViewMatrix * position;
	gl_Position = pos;
}