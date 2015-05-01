/**
AGP Assignment
LightManager.cpp
Purpose: Global class to manage the lighting.
		Set the light data in the manager for
		the models to access the data automatically.

@author Sarah Bulk
*/

#include "LightManager.h"


static LightManager* _instance = NULL;

//////////////////////////////////////////////////////////////////////////////////////
// Return the instance
//////////////////////////////////////////////////////////////////////////////////////
LightManager * LightManager::GetInstance() {
	if (!_instance) {
		_instance = new LightManager();
	}
	return _instance;
}

//////////////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////////////
LightManager::~LightManager()
{
};

//////////////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////////////
LightManager::LightManager()
{
};

//std::string LightManager::GetName()
//{
//	return "LightManager";
//}

//////////////////////////////////////////////////////////////////////////////////////
// Setters
//////////////////////////////////////////////////////////////////////////////////////
void LightManager::AddPointLight(PointLight* p)
{
	pointLights.push_back(p);
};

void LightManager::RemovePointLight(PointLight* p)
{
	for (int i = 0; i < pointLights.size(); i++)
	{
		if (pointLights[i] == p)
			pointLights.erase(pointLights.begin() + i);
	}
};

void LightManager::SetDirectionalLight(DirectionalLight* d)
{
	directionalLight = d;
};

void LightManager::SetAmbientLight(Light* l)
{
	ambientLight = l;
};

//////////////////////////////////////////////////////////////////////////////////////
// Getters
//////////////////////////////////////////////////////////////////////////////////////
std::vector<PointLight*> LightManager::GetPointLights()
{
	return pointLights;
};
DirectionalLight* LightManager::GetDirectionalLight()
{
	return directionalLight;
};
Light* LightManager::GetAmbientLight()
{
	return ambientLight;
};