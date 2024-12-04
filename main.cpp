#include <memory>

#include "BlockyEngine.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/example/SpawnerComp.hpp"
#include "components/example/RotationComp.hpp"

int main() {
	BlockyEngine blockyEngine;
	
	auto root = std::make_unique<GameObject>("root");
	auto& container = root->AddChild("ProjectileContainer");
	container.transform->SetPosition(400, 300);
	container.transform->SetScale(35, 35);
	
	auto& cannon = root->AddChild("Cannon");
	cannon.transform->SetPosition(400, 300);
	cannon.transform->SetScale(50, 50);
	cannon.AddComponent<RectangleRenderable>("CannonR", glm::vec4(150, 75, 15, 155), true);
	cannon.AddComponent<SpawnerComp>("Spawner");
	cannon.AddComponent<RotationComp>("Spawner");

	auto& barrel = cannon.AddChild("Barrel");
	barrel.AddComponent<RectangleRenderable>("BarrelR", glm::vec4(125, 125, 250, 255), true);
	barrel.transform->SetScale(2, 0.5f);
	barrel.transform->SetPosition(0.5f, 0);

	SceneManager& sceneManager = blockyEngine.GetSceneManager();
	sceneManager.AddScene(std::move(root));
	sceneManager.SwitchScene("root");

	blockyEngine.Run();
}
