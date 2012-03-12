uniform sampler2DRect source;
uniform vec2 direction;
void main(void) {
	vec2 tc = gl_TexCoord[0].st;
	gl_FragColor = 0.0285367 * texture2DRect(source, tc);
	gl_FragColor += 0.0567264 * 
		(texture2DRect(source, tc - (direction * 1.49817)) + 
		texture2DRect(source, tc + (direction * 1.49817)));
}

