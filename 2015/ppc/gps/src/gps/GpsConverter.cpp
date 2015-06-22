/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#include "gps/GpsConverter.h"
#include "ac/IGpsACPusher.h"
#include "can/canframes/CANFrame.h"
#include "can/ICANTransceiver.h"
#include <stdio.h>

using namespace can;

namespace gps
{

GpsConverter::GpsConverter(
		ICANTransceiver& transceiver,
		IGpsACPusher& acPusher)
	: fCanTransceiver(transceiver)
	, fCanFilter(GPS_FRAME_ID, GPS_FRAME_ID)
	, fAcPusher(acPusher)
{
}

void GpsConverter::frameReceived(const CANFrame& canFrame)
{
	const uint8* payload = canFrame.getPayload();
    // TOOD implement conversion to arc-msec and call IGpsACPusher
}


} // namespace gps


