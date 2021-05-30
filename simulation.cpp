#include "simulation.h"
#include <stdio.h>

void linSolve(vec3D_f& vec, vec3D_f& temp_vec, float a, float div)
{
	// something about gauss-seidel relaxation
	// TODO: learn how this works
	int N = vec.size();
	for (int i = 1; i < N - 1; ++i)
		for (int j = 1; j < N - 1; ++j)
			for (int k = 1; k < N - 1; ++k)
				vec[i][j][k] = (temp_vec[i][j][k] +
							a* (vec[i+1][j  ][k  ] +
								vec[i-1][j  ][k  ] +
								vec[i  ][j+1][k  ] +
								vec[i  ][j-1][k  ] +
								vec[i  ][j  ][k+1] +
								vec[i  ][j  ][k-1] )) / div;
}

// http://graphics.cs.cmu.edu/nsp/course/15-464/Fall09/papers/StamFluidforGames.pdf
// https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

void simulation::tick(float step)
{
	addVelocity(Y, N/2, N/2, N/2, 100000*step);
	step /= 10000000.0f;

	for (int i = 1; i < N - 1; ++i)
		for (int j = 1; j < N - 1; ++j)
			for (int k = 1; k < N - 1; ++k)
			{
				density[i][j][k] -= 50 * step;
			}
	addDensity(N/2, N/2, N/2, N*N*N*step*100);


	// vel_step
	addSource(velocities[X], temp_velocities[X], step);
	addSource(velocities[Y], temp_velocities[Y], step);
	addSource(velocities[Z], temp_velocities[Z], step);
	velocities.swap(temp_velocities);
	diffuse(X, visc, step);
	diffuse(Y, visc, step);
	diffuse(Z, visc, step);
	project(temp_velocities[X], temp_velocities[Y], step);
	velocities.swap(temp_velocities);
	advect(X, step);
	advect(Y, step);
	advect(Z, step);
	project(temp_velocities[X], temp_velocities[Y], step);

	// dens_step
	addSource(density, temp_density, step);
	density.swap(temp_density);
	diffuse(W, diff, step);
	density.swap(temp_density);
	advect(W, step);
}

void simulation::diffuse(direction dir, float diff, float step)
{
	vec3D_f& vec      = dir == W ?      density :      velocities[dir];
	vec3D_f& temp_vec = dir == W ? temp_density : temp_velocities[dir];
		
	float a = step * diff * (N - 2) * (N - 2) * (N - 2);
	for (int iter = 0; iter < iters; ++iter)
	{
		linSolve(vec, temp_vec, a, 1 + 6 * a);
		correctBounds(dir, vec);
	}
}

void simulation::advect(direction dir, float step)
{
	vec3D_f& vec      = dir == W ?      density :      velocities[dir];
	vec3D_f& temp_vec = dir == W ? temp_density : temp_velocities[dir];

	int i, j, k, i0, j0, k0, i1, j1, k1;
	float x, y, z, s0, t0, u0, s1, t1, u1, dt0;
	dt0 = step * (N - 2);

	for (i = 1; i < N - 1; ++i)
		for (j = 1; j < N - 1; ++j)
			for (k = 1; k < N - 1; ++k)
			{
				x = i - dt0 * velocities[X][i][j][k];
				y = j - dt0 * velocities[Y][i][j][k];
				z = k - dt0 * velocities[Z][i][j][k];

				if (x<0.5) x=0.5; if (x>N-2+0.5) x=N-2+ 0.5; i0=(int)x; i1=i0+1;
				if (y<0.5) y=0.5; if (y>N-2+0.5) y=N-2+ 0.5; j0=(int)y; j1=j0+1;
				if (z<0.5) z=0.5; if (z>N-2+0.5) z=N-2+ 0.5; k0=(int)z; k1=k0+1;

				s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1; u1 = z-k0; u0 = 1-u1;

				vec[i][j][k] =
					s0 * t0 * u0 * temp_vec[i0][j0][k0] +
					s0 * t0 * u1 * temp_vec[i0][j0][k1] +
					s0 * t1 * u0 * temp_vec[i0][j1][k0] +
					s0 * t1 * u1 * temp_vec[i0][j1][k1] + 
 					s1 * t0 * u0 * temp_vec[i1][j0][k0] +
					s1 * t0 * u1 * temp_vec[i1][j0][k1] + 
					s1 * t1 * u0 * temp_vec[i1][j1][k0] +
					s1 * t1 * u1 * temp_vec[i1][j1][k1];
			}
	correctBounds(dir, vec);
}

