precision highp float; // this will make the default precision high

uniform vec2        resolution;
uniform float       time;
uniform sampler2D   tex0;

varying vec2        texcoord0;
		
void main()
{
    // ---------------------------------------------------------
    // just draw the texture to screen
    //gl_FragColor = texture2D(tex0,texcoord0);

    // ---------------------------------------------------------
    // just draw the texture to screen, inverted
    
    / this isn't working, and can't see the output log, wil fix in a bit.
    //gl_FragColor = vec4(1,1,1,0) - texture2D(tex0,texcoord0); // vec4(1,1,1,0) as we don't want to touch the alpha


    /*
    // ---------------------------------------------------------
    // let's wobble the image channels around independently, a bit Fear and Loathing in Las Vegas style
    mediump float newTime = time * 2.0;

    vec2 newTexCoord;
    newTexCoord.s = texcoord0.s + (cos(newTime + (texcoord0.s*20.0)) * 0.01);
    newTexCoord.t = texcoord0.t + (sin(newTime + (texcoord0.t*20.0)) * 0.01);

    mediump vec2 texCoordRed    = newTexCoord;
    mediump vec2 texCoordGreen  = newTexCoord;
    mediump vec2 texCoordBlue   = newTexCoord;

    texCoordRed     += vec2( cos((newTime * 2.76)), sin((newTime * 2.12)) )* 0.01;
    texCoordGreen   += vec2( cos((newTime * 2.23)), sin((newTime * 2.40)) )* 0.01;
    texCoordBlue    += vec2( cos((newTime * 2.98)), sin((newTime * 2.82)) )* 0.01;  

    mediump float colorR = texture2D( tex0, texCoordRed ).r;
    mediump float colorG = texture2D( tex0, texCoordGreen).g;
    mediump float colorB = texture2D( tex0, texCoordBlue).b;       

    mediump vec4 outColor = vec4( colorR, colorG, colorB, 1.0 );

    gl_FragColor = outColor;
    */


    /*
    // --------------------------------------------------------- 
    // http://www.iquilezles.org/apps/shadertoy/?p=Postpro
	vec2 q = gl_FragCoord.xy / resolution.xy;
    vec2 uv = 0.5 + (q-0.5)*(0.9 + 0.1*sin(0.2*time));

    vec3 oricol = texture2D(tex0,vec2(q.x,1.0-q.y)).xyz;
    vec3 col;

    col.r = texture2D(tex0,vec2(uv.x+0.003,-uv.y)).x;
    col.g = texture2D(tex0,vec2(uv.x+0.000,-uv.y)).y;
    col.b = texture2D(tex0,vec2(uv.x-0.003,-uv.y)).z;

    col = clamp(col*0.5+0.5*col*col*1.2,0.0,1.0);

    col *= 0.5 + 0.5*16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y);

    col *= vec3(0.8,1.0,0.7);

    col *= 0.9+0.1*sin(10.0*time+uv.y*1000.0);

    col *= 0.97+0.03*sin(110.0*time);

    float comp = smoothstep( 0.2, 0.7, sin(time) );
    col = mix( col, oricol, clamp(-2.0+2.0*q.x+3.0*comp,0.0,1.0) );

    gl_FragColor = vec4(col,1.0);
    */
}