#include "Main.h"
#include <map>
#include <vector>
namespace Texture{
	void loadTexture(std::string textureName, char* imageName);
	extern std::map<std::string, GLuint> textures;
}