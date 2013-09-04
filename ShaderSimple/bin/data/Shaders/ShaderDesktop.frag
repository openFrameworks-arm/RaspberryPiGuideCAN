#version 120

uniform float time;

void main( void )
{
	/* // Pulse screen
	float col = (cos(time*2.0)+1.0)*0.5;
	gl_FragColor = vec4( col, col, col, 1.0 );
	*/

	/* // Bars
	float barLength = (((cos(time)+1.0)*0.5) * 90.0) + 10.0;
	float col = mod( gl_FragCoord.x, barLength) / barLength;
	gl_FragColor = vec4( col, col, col, 1.0 ); 
	*/

	
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	float mov0 = x+y+cos(sin(time)*2.)*100.+sin(x/100.)*1000.;
	float mov1 = y / 720.0 / 0.2 + time;
	float mov2 = x / 1280.0 / 0.2;
	float c1 = abs(sin(mov1+time)/2.+mov2/2.-mov1-mov2+time);
	float c2 = abs(sin(c1+sin(mov0/1000.+time)+sin(y/40.+time)+sin((x+y)/100.)*3.));
	float c3 = abs(sin(c2+cos(mov1+mov2+c2)+cos(mov2)+sin(x/1000.)));
	gl_FragColor = vec4( c1,c2,c3,1.0);
	

	/*float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	vec4 outCol = vec4(1,1,1,1);	
	outCol.g = sin(x * cos(time/15.0) * 120.0) + cos(y * sin(time/10.0) * 120.0) + sin(sqrt(y * y + x * x) * 40.0);
	gl_FragColor = outCol;*/

	/*
	// From: https://www.shadertoy.com/view/XdX3Wn
	// Rebb/TRSi^Paradise 

float an= sin(iGlobalTime)/3.14157;
float as= sin(an);
float zoo = .23232+.38*sin(.7*iGlobalTime);
void main(void)
{
  vec2 position = ( gl_FragCoord.xy / iResolution.xy *3.3 );

	float color = 0.0;
	color += sin(position.x - position.y) ;
	color += sin(iGlobalTime)* cos(sin(iGlobalTime)*position.y*position.x*sin(position.x))+.008;
	color += sin(iGlobalTime)+position.x*sin(position.y*sin(sin(tan(cos (iGlobalTime)))));
	gl_FragColor = vec4( vec3(sin(color*color)*4.0, sin(color*color) , color )*sin(iGlobalTime+position.x/(iGlobalTime*3.14)),iGlobalTime/10.828 );

}*/


}