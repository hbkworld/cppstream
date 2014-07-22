#include <stdint.h>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif

#include "TransportHeader.h"

namespace hbm {
	namespace streaming {
		TransportHeader::TransportHeader(SocketNonblocking& socket)
			: m_socket(socket)
		{
		}

		int TransportHeader::receive()
		{
			//big endian:
			// 12 bit signal info | 20 bit signal number

			// signal info
			// 2 bits reserved | 2 bits signal type | 8 bits size


			uint32_t headerBig;
			uint32_t header;

			ssize_t retVal = m_socket.receiveComplete(&headerBig, sizeof(headerBig));
			if(retVal!=sizeof(headerBig)) {
				return -1;
			}

			header = ntohl(headerBig);
			m_signalNumber =  header & 0x000fffff;
			m_type = (header & 0x30000000) >> 28;
			m_dataByteCount = (header & 0x0ff00000) >> 20;
			if(m_dataByteCount==0) {
				uint32_t additionalSizeBig;
				retVal = m_socket.receiveComplete(&additionalSizeBig, sizeof(additionalSizeBig));
				if(retVal!=sizeof(additionalSizeBig)) {
					return -1;
				}

				m_dataByteCount = ntohl(additionalSizeBig);
			}

			return 0;
		}
	}
}