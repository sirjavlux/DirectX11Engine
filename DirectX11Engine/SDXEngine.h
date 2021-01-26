#pragma once

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <assert.h>
#include <sstream>
#include <cmath>

#include <windows.h>
#include <d3d11.h>       // D3D interface
#include <dxgi.h>        // DirectX driver interface
#include <dxgi1_2.h>
#include <d3dcompiler.h> // shader compiler
#include <DirectXMath.h>

#include "ObjModel.h"

#pragma comment( lib, "user32" )          // link against the win32 library
#pragma comment( lib, "d3d11.lib" )       // direct3D library
#pragma comment( lib, "dxgi.lib" )        // directx graphics interface
#pragma comment( lib, "d3dcompiler.lib" ) // shader compiler

// classes
class Engine;
class Scene;
class Camera;

// structs
struct PysicsVector3D;

/*///////////////////////
* Graphics class
*////////////////////////

class Graphics {
private:
	ID3D11Device* devicePntr;
	ID3D11DeviceContext* deviceContextPntr;
	IDXGISwapChain* swapchainPntr;
	ID3D11RenderTargetView* renderTargetViewPntr;

	ID3D11VertexShader* vertexShaderPntr;
	ID3D11PixelShader* pixelShaderPntr;
	ID3D11InputLayout* inputLayoutPntr;

	UINT vertexStride;
	UINT vertexOffset;
	UINT vertexCount;

	ID3D11Buffer* vertexBufferPntr;

	HWND* hWnd;
	WNDCLASSEX* wcex;
public:
	Graphics();
	Graphics(HWND* hWnd, WNDCLASSEX* wcex);
	IDXGISwapChain* getSwapChain();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11VertexShader* getVertexShader();
	void render();
	void update();
};

/*///////////////////////
* Engine class
*////////////////////////

class Engine {
private:
	Graphics* graphics;
	Scene* activeScene;
	std::map <const char*, Scene*>* scenes;
	Camera* activeCamera;
	std::map <const char*, Camera*>* cameras;
public:
	Engine();
	Engine(Graphics * gra);
	Scene* getActiveScene();
	Scene* getScene(std::string name);
	void setActiveScene(Scene* scene);
	void addScene(Scene* scene);
	void removeScene(Scene* scene);
	void removeScene(std::string name);
	Camera* getActiveCamera();
	Camera* getCamera(std::string name);
	void setActiveCamera(Camera* camera);
	void addCamera(Camera* camera);
	void removeCamera(Camera* camera);
	void removeCamera(std::string name);
	Graphics* getGraphics();
};

/*///////////////////////
* GameObject class
*////////////////////////

class GameObject {
private: 
	ObjModel * model;
	double * loc;
	std::string name;
	PysicsVector3D * vector;
public:
	GameObject();
	GameObject(std::string name);

	std::string getName();
	
	//model
	void setObjModel(ObjModel* model);
	ObjModel* getObjModel();

	//location and rotation
	void setLocation(double* location);

	void setLocationX(double x);
	void setLocationY(double y);
	void setLocationZ(double z);

	double getLocationX();
	double getLocationY();
	double getLocationZ();

	PysicsVector3D* getPysicsVector3D();
	void setPysicsVector3D(PysicsVector3D * vector);
};

/*///////////////////////
* Scene class
*////////////////////////

class Scene {
private:
	std::string name;
	std::map<const char*, GameObject*> * gameObjects;
public:
	Scene();
	Scene(std::string name);
	std::string getName();
	void addGameObject(GameObject* obj);
	void removeGameObject(GameObject* obj);
	void removeGameObject(std::string name);
	std::map<const char*, GameObject*>* getObjModels();
	GameObject* getModel(std::string name);
};

/*///////////////////////
* Vertex class
*////////////////////////

struct Vertex {
	Vertex();
	Vertex(float x, float y, float z, float r, float g, float b, float a);

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

/*///////////////////////
* FysicsVector3D
*////////////////////////

struct PysicsVector3D {
private:
	double x, y, z;
public:
	PysicsVector3D();
	PysicsVector3D(double x, double y, double z);
	void normalize();
	void multiply(double amount);
	PysicsVector3D getDirectionalVector();
	double lenght();
	double getX();
	double getY();
	double getZ();
};

/*///////////////////////
* Camera
*////////////////////////

class Camera {
private:
	std::string name;
	double* loc;
	PysicsVector3D * vector;
public:
	Camera();
	Camera(std::string name);

	std::string getName();

	//location and rotation
	void setLocation(double* location);

	void setLocationX(double x);
	void setLocationY(double y);
	void setLocationZ(double z);

	double getLocationX();
	double getLocationY();
	double getLocationZ();

	PysicsVector3D* getPysicsVector3D();
	void setPysicsVector3D(PysicsVector3D * vector);
};