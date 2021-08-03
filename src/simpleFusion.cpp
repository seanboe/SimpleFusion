#include "simpleFusion.h"

sensorFusion::sensorFusion(void) {};

bool sensorFusion::init(int16_t filterUpdateRate, int16_t gyroFavoring, RotationType rotationType) {
	_filterUpdateRate = filterUpdateRate;
	_gyroFavoring = _gyroFavoring;
	if (_gyroFavoring > 1 || _gyroFavoring < 0)
		return false;
	_rotationType = rotationType;
	
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

int16_t sensorFusion::getFilteredAngle(ThreeAxis &gyroscope, ThreeAxis &accelerometer) { 
	int16_t relevantAccelerometer = 0;			// The roll calculation requires the x acclerometer, the pitch requires the y
	int16_t relevantGyroscope = 0;
	
	switch (_rotationType) {
		case PITCH:
			relevantAccelerometer = accelerometer.y;
			relevantGyroscope = gyroscope.x;
			break;
		case ROLL:
			relevantAccelerometer = accelerometer.x;
			relevantGyroscope = gyroscope.y;
			break;
	}	
	
	// Get the angle based on the accelerometer readings
	int16_t accelerometerAngle = tan(relevantAccelerometer / accelerometer.z);
	
	// Integrate the gyroscope angle to get the angle based on gyroscope readings
	_angle += relevantGyroscope * _filterUpdateRate;
	
	// Apply the complementary filter
	_angle = _gyroFavoring * _angle + accelerometerAngle * (1 - _gyroFavoring);
	
	return _angle;
	
};


