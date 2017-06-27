/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */
#ifndef AC_PUSHER_H_
#define AC_PUSHER_H_

#include "gps/IACPusher.h"

namespace android
{
class ICaimTransceiver;
}

namespace gps
{
class GpsAcPusher : public IACPusher
{
public:
	virtual void pushGPSCoordinates(sint32 latMs, sint32 longMs);
private:
	uint8 fPosition[15];
	ICaimTransceiver& fCaimTransceiver;
	static const uint8 LONGITUDE_OFFSET 							= 0;
	static const uint8 LATITUDE_OFFSET 								= 4;
	static const uint8 HEADING_OFFSET 								= 8;

	static const uint8 HEIGHT_OFFSET 								= 9;
	static const uint8 QUALITY_OFFSET 								= 11;
	static const uint8 SPEED_OFFSET 								= 13;
};
} // namespace gps

#endif /* end of include guard */

