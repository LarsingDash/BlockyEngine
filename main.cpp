#include <SDL_main.h>

#include <memory>

#include <logging/BLogger.hpp>

#include "BlockyEngine.hpp"
#include "utilities/JsonUtil.hpp"
#include "logging/BLogger.hpp"

#include "components/example/SceneSwitchComp.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/TextRenderable.hpp"

#include "components/example/SpawnerComp.hpp"
#include "components/example/RotationComp.hpp"
#include "components/json/JsonLoader.hpp"
#include "components/json/JsonSaveAndLoader.hpp"

#include "components/example/inputScripts/MouseReparenting.hpp"
#include "components/example/inputScripts/MouseInputComponent.hpp"
#include "components/example/inputScripts/KeyboardInputComponent.hpp"
#include "components/example/inputScripts/MouseCameraController.hpp"
#include "components/example/NetworkingComponent.hpp"

#include <components/physics/collider/BoxCollider.hpp>
#include <components/physics/collision/CollisionHandler.hpp>
#include <components/physics/rigidBody/BoxRigidBody.hpp>
#include <components/physics/collider/CircleCollider.hpp>
#include <components/example/MoveWithPhysics.hpp>

#include "components/pathfinding/PathfindingGrid.hpp"
#include "components/pathfinding/MouseTargetedNavigation.hpp"
#include "components/pathfinding/GridNavigator.hpp"

void buildJsonPrefabScene(SceneManager& scenes, const char* next) {
	auto root = std::make_unique<GameObject>("JsonPrefab");
	root->SetActive(false);

	//JsonLoader
	root->AddComponent<JsonSaveAndLoader>("JsonLoader", "../assets/PrefabScene.json", "Instances");

	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", next);

	scenes.AddScene(std::move(root));
}

void buildInputReparentingScene(SceneManager& scenes, const char* next) {
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
			"spriteTag", 32, 32, 0, SpriteFlip::FlipHorizontal
	);

	auto& text = animatedObject.AddComponent<TextRenderable>(
			"PlayerText", "Player",
			glm::vec4{255},
			"../assets/fonts/font1.ttf", 24, 1);
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
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", next);

	scenes.AddScene(std::move(root));
}

void buildCameraScene(SceneManager& scenes, const char* next) {
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
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", next);

	scenes.AddScene(std::move(root));
}

void buildNetworkingScene(SceneManager& scenes, const char* next) {
	auto root = std::make_unique<GameObject>("Networking");
	root->SetActive(false);

	root->AddComponent<MouseCameraController>("CameraController");

	auto& box = root->AddChild("Box");
	box.transform->SetScale(200, 150);
	box.transform->SetPosition(400, 300);
	box.AddComponent<RectangleRenderable>("BoxR", glm::vec4{175, 0, 0, 255}, 0, true);

	root->AddComponent<NetworkingComponent>("NetworkingComponent");
	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", next);

	scenes.AddScene(std::move(root));
}

