#pragma once
#include "../../../libs.h"
#include "Vertex.h"

class ObjLoader {
public:
	static std::vector<Vertex> loadObj(const char* fileName);
};