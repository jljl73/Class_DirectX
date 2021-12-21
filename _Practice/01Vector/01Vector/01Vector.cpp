#include <iostream>
#include "cVector3.h"
#include "Global.h"

using namespace std;

int main()
{
	cVector3 vec1(1.0f, 0.0f, 0.0f);
	cVector3 vec2(0.0f, 1.0f, 0.0f);

	cout << "vec1 == vec2 : " << (vec1 == vec2) << endl;
	cout << "vec1 != vec2 : " << (vec1 != vec2) << endl;

	cVector3 vec3 = vec1 + vec2;
	printf(" vec1 + vec2 : (%f, %f, %f)\n", vec3.x, vec3.y, vec3.z);

	cVector3 vec4 = vec1 - vec2;
	printf(" vec1 - vec2 : (%f, %f, %f)\n", vec4.x, vec4.y, vec4.z);

	float dot = cVector3::Dot(vec1, vec2);
	cout << " vec1 * vec2 : " << dot << endl;

	cVector3 vecCross = cVector3::Cross(vec1, vec2);
	printf(" vec1 x vec2 : (%f , %f, %f) \n", vecCross.x, vecCross.y, vecCross.z);

	cVector3 vecCross2 = cVector3::Cross(vec2, vec1);
	printf(" vec2 x vec1 : (%f, %f, %f) \n", vecCross2.x, vecCross2.y, vecCross2.z);

	return 0;
}

