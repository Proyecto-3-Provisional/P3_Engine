#include "sound_manager.h"
#include "SDL.h"

static Uint8* audioPos; // Puntero a la posicion del bufer de audio que se reproduce actualmente
static Uint32 audioLen; // Longitud restante del bufer de audio por reproducir.

// Copia los datos del b�fer de audio al b�fer de audio del dispositivo.
void audio_callback(void* userdata, Uint8* stream, int len);

SoundManager::SoundManager()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		std::cerr << "Error al iniciar el sistema de audio: " << SDL_GetError() << std::endl;

	if (SDL_LoadWAV("../../executables/assets/sound.wav", &data.spec, &data.buffer, &data.bufferSize) == nullptr)
		std::cerr << "Error al cargar el sonido: " << SDL_GetError() << std::endl;

	data.spec.callback = audio_callback;
	data.spec.userdata = nullptr;

	audioPos = data.buffer;
	audioLen = data.bufferSize;
}

SoundManager::~SoundManager() 
{
	SDL_CloseAudio();
	SDL_FreeWAV(data.buffer);
}

// Reproduccion de audio
void SoundManager::playSound()
{
	device = SDL_OpenAudio(&data.spec, nullptr);
	if (device == 0) std::cerr << "Error de dispositivo de audio: " << SDL_GetError() << std::endl;

	SDL_PauseAudio(0);
}

// Detiene la reproduccion de audio
void SoundManager::stopSound() 
{
	SDL_PauseAudio(1);
}

void audio_callback(void* userdata, Uint8* stream, int len)
{
	// Comprueba si queda audio por reproducir en el bufer
	if (audioLen == 0)
		return;

	len = (len > audioLen ? audioLen : len); // Cantidad de datos que se van a copiar (valor m�nimo entre len y audioLen)
	SDL_memcpy(stream, audioPos, len); // Copia los datos del bufer audioPos al bufer stream
	SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME); // Mezclan de los datos copiados con los datos almacenados en stream

	audioPos += len; // Actualiza la posicion del bufer para apuntar al siguiente bloque de datos
	audioLen -= len; // Actualiza la longitud restante del bufer
}
