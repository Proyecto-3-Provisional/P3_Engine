// Fugas Memoria
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <iostream>

// para calcular el tiempo transcurrido entre fotogramas
#include <SDL_timer.h>

// GUILLERMO: "...proyectos como espacios de nombres"
#include <Render/render_manager.h>
#include <Render/ui_manager.h>
#include <Render/ui_button.h>
#include <Render/mesh.h>	
#include <Input/input_manager.h>
#include <Physics/physics_manager.h>
#include <Physics/rigidbody.h>
#include <Sounds/sound_manager.h>
#include <EC/entity_manager.h>
#include <EC/entity.h>
#include <EC/vector3D.h>
#include <EC/fps_counter.h>
#include <EC/transform.h>
#include <EC/progress_bar.h>
#include <EC/timer.h>
#include <EC/player_controller.h>
#include <EC/enemy_controller.h>
#include <Render/image.h>
#include <Render/text.h>
#include <Render/button.h>
#include <Sounds/audio_source.h>
#include <EC/factory_manager.h>
#include <EC/init_factories.h>
#include <Lua/scene_loader.h>
#include <EC/scene.h>
#include <EC/scene_manager.h>

// DECLARACIÓN DE FUNCIONES
void initManagers();
void releaseManagers();

int mainCode() {
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//
#ifdef _DEBUG

#if 1 // por comodidad (0 -> false; No 0 -> true)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else	
	_CrtSetBreakAlloc(12944); // id del new que queremos borrar
#endif
#endif
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//

	// Temporizador debug (también para físicas)
	const int miliecsToReport = 5000;
	int miliecsSinceLastReport = 0;
	int miliecsSinceLastReport2 = 0;
	//=====================

	std::cout << "======== MAGMA iniciado ========\n";

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	int lastFrameTime = (int)SDL_GetTicks(); // uint32 a int
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	int timeSinceLastFrame = 0;


	// ---------- Inicialización MANAGERS ----------
	initManagers();
	std::cout << "Managers inicializados\n";


	// ---------- Inicialización RENDER ----------
	// Cámara
	Singleton<magma_engine::RenderManager>::instance()->createCam(nullptr, { 0, 1000, 0 });
	Singleton<magma_engine::RenderManager>::instance()->setCamLookAt({ 0, -1000, 0 });
	Singleton<magma_engine::RenderManager>::instance()->setBgColor(0.8f, 0.8f, 0.7f);
	Singleton<magma_engine::RenderManager>::instance()->objectShowMode(0);
	// Sol
	magma_engine::GraphicalObject* sol = Singleton<magma_engine::RenderManager>::instance()->
		addObject("sol", nullptr, "SUN");
	sol->setLightColor(0.8f, 0.8f, 0.8f);
	sol->setDirection({ 0.0f, -1.0f, 0.0f }, true);
	
	// Fondo
	magma_engine::GraphicalObject* lavaBg = Singleton<magma_engine::RenderManager>::instance()->
		addObject("background", nullptr, "mPlane1080x800", "magma_background");
	lavaBg->setScale(1.67);	// Adaptar segun viewport camara
	lavaBg->setPosition({ 0, -225, 0 });
	lavaBg->yaw(90);

	// ---------- Inicialización EC ----------

	//magma_engine::ec::Entity* physicsEntity = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();
	//Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("Transform", physicsEntity);
	////physicsEntity->addC<Transform>(Singleton<FactoryManager>::instance()->findAndCreate("Transform"));
	////physicsEntity->getComponent<magma_engine::Transform>()->initComponent({ 0, 0, 0 }, { 40,40,40 });

	//Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("Mesh", physicsEntity);
	//bool meshInit2 = physicsEntity->getComponent<magma_engine::Mesh>()->initComponent("ejemploPhysics", "axolotl.mesh", "axolotl");

	//magma_engine::Rigidbody* physicsEntityRigidbodyCmp = physicsEntity->addComponent<magma_engine::Rigidbody>();
	//bool eliminar = physicsEntity->getComponent<magma_engine::Rigidbody>()->initComponent();

	
	/*ec::Entity* physicsEntity = Singleton<ec::EntityManager>::instance()->addEntity();
	Transform* physicsEntityTransformCmp = physicsEntity->addComponent<Transform>();
	physicsEntityTransformCmp->setPosition({ 0, 0, 0 });
	physicsEntityTransformCmp->setScale({ 40,40,40 });
	Mesh* physicsEntityMeshCmp = physicsEntity->addComponent<Mesh>();
	bool meshInit2 = physicsEntityMeshCmp->initComponent("ejemploPhysics", "axolotl.mesh", "axolotl");*/
	// hacer cosas con el cmp solo si se inicializó correctamente
	//if (meshInit2)
	//{
	//	//sampleEntityMeshCmp->getObj()->showDebugBox(true);
	//	//sampleEntityMeshCmp->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	//}
	//Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("Mesh", physicsEntity);
	//bool meshInit2 = physicsEntity->getComponent<magma_engine::Mesh>()->initComponent("ejemploPhysics", "axolotl.mesh", "axolotl");
	//if (meshInit2)
	//{
	//	//sampleEntityMeshCmp->getObj()->showDebugBox(true);
	//	//sampleEntityMeshCmp->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	//}

	//magma_engine::ec::Entity* physicsEntity2 = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();
	//magma_engine::Transform* physicsEntityTransformCmp2 = physicsEntity2->addComponent<magma_engine::Transform>();
	//physicsEntityTransformCmp2->setPosition({ 500, 0, 0 });
	//physicsEntityTransformCmp2->setScale({ 40,40,40 });
	//magma_engine::Mesh* physicsEntityMeshCmp2 = physicsEntity2->addComponent<magma_engine::Mesh>();
	//bool meshInit3 = physicsEntityMeshCmp2->initComponent("ejemploPhysics2", "axolotl.mesh", "axolotl");

	// hacer cosas con el cmp solo si se inicializó correctamente
	//if (meshInit3)
	//{
	//	physicsEntityMeshCmp2->getObj()->showDebugBox(true);
	//	physicsEntityMeshCmp2->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, magma_engine::Vector3D(1, 0, 0));
	//}
	//magma_engine::Rigidbody* physicsEntityRigidbodyCmp2 = physicsEntity2->addComponent<magma_engine::Rigidbody>();




	magma_engine::ec::Entity* physicsEntity3 = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();
	magma_engine::Transform* physicsEntityTransformCmp3 = physicsEntity3->addComponent<magma_engine::Transform>();
	physicsEntityTransformCmp3->setPosition({ 500, 0, 0 });
	physicsEntityTransformCmp3->setScale({ 40,40,40 });
	magma_engine::Mesh* physicsEntityMeshCmp3 = physicsEntity3->addComponent<magma_engine::Mesh>();
	bool meshInit4 = physicsEntityMeshCmp3->initComponent("ejemploPhysics3", "axolotl.mesh", "Axolotl");
	
	
	
	
	//// hacer cosas con el cmp solo si se inicializó correctamente
	//if (meshInit4)
	//{
	//	physicsEntityMeshCmp3->getObj()->showDebugBox(true);
	//	physicsEntityMeshCmp3->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, magma_engine::Vector3D(1, 0, 0));
	//}
	//magma_engine::Rigidbody* physicsEntityRigidbodyCmp3 = physicsEntity3->addComponent<magma_engine::Rigidbody>();

	//Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("PlayerController", physicsEntity3);
	//physicsEntity3->getComponent<magma_engine::PlayerController>()->initComponent(50000.0f, 1.0f);

	//Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("EnemyController", physicsEntity2);
	//physicsEntity2->getComponent<magma_engine::EnemyController>()->initComponent(physicsEntityTransformCmp3, 45000.0f, 2.0f, true);

	//magma_engine::Fps fps;

	// ---------- Inicialización UI ----------

	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	/*UI_Text* testText = Singleton<UI_Manager>::instance()->createElement<UI_Text>("Prueba", 0.0f, 0.0f, 200.0f, 34.0f, "arial", "Who's the impostor?", 0.5f, 0.3f, 0.1f);
	testText->setText("Ahhh yessss");
	UI_Image* testImage = Singleton<UI_Manager>::instance()->createElement<UI_Image>("ImgPrueba", "golf", 0.0f, 80.0f, 100.0f, 100.0f);
	UIButton* testButton = Singleton<UI_Manager>::instance()->createElement<UIButton>("PruebaBoton", "golf", "bubble_color", "bubble_color", 0.0f, 30.0f, 100.0f, 100.0f);*/

	magma_engine::ec::Entity* imageEntity = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();

	//float progreso = 20.0f; 

	//magma_engine::Text* componentTextEntity = imageEntity->addComponent<magma_engine::Text>();
	//componentTextEntity->initComponent("Prueba", "PruebaTexto", "arial", "It's working? Yessssss", 0.0f, 0.0f, 200.0f, 34.0f, 0.5f, 0.3f, 0.1f);
	//componentTextEntity->start();

	//magma_engine::Button* componentButtonEntity = imageEntity->addComponent<magma_engine::Button>();
	//componentButtonEntity->initComponent("ButtonPrueba", "button_solid", "button_transparent", "bubble", 100.0f, 50.0f, 0.0f, 0.0f);
	//componentButtonEntity->start();

	//magma_engine::Image* componentImageEntity = imageEntity->addComponent<magma_engine::Image>();
	//componentImageEntity->initComponent("ImgPrueba", "bubble", 200.0f, 200.0f, 100.0f, 100.0f);
	//componentImageEntity->start();

	//// Botones volumenes
	//magma_engine::Button* componentButtonVolEntity = imageEntity->addComponent<magma_engine::Button>();
	//componentButtonVolEntity->initComponent("ButtonDownVol", "buttonVol1_solid", "buttonVol1_solid", "buttonVol1_transparent", 50.0f, 50.0f, 350.0f, 350.0f);
	//componentButtonVolEntity->start();

	//magma_engine::Button* componentButtonVol2Entity = imageEntity->addComponent<magma_engine::Button>();
	//componentButtonVol2Entity->initComponent("ButtonUpVol", "buttonVol2_solid", "buttonVol2_solid", "buttonVol2_transparent", 50.0f, 50.0f, 650.0f, 350.0f);
	//componentButtonVol2Entity->start();

	magma_engine::AudioSource* componentSoundEffect = imageEntity->addComponent<magma_engine::AudioSource>();
	componentSoundEffect->initComponent("./assets/sounds/eat.wav", 120, 1, false, false);
	componentSoundEffect->start();

	magma_engine::ec::Entity* imageEntity2 = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();
	magma_engine::AudioSource* componentSound = imageEntity2->addComponent<magma_engine::AudioSource>();
	componentSound->initComponent("./assets/sounds/popcorn.wav", 10, 2, true, true);
	componentSound->start();
	
	

	// Carga de mapa
	int errScn = Singleton<magma_engine::SceneLoader>::instance()->loadScene("assets/scenes/test.magmascene");
	magma_engine::Scene* scn = nullptr;
	if (errScn >= 0) {
		SceneMap* sncMp = Singleton<magma_engine::SceneLoader>::instance()->getMapFile();

		scn = new magma_engine::Scene();
		scn->loadScene(sncMp);
		//Singleton<magma_engine::SceneManager>::instance()->pushScene(scn);
	}
	// Carga de mapa

	auto nEntity = Singleton<magma_engine::ec::EntityManager>::instance()->getEntities(); 
	std::cout << nEntity.size() << " NEntidades\n";
	auto nComponente = nEntity[0]->getComponent<magma_engine::Mesh>();

	if (nComponente != nullptr)
		std::cout << "Mesh existe\n"; 

	/*magma_engine::Progress_Bar* componentProgress = imageEntity->addComponent<magma_engine::Progress_Bar>();
	componentProgress->initComponent("ImgPrueba", "golf", 50.0f, 50.0f, 200.0f, 200.0f, progreso, 300.0f);
	componentProgress->start();

	magma_engine::Timer* timeComponent = imageEntity->addComponent<magma_engine::Timer>();
	timeComponent->initComponent();
	timeComponent->start();*/

	// ---------- BUCLE PRINCIPAL ----------
	bool error = false;
	int s = 50;
	while (!Singleton<magma_engine::InputManager>::instance()->exitRequested() && !error && s > 0)
	{
		// Marcas de tiempo y cálculo del "delta"
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = (int)SDL_GetTicks();

		// ---------- TEST RENDER ----------

		//Prueba de animaciones
		Singleton<magma_engine::RenderManager>::instance()->stepAnimations(timeSinceLastFrame);
		//Imprimir número de objetos gráficos cada cierto tiempo
		miliecsSinceLastReport += timeSinceLastFrame;
		if (miliecsSinceLastReport > miliecsToReport)
		{
			std::cout << "Objetos gráficos: " <<
				Singleton<magma_engine::RenderManager>::instance()->getNumObjects() << std::endl;
		}
		//Control de cuándo se borran aquellos que deben ser borrados
		int f = Singleton<magma_engine::RenderManager>::instance()->refreshObjects();
		if (f != 0)
		{
			std::cout << f <<
				" destrucciones graficas diferidas fallidas\t/!\\" << std::endl;
		}
		//Renderizar fotogramas de uno en uno
		if (!Singleton<magma_engine::RenderManager>::instance()->renderFrame())
			error = true;


		// ---------- TEST PHYSICS ----------

		//miliecsSinceLastReport2 += timeSinceLastFrame;
		//if (miliecsSinceLastReport2 > miliecsToReport) {
		//	miliecsSinceLastReport2 = 0;
		//}
		//Singleton<magma_engine::PhysicsManager>::instance()->update(timeSinceLastFrame * 0.001f);
		//if (eliminar) {
		//	if (physicsEntityRigidbodyCmp->isOnCollision()) {
		//		physicsEntity->setAlive(false);
		//		eliminar = false;
		//	}
		//}

		// ---------- TEST INPUT & UI ----------update
		Singleton<magma_engine::InputManager>::instance()->inputEvent();

		// ---------- TEST EC ----------
		Singleton<magma_engine::ec::EntityManager>::instance()->update(timeSinceLastFrame * 0.001f);
		Singleton<magma_engine::ec::EntityManager>::instance()->refresh();


		//mouseImage->setImagePosition(input->getMousePos().first, input->getMousePos().second); 

		if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_SPACE))
		{
			/*progreso += 5.0f;
			componentProgress->setProgress(progreso);

			timeComponent->pause(); */
			componentSoundEffect->playSong();

		}

		if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_K))
		{
			componentSound->setVolume(100);
		}

		/*else if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_O))
		{
			timeComponent->resume();
		}

		else if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_I))
		{
			timeComponent->reset();
		}

		else if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_P))
		{
			timeComponent->assignText(componentTextEntity);
		}*/


		/*if (testButton->isCursorInsideBounds(posMouse.first, posMouse.second))
		{
			testButton->cursorOnButton();

			if (Singleton<InputManager>::instance()->isMouseDown())
			{
				testButton->mousePressedButton();
				std::cout << "Boton pulsado\n";
			}
		}
		else
		{
			if (testButton->isOnButton())
				testButton->mouseLeavingButton();
		}*/

		//Redimensión ventana
		if (Singleton<magma_engine::InputManager>::instance()->hasWindowChange()) {
			Singleton<magma_engine::RenderManager>::instance()->notifyWindowResized();
		}

		//esto hace que ya pille bien el imput la ui al pulsar el raton
		//imageEntity->update(timeSinceLastFrame * 0.001f);


		Singleton<magma_engine::InputManager>::instance()->flush();

		// ---------- FPS CALCULATOR ----------
		//fps.update();

		if (miliecsSinceLastReport > miliecsToReport) {
			miliecsSinceLastReport = 0;
		}
	}
	if (error)
	{
		std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
	}


	// Carga de mapa
	if (errScn >= 0) {
		//Singleton<magma_engine::SceneManager>::instance()->popScene();
		delete scn;
		scn = nullptr;
	}
	// Carga de mapa

	releaseManagers();

	return 0;
}

