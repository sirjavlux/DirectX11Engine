#include "SDXEngine.h"

unsigned int sceneCount;
Scene::Scene() {
	gameObjects = new std::map<const char*, GameObject*>();
	std::stringstream stm;
	stm << "scene_" << sceneCount;
	name = stm.str();
	sceneCount++;
}

Scene::Scene(std::string name) {
	gameObjects = new std::map<const char*, GameObject*>();
	Scene::name = name;
	sceneCount++;
}

std::string Scene::getName() {
	return name;
}

void Scene::addGameObject(GameObject* obj) {
	if (gameObjects->find(obj->getName().c_str()) == gameObjects->end()) gameObjects->insert( { obj->getName().c_str(), obj } );
}

void Scene::removeGameObject(GameObject* obj) {
	gameObjects->erase(obj->getName().c_str());
}

void Scene::removeGameObject(std::string name) {
	gameObjects->erase(name.c_str());
}

std::map<const char*, GameObject*>* Scene::getObjModels() {
	return gameObjects;
}

GameObject* Scene::getModel(std::string name) {
	if (gameObjects->find(name.c_str()) != gameObjects->end()) return gameObjects->at(name.c_str());
	else return NULL;
}