uniform sampler2D uVelocity;

vec2 tex_size = textureSize(uVelocity,0);
vec2 tex_size_rev = vec2(1.0,1.0)/textureSize(uVelocity,0);
vec2 toPixCoords(vec2 tex_coords)
{
	return tex_coords*tex_size;
}
vec2 toTexCoords(vec2 pix_coords)
{
	return pix_coords*tex_size_rev;
}

/* Performs one step of the Jacobi iteration */
void main()
{
	vec4 left = texture2D(uVelocity, gl_TexCoord[0].xy + toTexCoords(vec2(-1.0,0.0)));
	vec4 right = texture2D(uVelocity, gl_TexCoord[0].xy + toTexCoords(vec2(1.0,0.0)));
	vec4 top = texture2D(uVelocity, gl_TexCoord[0].xy + toTexCoords(vec2(0.0,1.0)));
	vec4 bottom = texture2D(uVelocity, gl_TexCoord[0].xy + toTexCoords(vec2(0.0,-1.0)));

	vec2 gradient = vec2(right.z - left.z, top.z - bottom.z)/2.0;

	gl_FragColor = texture2D(uVelocity,gl_TexCoord[0].xy);
	gl_FragColor.xy = texture2D(uVelocity,gl_TexCoord[0].xy).xy - gradient;
	gl_FragColor.z = 0.0;
}
