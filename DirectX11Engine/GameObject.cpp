#include "SDXEngine.h"

unsigned int objCount;
GameObject::GameObject(std::string name) {
	model = NULL;
	loc = new double[3]{ 0.0 };
	vector = NULL;
	GameObject::name = name;
	objCount++;
}

GameObject::GameObject() {
	model = NULL;
	loc = new double[3]{ 0.0 };
	vector = NULL;
	std::stringstream stm;
	stm << "obj_" << objCount;
	name = stm.str();
	objCount++;
}

std::string GameObject::getName() {
	return name;
}

/*////////////////////////////
* Model functions
*/////////////////////////////

void GameObject::setObjModel(ObjModel* model) {
	GameObject::model = model;
}

ObjModel* GameObject::getObjModel() {
	return model;
}

/*////////////////////////////
* Location and rotation
*/////////////////////////////

void GameObject::setLocation(double* location) {
	loc = location;
}

void GameObject::setLocationX(double x) {
	loc[0] = x;
}

void GameObject::setLocationY(double y) {
	loc[1] = y;
}

void GameObject::setLocationZ(double z) {
	loc[2] = z;
}

double GameObject::getLocationX() {
	return loc[0];
}

double GameObject::getLocationY() {
	return loc[1];
}

double GameObject::getLocationZ() {
	return loc[2];
}

PysicsVector3D* GameObject::getPysicsVector3D() {
	return vector;
}

void GameObject::setPysicsVector3D(PysicsVector3D* vector) {
	GameObject::vector = vector;
}