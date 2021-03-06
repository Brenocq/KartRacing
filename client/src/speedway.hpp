//------------------------------------//
// Author: Breno Cunha Queiroz        //
// Date: 2020-11-18                   //
// SCC0650 - Computação Gráfica (2020)//
//------------------------------------//
#ifndef SPEEDWAY_H
#define SPEEDWAY_H
#include <vector>
#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"

class Speedway
{
	public:
		Speedway(Shader* shader);
		~Speedway();

		void draw();

		static Mesh* mesh;
		static Texture* texture;
		static Mesh* meshGrass;
		static Texture* textureGrass;
		static Mesh* meshGrandstand;
		static Texture* textureGrandstand;
		static Mesh* meshPost;
		static Texture* texturePost;

	private:
		Shader* _shader;
};

#endif// SPEEDWAY_H
