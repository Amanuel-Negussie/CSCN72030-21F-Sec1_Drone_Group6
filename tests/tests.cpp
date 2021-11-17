#include "pch.h"
#include "CppUnitTest.h"
#include "batteryWater.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BatteryWater
{
	TEST_CLASS(tempSensorTests)
	{
	public:

		TEST_METHOD(constructorValidID)
		{
			connection* con = new connection("a1", "A2");
			tempSensor* test = new tempSensor("001", con);
			Assert::AreEqual((string)"001", test->getID());

		}
		TEST_METHOD(constructorValidConnection)
		{
			connection* con = new connection("a1", "A2");
			tempSensor* test = new tempSensor("001", con);
			if (con->point1 == "a1") {
				if (con->point2 == "a2") {
					
				}
				else {
					Assert::Fail;
				}
			}
			else {
				Assert::Fail;
			}
		}
		TEST_METHOD(getTempValidRange50Runs)
		{
		}
		TEST_METHOD(isOnlineHasOneOffline)
		{
		}
		TEST_METHOD(getValidID)
		{
		}
	};

	TEST_CLASS(sonarSensorTests)
	{
	public:
		TEST_METHOD(constructorValidID)
		{
		}
		TEST_METHOD(constructorValidConnection)
		{
		}
		TEST_METHOD(getTimeValidCapacity)
		{
		}
		TEST_METHOD(isOnlineHasOneoffline)
		{
		}
		TEST_METHOD(getValidID)
		{
		}
	};

	TEST_CLASS(connectionTests)
	{
	public:
		TEST_METHOD(ContructorValidPointOne)
		{
		}
		TEST_METHOD(ContructorValidPointTwo)
		{
		}
		TEST_METHOD(testConnectionOneInvalid20Runs)
		{
		}
	};

	TEST_CLASS(batteryWaterTests)
	{
	public:
		TEST_METHOD(initializerProperCapacityWater)
		{
		}
		TEST_METHOD(initializerProperCapacityBattery)
		{

		}
		TEST_METHOD(initializerPadConnected)
		{
		}
		TEST_METHOD(initializerCharging)
		{
		}
		TEST_METHOD(initializerDoorClosed)
		{
		}
		TEST_METHOD(initializerProperMaxTemp)
		{
		}
		TEST_METHOD(initializerProperBatteryWarning)
		{
		}
		TEST_METHOD(initializerProperWaterWarning)
		{
		}
		TEST_METHOD(update100BatteryDead)
		{
		}
		TEST_METHOD(update100TempWarningShown)
		{
		}
		TEST_METHOD(update100DamagedSensorWarningShown)
		{
		}
		TEST_METHOD(update100batteryWarningShown)
		{
		}
		TEST_METHOD(update100WaterStaysSame)
		{
		}
		TEST_METHOD(swapBatteryCurrentTo100Percent)
		{
		}
		TEST_METHOD(isChargingWhenConnected)
		{
		}
		TEST_METHOD(isChargingWhenDisconnected)
		{
		}
		TEST_METHOD(getCurrentWaterStorage)
		{
		}
		TEST_METHOD(getCurrentBattery)
		{
		}
		TEST_METHOD(fillWaterLessThenCurrentCapacity)
		{
		}
		TEST_METHOD(fillWaterHigherThenMaxCapacity)
		{
		}
		TEST_METHOD(fillWaterValidRangeHigherThenCurrentCapacity)
		{
		}
		TEST_METHOD(drainWaterZeroPercent)
		{
		}
		TEST_METHOD(startChargingConnectsToPad)
		{
		}
		TEST_METHOD(startChargingBeginsCharge)
		{
		}
		TEST_METHOD(startChargingIncreasesBattery)
		{
		}
		TEST_METHOD(endChargingStopsCharge)
		{
		}
		TEST_METHOD(endChargingDisconnectsBase)
		{
		}
		TEST_METHOD(endChargingBatteryDoesNotChange)
		{
		}
		TEST_METHOD(saveSuccess)
		{
		}
		TEST_METHOD(getFlightEstimate)
		{
		}
		TEST_METHOD(decreaseBattery4_3)
		{
		}
		TEST_METHOD(decreaseBattery8_3)
		{
		}
		TEST_METHOD(decreaseBattery12_3)
		{
		}
		TEST_METHOD(decreaseBattery16_3)
		{
		}
		TEST_METHOD(decreaseBattery20_3)
		{
		}
	};
}


namespace Flight
{
	TEST_CLASS(tests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		}
	};
}
namespace Navigation
{
	TEST_CLASS(tests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		}
	};
}
