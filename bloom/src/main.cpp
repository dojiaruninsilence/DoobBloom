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
	dDiagnostics::dLog::Init();
	DB_INFO("did it work");
	//printf("did it work");

	doob::initializeGlfw();
	doob::createTestWindow();
	while (!doob::testWindowShouldClose()) {
		//DB_INFO("did it work");
		doob::testWindowPoll();
		doob::testWindowSwapBuffer();

	}
}