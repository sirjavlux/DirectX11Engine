#include "SDXEngine.h"

PysicsVector3D::PysicsVector3D() {
	PysicsVector3D::x = 0;
	PysicsVector3D::y = 0;
	PysicsVector3D::z = 0;
}

PysicsVector3D::PysicsVector3D(double x, double y, double z) {
	PysicsVector3D::x = x;
	PysicsVector3D::y = y;
	PysicsVector3D::z = z;
}

void PysicsVector3D::multiply(double amount) {
	x = x* amount, y = y* amount, z = z* amount;
}

double PysicsVector3D::lenght() {
	return sqrt(pow(x, 2) + pow(x, 2) + pow(x, 2));
}

void PysicsVector3D::normalize() {
	double l = lenght();
	x = x / l, y = y / l, z = z / l;
}

PysicsVector3D PysicsVector3D::getDirectionalVector() {
	double l = lenght();
	return PysicsVector3D(x / l, y / l, z / l);
}

double PysicsVector3D::getX() {
	return x;
}

double PysicsVector3D::getY() {
	return y;
}

double PysicsVector3D::getZ() {
	return z;
}