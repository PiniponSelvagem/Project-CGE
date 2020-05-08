#pragma once
#include "../../../libs.h"
#include "Vertex.h"
#include "Mesh.h"

class ObjLoader {
	public:
		static Mesh* loadObj(const char* fileName);
};