#pragma once
#include <Siv3D.hpp>

using namespace std;

class Kinect
{
public:

	Kinect(int fletMax);
	~Kinect();

	void Update();
	void Draw(vector<int> soundTime, vector<double> fletAngle);

	double getHandDiff() { return handDiff; };
	vector<double> getHandAngle() { return handAngle; };

private:
	array<Optional<KinectV1Body>, 2>	bodies;

	vector<vector<Vec3>>	bodyPos;
	vector<Vec3>		currentBodyPos;

	vector<double>	handAngle;

	Vec2		depthDrawPos;
	const int	logSize = 10;
	double		handDiff;

	DynamicTexture	depthTexture;

};