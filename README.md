# SimpleFusion

A simple library that applies a complementary filter to accelerometer and 
gyroscope readings (6-dof IMU) in order to achieve an accurate estimation 
of the pitch and roll of a gyroscope.

### Be Aware:
The library expects accelerometer readings in m/second^2 and gyroscope readings in radians/second. It can output an angle in radians or degrees.

### Benefits

Complementary filters remove the drift from gyroscopes by considering accelerometer readings, which don't drift (but are very noisy and subject to inaccuracy).



Sooner or later, I'll publish this as an official Arduino library... once I've 
done more testing and ironed out the bugs 😉.
