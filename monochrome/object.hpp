#pragma once
#include<cmath>

struct Vector {
	double x = 0.0;
	double y = 0.0;
	static double const cross(Vector const& v1, Vector const& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	Vector(double x_, double y_): x(x_), y(y_) {}
	Vector() {}
};

class Mirror {
public:
	static const int width = 64;
	Vector location;
	Vector normal;
	Mirror(Vector const location_, Vector const normal_): location(location_), normal(normal_) {}
private:
	Mirror() {}
};

class Ray {
public:
	static const int radius = 32;
	static const int speed = 3;
	Vector location;
	Vector vector;
	bool isHittable;
	Ray(Vector const location_, Vector const vector_): location(location_), vector(vector_) {}
	bool isHit(Mirror const& m) const {
		double const eps = 0.0001;

		double const vrad = std::atan2(vector.y, vector.x);
		Vector const rayDiameter(std::cos(vrad) * 2.0 * radius, std::sin(vrad) * 2.0 * radius);
		Vector const rayStartPos(location.x - std::cos(vrad) * radius, location.y - std::sin(vrad) * radius);
		
		double const mrad = std::atan2(m.normal.y, m.normal.y) + 3.1415926 / 4.0;
		Vector const mirrorSurface(std::cos(mrad) * m.width, std::sin(mrad) * m.width);
		Vector const mirrorStartPos(m.location.x - std::cos(mrad) * (m.width / 2), m.location.y - std::sin(mrad) * (m.width / 2));

		Vector const dist(mirrorStartPos.x - rayStartPos.x, mirrorStartPos.y - rayStartPos.y);
		double const mirrorCrsRay = Vector::cross(mirrorSurface, rayDiameter);
		if(std::abs(mirrorCrsRay) < eps) { return false; }
		
		double const distCrsMirror = Vector::cross(dist, mirrorSurface);
		double const distCrsRay = Vector::cross(dist, rayDiameter);

		double const internalyDivPointMirror = distCrsMirror / mirrorCrsRay;
		double const internalyDivPointRay = distCrsRay / mirrorCrsRay;

		return(
			internalyDivPointMirror - eps > 0.0 &&
			internalyDivPointMirror + eps < 1.0 &&
			internalyDivPointRay - eps > 0.0 &&
			internalyDivPointRay + eps < 1.0
		);
	}

	Vector getRefrectVec(Mirror const& m) const {


	}

	void Move(){
		location.x += vector.x;
		location.y += location.y;
	}
private:
	Ray() {}
};
