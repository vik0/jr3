/* Copyright (C) 2013, Fabian Gerlinghaus <gerlinghaus@cs.stanford.edu> */



#ifndef JR3_FORCE_SENSOR_H
#define JR3_FORCE_SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Eigen/Dense>

extern "C" {
#include "jr3Struct.h"
#include "jr3DriverInterface.h"
}

class Jr3Sensor {
public:

	Jr3Sensor();

	// Returns false if there is an error while reading from the sensor
	bool	GetCartesianForcesTorques(float *MeasuredCartesianForcesTorques, int filter);
	void	ResetOffsets();


private:
	// Rotation Matrix from sensor frame to turned sensor frame
	// Depends on how the sensor is mounted on the TCP
	Eigen::Matrix3f R_SS;

};

#endif
