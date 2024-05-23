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

	//doob::createTestWindow();
	/*doob::testFrame mainFrame(400, 800, "Doob Bloom");
	mainFrame.createTestFrame();*/
	doob::dGenericFrame mainFrame(400, 800, "Doob Bloom");
	mainFrame.createGenericFrame();
	
	bool isRunning = true;

	while (isRunning) {
		//DB_INFO("did it work");
		//doob::testWindowSwapBuffer();
		//doob::testWindowPoll();

		/*mainFrame.testFrameUpdateBegin();
		mainFrame.testFrameUpdateEnd();

		if (mainFrame.testFrameShouldClose()) {
			isRunning = false;
			mainFrame.testFrameShutdown();
		}*/

		mainFrame.genericFrameUpdateBegin();
		mainFrame.genericFrameUpdateEnd();

		if (mainFrame.genericFrameShouldClose()) {
			isRunning = false;
			mainFrame.genericFrameShutdown();
		}

	}
	doob::shutdownGlfw();

	return 0;
}