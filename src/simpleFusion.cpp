#include "simpleFusion.h"

SimpleFusion::SimpleFusion(void) {};


/*!
 *    @brief Initializes filter parameters. 
 *    @param filterUpdateRate The frequency of filter updates up to 1000000 Hertz
 *    @param pitchGyroFavoring The amount that the gyroscope is favored in the pitch direction as a decimal percent less than 1
 * 		@param rollGyroFavoring The amount that the gyroscope is favored in the roll direction as a decimal percent less than 1 
 *		@returns false if any gyro favoring is an invalid value, true if they are valid.
*/
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

/*!
 *    @brief Allows you to update the library at the desired frequency. You should update the sensor only when the library is running
 *		@returns true if it is time to update the library, false if it isn't
*/
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

/*!
 *    @brief Calculates rotation angles based on gyroscope and accelerometer readings
 *    @param accelerometer The accelerometer readings from the IMU as ThreeAxis struct variables (Units are m/s^2)
 *    @param gyroscope The gyroscope readings from the IMU as ThreeAxis struct variables (Units are radians/second)
 * 		@param angleOutputs The address of a FusedAngles struct variable for holding angular outputs
*/
void SimpleFusion::getFilteredAngles(ThreeAxis &accelerometer, ThreeAxis &gyroscope, FusedAngles *angleOutputs, AngleUnit angleUnit) { 
	
	float pitchFromAccel = 0;
	float rollFromAccel  = 0;
	
	pitchFromAccel = atan(-accelerometer.x / sqrt(pow(accelerometer.y, 2) + pow(accelerometer.z, 2)));	
	rollFromAccel = atan(accelerometer.y / sqrt(pow(accelerometer.x, 2) + pow(accelerometer.z, 2)));
	// rollFromAccel = atan2(accelerometer.y, accelerometer.z);
	
	// Complimentary Filter
	_pitch = (_pitchGyroFavoring) * (_pitch + (gyroscope.y * (1.00 / _filterUpdateRate))) + (1.00 - _pitchGyroFavoring) * (pitchFromAccel);
	_roll = (_rollGyroFavoring) * (_roll + (gyroscope.x * (1.00 / _filterUpdateRate))) + (1.00 - _rollGyroFavoring) * (rollFromAccel);

	
	switch (angleUnit) {
		case UNIT_DEGREES:
			angleOutputs->pitch = _pitch * (180 / PI);
			angleOutputs->roll = _roll * (180 / PI);
			break;
		case UNIT_RADIANS:
			angleOutputs->pitch = _pitch;      
			angleOutputs->roll 	= _roll;
			break;
	}

};

