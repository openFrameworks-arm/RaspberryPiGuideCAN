precision highp float; // this will make the default precision high

// Uniforms --------------
uniform sampler2D u_paletteSampler;

// Varyings --------------
varying float v_heightFrac;

// -------------------------------------------
void main()
{

	vec2 texCoord = vec2(0.0, 0.0);
	texCoord.s = v_heightFrac;
	vec4 color = texture2D( u_paletteSampler, texCoord );
	
	gl_FragColor = color;// * gl_Color;
	
	//gl_FragColor = vec4(v_heightFrac,v_heightFrac,v_heightFrac,1.0);
	
}
