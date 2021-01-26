#include "SDXEngine.h"

/*////////////////////////////////
* Engine class functions
*/////////////////////////////////

// consrtuctor
Engine::Engine() { 
	graphics = nullptr;
	activeScene = NULL;
	scenes = new std::map<const char*, Scene*>();
	activeCamera = NULL;
	cameras = new std::map<const char*, Camera*>();
}

Engine::Engine(Graphics * gra) {
	//set variables
	graphics = gra;
	activeScene = NULL;
	scenes = new std::map<const char*, Scene*>();
	activeCamera = NULL;
	cameras = new std::map<const char*, Camera*>();
}

// get graphics component
Graphics * Engine::getGraphics() {
	return graphics;
}

// modify scenes
Scene* Engine::getActiveScene() {
	return activeScene;
}

Scene* Engine::getScene(std::string name) {
	if (scenes->find(name.c_str()) != scenes->end()) return scenes->at(name.c_str());
	else return NULL;
}

void Engine::setActiveScene(Scene* scene) {
	activeScene = scene;
}

void Engine::addScene(Scene* scene) {
	if (scenes->find(scene->getName().c_str()) == scenes->end()) scenes->insert({ scene->getName().c_str(), scene });
}

void Engine::removeScene(Scene* scene) {
	scenes->erase(scene->getName().c_str());
}

void Engine::removeScene(std::string name) {
	scenes->erase(name.c_str());
}

// modify cameras
Camera* Engine::getActiveCamera() {
	return activeCamera;
}

Camera* Engine::getCamera(std::string name) {
	if (cameras->find(name.c_str()) != cameras->end()) return cameras->at(name.c_str());
	else return NULL;
}

void Engine::setActiveCamera(Camera* camera) {
	activeCamera = camera;
}

void Engine::addCamera(Camera* camera) {
	if (cameras->find(camera->getName().c_str()) == cameras->end()) cameras->insert({ camera->getName().c_str(), camera });
}

void Engine::removeCamera(Camera* camera) {
	cameras->erase(camera->getName().c_str());
}

void Engine::removeCamera(std::string name) {
	cameras->erase(name.c_str());
}

/*///////////////////////////////
* Window handling
*////////////////////////////////

//windproc function, handles window events
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch(message) {
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// run on startup
static const wchar_t* windName = L"SDXEngine";
static const wchar_t* windTitle = L"SDXEngine Window";
void onEnable(Engine* engine);
int WINAPI wWinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, 
	int nCmdShow) 
{
	// register window class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = windName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	if (!RegisterClassEx(&wcex)) return 0; // if didn't work

	// create window
	RECT rc = { 0, 0, 800, 600 }; 
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindow(
		windName, // class name
		windTitle, // title name
		WS_OVERLAPPEDWINDOW, // style
		CW_USEDEFAULT, // window x pos
		CW_USEDEFAULT, // window y pos
		rc.right - rc.left, // width
		rc.bottom - rc.top, // height
		NULL, // no parent window
		NULL, // no menu
		hInstance, // handle to the instance
		NULL // no params passed
	);
	if (!hWnd) return 0; // if didn't work

	// display window
	ShowWindow(hWnd, nCmdShow);

	// create engine
	Graphics graphics(&hWnd, &wcex);
	Engine engine(&graphics);

	// run on enable method
	onEnable(&engine);
	
	// main window message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//render frame
		graphics.update();
		graphics.render();
	}

	return (int)msg.wParam;
}