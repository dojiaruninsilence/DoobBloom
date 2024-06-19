#pragma once

#include "dUtils/dMath/dGeneralMath/dRng.h"

#include <sstream>
#include <iomanip>

namespace doob {
	class dUuid {
	public:
		dUuid() {
			// initialize the rng for generating uuid parts
			dRng<unsigned int> rng;

			std::stringstream ss;
			ss << std::hex << std::setw(8) << std::setfill('0') << rng.next(0, 0xFFFFFFFF);
			ss << "-";
			ss << std::hex << std::setw(4) << std::setfill('0') << rng.next(0, 0xFFFF);
			ss << "-";
			ss << std::hex << std::setw(4) << std::setfill('0') << rng.next(0, 0xFFFF);
			ss << "-";
			ss << std::hex << std::setw(4) << std::setfill('0') << rng.next(0, 0xFFFF);
			ss << "-";
			ss << std::hex << std::setw(12) << std::setfill('0') << rng.next(0, 0xFFFFFFFF) << rng.next(0, 0xFFFFFFFF) << rng.next(0, 0xFFFFFFFF);

			id = ss.str();
		}

		const std::string& str() const {
			return id;
		}

		bool operator==(const dUuid& other) const {
			return id == other.id;
		}

		bool operator!=(const dUuid& other) const {
			return id != other.id;
		}

	private:
		std::string id;
	};
}

namespace std {
	template <>
	struct hash<doob::dUuid> {
		std::size_t operator()(const doob::dUuid& uuid) const {
			return std::hash<std::string>()(uuid.str());
		}
	};
}