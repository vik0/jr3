/* Copyright (C) 2013, Fabian Gerlinghaus <gerlinghaus@cs.stanford.edu> */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Jr3Sensor.h"

extern "C" {
#include "jr3Struct.h"
#include "jr3DriverInterface.h"
}

static jr3DSPStruct jr3Data;

Jr3Sensor::Jr3Sensor() : R_SS (3,3)
{
	jr3Init();

	if (jr3DataRead(&jr3Data) != sizeof(jr3Data)) {
		std::cout << "Jr3Sensor: Could not read from device!\n";
	}
	else {
		//jr3SensorResetOffsets();

		std::cout << "Jr3 Force/Torque Sensor initialized (but not zeroed)!\n" << std::flush;
	}
}

bool Jr3Sensor::GetCartesianForcesTorques(float * MeasuredCartesianForcesTorques, int filter) {
	Eigen::Vector3f forces(3), torques(3);
	forces.setZero(3);
	torques.setZero(3);

	if (jr3DataRead(&jr3Data) != sizeof(jr3Data)) {
		std::cout << "Jr3Sensor: Could not read from device!\n";
		for (int i=0; i<6; i++) MeasuredCartesianForcesTorques[i] = 0.0;
		return false;
	}
	else {
		// 500Hz
		if (filter == 1) {
			forces(0) = float(jr3Data.f1.fx) * float(jr3Data.fullScale.fx) / 16384.0;
			forces(1) = float(jr3Data.f1.fy) * float(jr3Data.fullScale.fy) / 16384.0;
			forces(2) = float(jr3Data.f1.fz) * float(jr3Data.fullScale.fz) / 16384.0;

			torques(0) = float(jr3Data.f1.mx) * float(jr3Data.fullScale.mx) / 10.0 / 16384.0;
			torques(1) = float(jr3Data.f1.my) * float(jr3Data.fullScale.my) / 10.0 / 16384.0;
			torques(2) = float(jr3Data.f1.mz) * float(jr3Data.fullScale.mz) / 10.0 / 16384.0;
		}
		// 125Hz
		if (filter == 2) {
			forces(0) = float(jr3Data.f2.fx) * float(jr3Data.fullScale.fx) / 16384.0;
			forces(1) = float(jr3Data.f2.fy) * float(jr3Data.fullScale.fy) / 16384.0;
			forces(2) = float(jr3Data.f2.fz) * float(jr3Data.fullScale.fz) / 16384.0;

			torques(0) = float(jr3Data.f2.mx) * float(jr3Data.fullScale.mx) / 10.0 / 16384.0;
			torques(1) = float(jr3Data.f2.my) * float(jr3Data.fullScale.my) / 10.0 / 16384.0;
			torques(2) = float(jr3Data.f2.mz) * float(jr3Data.fullScale.mz) / 10.0 / 16384.0;
		}
		if (filter != 1 && filter != 2) return false;

//		std::cout << "Fz [N]: " << float(jr3Data.f1.fz) * float(jr3Data.fullScale.fz) / 16384.0 << "\n";

//		std::cout << "Units: " << jr3Data.units << "\n";
//		std::cout << "jr3Data.fullScale.fx: " << jr3Data.fullScale.fx << "\n";
//		std::cout << "jr3Data.fullScale.mx: " << jr3Data.fullScale.mx << "\n";
//		std::cout << "jr3Data.fullScale.fy: " << jr3Data.fullScale.fy << "\n";
//		std::cout << "jr3Data.fullScale.my: " << jr3Data.fullScale.my << "\n";
//		std::cout << "jr3Data.fullScale.fz: " << jr3Data.fullScale.fz << "\n";
//		std::cout << "jr3Data.fullScale.mz: " << jr3Data.fullScale.mz << "\n";
//		std::cout << "jr3Data.f1.fx: " << jr3Data.f1.fx << "\n";
//		std::cout << "jr3Data.f1.mx: " << jr3Data.f1.mx << "\n";

		for (int i=0; i<3; i++) {
			// Forces in N
			MeasuredCartesianForcesTorques[i] = forces(i);
		}
		for (int i=0; i<3; i++) {
			// Torques in Nm
			MeasuredCartesianForcesTorques[i+3] = torques(i);
		}

		return true;
	}
}

void Jr3Sensor::ResetOffsets() {
	jr3SensorResetOffsets();
}
