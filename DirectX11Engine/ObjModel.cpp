#include "SDXEngine.h"

ObjModel::ObjModel() {
	verts = std::vector<vertex>();
	faces = std::vector<face>();
}

ObjModel::ObjModel(const char* filename) {
	verts = std::vector<vertex>();
	faces = std::vector<face>();
	readFile(filename);
}

void ObjModel::readFile(const char* filename) {
	verts.clear();
	faces.clear();

	std::ifstream fin(filename);

	std::string str;
	if (!fin) return;
	while (fin >> str) {
		switch (*str.c_str()) {
		case 'v': {
			vertex v;
			fin >> v.x >> v.y >> v.z;
			verts.push_back(v);
		} break;
		case 'f': {
			face f;
			fin >> f.v1 >> f.v2 >> f.v3;
			faces.push_back(f);
		} break;
		}
	}
}