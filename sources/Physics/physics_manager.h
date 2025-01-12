#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <singleton.h>
#include <vector>
#include <EC/entity.h>

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btCollisionShape;
class btRigidBody;
template <typename T> class btAlignedObjectArray;

namespace magma_engine
{
	class Vector3D;

	class MAGMAENGINE_API PhysicsManager : public Singleton<PhysicsManager>
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		//Metodo para a�adir un elemento rigidbody 
		int addRigidBody(Entity* e, const double& xShape, const double& yShape, const double& zShape, 
			const double& xTransform, const double& yTransform, const double& zTransform, const float& mass = 1.0f);

		//Metodos para eliminar rigidbodys almacenados 
		void deleteRigidBody(const int& userIndex);
		void deleteRigidBodies(std::vector<int>& vIndex);

		//Metodo que actualiza las fisicas
		void update(float deltaTime);

		//Metodo que muestra los pares que colisionan
		void updateCollisions();

		//Metodo para comprobar si ha habido colision entre rigidbodys
		bool isCollide(const int& index1, const int& index2);

		//Metodo para obtener un vector con 
		std::vector<Entity*> getArrayOfColliders(int index);

		Vector3D getPos(int index);

		btRigidBody* getRigidBody(int index);

		//Metodo para a�adir un vector de fuerzas
		void addForceTo(int index, const Vector3D& force);

		int initPhysics();
		void detachPhysics();

	private:

		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		btAlignedObjectArray<btCollisionShape*>* collisionShapes;
		
		std::vector<Entity *> entities;
	};
}

