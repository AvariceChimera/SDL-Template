#include "GameManager.h"

namespace SDLFramework {
    GameManager* GameManager::sInstance = nullptr;

    GameManager* GameManager::Instance() {
        if (sInstance == nullptr) {
            sInstance = new GameManager();
        }

        return sInstance;
    }

    void GameManager::Release() {
        delete sInstance;
        sInstance = nullptr;
    }

    void GameManager::Run() {
        //Main Game Loop
        while (!mQuit) {
            mTimer->Update();
            //Event Polling Loop
            //While there are events inside of our events varaible...
            while (SDL_PollEvent(&mEvents)) {
                //Handle each and every event we want to look for
                switch (mEvents.type) {
                case SDL_QUIT:
                    mQuit = true;
                    break;
                }
            }

            if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
                mTimer->Reset();
                Update();
                LateUpdate();
                Render();
            }
        }
    }

    void GameManager::Update() {
        mInputManager->Update();

        if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
        }
        //To prevent diagonal movement, add an else to the if statement below
        if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
        }

        //TODO:
        //Setup rotation using the Q and E keys
        //Setup scaling the texture using the Z and C keys
        //Setup a second set of movement (ie arrow keys/IJKL) for the second texture

        if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
            std::cout << "Space key pressed!" << std::endl;
            mAudioManager->PlaySFX("coin_credit.wav", 0, -1);
        }

        if (mInputManager->KeyReleased(SDL_SCANCODE_SPACE)) {
            std::cout << "Space key released!" << std::endl;
        }

        if (mInputManager->MouseButtonPressed(InputManager::Left)) {
            std::cout << "Left Mouse button pressed!" << std::endl;
        }

        if (mInputManager->MouseButtonReleased(InputManager::Left)) {
            std::cout << "Left Mouse button released!" << std::endl;
        }
    }

    void GameManager::LateUpdate() {
        mPhysicsManager->Update();
        mInputManager->UpdatePrevInput();
    }

    void GameManager::Render() {
        //This is the old frame we need to clear
        mGraphics->ClearBackBuffer();
        //Actually showing everthing that we have told to render
        mGraphics->Render();
    }

    GameManager::GameManager() : mQuit(false) {
        //calling to our Graphics Singleton
        mGraphics = Graphics::Instance();

        if (!Graphics::Initialized()) {
            mQuit = true;
        }

        //Initialize all other modules
        mTimer = Timer::Instance();
        mAssetManager = AssetManager::Instance();
        mInputManager = InputManager::Instance();
        mAudioManager = AudioManager::Instance();
        mPhysicsManager = PhysicsManager::Instance();

        //Create the Physics Layers
        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly,
            PhysicsManager::CollisionFlags::Hostile |
            PhysicsManager::CollisionFlags::HostileProjectile);

        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
            PhysicsManager::CollisionFlags::Friendly |
            PhysicsManager::CollisionFlags::FriendlyProjectile);

        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile,
            PhysicsManager::CollisionFlags::Hostile |
            PhysicsManager::CollisionFlags::HostileProjectile);

        mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile,
            PhysicsManager::CollisionFlags::Friendly |
            PhysicsManager::CollisionFlags::FriendlyProjectile);
        //game objects made below
    }

        GameManager::~GameManager() {
        //Release Variables

        //Release Modules
        Graphics::Release();
        mGraphics = nullptr;

        Timer::Release();
        mTimer = nullptr;

        AssetManager::Release();
        mAssetManager = nullptr;

        InputManager::Release();
        mInputManager = nullptr;

        AudioManager::Release();
        mAudioManager = nullptr;

        PhysicsManager::Realease();
        mPhysicsManager = nullptr;

        //Quit SDl Subsystems
        SDL_Quit();
    }
    //Namespace bracket is below
}