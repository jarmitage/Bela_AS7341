#include <Bela.h>
#include <libraries/Scope/Scope.h>
#include <libraries/Gui/Gui.h>
#include "AS7341.h"

Scope gScope;
Gui gGui;
AuxiliaryTask gSensorTask;
AS7341 gSpectralSensor;

float gResult[6] = {0};
unsigned int gReadInterval;
unsigned int gReadCounter;

void readSpectralSensor(void *arg)
{
	gSpectralSensor.readResult(gResult);
}

bool setup(BelaContext *context, void *userData)
{
	gScope.setup(6, context->audioSampleRate / context->audioFrames);
	gGui.setup(context->projectName);

	if(!gSpectralSensor.begin())
		return false;
	if(!gSpectralSensor.initialise())
		return false;

	gReadCounter = 0;
	gReadInterval = 0.0025 * context->audioSampleRate; // 2.5ms

    gSensorTask = Bela_createAuxiliaryTask(readSpectralSensor, 50, "read-as7341");
	return true;
}

void render(BelaContext *context, void *userData)
{
	gReadCounter += context->audioFrames;
	if(gReadCounter >= gReadInterval) {
		gReadCounter = 0;
		gGui.sendBuffer(0, gResult[0]);
		Bela_scheduleAuxiliaryTask(gSensorTask);
	}	
	gScope.log(gResult[0]);
}

void cleanup(BelaContext *context, void *userData){}
