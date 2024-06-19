#pragma once

#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {
	template <typename Type>
	class dCircularBuffer {
	public:
		dCircularBuffer(size_t size) : m_buffer(size), m_head(0), m_tail(0), m_full(false) {}

		~dCircularBuffer() {}

		void add(Type item) {
			m_buffer[m_tail] = item;
			m_tail = (m_tail + 1) % m_buffer.getSize();

			if (m_full) {
				m_head = (m_head + 1) % m_buffer.getSize();
			}

			if (m_tail == m_head) {
				m_full = true;
			}
			else {
				m_full = false;
			}

			// DB_INFO(item);
		}

		dVector<Type> getBuffer() const {
			dVector<Type> result;
			if (!m_full && m_tail == m_head) return result;
			size_t index = m_head;
			do {
				result.push_back(m_buffer[index]);
				index = (index + 1) % m_buffer.getSize();
			} while (index != m_tail);
			return result;
		}

		void printBuffer() const {
			if (isEmpty()) {
				std::cout << "Buffer is empty" << std::endl;
				return;
			}

			size_t index = m_head;
			size_t count = 0;

			do {
				std::cout << "Buffer[" << count++ << "]: " << m_buffer[index] << std::endl;
				index = (index + 1) % m_buffer.getSize();
			} while (index != m_tail);
		}

		size_t size() const { return m_buffer.getSize(); }
		size_t head() const { return m_head; }
		size_t tail() const { return m_tail; }

		bool isFull() const { return m_full; }
		bool isEmpty() const { return (!m_full && (m_head == m_tail)); }

	private:
		dVector<Type> m_buffer;
		size_t m_head, m_tail;
		bool m_full;
	};
}

