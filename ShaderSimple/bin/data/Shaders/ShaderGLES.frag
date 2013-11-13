precision highp float; // this will make the default precision high

uniform vec4 color;

uniform float time;
		
void main()
{
	// Pulse screen
	float col = (cos(time*2.0)+1.0)*0.5;
	gl_FragColor = vec4( col, col, col, 1.0 ); 

	/*
	// Bars
	float barLength = (((cos(time)+1.0)*0.5) * 90.0) + 10.0;
	float col = mod( gl_FragCoord.x, barLength) / barLength;
	gl_FragColor = vec4( col, col, col, 1.0 ); 
	*/
	
	/*
	// Plasma
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	float mov0 = x+y+cos(sin(time)*2.)*100.+sin(x/100.)*1000.;
	float mov1 = y / 768.0 / 0.2 + time;
	float mov2 = x / 1024.0 / 0.2;
	float c1 = abs(sin(mov1+time)/2.+mov2/2.-mov1-mov2+time);
	float c2 = abs(sin(c1+sin(mov0/1000.+time)+sin(y/40.+time)+sin((x+y)/100.)*3.));
	float c3 = abs(sin(c2+cos(mov1+mov2+c2)+cos(mov2)+sin(x/1000.)));
	gl_FragColor = vec4( c1,c2,c3,1.0);
	*/
}
