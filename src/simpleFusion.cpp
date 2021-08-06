#include "simpleFusion.h"

SimpleFusion::SimpleFusion(void) {};

bool SimpleFusion::init(int16_t filterUpdateRate, float pitchGyroFavoring, float rollGyroFavoring) {
	_filterUpdateRate = filterUpdateRate;
	_pitchGyroFavoring = pitchGyroFavoring;
	_rollGyroFavoring = rollGyroFavoring;
	
	if (_pitchGyroFavoring > 1 || _pitchGyroFavoring < 0)
		return false;
	if (_rollGyroFavoring > 1 || _rollGyroFavoring < 0)
		return false;
	
	_previousTime = micros();
	_justUpdatedData = false;
	
	_pitch = 0;
	_roll = 0;
	
	return true;
};


bool SimpleFusion::shouldUpdateData() {
	long dt = (micros() - _previousTime);
	
	if ((dt % (1000000 / _filterUpdateRate) <= DATA_UPDATE_POLL_TOLERANCE) && (_justUpdatedData == false)) {
		_justUpdatedData = true;
		return true;
	}
	else if ((dt % (1000000 / _filterUpdateRate) > DATA_UPDATE_POLL_TOLERANCE))
		_justUpdatedData = false;
		
	return false;
};


void SimpleFusion::getFilteredAngles(ThreeAxis &accelerometer, ThreeAxis &gyroscope, FusedAngles *angleOutputs, AngleUnit angleUnit) { 
	
	float pitchFromAccel = 0;
	float rollFromAccel  = 0;
	
	pitchFromAccel = atan(-accelerometer.x / sqrt(pow(accelerometer.y, 2) + pow(accelerometer.z, 2))) * (float)(180 / PI);	
	rollFromAccel = atan(accelerometer.y / sqrt(pow(accelerometer.x, 2) + pow(accelerometer.z, 2))) * (float)(180 / PI);
	
	// Complimentary Filter
	_pitch = (_pitchGyroFavoring) * (_pitch + (gyroscope.y * (180 / PI) * (1.00 / _filterUpdateRate))) + (1.00 - _pitchGyroFavoring) * (pitchFromAccel);
	_roll = (_rollGyroFavoring) * (_roll + (gyroscope.x * (180 / PI) * (1.00 / _filterUpdateRate))) + (1.00 - _rollGyroFavoring) * (rollFromAccel);

	
	switch (angleUnit) {
		case UNIT_DEGREES:
			angleOutputs->pitch = _pitch;
			angleOutputs->roll = _roll;
			break;
		case UNIT_RADIANS:
			angleOutputs->pitch = _pitch * (PI / 180);      
			angleOutputs->roll 	= _roll  * (PI / 180);
			break;
	}

};

