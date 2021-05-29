#ifndef SIMULATION
#define SIMULATION

#include <vector>

// https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

class simulation {
private:

	int size;
	float diff;
	float visc;

	// TODO: maybe make this a raw array
	std::vector<std::vector<std::vector<float>>> density;
	// TODO: rest of variables and functions

private:

	void addDensity(int x, int y, int z, float amount);
	void addVelocity(int x, int y, int z, float amountX, float amountY, float amountZ);

	void diffuse(float step);
	void project(float step);
	void advect(float step);


public:
	simulation(int n, int diffusion, int viscosity)
		: size(n), diff(diffusion), visc(viscosity)
	{
		density.resize(n, std::vector<std::vector<float>>(n, std::vector<float>(n)));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				for (int k = 0; k < n; ++k)
					density[i][j][k] = 0.1;

	}

	float getDensity(int i, int j, int k) { return density[i][j][k]; }

	void tick(float step);
};

#endif /*SIMULATION*/