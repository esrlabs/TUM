/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */
#ifndef IAC_PUSHER_H_
#define IAC_PUSHER_H_

#include "commonTypes.h"

namespace gps
{
class IGpsACPusher
{
public:
	virtual void pushGPSCoordinates(sint32 latMs, sint32 longMs) = 0;

};
} // namespace gps
#endif /* end of include guard */

