/**
 * \copyright
 * (c) 2012 - 2015 E.S.R. Labs GmbH (http://www.esrlabs.com)
 * All rights reserved.
 */

/**
 * Contains interface ICANFrameListener.
 * @file 		ICANFrameListener.h
 * @ingroup		framemgmt
 */
#ifndef ICANFRAMELISTENER_H
#define ICANFRAMELISTENER_H

#include "util/SLinkedListSet.h"
#include "util/Uncopyable.h"

namespace can
{
class CANFrame;
class IFilter;

/**
 * CANFrameListener interface
 * @author		matthias.kessler
 *
 * An ICANFrameListener subclass is a class interested in the reception
 * of CANFrames. Therefore it needs to register at an AbstractCANTransceiver.
 */
class ICANFrameListener :
	public SLinkedListSetNode<ICANFrameListener>
{
	MAKE_UNCOPYABLE(ICANFrameListener)
public:
	ICANFrameListener() {}

	/**
	 * This method notifies the listener of a CANFrame reception.
	 */
	virtual void frameReceived(const CANFrame& canFrame) = 0;

	/**
	 * Returns the ICANFrameListeners filter.
	 */
	virtual IFilter& getFilter() = 0;
};

} //namespace can

#endif // ICANFRAMELISTENER_H
