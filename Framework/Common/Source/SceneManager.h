#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include <map>
#include <list>
#include <string>

class Scene;
typedef std::list<Scene*> SceneList;

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
public:
	bool quit;

	// System Interface
	void Update();
	void Render();
	void Exit();

	// User Interface
	void AddScene(const std::string& _name, Scene* _scene);
	void RemoveScene(const std::string& _name);
	void SetActiveScene(const std::string& _name, bool overlay = false);
	bool CheckSceneExist(const std::string& _name);
	void PreviousScene();

private:
	SceneManager();
	~SceneManager();

	std::map<std::string, Scene*> sceneMap;
	SceneList activeScene;
	Scene* nextScene;

	bool overlay;
	bool back;
};

#endif // SCENE_MANAGER_H