#include "dbpch.h"

#include "dOscilloscopeManager.h"

namespace doob {
	dOscilloscopeManager::dOscilloscopeManager(size_t bufferSize) : m_bufferSize(bufferSize) {

	}

	dOscilloscopeManager::~dOscilloscopeManager() {

	}

	dUuid dOscilloscopeManager::createOscilloscope() {
		dUuid id;
		if (m_oscilloscopes.find(id) == m_oscilloscopes.end()) {
			m_oscilloscopes[id] = std::make_unique<dOscilloscope>(m_bufferSize);
		}
		return id;
	}

	void dOscilloscopeManager::removeOscilloscope(const dUuid& id) {
		m_oscilloscopes.erase(id);
	}

	void dOscilloscopeManager::addSample(const dUuid& id, float sample) {
		if (m_oscilloscopes.find(id) != m_oscilloscopes.end()) {
			m_oscilloscopes[id]->addSample(sample);
		}
	}

	const dVector<float>& dOscilloscopeManager::getBuffer(const dUuid& id) const {
		static dVector<float> emptyBuffer;
		if (m_oscilloscopes.find(id) != m_oscilloscopes.end()) {
			return m_oscilloscopes.at(id)->getBuffer();
		}
		return emptyBuffer;
	}

	dOscilloscope* dOscilloscopeManager::getOscilloscope(const dUuid& id) {
		auto it = m_oscilloscopes.find(id);
		if (it != m_oscilloscopes.end()) {
			return it->second.get();
		}
		return nullptr;
	}

	void dOscilloscopeManager::renderAllOscilloscopes() {
		for (const auto& oscilloscope : m_oscilloscopes) {
			oscilloscope.second->render();
		}
	}
}