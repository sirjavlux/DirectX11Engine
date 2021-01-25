#include "SDXEngine.h"

unsigned int objCount;
GameObject::GameObject(std::string name) {
	model = NULL;
	loc = new double[3]{ 0.0 };
	rot = new double[3]{ 0.0 };
	GameObject::name = name;
	objCount++;
}

GameObject::GameObject() {
	model = NULL;
	loc = new double[3]{ 0.0 };
	rot = new double[3]{ 0.0 };
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

void GameObject::setRotation(double* rotation) {
	rot = rotation;
}

void GameObject::setLocation(double* location) {
	loc = location;
}

void GameObject::setRotationX(double x) {
	rot[0] = x;
}

void GameObject::setRotationY(double y) {
	rot[1] = y;
}

void GameObject::setRotationZ(double z) {
	rot[2] = z;
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

double GameObject::getRotationX() {
	return rot[0];
}

double GameObject::getRotationY() {
	return rot[1];
}

double GameObject::getRotationZ() {
	return rot[2];
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