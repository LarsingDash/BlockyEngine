target_sources(${ENGINE_TARGET} PRIVATE
        MovementComp.cpp
        RotationComp.cpp
        SpawnerComp.cpp
        InstantiatePhysicsObject.cpp
        SceneSwitchComp.cpp
        inputScripts/MouseCameraController.cpp
        inputScripts/MouseInputComponent.cpp
        inputScripts/MouseReparenting.cpp
        inputScripts/KeyboardInputComponent.cpp
)