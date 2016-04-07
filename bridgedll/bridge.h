#pragma once

#define BUFDIM 200

#define _DLLExport __declspec (dllexport)

// =================== export below funcions to Unity 3D =================== //

extern "C" _DLLExport unsigned int* BridgeGetLedBuffer();

extern "C" _DLLExport void BridgeSend();

extern "C" _DLLExport void BridgeHandshake();

extern "C" _DLLExport void BridgeConstruct(
	int _floorCounter, int _roundsCounter, float _step,
	float _distance, float _height, float _pillar, int _len);

extern "C" _DLLExport void BridgeDeConstruct();