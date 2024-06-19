#pragma once

#include "dUtils/dUuid.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {
	class dGenericFrame {
	public:
		dGenericFrame(int width, int height, const char* name)
			: m_width(width), m_height(height), m_name(name) {}

		~dGenericFrame() {};

		void createGenericFrame();

		bool genericFrameShouldClose();

		void genericFrameUpdateBegin();
		void genericFrameUpdateEnd();

		void genericFrameShutdown();

	private:
		int m_width;
		int m_height;
		int m_fbWidth;
		int m_fbHeight;
		int m_xPos;
		int m_yPos;
		const char* m_name;

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

		bool m_isDocked = false;

		dUuid m_oscId;
	};
}