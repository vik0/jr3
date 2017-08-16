
#include <iostream>
#include <Eigen/Dense>

#include "Jr3Sensor.h"

int main()
{

	Jr3Sensor* my_jr3 = new Jr3Sensor();

	Eigen::VectorXd force;
	force.setZero(6);


	float jr3_raw [6];
	for (int i = 0; i < 6; i++)
    {  jr3_raw [i] =   (float)0.0; }

	std::cout << "Hello Jr3" << std::endl;

	int ctr = 0;
	while(ctr < 1000000)
	{

		// my_jr3->GetCartesianForcesTorques(jr3_raw, 0);

		if (my_jr3->GetCartesianForcesTorques(jr3_raw, 1) == false) 
		{
			std::cout << "Could not read from force/torque sensor!" << std::endl;
		}

        for (int i = 0; i < 6; ++i)
        {
            force[i] = jr3_raw[i];
        }

        std::cout << force.transpose() << std::endl;

		ctr++;
	}


	return 0;
}


