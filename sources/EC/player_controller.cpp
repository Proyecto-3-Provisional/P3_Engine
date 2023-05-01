#include "player_controller.h"

#include <Physics/rigidbody.h>
#include <Input/input_manager.h>
#include <EC/entity.h>
#include <EC/transform.h>


namespace magma_engine
{
	PlayerController::PlayerController() : enemySpeed(0.0f), timeBetweenMovements(0.0f), currTimeBetweenMovements(0.0f)
	{
	}

	PlayerController::~PlayerController()
	{

	}

	bool PlayerController::initComponent(float playerSpeed_, float timeBetweenMovements_)
	{
		try {
			rb = ent->getComponent<Rigidbody>();
			tr = ent->getComponent<Transform>();

			enemySpeed = playerSpeed_;
			timeBetweenMovements = timeBetweenMovements_;
			currTimeBetweenMovements = timeBetweenMovements;

			Vector3D movementDirection(0, 0, 0);
		}
		catch (...) {
			return false;
		}
		return false;
	}

	bool PlayerController::initComponent(std::map<std::string, std::string> args)
	{
		try {
			enemySpeed = stof(args["playerSpeed"]);
			timeBetweenMovements = stof(args["timeBetweenMovements"]);
			currTimeBetweenMovements = stof(args["timeBetweenMovements"]); ;

			Vector3D movementDirection(0, 0, 0);
		}
		catch (...) {
			return false;
		}
		return true;
	}

	bool PlayerController::start()
	{
		tr = ent->getComponent<Transform>();
		rb = ent->getComponent<Rigidbody>();
		return (tr != nullptr && rb != nullptr);
	}

	void PlayerController::update(float deltaTime)
	{
		bool move = false;

		if (currTimeBetweenMovements < 0.0f) {
			movementDirection = { 0,0,0 };

			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_A)) {

				rb->addForce(Vector3D(-1, 0, 0) * enemySpeed);
				movementDirection += Vector3D(-1, 0, 0);
				move = true;
			}
		
			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_D)) {

				rb->addForce(Vector3D(1, 0, 0) * enemySpeed);
				movementDirection += Vector3D(1, 0, 0);

				move = true;

			}

			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_W)) {

				rb->addForce(Vector3D(0, 0, -1) * enemySpeed);
				movementDirection += Vector3D(0, 0, -1);

				move = true;

			}

			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_S)) {

				rb->addForce(Vector3D(0, 0, 1) * enemySpeed);
				movementDirection += Vector3D(0, 0, 1);

				move = true;

			}

			if (move) {
				tr->setDirection(movementDirection);
				currTimeBetweenMovements = timeBetweenMovements;
			}

		}

		currTimeBetweenMovements -= deltaTime;

	}
}