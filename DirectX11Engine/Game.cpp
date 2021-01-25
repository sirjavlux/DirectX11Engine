#include "SDXEngine.h"

/*//////////////////////
* Called on startup
*///////////////////////

void onEnable(Engine * engine) {

	//test scene
	Scene * scene = new Scene("test_scene");
	engine->addScene(scene);
	engine->setActiveScene(scene);

	//test object
	ObjModel testModel("Resources/test.obj");
	GameObject testObject("test_obj");
	testObject.setObjModel(&testModel);
	scene->addGameObject(&testObject);
}