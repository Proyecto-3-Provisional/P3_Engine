#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <singleton.h>

#include <stack>

namespace magma_engine
{
	class Scene;

	class MAGMAENGINE_API SceneManager : public Singleton<SceneManager> {

	public:
		SceneManager();
		~SceneManager();

		void popScene();

		void pushScene(Scene* newScene);

		void changeScene(Scene* newScene);

		Scene* currentScene();

		void update(float deltaTime);
	private:

		void deleteScenes();

		std::stack<Scene*> scenes;
		std::stack<Scene*> scenesToDelete;
	};
}

