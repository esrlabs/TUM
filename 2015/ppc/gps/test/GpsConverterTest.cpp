#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "commonTypes.h"
#include "can/canframes/CANFrame.h"
#include "gps/GpsConverter.h"
#include "ac/IGpsACPusher.h"
#include "CanTransceiverMock.h"
#include "busId/BusId.h"

using namespace gps;
using namespace common;
using namespace can;

namespace test
{

class GpsAcPusherMock : public gps::IGpsACPusher
{
public:
	GpsAcPusherMock()
		: gpsWasSet(false)
	{}
	virtual void pushGPSCoordinates(sint32 latMs, sint32 longMs)
	{
		printf("pushGPSCoordinates received: %d and %d\n", latMs, longMs);
		gpsWasSet = true;
		latitudeMs = latMs;
		longitudeMs = longMs;
	}
	void clear()
	{
		gpsWasSet = false;
		latitudeMs = 0;
		longitudeMs = 0;
	}
	sint32 latitudeMs;
	sint32 longitudeMs;
	bool gpsWasSet;
};
class GpsConverterTest
{
public:
	GpsConverterTest()
		: canTransceiverMock()
		, converter(canTransceiverMock, acPusherMock)
	{}

	virtual ~GpsConverterTest() {}

	can::CanTransceiverMock canTransceiverMock;
	GpsAcPusherMock acPusherMock;
	GpsConverter converter;
};

static bool withinTolerance(sint32 x1, sint32 x2, sint32 tolerance)
{
	return abs(x1-x2) < tolerance;
}

TEST_CASE_METHOD(GpsConverterTest, "london east calling", "[gps]")
{
	uint8 payload[8] = { 0xDF, 0x48, 0xEA, 0xFF, 0x08, 0xC5, 0xA5, 0x24 };
	CANFrame gpsInfo(0x34a, payload, 8);
	converter.frameReceived(gpsInfo);
	CHECK(acPusherMock.gpsWasSet);
	CHECK(withinTolerance(acPusherMock.latitudeMs, 185528159, 100));
	CHECK(withinTolerance(acPusherMock.longitudeMs, -429429, 100));
}

TEST_CASE_METHOD(GpsConverterTest, "london west calling", "[gps]")
{
	uint8 payload[8] = { 0x1F, 0xB7, 0x15, 0x00, 0x08, 0xC5, 0xA5, 0x24 };
	CANFrame gpsInfo(0x34a, payload, 8);
	converter.frameReceived(gpsInfo);
	SECTION("receive once")
	{
		CHECK(acPusherMock.gpsWasSet);
		CHECK(withinTolerance(acPusherMock.latitudeMs, 185528159, 100));
		CHECK(withinTolerance(acPusherMock.longitudeMs, 429428, 100));
	}
	SECTION("receive twice same value, only propagate once")
	{
		CHECK(acPusherMock.gpsWasSet);
		CHECK(withinTolerance(acPusherMock.latitudeMs, 185528159, 100));
		CHECK(withinTolerance(acPusherMock.longitudeMs, 429428, 100));
		acPusherMock.clear();
		converter.frameReceived(gpsInfo);
		CHECK(!acPusherMock.gpsWasSet);
	}
}
TEST_CASE_METHOD(GpsConverterTest, "invalid data", "[gps]")
{
	uint8 payload[8] = { 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80 };
	CANFrame gpsInfo(0x34a, payload, 8);
	converter.frameReceived(gpsInfo);
	CHECK(!acPusherMock.gpsWasSet);
}
TEST_CASE_METHOD(GpsConverterTest, "no signal", "[gps]")
{
	uint8 payload[8] = { 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F };
	CANFrame gpsInfo(0x34a, payload, 8);
	converter.frameReceived(gpsInfo);
	CHECK(!acPusherMock.gpsWasSet);
}
// 48.1172966,11.5913253
// 48.1173275,11.591452

} // namespace test


