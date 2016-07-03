#ifndef CANTRANSCEIVER_MOCK_H_
#define CANTRANSCEIVER_MOCK_H_

#include "can/ICANTransceiver.h"
#include "busId/BusId.h"

namespace can
{

class CanTransceiverMock
	: public ICANTransceiver
{
public:
	CanTransceiverMock()
	{}
	virtual ErrorCode init()
	{
		return CAN_ERR_OK;
	}
	virtual void shutdown() {}
	virtual ErrorCode open()
	{
		return CAN_ERR_OK;
	}
	virtual ErrorCode close()
	{
		return CAN_ERR_OK;
	}
	virtual ErrorCode mute()
	{
		return CAN_ERR_OK;
	}
	virtual ErrorCode unmute()
	{
		return CAN_ERR_OK;
	}
	virtual ErrorCode write(const can::CANFrame& frame)
	{
		return CAN_ERR_OK;
	}
	virtual uint32 getBaudrate() const
	{
		return 500000;
	}
	virtual uint16 getHwQueueTimeout() const
	{
		return 50;
	}
};
} // namespace can
#endif /* end of include guard */


