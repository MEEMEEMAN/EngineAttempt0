#include "pch.h"
#include "..//rendering/GLTexture.h"
#include "..//rendering/Material.h"

class TexturedMaterial : public Material
{
	public:

	using Material::Material;

	void AddTexture(GLTexture texture)
	{
		textures.push_back(texture);
	}

		void ApplyShaderParameters() override
		{
			for (size_t i = 0; i < textures.size(); i++)
			{
				textures[i].BindTexture2D(i);
			}
		}

	private:
	std::vector<GLTexture> textures;
};