#ifndef SIMULATION
#define SIMULATION

class simulation {
private:
	int x;

public:
	simulation()
	{
		x = 0;
	}

	void tick(float step);
};

#endif /*SIMULATION*/