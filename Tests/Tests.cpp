#include "pch.h"
#include "CppUnitTest.h"
#include "batteryWater.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace batteryWaterTests
{


	TEST_CLASS(connectionOBJTests)
	{
	public:
		
		TEST_METHOD(initializer_point1)
		{
			char* p1 = "A1";
			char* p2 = "A2";
			connection* test = new connection(p1,p2);
			
		
			Assert::AreEqual(test->point1, "A1");
		
			
		}
		TEST_METHOD(initializer_point2)
		{
			char* p1 = "A1";
			char* p2 = "A2";
			connection* test = new connection(p1, p2);


			Assert::AreEqual(test->point2, "A2");


		}
	};
}
