#ifndef SIMPLE_FUSION
#define SIMPLE_FUSION

#include <Arduino.h>

#define DATA_UPDATE_POLL_TOLERANCE	5			// The leniency of shouldUpdateData(), in microseconds

typedef struct {
	float x;
	float y;
	float z;
} ThreeAxis;

typedef struct {
	float roll;
	float pitch;
} FusedAngles;

typedef enum {
	UNIT_DEGREES, UNIT_RADIANS
}	AngleUnit;

class SimpleFusion {

	public:
		SimpleFusion();
		bool init(int16_t filterUpdateRate, float pitchGyroFavoring, float rollGyroFavoring);
		void getFilteredAngles(ThreeAxis &accelerometer, ThreeAxis &gyroscope, FusedAngles *angleOutputs, AngleUnit angleUnit);

		bool shouldUpdateData();
		
	private:
		
		int16_t	_filterUpdateRate;		// Hertz, less than 1000000
		float _pitchGyroFavoring; 	// The amount that the gyro is favored (alpha)
		float _rollGyroFavoring;				

		float _pitch;
		float _roll;

		long _previousTime;
		bool _justUpdatedData;
};

#endif