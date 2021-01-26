#include "SDXEngine.h"

unsigned int cameraCount;
Camera::Camera(std::string name) {
	loc = new double[3]{ 0.0 };
	vector = NULL;
	Camera::name = name;
	cameraCount++;
}

Camera::Camera() {
	loc = new double[3]{ 0.0 };
	vector = NULL;
	std::stringstream stm;
	stm << "camera_" << cameraCount;
	name = stm.str();
	cameraCount++;
}

std::string Camera::getName() {
	return name;
}

/*////////////////////////////
* Location and rotation
*/////////////////////////////

void Camera::setLocation(double* location) {
	loc = location;
}

void Camera::setLocationX(double x) {
	loc[0] = x;
}

void Camera::setLocationY(double y) {
	loc[1] = y;
}

void Camera::setLocationZ(double z) {
	loc[2] = z;
}

double Camera::getLocationX() {
	return loc[0];
}

double Camera::getLocationY() {
	return loc[1];
}

double Camera::getLocationZ() {
	return loc[2];
}

PysicsVector3D* Camera::getPysicsVector3D() {
	return vector;
}

void Camera::setPysicsVector3D(PysicsVector3D* vector) {
	Camera::vector = vector;
}