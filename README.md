<h1 align="center">
  <br>
  <a href="https://github.com/seanboe/QuadrupedProject"><img src="extras/images/complementary_filter.png" alt="complementary_filter" width="600"></a>
  <br>
  SimpleFusion
  <br>
</h1>

<p align="center">
A library that fuses accelerometer and gyroscope readings quickly and easily with a complementary filter.
<br>
<br>	
<a href="https://github.com/seanboe/SimpleFusion"> <img src="https://img.shields.io/badge/License-MIT-informational.svg"> </a>
<a href="https://github.com/seanboe/SimpleFusion"> <img src="https://img.shields.io/badge/Maintained%3F-yes-orange.svg"> </a>	
  <a href="https://github.com/seanboe/SimpleFusion"><img src="https://img.shields.io/github/v/release/seanboe/SimpleFusion?color=bright-green"></a>
</p>

## Overview
This library combines accelerometer (in meters / second &sup2;) and gyroscope (in radians / second) data to output the IMU's rotation (Euler angles). It is accurate
up to &plusmn; 90 degrees. 

Note the the lxibrary defines pitch to be a rotation about the y-axis and roll to be a rotation about the x-axis.

## Benefits
Here's a comparison of different high-speed methods for estimating pitch and roll.

<p align = "center">
<br>
<img src="extras/images/filter_comparisons.jpg" atl="filter_comparisons" width = "600">
<br>
</p>

The complementary filter returns smooth readings despite non-zero acceleration.

## License

<a href="LICENSE">MIT<a>
