#version 120

#extension GL_ARB_texture_rectangle : enable

// Uniforms --------------
uniform sampler2DRect u_paletteSampler;

// Varyings --------------
varying float v_heightFrac;


// -------------------------------------------
void main( void )
{  
	vec2 texCoord = vec2(0.0, 0.0);
	texCoord.s = v_heightFrac;
	texCoord.s *= 256.0; 	// we assume the palettes are always 256 pixels/colors wide
	vec4 color = texture2DRect( u_paletteSampler, texCoord );
	
	gl_FragColor = color * gl_Color;
	
	//gl_FragColor = vec4(v_heightFrac,v_heightFrac,v_heightFrac,1.0);
}

