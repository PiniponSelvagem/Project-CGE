#pragma once
#include <engine/Libs.h>
#include <engine/models/Vertex.h>
#include <engine/models/Mesh.h>

class ObjLoader {
	public:
		static Mesh* loadObj(const char* fileName);
		static Mesh* loadObj_arrays(const char* fileName);
};