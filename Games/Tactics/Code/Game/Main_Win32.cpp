#include <cmath>
#include <cassert>
#include <crtdbg.h>

#include "Engine/Core/WindowsLean.hpp"

#include "Engine/Core/TypedProperties.hpp"
#include "Engine/Core/BitSet.hpp"
#include "Engine/Math/Vectors.hpp"
#include "Engine/Math/Matrix.hpp"

#include "Engine/Events/EventSystem.hpp"

#include "Engine/Async/Thread.hpp"
#include "Engine/Async/Containers/ThreadSafeQueue.hpp"
#include "Engine/Jobs/JobSystem.hpp"

#include "Engine/Rendering/RGBA.hpp"




bool EventTest(TypedProperties& args)
{
	int i = args.Get("intVal", 1);
	return false;
}

class TestClass
{
public:
	bool TestMemberFunction(TypedProperties& args)
	{
		int z = args.Get("intVal", 1);
		int i = z;
		return false;
	}
};


//-----------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE applicationInstanceHandle, HINSTANCE, LPSTR commandLineString, int)
{
	mat4 Ry_90 = mat4::CreateRotationYDegrees(90.0f);
	vec4 p = vec4(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 p2 = Mul(Ry_90, p);






	TestClass tc;

	EventSystem es;
	es.SubscribeEventCallbackFunction("Sunrise", EventTest);
	es.SubscribeEventCallbackMemberFunction("Sunrise", &tc, &TestClass::TestMemberFunction);

	TypedProperties args;
	args.Set("intVal", 15);
	es.FireEvent("Sunrise", args);




	std::string lastName = "Eiserloh";
	int ivals[7] = {1,2,3,4,5,6,7};

	TypedProperties props;
	props.Set("FirstName", "Squirrel"); 	// Setting as c-string (const char*) data...
	props.Set("LastName", lastName);		// Setting as std::string data...
	props.Set("Height", 1.93f);
	props.Set("Age", 45);
	props.Set("IsMarried", true);
	props.Set("Position", vec2(3.5f, 6.2f));
	props.Set("EyeColor", rgba(.25f, .1f, .8f));
	props.Set("ivals", (int*)ivals);
	props.Set("floatVal", 1.2f);



	std::string firstName	= props.Get("FirstName", "help");
	std::string nlastName	= props.Get("LastName", lastName);
	float height			= props.Get("Height", 5.0f);
	int age					= props.Get("Age", 5);
	bool isMarried			= props.Get("IsMarried", false);
	vec2 pos				= props.Get("Position", vec2(0.0f,0.0f));
	rgba eyeColor			= props.Get("EyeColor", rgba());
	int* ivalsOut			= props.Get("ivals", nullptr);
	ivalsOut				= props.Get<int*>("ivals", nullptr);
	float floatVal			= props.Get("floatVal", 5.0f);

	return 0;
}