#ifndef LTEXTURE_H
#define LTEXTURE_H


#include <glew.h>
#include <string>
#include <il.h>
#include <cstdlib>
#include <GLFW\glfw3.h>
#include <cstring>
#include <iostream>
#include <stdio.h>

class LTexture
{
    public:
        LTexture();
        /*
        Pre Condition:
         -None
        Post Condition:
         -Initializes member variables
        Side Effects:
         -None
        */

        ~LTexture();
        /*
        Pre Condition:
         -None
        Post Condition:
         -Frees texture
        Side Effects:
         -None
        */
		bool loadTextureFromFile(const char* path);

        bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height );
        /*
        Pre Condition:
         -A valid OpenGL context
        Post Condition:
         -Creates a texture from the given pixels
         -Reports error to console if texture could not be created
        Side Effects:
         -Binds a NULL texture
        */

        void freeTexture();
        /*
        Pre Condition:
         -A valid OpenGL context
        Post Condition:
         -Deletes texture if it exists
         -Sets texture ID to 0
        Side Effects:
         -None
        */

		void render(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
        /*
        Pre Condition:
         -A valid OpenGL context
         -Active modelview matrix
        Post Condition:
         -Translates to given position and renders textured quad
        Side Effects:
         -Binds member texture ID
        */

        GLuint getTextureID();
        /*
        Pre Condition:
         -None
        Post Condition:
         -Returns texture name/ID
        Side Effects:
         -None
        */

        GLuint textureWidth();
        /*
        Pre Condition:
         -None
        Post Condition:
         -Returns texture width
        Side Effects:
         -None
        */

        GLuint textureHeight();
        /*
        Pre Condition:
         -None
        Post Condition:
         -Returns texture height
        Side Effects:
         -None
        */

    private:
        //Texture name
        GLuint mTextureID;

        //Texture dimensions
        GLuint mTextureWidth;
        GLuint mTextureHeight;
};

#endif



