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
	Scene* SetActiveScene(const std::string& _name, bool overlay = false);
	
	bool CheckSceneExist(const std::string& _name);
	void PreviousScene();


	inline Scene* GetActiveScene() { return activeScene.front(); }
	inline std::string GetActiveSceneName() { return name; }
	inline Scene* GetScene(std::string scene_name){ return sceneMap.find(scene_name)->second; };

private:
	SceneManager();
	~SceneManager();

	std::map<std::string, Scene*> sceneMap;
	SceneList activeScene;
	Scene* nextScene;
	std::string name;

	bool overlay;
	bool back;
};

#endif // SCENE_MANAGER_H