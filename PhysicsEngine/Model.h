#include <map>
#include <vector>
#include "Main.h"

namespace Mod{
	#ifndef ModelDefined
	#define ModelDefined
	struct Model
	{
		unsigned int vao;
		std::vector<unsigned int> vbos;
		unsigned int nVerticies;
		GLenum drawType;
		Model(){}
	};
	#endif
	extern std::map<std::string, Model> models;
	void createModel(GLenum drawType, unsigned int nVerticies, glm::vec3 verticies[], unsigned int nUv, glm::vec2 uvCoords[], std::string modelName);
	void createSquareModel(std::string modelName);
	void createCubeModel(std::string modelName);
}