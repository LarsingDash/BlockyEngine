target_sources(${ENGINE_TARGET} PRIVATE
        NetworkingComponent.cpp
        MovementComp.cpp
        RotationComp.cpp
        SpawnerComp.cpp
        InstantiatePhysicsObject.cpp
        SceneSwitchComp.cpp
        MoveWithPhysics.cpp
        inputScripts/MouseCameraController.cpp
        inputScripts/MouseInputComponent.cpp
        inputScripts/MouseReparenting.cpp
        inputScripts/KeyboardInputComponent.cpp
)
