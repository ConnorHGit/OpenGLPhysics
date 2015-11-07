#include "Main.h"
namespace Terrain
{
	struct tVertData{
		glm::vec3 vert;
		float slope;
		tVertData(glm::vec3 vertA, float slopeA){
			vert = vertA;
			slope = slopeA;
		}
	};
	void initTerrain();
	void destroyTerrain();
	void createTerrainModel(std::string modelName);
	unsigned int createTerrainIndexBuffer(glm::vec2 start, glm::vec2 end, bool existing);
	void renderTerrain(glm::mat4 viewProjectMatrix);
	float getElevation(glm::vec2 pos);
	extern glm::vec3 normal;
}