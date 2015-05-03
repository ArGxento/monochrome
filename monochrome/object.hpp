#pragma once
#include<cmath>

struct Vector {
	double x = 0.0;
	double y = 0.0;
	Vector(double x_, double y_): x(x_), y(y_) {}
	Vector() {}
};

class Mirror {
public:
	static const int width = 64;
	Vector location;
	Vector normal;
	Mirror(Vector location_, Vector normal_): location(location_), normal(normal_) {}
private:
	Mirror() {}
};

class Ray {
public:
	static const int radius = 32;
	Vector location;
	Vector vector;
	bool isHittable;
	Ray(Vector location_, Vector vector_): location(location_), vector(vector_) {}
	bool isHit(Mirror const& m) const {
		double const vrad = std::atan2(vector.y, vector.x);
		Vector const rayDiameter(std::cos(vrad) * 2.0 * radius, std::sin(vrad) * 2.0 * radius);
		Vector const rayStartPos();
	}
private:
	Ray() {}
};