void initManagers() {
	// ------ RENDER		------
	if (Singleton<magma_engine::RenderManager>::init(false, 1280, 720, false, true, 4, false))
	{
		if (!Singleton<magma_engine::RenderManager>::instance()->initApp()) // if (!correct)
		{
			// Fin del renderizado
			Singleton<magma_engine::RenderManager>::instance()->closeApp();
			Singleton<magma_engine::RenderManager>::instance()->release();
		}
	}
	// ------ EC			------
	Singleton<magma_engine::ec::EntityManager>::init();
	// ------ FACTORY		------
	Singleton<magma_engine::FactoryManager>::init();
	magma_engine::setUpFactories();
	// ------ GAME SCENES	------
	Singleton<magma_engine::SceneManager>::init();
	// ------ LUA SCENES	------
	Singleton<magma_engine::SceneLoader>::init();

	// ------ PHYSICS		------
	bool correct = false;
	if (Singleton<magma_engine::PhysicsManager>::init())
		correct = Singleton<magma_engine::PhysicsManager>::instance()->initPhysics();
	if (!correct)
		// Fin del renderizado
		Singleton<magma_engine::PhysicsManager>::instance()->detachPhysics();
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	/// esta detección con 'correct' HAY QUE HACERLA PARA TODO !!!!
	// ------ UI			------
	Singleton<magma_engine::UI_Manager>::init();
	// ------ INPUT			------
	Singleton<magma_engine::InputManager>::init();
	// ------ SOUND			------
	if (Singleton<magma_engine::SoundManager>::init())
		Singleton<magma_engine::SoundManager>::instance()->initAudio();
}

