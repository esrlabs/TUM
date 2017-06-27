/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#ifndef I_CAN_TRANSCEIVER_H_
#define I_CAN_TRANSCEIVER_H_

#include "can/canframes/CANFrame.h"

namespace can
{
class ICANTransceiver
{
public:
	enum ErrorCode
	{
		CAN_ERR_OK,
		CAN_ERR_TX_FAIL
	};

	virtual ErrorCode init() = 0;

	virtual void shutdown() = 0;

	virtual ErrorCode open() = 0;

	virtual ErrorCode close() = 0;

	virtual ErrorCode mute() = 0;

	virtual ErrorCode unmute() = 0;

	virtual ErrorCode write(const can::CANFrame& frame) = 0;

	virtual uint32 getBaudrate() const = 0;

	virtual uint16 getHwQueueTimeout() const = 0;

};
} // namespace can
#endif /* end of include guard */

