Outils :
	- SDL2 (gestion graphique CPU)
	- OpenCL (Implementation GPU multi threading)

SDL2 :
	Installation :
		Clonez le repo SDL2 a la racine du projet.
		--> https://github.com/42RT/SDL2.git
	
	Include :
		#include "SDL2/SDL.h"
	
	Compilation :
		Ajoutez les flags suivants pour compiler :
		-> -I SDL2/include
		-> -L SDL2/lib -lSDL2

OpenCL :
	Installation :
		Deja integree

	Include (surtout pas mettre dans les .cl):
		#ifdef __APPLE__
		#include <OpenCL/opencl.h>
		#else
		#include <CL/cl.h>
		#endif

	Compilation :
		flag : "-framework opencl"