void simulation::project(vec3D_f& p, vec3D_f& div, float step)
{
	// yeah I don't fully understand how this method is meant to scale
	// from 2D to 3D, Stam's paper doesn't fully explain it
	for (int i = 1; i < N - 1; ++i)
		for (int j = 1; j < N - 1; ++j)
			for (int k = 1; k < N - 1; ++k)
			{
				div[i][j][k] = -0.5f / float(N-2) *
					(velocities[X][i+1][j  ][k  ]
					-velocities[X][i-1][j  ][k  ]
					+velocities[Y][i  ][j+1][k  ]
					-velocities[Y][i  ][j-1][k  ]
					+velocities[Z][i  ][j  ][k+1]
					-velocities[Z][i  ][j  ][k-1]);
				p[i][j][k] = 0;
			}
	
	correctBounds(W, div);
	correctBounds(W, p);

	for (int iter = 0; iter < iters; ++iter)
	{
		linSolve(p, div, 1, 6);
		correctBounds(W, p);
	}

	for (int i = 1; i < N - 1; ++i)
		for (int j = 1; j < N - 1; ++j)
			for (int k = 1; k < N - 1; ++k)
			{
				velocities[X][i][j][k] -= 0.5f * (N - 2) * (  p[i+1][j  ][k  ]
															- p[i-1][j  ][k  ]);
				velocities[Y][i][j][k] -= 0.5f * (N - 2) * (  p[i  ][j+1][k  ]
															- p[i  ][j-1][k  ]);
				velocities[Z][i][j][k] -= 0.5f * (N - 2) * (  p[i  ][j  ][k+1]
															- p[i  ][j  ][k-1]);
			}
	
	correctBounds(X, velocities[X]);
	correctBounds(Y, velocities[Y]);
	correctBounds(Z, velocities[Z]);
}

void simulation::addSource(vec3D_f& vec, vec3D_f& temp_vec, float step)
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				vec[i][j][k] += step * temp_vec[i][j][k];
}

void simulation::correctBounds(direction dir, vec3D_f& vec)
{
	for (int j = 1; j < N - 1; ++j)
		for (int k = 1; k < N - 1; ++k)
		{
			vec[0  ][j][k] = (dir == X ? -1 : 1) * vec[1  ][j][k];
			vec[N-1][j][k] = (dir == X ? -1 : 1) * vec[N-2][j][k];
		}

	for (int i = 1; i < N - 1; ++i)
		for (int k = 1; k < N - 1; ++k)
		{
			vec[i][0  ][k] = (dir == Y ? -1 : 1) * vec[i][1  ][k];
			vec[i][N-1][k] = (dir == Y ? -1 : 1) * vec[i][N-2][k];
		}

	for (int i = 1; i < N - 1; ++i)
		for (int j = 1; j < N - 1; ++j)
		{
			vec[i][j][0  ] = (dir == Z ? -1 : 1) * vec[i][j][1  ];
			vec[i][j][N-1] = (dir == Z ? -1 : 1) * vec[i][j][N-2];
		}

	vec[0  ][0  ][0  ] = 0.33f * (vec[1  ][0  ][0  ]
								+ vec[0  ][1  ][0  ]
								+ vec[0  ][0  ][1  ]);
	vec[0  ][N-1][0  ] = 0.33f * (vec[1  ][N-1][0  ]
								+ vec[0  ][N-2][0  ]
								+ vec[0  ][N-1][1  ]);
	vec[0  ][0  ][N-1] = 0.33f * (vec[1  ][0  ][N-1]
								+ vec[0  ][1  ][N-1]
								+ vec[0  ][0  ][N-2]);
	vec[0  ][N-1][N-1] = 0.33f * (vec[1  ][N-1][N-1]
								+ vec[0  ][N-2][N-1]
								+ vec[0  ][N-1][N-2]);
	vec[N-1][0  ][0  ] = 0.33f * (vec[N-2][0  ][0  ]
								+ vec[N-1][1  ][0  ]
								+ vec[N-1][0  ][1  ]);
	vec[N-1][N-1][0  ] = 0.33f * (vec[N-2][N-1][0  ]
								+ vec[N-1][N-2][0  ]
								+ vec[N-1][N-1][1  ]);
	vec[N-1][0  ][N-1] = 0.33f * (vec[N-2][0  ][N-1]
								+ vec[N-1][1  ][N-1]
								+ vec[N-1][0  ][N-2]);
	vec[N-1][N-1][N-1] = 0.33f * (vec[N-2][N-1][N-1]
								+ vec[N-1][N-2][N-1]
								+ vec[N-1][N-1][N-2]);
}
