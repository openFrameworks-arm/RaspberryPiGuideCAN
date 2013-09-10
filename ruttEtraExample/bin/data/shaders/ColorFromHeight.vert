#version 120

// Uniforms --------------
uniform float u_maxHeight;

// Varyings --------------
varying float v_heightFrac;

// -------------------------------------------
void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
	gl_FrontColor = gl_Color;
	v_heightFrac = gl_Vertex.y / u_maxHeight;
}