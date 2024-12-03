#include <memory>

#include "BlockyEngine.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/example/SpawnerComp.hpp"

int main() {
	std::unique_ptr<BlockyEngine> blockyEngine = std::make_unique<BlockyEngine>();

	auto cannon = std::make_unique<GameObject>("Cannon");
	cannon->transform->SetPosition(30, 300);
	cannon->transform->SetScale(50, 50);
	cannon->AddComponent<RectangleRenderable>("CannonR", glm::vec4(150, 75, 15, 155), true);
	cannon->AddComponent<SpawnerComp>("Spawner");

	SceneManager& sceneManager = blockyEngine->GetSceneManager();
	sceneManager.AddScene(std::move(cannon));
	sceneManager.SwitchScene("Cannon");

	blockyEngine->Run();
}
