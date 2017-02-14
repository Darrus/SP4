///////////////////////////////////////////////////////////////////////////////
/*!
\file   MyMath.h
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Header file for math helper functions
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef MY_MATH_H
#define MY_MATH_H

#include <cmath>
#include <exception>
#include <ctime>
#include <cstdlib>

/******************************************************************************/
/*!
\brief
Math namespace
*/
/******************************************************************************/
namespace Math
{

	const float	EPSILON    =	0.00001f;  ///Used for error checking
	const float	PI         = 3.1415926535897932384626433832795f;
	const float TWO_PI     = PI * 2.0f;
	const float HALF_PI    = PI / 2.0f;
	const float QUARTER_PI = PI / 4.0f;

	inline float FAbs(float value)
	{
		return (value < 0) ? -value : value;
	}

/******************************************************************************/
	/*!
	\brief
	Converts from degrees to radians

	\param value - an angle in degress

	\exception None
	\return the angle in radians
	*/
/******************************************************************************/
	inline float DegreeToRadian(float value)
	{
		return value * PI / 180.0f;
	}
/******************************************************************************/
	/*!
	\brief
	Converts from radians to degrees

	\param value - an angle in radians

	\exception None
	\return the angle in degrees
	*/
/******************************************************************************/
	inline float RadianToDegree(float value)
	{
		return value * 180.0f / PI;
	}
/******************************************************************************/
	/*!
	\brief
	Keeps a value between a min and max point.  If it goes to low, it will become
	the max.  If the value gets too high, it will become the min.

	\param val - the value to Wrap.
	\param minVal - the minimum value allowed.
	\param maxVal - the maximum value allowed.

	\exception None
	\return The wrapped value.
	*/
/******************************************************************************/
	template<typename T>
	T Wrap(T val, T minVal, T maxVal)
	{
		if (val < minVal)
		{
			return maxVal;
		}
		else if (val > maxVal)
		{
			return minVal;
		}

		return val;
	}
/******************************************************************************/
	/*!
	\brief
	Keeps a value between a min and max point.  If it goes to low, it will become
	the min.  If the value gets too high, it will become the max.

	\param val - the value to clamp.
	\param minVal - the minimum value allowed.
	\param maxVal - the maximum value allowed.

	\exception None
	\return The clampped value.
	*/
/******************************************************************************/
	template<typename T>
	T Clamp(T val, T minVal, T maxVal)
	{
		if (val < minVal)
		{
			return minVal;
		}
		else if (val > maxVal)
		{
			return maxVal;
		}

		return val;
	}
/******************************************************************************/
	/*!
	\brief
	Returns the smaller of the two values

	\param x the first value to check
	\param y the second value to check

	\exception None
	\return The smaller of the two values
	*/
/******************************************************************************/
	template<typename T>
	T Min(T x, T y)
	{
		return (x < y) ? x : y;
	}
/******************************************************************************/
	/*!
	\brief
	Returns the larger of the two values

	\param x the first value to check
	\param y the second value to check

	\exception None
	\return The larger of the two values
	*/
/******************************************************************************/
	template<typename T>
	T Max(T x, T y)
	{
		return (x > y) ? x : y;
	}
/******************************************************************************/
	/*!
	\brief
	Returns the square of a value

	\param x the value

	\exception None
	\return The square of the value
	*/
/******************************************************************************/
	template<typename T>
	T Square(T x)
	{
		return x * x;
	}
/******************************************************************************/
/*!
\brief
Initialize Random Number Generator

\param None
 
\exception None
\return None
*/
	inline void InitRNG(void)
	{
		srand (static_cast<unsigned> (time(0)));
	}//end of InitRNG function
	
/******************************************************************************/
/*!
\brief
Return a random integer

\param None
 
\exception None
\return Random integer
*/
	inline unsigned RandInt(void)
	{
		return rand();
	}//end of RandInt function
	
/******************************************************************************/
/*!
\brief
Return a random integer between min and max

\param min - minimum range
\param max - maximum range
 
\exception None
\return Random integer
*/
	inline int RandIntMinMax (int min, int max)
	{
		int num = rand() % (max - min + 1);
		return (num + min);
	}//end of RandIntMinMax function
	
/******************************************************************************/
/*!
\brief
Return a random float

\param None
 
\exception None
\return Random float
*/
	inline float RandFloat (void)
	{
		return rand() / static_cast <float> (RAND_MAX);
	}//end of RandFloat function
	
/******************************************************************************/
/*!
\brief
Return a random float between min and max

\param min - minimum range
\param max - maximum range
 
\exception None
\return Random float
*/
	inline float RandFloatMinMax (float min, float max)
	{
		float num = (max - min) * RandFloat ();
		return (num + min);
	}//end of RandFloatMinMax function

}//end namespace Math

/******************************************************************************/
/*!
		Class DivideByZero:
\brief	Exception for divide by zero
*/
/******************************************************************************/
class DivideByZero : public std::exception
{
public:
	const char* what() { return "Divide By Zero"; }
};


#endif /// MY_MATH_H



