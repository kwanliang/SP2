#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
    static Mesh* GenerateQuad(const std::string &meshName, Color color);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, TexCoord texCoord);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
    static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlices = 36);
    static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices = 36);
    static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlices = 36);
    static Mesh* GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlices = 36);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStacks = 18, unsigned numSlices = 36);
	//static Mesh* GenerateTorus(const std::string &meshName, unsigned numStack, unsigned numSlice, float outerR, float innerR);
    static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
    static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif