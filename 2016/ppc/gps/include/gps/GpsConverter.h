/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#ifndef GPSCONVERTER_H_
#define GPSCONVERTER_H_

#include "commonTypes.h"
#include "can/framemgmt/ICANFrameListener.h"
#include "can/filter/IntervalFilter.h"

namespace can
{
class CANFrame;
class ICANTransceiver;
}
namespace gps
{
class IGpsACPusher;

class GpsConverter :
	public can::ICANFrameListener
{
public:
	enum { GPS_FRAME_ID = 0x34a }; //NavGps1
	GpsConverter(can::ICANTransceiver& transceiver, IGpsACPusher& acPusher);

	/* ICANFrameListener */
	virtual void frameReceived(const can::CANFrame& canFrame);
	virtual can::IFilter& getFilter()
	{
		return fCanFilter;
	}

private:
	can::ICANTransceiver& fCanTransceiver;
	can::IntervalFilter	fCanFilter;

	IGpsACPusher& fAcPusher;
	sint32 fLastLatInMs;
	sint32 fLastLongInMs;
};

} // namespace gps
#endif /* end of include guard */

