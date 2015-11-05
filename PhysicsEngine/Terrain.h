#include "Main.h"
namespace Terrain
{
	void initTerrain();
	void destroyTerrain();
	void createTerrainModel(std::string modelName);
	unsigned int createTerrainIndexBuffer(glm::vec2 start, glm::vec2 end, bool existing);
	void renderTerrain(glm::mat4 viewProjectMatrix);
	float getElevation(glm::vec2 pos);
	extern glm::vec3 normal;
}