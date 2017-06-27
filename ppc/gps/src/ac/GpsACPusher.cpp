/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#include "gps/AcPusher.h"
#include "android/caim/base/ICaimTransceiver.h"
#include "util/endian.h"

namespace gps
{

void GpsAcPusher::pushGPSCoordinates(sint32 latMs, sint32 longMs)
{
	uint8 newPosition[sizeof(fPosition)];

	writeMem32(newPosition + LONGITUDE_OFFSET, longMs);
	writeMem32(newPosition + LATITUDE_OFFSET, latMs);

	writeMem16(newPosition + HEIGHT_OFFSET, 0);
	writeMem16(newPosition + SPEED_OFFSET, 0);
	newPosition[HEADING_OFFSET] = 0;
	writeMem16(newPosition + QUALITY_OFFSET, 0);

	if (memcmp(newPosition, fPosition, sizeof(fPosition)))
	{
		memcpy(fPosition, newPosition, sizeof(fPosition));
		fCaimTransceiver.push(POSITION_COMMAND, fPosition, sizeof(fPosition));
	}
}
} // namespace gps

