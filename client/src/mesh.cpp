//------------------------------------//
// Author: Breno Cunha Queiroz        //
// Date: 2020-11-18                   //
// SCC0650 - Computação Gráfica (2020)//
//------------------------------------//
#include <fstream>
#include <sstream>
#include <iostream>
#include "mesh.hpp"
#include "helpers/log.hpp"

Mesh::Mesh(std::string fileName)
{
	loadFile(fileName);
	setupMesh();
}

Mesh::~Mesh()
{

}

std::vector<std::string> Mesh::splitLine(const std::string s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
    std::string item;

    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;	
}

void Mesh::loadFile(std::string fileName)
{
	std::ifstream file(("assets/models/"+fileName).c_str());
	if(file.is_open())
	{
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;

		std::string line;
		while(getline(file, line))
		{
			std::vector<std::string> splitted = splitLine(line, ' ');
			std::string code = splitted[0];
			if(code=="#")
				continue;
			else if(code=="v")
			{
				Vertex v;
				v.position.x = std::stof(splitted[1]);
				v.position.y = std::stof(splitted[2]);
				v.position.z = std::stof(splitted[3]);
				//std::cout << "vertex " << v.position.x << " " << v.position.y << " " << v.position.z << std::endl;
				_vertices.push_back(v);
			}
			else if(code=="vt")
			{
				glm::vec2 v;
				v.x = std::stof(splitted[1]);
				v.y = std::stof(splitted[2]);
				texCoords.push_back(v);
				//std::cout << "tex " << _vertices[texIndex-1].texCoords.x << " " << _vertices[texIndex-1].texCoords.y << std::endl;
			}
			else if(code=="vn")
			{
				glm::vec3 v;
				v.x = std::stof(splitted[1]);
				v.y = std::stof(splitted[2]);
				v.z = std::stof(splitted[3]);
				normals.push_back(v);
			}
			else if(code=="f")
			{
				for(int i=1;i<(int)splitted.size();i++)
				{
					std::vector<std::string> values = splitLine(splitted[i],'/');
					int vert = std::stoi(values[0])-1;
					int tex = std::stoi(values[1])-1;
					int normal = std::stoi(values[2])-1;
					_indices.push_back(vert);
					_vertices[vert].texCoords = texCoords[tex];
					_vertices[vert].normal = normals[normal];
				}
			}
			else if(code=="usemtl" || code=="usemat")
			{

			}
		}
		Log::success("Mesh", fileName+" loaded successfully: " 
				+ std::to_string((int)_vertices.size()) + " vertices, "
				+ std::to_string((int)_indices.size()) + " indices.");

		file.close();
	}
	else
	{
		Log::error("Mesh", "Failed to open file " + fileName);
	}
}

void Mesh::setupMesh()
{
	// Generate buffers
 	glGenVertexArrays(1, &_VAO);// Vertex array object
    glGenBuffers(1, &_VBO);// Vertex buffer object
    glGenBuffers(1, &_EBO);// Element buffer object
  
	// Operations on VAO
    glBindVertexArray(_VAO);

	// Add vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);  

	// Add indices to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // Vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // Vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	// Unbind VAO
    glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
