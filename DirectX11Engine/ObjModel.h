#pragma once

class ObjModel {
private:
	struct vertex {
		float x, y, z;
	};
	struct face {
		unsigned int v1, v2, v3;
	};
	std::vector<vertex> verts;
	std::vector<face> faces;
public:
	ObjModel();
	ObjModel(const char* filename);
	void readFile(const char* filename);
};