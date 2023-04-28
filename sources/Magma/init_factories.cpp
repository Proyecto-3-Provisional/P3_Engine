#include <Magma/init_factories.h>
#include <Magma/factory_manager.h>

#include <EC/entity.h>
#include <EC/player_controller.h>
#include <EC/transform.h>
#include <EC/progress_bar.h>
#include <EC/timer.h>

#include <Physics/rigidbody.h>

#include <Render/mesh.h>
#include <Render/button.h>
#include <Render/image.h>
#include <Render/text.h>


#include <Sounds/audio_source.h>

namespace magma_engine
{
	ec::Component* TransformFactory::createComponent(ec::Entity* e)
	{
		//return e->addComponent<Transform>()->initComponent({ 0, 0, 0 }, { 40,40,40 });
		return e->addComponent<Transform>();
	}

	ec::Component* RigidbodyFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<Rigidbody>();
	}

	ec::Component* MeshFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<Mesh>();
	}

	ec::Component* AudioSourceFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<AudioSource>();
	}

	ec::Component* ButtonFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<Button>();
	}

	ec::Component* ImageFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<Image>();
	}

	ec::Component* TextFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<Text>();
	}

	ec::Component* ProgressBarFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<Progress_Bar>();
	}

	ec::Component* TimerFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<Timer>();
	}

	ec::Component* PlayerControllerFactory::createComponent(ec::Entity* e)
	{
		return e->addComponent<PlayerController>();
	}

	void setUpFactories()
	{
		FactoryManager::instance()->addFactory("Transform", new TransformFactory());
		FactoryManager::instance()->addFactory("Rigidbody", new RigidbodyFactory());
		FactoryManager::instance()->addFactory("Mesh", new MeshFactory());
		FactoryManager::instance()->addFactory("AudioSource", new AudioSourceFactory());
		FactoryManager::instance()->addFactory("Button", new ButtonFactory());
		FactoryManager::instance()->addFactory("Image", new ImageFactory());
		FactoryManager::instance()->addFactory("Text", new TextFactory());
		FactoryManager::instance()->addFactory("PlayerController", new PlayerControllerFactory());
		FactoryManager::instance()->addFactory("ProgressBar", new ProgressBarFactory());
		FactoryManager::instance()->addFactory("Timer", new TimerFactory());
	}


}

