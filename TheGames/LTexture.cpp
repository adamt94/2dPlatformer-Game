#include "stdafx.h"
#include "LTexture.h"
LTexture::LTexture()
{
	//Initialize texture ID
	mTextureID = 0;

	//Initialize texture dimensions
	mTextureWidth = 0;
	mTextureHeight = 0;
}

LTexture::~LTexture()
{
	//Free texture data if needed
	freeTexture();
}
bool LTexture::loadTextureFromFile(const char* path)
{
	//Texture loading success
	bool textureLoaded = false;

	//Generate and set current image ID
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);
	
	
	
	
	//Load image
	if (path == NULL)
	{
		std::cout << false << std::endl;
		return false;
	}
	 ilLoadImage((path));
	 ILboolean success = true;
	//Image loaded successfully
	if (success == IL_TRUE)
	{
		//Convert image to RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (success == IL_TRUE)
		{
			//Create texture from file pixels
			textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}

		//Delete file from memory
		ilDeleteImages(1, &imgID);
	}

	//Report error
	if (!textureLoaded)
	{
		printf("Unable to load %s\n", path);
	}

	return textureLoaded;
}

bool LTexture::loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height)
{
	//Free texture if it exists
	freeTexture();

	//Get texture dimensions
	mTextureWidth = width;
	mTextureHeight = height;
	// Generate texture ID
		glGenTextures(1, &mTextureID);

	//Bind texture ID
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	//Generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error loading texture from %p pixels! %s\n", pixels, gluErrorString(error));
		return false;
	}

	return true;
}

void LTexture::freeTexture()
{
	//Delete texture
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mTextureWidth = 0;
	mTextureHeight = 0;
}

void LTexture::render(GLfloat x, GLfloat y,GLfloat width, GLfloat height)
{
	//If the texture exists
	if (mTextureID != 0)
	{
		//Enable 2D textures
		glEnable(GL_TEXTURE_2D);
		//Enable transparency (alpha channels)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Set up the environment
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//Bind the texture ID we'll be using
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		//Draw the textured quad
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0); glVertex2f(x + width, y + height);
		glTexCoord2f(0, 0); glVertex2f(x, y + height);
		glTexCoord2f(0, 1); glVertex2f(x, y);
		glTexCoord2f(1, 1); glVertex2f(x + width, y);
		glEnd();

		//Disable enabled modes as we're done with them
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
}
GLuint LTexture::getTextureID()
{
	return mTextureID;
}

GLuint LTexture::textureWidth()
{
	return mTextureWidth;
}

GLuint LTexture::textureHeight()
{
	return mTextureHeight;
}