void buildCollisionScene(SceneManager& scenes, const char* next) {
	auto root = std::make_unique<GameObject>("Collision");
	root->SetActive(false);

	auto& sceneBase = root->AddChild("BaseOfScene");
	sceneBase.transform->SetPosition(500, 500);
	sceneBase.transform->SetScale(200, 200);

	// baseRectangle.AddComponent<RectangleRenderable>("RectangleBase", glm::vec4{93, 93, 93, 255}, 0, true);
	sceneBase.AddComponent<EllipseRenderable>("EllipseBase", glm::vec4{93, 93, 93, 255}, 0, true);

	// auto& collider = baseRectangle.AddComponent<BoxCollider>("SceneRectangle");
	auto& collider = sceneBase.AddComponent<CircleCollider>("SceneEllipse");
	// collider.componentTransform->SetScale(2,2);
	sceneBase.AddComponent<CollisionHandler>("Trigger handler", collider,
											 [](GameObject& other) {
												 BLOCKY_ENGINE_DEBUG_STREAM("ENTERING: " << other.tag);
											 },
											 [](GameObject& other) {
												 BLOCKY_ENGINE_DEBUG_STREAM("EXITING: " << other.tag);
											 });

	TypeProperties properties(
			RIGIDBODY,
			false,
			glm::vec2{0, 0},
			0,
			0,
			0,
			false
	);

	auto& rigidBox = root->AddChild("rigidBox");
	glm::vec2 pos = sceneBase.transform->GetLocalPosition();
	rigidBox.transform->SetPosition(pos.x - 200, pos.y);
	rigidBox.transform->SetScale(50, 50);
	rigidBox.AddComponent<RectangleRenderable>("PhysicsObjMesh", glm::vec4{255, 255, 0, 255}, 1, true);
	auto& boxRigidBody = rigidBox.AddComponent<BoxRigidBody>("BoxColl", properties);
	rigidBox.AddComponent<MoveWithPhysics>("TestMover", boxRigidBody);

	properties.isStatic = true;

	auto& staticRigidBox = root->AddChild("rigidBox");
	staticRigidBox.transform->SetPosition(pos.x - 300, pos.y);
	staticRigidBox.transform->SetScale(50, 50);
	staticRigidBox.AddComponent<RectangleRenderable>("PhysicsObjMesh", glm::vec4{255, 255, 0, 255}, 1, false);
	staticRigidBox.AddComponent<MoveWithPhysics>("TestMover",
												 staticRigidBox.AddComponent<BoxRigidBody>("BoxColl", properties));

	properties = TypeProperties(
			RIGIDBODY,
			false,
			glm::vec2{0, 0},
			0,
			0,
			0,
			true
	);

	auto& sceneBase2 = root->AddChild("BaseOfScene");
	sceneBase2.transform->SetPosition(pos.x - 210, pos.y - 400);
	sceneBase2.transform->SetScale(10, 10);
	sceneBase2.AddComponent<RectangleRenderable>("RectangleRenderable", glm::vec4{0, 0, 255, 255}, 0, true);
	sceneBase2.AddComponent<BoxRigidBody>("BoxRigidBody", properties);

	for (int i = 0; i < 20; ++i) {
		auto& obj = root->AddChild("ParentA");
		obj.AddComponent<RectangleRenderable>("ParentAR", glm::vec4{255, 0, 0, 255}, -1, true);
		obj.transform->SetPosition(800, 250);
		obj.transform->SetScale(100, 100);
		obj.AddComponent<BoxRigidBody>("ParentARB", TypeProperties(RIGIDBODY, false, {0, 0}, 0, 0, 0, true));
	}
	for (int i = 0; i < 20; ++i) {
		auto& obj = root->AddChild("ParentA");
		obj.AddComponent<RectangleRenderable>("ParentAR", glm::vec4{0, 255, 0, 255}, -1, true);
		obj.transform->SetPosition(400, 250);
		obj.transform->SetScale(100, 100);
		obj.AddComponent<BoxRigidBody>("ParentARB", TypeProperties(RIGIDBODY, false, {0, 0}, 0, 0, 0, false));
	}

	//Basic mouse input
	auto& mouseInputComponent = root->AddChild("MouseInput");
	mouseInputComponent.AddComponent<MouseInputComponent>("MouseInputComponent");

	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", next);
	scenes.AddScene(std::move(root));
}

void buildPathfindingScene(SceneManager& scenes, const char* next) {
	auto root = std::make_unique<GameObject>("Pathfinding");
	root->SetActive(false);

	root->AddComponent<MouseCameraController>("CameraController");

	//GridObject
	auto& gridObject = root->AddChild("Grid");
	auto screen = ModuleManager::GetInstance().GetModule<WindowModule>().GetScreenSizeF();
	gridObject.transform->SetPosition(screen.x / 2.f, screen.y / 2.f);
	gridObject.transform->SetScale(screen.x, screen.y);

	//Background
	gridObject.AddComponent<RectangleRenderable>(
			"Background",
			glm::ivec4{25, 15, 15, 255},
			-10, true
	);

	//Grid
	const int width = 40;
	const int height = 22;

	auto& grid = gridObject.AddComponent<PathfindingGrid>(
			"Grid",
			1,
			glm::ivec2{width, height}
	);
	auto& worldScale = grid.componentTransform->GetWorldScale();
	float gridFactor = 0.75f;
	grid.componentTransform->SetScale(worldScale.x * gridFactor, worldScale.y * gridFactor);

	//Grid settings
	grid.SetVisualization(true);
	grid.SetVisualizationOpacity(150);
	grid.SetNodeSize(25.f);

	//Weight settings
	grid.SetNonWalkableColor({0, 0, 200});
	grid.SetWeightColor(2, glm::ivec3{100});
	grid.SetWeightColor(4, glm::ivec3{50});
	grid.SetWeightColor(8, glm::ivec3{25});

	//Assign weights
	grid.SetWeightsFromText(R"(1111111111111111111111111111111111111111
111111111111111111NNNN111111111111111111
1111111111111111122222111111111111111111
1111111111111111224422111111111111111111
1111111111111111122222111111111111111111
111111111111111111NNNN111111111111111111
1111111111111144444111111111111111111111
1111111111111448884411111111111111111111
1111111111111144444111111111111111111111
1111111111111111111111111111111111111111
1111111111111111111111111111111111111111
1111111111111111112221111111111111111111
1111111111111111128422111111111111111111
1111111111111111248822111111111111111111
1111111111111111128422111111111111111111
1111111111111111112221111111111111111111
111111NNNN111111111111111111111111111111
111111NNNN111111111111111111111111111111
1111111111111111111111111111111111111111
1111111111111111111111111111111111111111
1111111111111111112444111111111111111111
1111111111111111111111111111111111111111
)");

	//Manually tweak by adding some lines
	for (int i = 0; i < 10; ++i) {
		grid.GetNode(4, i + 3).Weight = 8;
		grid.GetNode(30, i + 6).IsWalkable = false;
	}

	//Grid Navigator
	auto& navigatorObject = root->AddChild("GridNavigatorObject");
	navigatorObject.transform->SetScale(50, 50);

	navigatorObject.AddComponent<SpriteRenderable>(
			"NavigatorSprite",
			"../assets/kaboom.png",
			"NavSprite"
	);
	navigatorObject.AddComponent<GridNavigator>(
			"GridNavigator",
			"Grid",
			glm::ivec2{20, 10},
			2.f
	);
	navigatorObject.AddComponent<MouseTargetedNavigation>("MouseTargetedNavigation");

	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", next);

	scenes.AddScene(std::move(root));
}

