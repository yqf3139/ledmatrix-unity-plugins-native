#include "bridge.h"
#include "senddata.h"

static SendData *sd = NULL;

static unsigned int data[BUFDIM * BUFDIM * BUFDIM];

static int len = 0;

static FILE * pConsole;

unsigned int* BridgeGetLedBuffer()
{
	return data;
}

void BridgeSend()
{
	sd->setData((int *)data, len);
	sd->send();
}

void BridgeHandshake()
{
	printf("BridgeHandshake\n");
	sd->send37();
}

void BridgeConstruct(
	int _floorCounter, int _roundsCounter, float _step,
	float _distance, float _height, float _pillar, int _len)
{
	printf("BridgeConstruct\n");

	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);

	len = _len;
	if (sd) BridgeDeConstruct();
	sd = new SendData("192.168.1.90", 60000);
	sd->setCylinderConf(_roundsCounter, _step*10, 1024, _floorCounter, _distance*10, _height*10);
}

void BridgeDeConstruct()
{
	printf("BridgeDeConstruct\n");
	if (sd) delete sd;
	sd = NULL;
}