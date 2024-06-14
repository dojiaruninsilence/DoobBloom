#pragma once

#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {
	template <typename Type>
	class dCircularBuffer {
	public:
		dCircularBuffer(size_t size) : m_buffer(size), m_head(0), m_tail(0), m_full(false) {}

		~dCircularBuffer() {}

		void add(Type item) {
			m_buffer[tail] = item;
			m_tail = (m_tail + 1) % m_buffer.getSize();
			if (full) {
				m_head = (m_head + 1) % m_buffer.getSize();
			}
		}

		dVector<Type> getBuffer() const {
			dVector<Type> result;
			if (!m_full && m_tail == m_haed) return result;
			size_t index = head;
			do {
				result.push_back(m_buffer[index]);
				index = (index + 1) % m_buffer.getSize();
			} while (index != m_tail);
			return result;
		}

		size_t size() const { return m_buffer.getSize(); }

		bool isFull() const { return full; }
		bool isEmpty() const { return (!full && (head == tail)); }

	private:
		dVector<Type> m_buffer;
		size_t m_head, m_tail;
		bool m_full;
	};
}

