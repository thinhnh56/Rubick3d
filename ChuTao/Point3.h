#pragma once
class Point3
{
public:
	/* 3 coordinate of the point*/
	float x, y, z;
	/* Set 3 coordinates of the point */
	void set(float dx, float dy, float dz);
	/* Set 3 coordinates of the point as the parameter point 'p'*/
	void set(Point3& p);

	/* Constructor with parameters are 3 coordinates*/
	Point3(float xx, float yy, float zz);
	/* Default constructor, 3 coordinates are equals to 0*/
	Point3();
	/* Copy constructor */
	Point3(Point3& p);

	~Point3();
};

