/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains Cpp2CAN CANFrame.
 * @file 		CANFrame.h
 * @ingroup		cpp2can
 */
#ifndef CANFRAME_H
#define CANFRAME_H

#include "commonTypes.h"
#include <cassert>

namespace can
{

/**
 * Class representing a CANFrame.
 * @author		matthias.kessler
 *
 * A object of type CANFrame does not provide any payload-buffer by default.
 * It has to be provided with buffers by using a certain constructor or the
 * setPayload() method.
 *
 * @note
 * CANFrame may be used as base class for special frame classes providing
 * the programmer with explicit methods to access the signals that are
 * encoded in the CANFrames payload.
 */
class CANFrame
{
public:
	/** bitmask to extract sender */
	static const uint8 	SENDER_MASK 		= 0xFF;
	/** overhead of a CANFrame (in bit) */
	static const uint8 	CAN_OVERHEAD_BITS	= 47;
	/** maximum payload length of a CANFrame */
	static const uint8	MAX_FRAME_LENGTH	= 8;
	/** maximum value of a CANFrame id */
	static const uint16 MAX_FRAME_ID		= 0x7FF;

	/**
	 * @post	getId() == 0x00
	 * @post	getPayload() == NULL
	 * @post	getPayloadLength() == 0
	 * @post	getTimestamp() == 0
	 */
	CANFrame();

	/**
	 * Copy constructor
	 * @param	frame	CANFrame to copy content from
	 */
	CANFrame(const CANFrame& frame);

	/**
	 * Constructor initializing id, payload and length
	 *
	 * @pre		id <= MAX_FRAME_ID
	 * @pre		length <= MAX_FRAME_LENGTH
	 * @throws	assertion
	 *
	 * The payload will not be copied, it is passed as a
	 * reference and CANFrame will work on this payload!
	 */
	CANFrame(uint16 id, uint8 payload[], uint8 length);

	uint16 	getId() const
	{
		return fId;
	}

	void setId(uint16 id)
	{
		this->fId = id;
	}

	/**
	 * @return	pointer to modifiable payload of this CANFrame
	 */
	uint8* getPayload()
	{
		return fpPayload;
	}

	/**
	 * @return	pointer to read only payload of this CANFrame
	 */
	const uint8* getPayload() const
	{
		return fpPayload;
	}

	/**
	 * Sets the CANFrames payload and length
	 *
	 * @note
	 * This method just sets a pointer to the payload and does not copy it!
	 *
	 * @post	getPayload() == payload
	 * @post	getPayloadLength() == length
	 * @post	getMaxPayloadLength() == length
	 */
	void setPayload(uint8 payload[], uint8 length)
	{
		fpPayload = payload;
		fPayloadLength = length;
		fMaxPayloadLength = length;
	}

	/**
	 * @pre		getPayload() != NULL
	 * @pre		length <= getMaxPayloadLength()
	 * @throws	assertion
	 */
	void setPayloadLength(uint8 length);

	uint8 getPayloadLength() const
	{
		return fPayloadLength;
	}

	uint8 getMaxPayloadLength() const
	{
		return fMaxPayloadLength;
	}

	/**
	 * Assigns content of a CANFrame to another.
	 * @param	canFrame	frame to copy from
	 * @return	reference to frame with new content
	 * @pre		getMaxPayloadLength() >= canFrame.getPayloadLength()
	 * @throws	assertion
	 */
	CANFrame& operator=(const CANFrame& canFrame);

	/**
	 * @return	modifiable reference to timestamp
	 */
	uint64& getTimestamp()
	{
		return fTimestamp; // PRQA S 4024
	}

	/**
	 * @return	read only access to timestamp
	 */
	const uint64& getTimestamp() const
	{
		return fTimestamp;
	}

	bool isExtended() const { return false; } /* TODO: cleanup */

protected:
	friend bool operator==(const CANFrame& frame1, const CANFrame& frame2);

	uint8* 	fpPayload;
	uint16 	fId;
	uint8 	fPayloadLength;
	uint8 	fMaxPayloadLength;
	uint64	fTimestamp;
};

/**
 * Compares two CANFrames without considering the timestamp
 * @param	frame1	first frame to compare
 * @param	frame2	second frame to compare
 * @return
 * 			- true if frames are equal
 * 			- false if frames are not equal
 */
bool operator==(const CANFrame& frame1, const CANFrame& frame2);

} /* namespace can */

#endif /* CANFRAME_H */
