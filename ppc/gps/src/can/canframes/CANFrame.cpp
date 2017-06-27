/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

#include "can/canframes/CANFrame.h"

namespace can
{

//define const variables for GCC
#ifdef __GNUC__
const uint8 CANFrame::SENDER_MASK;
const uint8 CANFrame::CAN_OVERHEAD_BITS;
const uint8	CANFrame::MAX_FRAME_LENGTH;
const uint16 CANFrame::MAX_FRAME_ID;
#endif

CANFrame::CANFrame() :
	fpPayload(0L),
	fId(0),
	fPayloadLength(0),
	fMaxPayloadLength(0),
	fTimestamp(0)
{}

CANFrame::CANFrame(const CANFrame& frame) :
	fpPayload(frame.fpPayload),
	fId(frame.fId),
	fPayloadLength(frame.fPayloadLength),
	fMaxPayloadLength(frame.fMaxPayloadLength),
	fTimestamp(frame.fTimestamp)
{
}

CANFrame::CANFrame(uint16 id, uint8 payload[], uint8 length) :
	fpPayload(payload),
	fId(id),
	fPayloadLength(length),
	fMaxPayloadLength(length)
{
	assert(id <= MAX_FRAME_ID);
	assert(length <= MAX_FRAME_LENGTH);
}

CANFrame& CANFrame::operator=(const CANFrame& canFrame)
{
	if (&canFrame != this)
	{
		if (fMaxPayloadLength < canFrame.fPayloadLength)
		{
			assert(fMaxPayloadLength >= canFrame.fPayloadLength);
		}
		fId = canFrame.fId;
		for (uint8 i = 0; i < canFrame.fPayloadLength; ++i)
		{
			fpPayload[i] = canFrame.fpPayload[i];
		}
		fPayloadLength = canFrame.fPayloadLength;
		fTimestamp = canFrame.fTimestamp;
	}
	return *this;
}

void CANFrame::setPayloadLength(uint8 length)
{
	if (!fpPayload)
	{
		assert(fpPayload != 0L);
	}
	if (length > fMaxPayloadLength)
	{
		assert(length <= fMaxPayloadLength);
	}
	fPayloadLength = length;
}

bool operator==(const CANFrame& frame1, const CANFrame& frame2)
{
	if (frame1.fId != frame2.fId)
	{
		return false;
	}
	if (frame1.fPayloadLength != frame2.fPayloadLength)
	{
		return false;
	}
	for (uint8 i = 0; i < frame1.fPayloadLength; i++)
	{
		if (frame1.fpPayload[i] != frame2.fpPayload[i])
		{
			return false;
		}
	}
	return true;
}

} //namespace can
