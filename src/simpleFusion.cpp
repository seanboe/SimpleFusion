#include "simpleFusion.h"

sensorFusion::sensorFusion(void) {};

bool sensorFusion::init(int16_t filterUpdateRate, int16_t gyroFavoring) {
	_filterUpdateRate = filterUpdateRate;
	_gyroFavoring = _gyroFavoring;
	if (_gyroFavoring > 1 || _gyroFavoring < 0)
		return false;
	
	_previousTime = millis();
	_justUpdatedData = false;
	
	return true;
};


bool sensorFusion::shouldUpdateData() {
	int16_t dt = (millis() - _previousTime);
	if (dt % (1000 / _filterUpdateRate) < DATA_UPDATE_POLL_TOLERANCE && _justUpdatedData == false) {
		_justUpdatedData = true;
		return true;
	}
	else if (!(dt % (1000 / _filterUpdateRate) < DATA_UPDATE_POLL_TOLERANCE))
		_justUpdatedData = false;
	return false;
};

int16_t sensorFusion::getFilteredAngles(ThreeAxis &gyroscope, ThreeAxis &accelerometer, FusedAngles *angleOutputs) { 
	
	int16_t pitchFromAccel = 0;
	int16_t rollFromAccel  = 0;
	
	pitchFromAccel = atan(accelerometer.x / sqrt(pow(accelerometer.y, 2) + pow(accelerometer.z, 2))) * (180 / PI);	
	rollFromAccel = atan(accelerometer.y / sqrt(pow(accelerometer.x, 2) + pow(accelerometer.z, 2))) * (180 / PI);
	
	// Complimentary Filter
	_pitch = ()
	
};

