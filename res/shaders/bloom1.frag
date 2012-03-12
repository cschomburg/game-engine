#extension GL_ARB_texture_rectangle : enable

void main()
{
   vec4 sum;
   vec2 texcoord = vec2(gl_TexCoord[0]);
   int j;
   int i;

   for( i= -4 ;i < 4; i++)
   {
        for (j = -3; j < 3; j++)
        {
            sum += texture2DRect(bgl_RenderedTexture, texcoord + vec2(j, i)*2.0) * 0.25;
        }
   }
}
