#ifndef _HBM__STREAMING__TYPES
#define _HBM__STREAMING__TYPES

#include <vector>
#include <json/value.h>

namespace hbm {
	static const char PARAMS[] = "params";
	static const char METHOD[] = "method";



	namespace streaming {
		typedef std::vector < std::string > signalReferences_t;

		static const std::string DAQSTREAM_PORT = "7411";

		static const char META_METHOD_AVAILABLE[] = "available";
		static const char META_METHOD_UNAVAILABLE[] = "unavailable";
		static const char META_METHOD_ALIVE[] = "alive";
		static const char META_METHOD_FILL[] = "fill";
	}
}
#endif
