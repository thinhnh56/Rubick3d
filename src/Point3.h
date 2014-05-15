#pragma once
/*class Point3
{
public:
	 3 coordinate of the point
	float x, y, z;
	 Set 3 coordinates of the point
	void set(float dx, float dy, float dz);
	 Set 3 coordinates of the point as the parameter point 'p'
	void set(Point3& p);

	 Constructor with parameters are 3 coordinates
	Point3(float xx, float yy, float zz);
	 Default constructor, 3 coordinates are equals to 0
	Point3();
	 Copy constructor
	Point3(Point3& p);

	~Point3();
};*/

class Point3{
 public:
  float x,y,z;

  Point3(float xx, float yy, float zz){
	  x = xx; y = yy; z = zz;
  }
  Point3(){x = y = z = 0;}

  void build4tuple(float v[])
    {
      // load 4-tuple with this color: v[3] = 1 for homogeneous
      v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
    }
  void set(float dx, float dy, float dz){x = dx; y = dy; z = dz;}
  void set(Point3& p){x = p.x; y = p.y; z = p.z;}
};
