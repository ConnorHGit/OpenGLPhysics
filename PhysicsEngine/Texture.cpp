#include "Texture.h"

using namespace Texture;

std::map<std::string, GLuint> Texture::textures;

void Texture::loadTexture(std::string textureName, char* imagePath){
	unsigned char* imgData;
	unsigned int w, h;

	unsigned err = lodepng_decode32_file(&imgData, &w, &h, imagePath);
	if (err) std::cout << "decoder error " << err << ": " << lodepng_error_text(err) << std::endl;


	GLuint textID;
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	glUniform1i(glGetUniformLocation(Main::program, "textSamp"), 0);

	textures[textureName] = textID;
}