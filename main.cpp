#include <SDL_main.h>

#include <memory>
#include <components/audio/Audio.hpp>
#include <components/physics/rigidBody/BoxRigidBody.hpp>

#include "BlockyEngine.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/TextRenderable.hpp"
#include "components/example/SpawnerComp.hpp"
#include "components/example/RotationComp.hpp"
#include "components/example/MouseReparenting.hpp"
#include "components/example/MouseInputComponent.hpp"
#include "components/example/KeyboardInputComponent.hpp"
#include "components/example/SceneSwitchComp.hpp"
#include "components/example/MouseCameraController.hpp"

void buildPrefabScene(SceneManager& scenes) {
	auto root = std::make_unique<GameObject>("Prefabs");
	root->SetActive(false);

	root->AddComponent<MouseCameraController>("CameraController");

	auto& container = root->AddChild("ProjectileContainer");
	container.transform->SetPosition(400, 300);
	container.transform->SetScale(35, 35);

	auto& cannon = root->AddChild("Cannon");
	cannon.transform->SetPosition(400, 300);
	cannon.transform->SetScale(50, 50);
	cannon.AddComponent<RectangleRenderable>("CannonR", glm::vec4(150, 75, 15, 155), 0, true);
	cannon.AddComponent<SpawnerComp>("Spawner");
	cannon.AddComponent<RotationComp>("Spawner");

	auto& barrel = cannon.AddChild("Barrel");
	barrel.AddComponent<RectangleRenderable>("BarrelR", glm::vec4(125, 125, 250, 255), 3, true);
	barrel.transform->SetScale(2, 0.5f);
	barrel.transform->SetPosition(0.5f, 0);

	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", "InputReparenting");

	scenes.AddScene(std::move(root));
}

void buildInputReparentingScene(SceneManager& scenes) {
	auto root = std::make_unique<GameObject>("InputReparenting");
	root->SetActive(false);

	root->AddComponent<MouseCameraController>("CameraController");

	//Basic mouse input
	auto& mouseInputComponent = root->AddChild("MouseInput");
	mouseInputComponent.AddComponent<MouseInputComponent>("MouseInputComponent");

	//ParentA
	auto& parentA = root->AddChild("ParentA");
	parentA.AddComponent<RectangleRenderable>("ParentAR", glm::vec4{255, 0, 0, 255}, -1, true);
	parentA.transform->SetPosition(200, 300);
	parentA.transform->SetScale(150, 300);
	parentA.transform->SetRotation(20);
	TypeProperties physicsProperties(RIGIDBODY, true, {0, 0}, 0, 0, 0, false);
	parentA.AddComponent<BoxRigidBody>("ParentARB", physicsProperties);
	parentA.AddComponent<Audio>("clowns-jingle", "../assets/audioFiles/clowns-jingle.mp3", 55, true).Play();

	//ParentB
	auto& parentB = root->AddChild("ParentB");
	parentB.AddComponent<RectangleRenderable>("ParentBR", glm::vec4{0, 0, 255, 255}, -1, true);
	parentB.transform->SetPosition(525, 325);
	parentB.transform->SetScale(350, 200);
	parentB.transform->SetRotation(-125);
	parentB.AddComponent<BoxRigidBody>("ParentBRB", physicsProperties);

	//Animated Object
	auto& animatedObject = parentA.AddChild("AnimatedObject");
	animatedObject.AddComponent<AnimationRenderable>(
		"animTag", "../assets/character_spritesheet.png",
		"spriteTag", 32, 32
	);

	TTF_Font* font = TTF_OpenFont("../assets/fonts/font1.ttf", 24);
	auto& text = animatedObject.AddComponent<TextRenderable>("PlayerText", "Player", glm::vec4{255}, font, 1);
	text.componentTransform->SetPosition(0.f, -0.5f);

	//Animator
	auto& animationController = animatedObject.AddComponent<AnimationController>("animControllerTag");
	animationController.AddAnimation("idle", 0, 11, 0.15f, true);
	animationController.AddAnimation("run", 12, 19, 0.1f, true);
	animationController.AddAnimation("jump", 27, 35, 0.1f, false);
	animatedObject.GetComponent<AnimationController>()->PlayAnimation("idle");

	//Keyboard input
	animatedObject.AddComponent<KeyboardInputComponent>("keyboardInputComponent");

	//Reparenting mouse input
	root->AddComponent<MouseReparenting>("Reparenting", "AnimatedObject", "ParentA", "ParentB");

	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", "Camera");

	scenes.AddScene(std::move(root));
}

void buildCameraScene(SceneManager& scenes) {
	auto root = std::make_unique<GameObject>("Camera");
	root->SetActive(false);

	root->AddComponent<MouseCameraController>("CameraController");

	auto& box = root->AddChild("Box");

	glm::vec2 screenSize = ModuleManager::GetInstance().GetModule<WindowModule>().GetScreenSizeF();
	box.transform->SetScale(screenSize.x / 4.f,
							screenSize.y / 4.f);
	box.transform->SetPosition(screenSize.x / 2.f,
							   screenSize.y / 2.f);

	box.AddComponent<RectangleRenderable>("BoxR", glm::vec4{175, 0, 0, 255}, 0, true);
	box.AddComponent<EllipseRenderable>("BoxEl", glm::vec4{255, 0, 0, 255}, 0, true);
	box.AddComponent<SpriteRenderable>("animTag", "../assets/character_spritesheet.png", "spriteTag");

	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", "Prefabs");

	scenes.AddScene(std::move(root));
}

int main(int argc, char* argv[]) {
	BlockyEngine::BlockyConfigs configs{
			800,
			600,
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP,
			"../assets/fonts/defaultFont.ttf"
	};

	BlockyEngine blockyEngine{configs};
	SceneManager& sceneManager = blockyEngine.GetSceneManager();

	buildPrefabScene(sceneManager);
	buildInputReparentingScene(sceneManager);
	buildCameraScene(sceneManager);

	//	sceneManager.SwitchScene("Prefabs");
	sceneManager.SwitchScene("InputReparenting");
	//	sceneManager.SwitchScene("Camera");

	blockyEngine.Run();

	return 0;
}
