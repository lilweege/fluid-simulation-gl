#ifndef SIMULATION
#define SIMULATION

#include <vector>
using std::vector;

typedef vector<vector<vector<float>>> vec3D_f;
enum direction { X, Y, Z, W };


class simulation {
private:
public:
	int N;
	float diff;
	float visc;
	int iters;
private:
	vec3D_f temp_density;
	vec3D_f density;
	vector<vec3D_f> temp_velocities;
	vector<vec3D_f> velocities;

private:

	void addSource(vec3D_f& vec, vec3D_f& temp_vec, float step);
	void correctBounds(direction dir, vec3D_f& vec);
	void diffuse(direction dir, float diff, float step);
	void advect(direction dir, float step);
	void project(vec3D_f& p, vec3D_f& div, float step);

public:

	simulation(int n, float diffusion, float viscosity/*, int iterations*/)
		: N(n), diff(diffusion), visc(viscosity), iters(4)
	{
		density.resize(n, vector<vector<float>>(n, vector<float>(n)));
		temp_density.resize(n, vector<vector<float>>(n, vector<float>(n)));
		velocities.resize(3, vector<vector<vector<float>>>(n, vector<vector<float>>(n, vector<float>(n))));
		temp_velocities.resize(3, vector<vector<vector<float>>>(n, vector<vector<float>>(n, vector<float>(n))));
	}

	void addDensity(int i, int j, int k, float amount) { density[i][j][k] += amount; }
	void addVelocity(direction dir, int i, int j, int k, float amount) { velocities[dir][i][j][k] += amount; }
	float getDensity(int i, int j, int k) { return density[i][j][k]; }

	void tick(float step);
};

#endif /*SIMULATION*/