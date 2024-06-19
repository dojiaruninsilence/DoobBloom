#include "dbpch.h"

#include "dOscilloscope.h"

#include <gl/GL.h>

namespace doob {

	dOscilloscope::dOscilloscope(size_t bufferSize) : m_buffer(bufferSize), m_id() {
		// initialize the buffer to zero
		for (size_t i = 0; i < bufferSize; ++i) {
			m_buffer.add(0.0f);
		}
	}

	dOscilloscope::~dOscilloscope() {

	}

	const dUuid& dOscilloscope::getId() const {
		return m_id;
	}

	void dOscilloscope::addSample(float sample) {
		m_buffer.add(sample);
		// DB_INFO(sample);
	}

	const dVector<float>& dOscilloscope::getBuffer() const {
		return m_buffer.getBuffer();
	}

	void dOscilloscope::printBuffer() const {
		return m_buffer.printBuffer();
	}

	void dOscilloscope::render() const {
		glBegin(GL_LINE_STRIP);
		const auto& data = m_buffer.getBuffer();
		size_t size = m_buffer.isFull() ? data.getSize() : m_buffer.head();
		for (size_t i = 0; i < size; ++i) {
			float x = (float)i / size * 2.0f - 1.0f;
			float y = data[i];
			glVertex2f(x, y);
		}
		glEnd();
	}
}