void buildJsonSandboxScene(SceneManager& scenes, const char* next) {
	auto root = std::make_unique<GameObject>("JsonSandbox");
	root->SetActive(false);

	//Camera
	root->AddComponent<MouseCameraController>("MouseCameraController");

	//Sandbox
	std::string fileDir = "Instances";
	std::string filePath = fileDir + "/Sandbox.json";
	if (!std::filesystem::exists(fileDir)) {
		std::filesystem::create_directories(fileDir);
	}

	auto sandbox = std::make_unique<GameObject>("Sandbox");
	auto screen = ModuleManager::GetInstance().GetModule<WindowModule>().GetScreenSizeF();
	sandbox->transform->SetPosition(screen.x / 2.f, screen.y / 2.f);

	//Renderables
	auto& renderables = sandbox->AddChild("Renderables");
	renderables.transform->SetScale(100, 100);

	renderables.AddComponent<RectangleRenderable>(
			"RectRender", glm::vec4{225, 0, 0, 255}, 0, true
	).componentTransform->SetPosition(-0.5f, 0.f);
	renderables.AddComponent<EllipseRenderable>(
			"EllipseRender", glm::vec4{0, 0, 225, 255}, 0, true
	).componentTransform->SetPosition(0.5f, 0.f);
	renderables.AddComponent<SpriteRenderable>(
			"SpriteRender",
			"../assets/kaboom.png",
			"SpriteRender",
			RenderableType::SPRITE,
			1, SpriteFlip::FlipVertical
	).componentTransform->SetPosition(-0.5f, 0.f);
	auto& animated = renderables.AddComponent<AnimationRenderable>(
			"animTag",
			"../assets/character_spritesheet.png",
			"spriteTag",
			32, 32,
			1, SpriteFlip::FlipHorizontal
	);
	animated.componentTransform->SetPosition(0.5f, 0.f);

	auto& animationController = renderables.AddComponent<AnimationController>("animControllerTag");
	animationController.AddAnimation("idle", 0, 11, 0.15f, true);
	animationController.PlayAnimation("idle");

	animated.SetCurrentFrame(5);

	auto& text = sandbox->AddComponent<TextRenderable>(
			"RenderablesText", "Renderables",
			glm::ivec4{0, 225, 0, 255},
			"../assets/fonts/font1.ttf", 24
	);
	text.componentTransform->SetPosition(-50, -100);
	text.componentTransform->SetScale(100, 24);

	//Save and Load
	JsonUtil::SaveToFile(*sandbox, filePath);
	JsonUtil::LoadFromFile(*root, filePath);

	//Scene switching
	root->AddComponent<SceneSwitchComp>("SceneSwitcher", next);

	scenes.AddScene(std::move(root));
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	BlockyEngine::BlockyConfigs configs{
			800,
			600,
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP,
			"../assets/fonts/defaultFont.ttf"
	};

	BlockyEngine blockyEngine{configs};
	SceneManager& sceneManager = blockyEngine.GetSceneManager();

	buildJsonPrefabScene(sceneManager, "InputReparenting");
	buildInputReparentingScene(sceneManager, "Camera");
	buildCameraScene(sceneManager, "Collision");
	buildCollisionScene(sceneManager, "Pathfinding");
	buildPathfindingScene(sceneManager, "JsonSandbox");
	buildJsonSandboxScene(sceneManager, "Networking");
	buildNetworkingScene(sceneManager, "JsonPrefab");

	sceneManager.SwitchScene("InputReparenting");

	blockyEngine.Run();

	return 0;
}
