
#include <singleton.h>
#include <iostream>
#include <Render/graphical_object.h>
#include <Render/render_manager.h>
#include <Render/mesh.h>

#include <EC/vector3D.h>
#include <EC/transform.h>
#include <EC/entity.h>

namespace magma_engine
{
	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
		if(gObjPtr != nullptr) RenderManager::instance()->removeObject(gObjPtr);
	}

	GraphicalObject* Mesh::getObj()
	{
		return gObjPtr;
	}

	bool Mesh::initComponent(std::map<std::string, std::string> args)
	{
		try
		{
			gObjPtr = RenderManager::instance()->addObject(args["entityName"], nullptr, args["mesh"], args["material"]);
			if (gObjPtr == nullptr)
			{
				std::cout << "WARNING! - error al asignar modelo en Mesh \n" ;
				return false;
			}
		}
		catch (std::exception& e)
		{
			std::cout << "WARNING! - error en un componente Mesh \n \n      " << e.what();
			return false;
		}

		return true;
	}

	bool Mesh::start()
	{
		trPtr = ent->getComponent<Transform>();
		if (trPtr == nullptr)
		{
			std::cout << "Mesh is missing Transform";
			return false;
		}
		return true;
	}

	void Mesh::update(float deltaTime)
	{
		if (trPtr != nullptr)
		{
			Vector3D v = trPtr->getPos();
			gObjPtr->setPosition({ v.getX(), v.getY(), v.getZ() });
			Vector3D s = trPtr->getScale();
			gObjPtr->setScale({ s.getX(), s.getY(), s.getZ() });
			Vector3D d = trPtr->getForward();
			gObjPtr->setDirection({ d.getX(), d.getY(), d.getZ() });
		}
	}

	void Mesh::render()
	{
	}

	void Mesh::recieve(const Message& m)
	{
		switch (m.id)
		{
		case _m_OBJECT_ROTATED:
			rotate(m.object_rotated_data.deg, m.object_rotated_data.axis);
			break;
		case _m_OBJECT_LOOKAT:
			setDirection(m.object_lookedat_data.x, m.object_lookedat_data.y, m.object_lookedat_data.z);
			break;
		default:
			break;
		}
	}

	void Mesh::rotate(float deg, char axis)
	{
		switch (axis)
		{
		case 'x':
			getObj()->pitch(deg);
			break;
		case 'y':
			getObj()->yaw(deg);
			break;
		case 'z':
			getObj()->roll(deg);
			break;
		default:
			break;
		}
	}

	void Mesh::setDirection(float x, float y, float z)
	{
	}

	Vector3D Mesh::getProportions()
	{
		return gObjPtr->getMeshProportions();
	}

	Quaternion Mesh::getOrientation()
	{
		Ogre::Quaternion q = gObjPtr->getOrientation();
		return Quaternion(q.w, q.x, q.y, q.z);
	}

	void Mesh::setVisible(bool visible)
	{
		gObjPtr->makeVisible(visible);
	}
}

