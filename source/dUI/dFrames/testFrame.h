#pragma once

#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {
	class testFrame {
	public:
		testFrame(int width, int height, const char* name)
			: m_width(width), m_height(height), m_name(name) {}

		~testFrame() {}

		void createTestFrame();

		bool testFrameShouldClose();

		void testFrameUpdateBegin();
		void testFrameUpdateEnd();

		void testFrameShutdown();

	private:
		int m_width;
		int m_height;
		int m_nextWidth;
		int m_nextHeight;
		int m_windowWidth;
		int m_windowHeight;
		int m_fbWidth;
		int m_fbHeight;
		int m_xPos;
		int m_yPos;
		int m_windowXPos;
		int m_windowYPos;
		const char* m_name;

		int m_counter;

		bool m_isDragging = false;
		bool m_titleDrag = false;
		bool m_leftEdgeDrag = false;
		bool m_leftCornerDrag = false;
		bool m_bottomDrag = false;
		bool m_rightEdgeDrag = false;
		bool m_rightCornerDrag = false;

		dVec2<float> m_initialMousePos;
		dVec2<float> m_initialWindowPos;
		dVec2<float> m_initialWindowSize;
		dVec2<float> m_mouseDelta;
	};
}