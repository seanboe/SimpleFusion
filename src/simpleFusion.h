#ifndef SIMPLE_FUSION
#define SIMPLE_FUSION

#include <Arduino.h>

#define DATA_UPDATE_POLL_TOLERANCE	5			//milliseconds

typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
} ThreeAxis;

typedef struct {
	int16_t roll;
	int16_t pitch;
} FusedAngles;

class sensorFusion {

	public:
		sensorFusion();
		bool init(int16_t filterUpdateRate, int16_t gyroFavoring, RotationType rotationType);
		bool shouldUpdateData();
		int16_t getFilteredAngle(ThreeAxis &gyroscope, ThreeAxis &accelerometer);
		
	private:
		RotationType _rotationType;
		int16_t	_filterUpdateRate;		// Hertz, less than 1000
		int16_t _gyroFavoring; 				// The amount that the gyro is favored

		int16_t _pitch;
		int16_t _roll;

		long long _previousTime;
		bool _justUpdatedData;
};

#endif