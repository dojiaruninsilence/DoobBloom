#pragma once

class dApplication {
public:
	dApplication();
	virtual ~dApplication();

	void run();
};

dApplication* createApplication();