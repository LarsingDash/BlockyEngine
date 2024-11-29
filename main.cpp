#include <memory>

#include "BlockyEngine.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"

int main() {
	std::unique_ptr<BlockyEngine> blockyEngine = std::make_unique<BlockyEngine>();

	auto projectile = std::make_unique<GameObject>("ProjectilePrefab");
	projectile->transform->SetScale(50,50);
	projectile->transform->SetPosition(3,3);
	projectile->AddComponent<EllipseRenderable>("ProjSprite", glm::vec4{255, 255, 0, 255}, true);
	
	SceneManager& sceneManager = blockyEngine->GetSceneManager();
	sceneManager.AddScene(std::move(projectile));
	sceneManager.SwitchScene("ProjectilePrefab");
	
	blockyEngine->Run();
}
