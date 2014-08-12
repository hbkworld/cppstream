#ifdef _WIN32
#include "json/value.h"
#include "json/reader.h"
#include "json/writer.h"
#else
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#endif

#include "Controller.h"
#include "HttpPost.h"
#include "Types.h"

namespace hbm {
	namespace streaming {

		static const char ERROR[] = "error";
		static const char JSONRPC[] = "jsonrpc";

		unsigned int Controller::s_id = 0;

		Controller::Controller(const std::string& streamId, const std::string& address, const std::string& port, const std::string& path)
			: m_streamId(streamId)
			, m_address(address)
			, m_port(port)
			, m_path(path)
		{
		}

		int Controller::subscribe(const signalReferences_t &signalReferences)
		{
			if(signalReferences.empty()) {
				return 0;
			}
			Json::Value content;
			content[JSONRPC] = "2.0";
			content[METHOD] = m_streamId +".subscribe";
			for(signalReferences_t::const_iterator iter = signalReferences.begin(); iter!=signalReferences.end(); ++iter) {
				content[PARAMS].append(*iter);
			}
			content["id"] = ++s_id;

			std::string request = Json::FastWriter().write(content);

			HttpPost httpPost(m_address, m_port, m_path);
			std::string response = httpPost.execute(request);

			Json::Value result;
			if(Json::Reader().parse(response, result)==false) {
				return -1;
			}
			if(result.isMember(ERROR)) {
				return -1;
			}

			return 0;
		}

		int Controller::unsubscribe(const signalReferences_t &signalReferences)
		{
			if(signalReferences.empty()) {
				return 0;
			}
			Json::Value content;
			content[JSONRPC] = "2.0";
			content[METHOD] = m_streamId +".unsubscribe";
			for(signalReferences_t::const_iterator iter = signalReferences.begin(); iter!=signalReferences.end(); ++iter) {
				content[PARAMS].append(*iter);
			}
			content["id"] = ++s_id;

			std::string request = Json::FastWriter().write(content);

			HttpPost httpPost(m_address, m_port, m_path);
			std::string response = httpPost.execute(request);

			Json::Value result;
			if(Json::Reader().parse(response, result)==false) {
				return -1;
			}
			if(result.isMember(ERROR)) {
				return -1;
			}

			return 0;
		}

	}
}