void releaseManagers() {
	// ------ LUA SCENES	------
	Singleton<magma_engine::SceneLoader>::release();
	// ------ GAME SCENES	------
	Singleton<magma_engine::SceneManager>::release();
	// ------ EC			------
	Singleton<magma_engine::ec::EntityManager>::release();
	// ------ PHYSICS		------
	Singleton<magma_engine::PhysicsManager>::instance()->detachPhysics();
	Singleton<magma_engine::PhysicsManager>::release();
	// ------ INPUT			------
	Singleton<magma_engine::InputManager>::release();
	// ------ UI			------
	Singleton<magma_engine::UI_Manager>::release();
	// ------ RENDER		------
	Singleton<magma_engine::RenderManager>::instance()->closeApp();
	Singleton<magma_engine::RenderManager>::release();
	// ------ SOUND			------
	Singleton<magma_engine::SoundManager>::release();
	// ------ FACTORY		------
	Singleton<magma_engine::FactoryManager>::release();
}

// Esta disyuntiva hace que en config. Release no aparezca la consola
// Hay diferentes funciones como punto de entrada por defecto al seleccionar
// valores distintos en 'Vinculador > Sistema > Subsistema' según la Configuración
#if _DEBUG
int main(int argc, char const** argv) {
	return mainCode();
}
#else
int __stdcall WinMain(void*, void*, char* cmdLine, int) {
	return mainCode();
}
#endif
