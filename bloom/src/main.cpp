#include "dbpch.h"

#include "dUtils/dOutwardIncludes.h"

//class bloom : public doob::dApplication {
//public:
//	bloom() {}
//
//	~bloom() {}
//};
//
//doob::dApplication* doob::createApplication() {
//	DB_TRACE("bloom created");
//	return new bloom();
//}

int main() {
	doob::dLog::Init();
	DB_INFO("did it work");
	//printf("did it work");

	if (!doob::initializeGlfw()) {
		DB_FATAL("Failed to initialize GLFW");
		return -1;
	}

	doob::createTestWindow();
	

	while (!doob::testWindowShouldClose()) {
		//DB_INFO("did it work");
		doob::testWindowSwapBuffer();
		doob::testWindowPoll();

	}
	doob::shutdownGlfw();
}