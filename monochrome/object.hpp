#pragma once
#include<cmath>

struct Vector {
	double x = 0.0;
	double y = 0.0;
	static double const cross(Vector const& v1, Vector const& v2) {
		return v1.x * v2.y - v2.x * v1.y;
	}
	double const rad() {
		return std::atan2(y, x);
	}

	static double const CheckRad(double rad){
		const double ANGLE_MIN = 0;
		const static double ANGLE_MAX = 2 * 3.1415926535897932384; //ç≈ëÂíl(<2ÉŒ)
		while (rad < ANGLE_MIN || rad >= ANGLE_MAX){
			if (rad < ANGLE_MIN){
				rad += ANGLE_MAX;
			}
			else{
				rad -= ANGLE_MAX;
			}
		}
		return rad;
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
	Mirror() {}
};

class Ray {
public:
	static const int radius = 1;
	static const int speed = 3;
	Vector location;
	Vector vector;
	bool isHittable;
	Ray(Vector const location_, Vector const vector_): location(location_), vector(vector_) {}

	/*
	bool isHit(Mirror const& m) const {
		double const eps = 0.0001;

		double const vrad = std::atan2(vector.y, vector.x);
		Vector const rayDiameter(std::cos(vrad) * 2.0 * radius, std::sin(vrad) * 2.0 * radius);
		Vector const rayStartPos(location.x - std::cos(vrad) * radius, location.y - std::sin(vrad) * radius);
		
		double const mrad = Vector::CheckRad(std::atan2(m.normal.y, m.normal.x) - 1.57079633);
		Vector const mirrorSurface(std::cos(mrad) * m.width, std::sin(mrad) * m.width);
		Vector const mirrorStartPos(m.location.x - std::cos(mrad) * (m.width / 2), m.location.y - std::sin(mrad) * (m.width / 2));

		Vector const dist(mirrorStartPos.x - rayStartPos.x, mirrorStartPos.y - rayStartPos.y);
		double const mirrorCrsRay = Vector::cross(mirrorSurface, rayDiameter);
		if (std::abs(mirrorCrsRay) < eps) { return false; }		
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
	*/


	bool isHit(Mirror const& m){
		int cx = location.x;
		int cy = location.y;
		int cr = radius;
		double const mrad = std::atan2(m.normal.y, m.normal.x) - 1.57079633;
		double mEdgeX = std::cos(mrad)*(m.width / 2);
		double mEdgeY = std::sin(mrad)*(m.width / 2);

		int lx1 = static_cast<int>(m.location.x + mEdgeX);
		int ly1 = static_cast<int>(m.location.y + mEdgeY);
		int lx2 = static_cast<int>(m.location.x - mEdgeX);
		int ly2 = static_cast<int>(m.location.y - mEdgeY);

		double A, B, C, CA, AS, BS;
		double d;
		A = std::pow(cx - lx1, 2.0) + std::pow(cy - ly1, 2.0);
		B = std::pow(cx - lx2, 2.0) + std::pow(cy - ly2, 2.0);
		C = std::pow(lx1 - lx2, 2.0) + std::pow(ly1 - ly2, 2.0);
		CA = (lx2 - lx1) * (cy - ly1) - (cx - lx1) * (ly2 - ly1);
		AS = (cx - lx1) * (lx2 - lx1) + (cy - ly1) * (ly2 - ly1);
		BS = (cx - lx2) * (lx2 - lx1) + (cy - ly2) * (ly2 - ly1);
		if (C != 0) d = pow(CA, 2.0) / C;
		else d = 0;
		if (d <= std::pow(cr, 2.0)){
			if (AS * BS <= 0){
				return true;
			}
			else if (std::pow(cr, 2.0) > A || std::pow(cr, 2.0) > B){
				return true;
			}
		}
		return 0;
	}
	Vector getRefrectVec(Mirror& m) const {
		double diff = m.normal.rad() - std::atan2(-vector.y, -vector.x);
		double rad = m.normal.rad() + diff;
		Vector result;
		result.x = std::cos(rad)*speed;
		result.y = std::sin(rad)*speed;
		return result;
	}

	void setStart(Vector startLocation, double startRad){
		location = startLocation;
		vector.x = cos(startRad)*speed;
		vector.y = sin(startRad)*speed;
	}
	void Move(){
		location.x += vector.x;
		location.y += vector.y;
	}
	Ray() {}
};
