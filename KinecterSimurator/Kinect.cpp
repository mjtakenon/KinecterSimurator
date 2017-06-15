#include "Kinect.h"

Kinect::Kinect(int fletMax)
{
	depthDrawPos = Vec2(0, 300);

	bodyPos = vector<vector<Vec3>>();
	currentBodyPos = vector<Vec3>(20);
	handDiff = 0;
	handAngle = vector<double>();
}

Kinect::~Kinect()
{

}

inline double Kinect::getHandDiff()
{
	return handDiff;
}

inline vector<double> Kinect::getHandAngle()
{
	return handAngle;
}

void Kinect::Update()
{
	handDiff = 0;

	if (KinectV1::HasNewDepthFrame())
	{
		KinectV1::GetDepthFrame(depthTexture);
	}

	depthTexture.draw(depthDrawPos);

	if (KinectV1::HasNewBodyFrame())
	{
		KinectV1::GetBodyFrame(bodies);
	}


	if (bodyPos.size() > logSize)
	{
		bodyPos.erase(bodyPos.begin());
	}

	if (handAngle.size() > logSize)
	{
		handAngle.erase(handAngle.begin());
	}
}

void Kinect::Draw(vector<int> soundTime, vector<double> fletAngle)
{
	int bodycount = 0;

	for (const auto& body : bodies)
	{
		if (!body)
		{
			continue;
		}

		if (bodycount == 0)
		{
			for (int joint = 0; joint < 20; joint++)
			{
				currentBodyPos[joint] = Vec3(body->joints[joint].depthSpacePos, body->joints[joint].cameraSpacePos.z);

				if (body->joints[joint].trackingState == TrackingState::NotTracked)
				{
					continue;
				}

				if (joint == V1JointType::HandRight)
				{
					handDiff = (currentBodyPos[V1JointType::HandRight].z - currentBodyPos[V1JointType::ShoulderRight].z);

					//Println(L"distance:" + ToString(handDiff));

					if (Abs(handDiff) > 0.35)
					{
						Circle(currentBodyPos[joint].xy() + depthDrawPos, 10).draw(Palette::Red);
					}
					else
					{
						Circle(currentBodyPos[joint].xy() + depthDrawPos, 10).draw(Palette::Lightgreen);
					}
				}
				else if (joint == V1JointType::ElbowRight)
				{
					Circle(currentBodyPos[joint].xy() + depthDrawPos, 10).draw(Palette::Yellow);
				}
				else
				{
					Circle(currentBodyPos[joint].xy() + depthDrawPos, 10).draw(Palette::White);
				}

				bodyPos.push_back(currentBodyPos);
			}

			Line(currentBodyPos[V1JointType::ElbowRight].xy() + depthDrawPos, currentBodyPos[V1JointType::HandRight].xy() + depthDrawPos).draw(5, Palette::Purple);

			//fletèÍèäÇÃï‚èïê¸
			Vec2 base = currentBodyPos[V1JointType::ElbowRight].xy() + depthDrawPos;
			for (int i = 0; i < fletAngle.size(); i++)
			{
				Vec2 v = Vec2(Sin(fletAngle[i]), Cos(fletAngle[i]));

				uint32 b = 255 - (255 - soundTime[i] * 8);
				if (soundTime[i] * 8 > 255 || soundTime[i] == 0)
				{
					b = 255;
				}
				int thick = 2 + ((255 - b) / 51);
				Line(base, base - v * 150).draw(thick, { 255,255,b,255 });
			}

			//äOé¸â~
			Circle(base, 150).drawFrame(2, 2, Palette::White);
			//â~Ç…í«è]Ç∑ÇÈéËÇÃäpìxÇÃâ~
			if (handAngle.size() > 2)
			{
				if (Abs(handDiff) > 0.35)
				{
					Circle(base + Vec2(Sin(handAngle[handAngle.size() - 1] + Pi), Cos(handAngle[handAngle.size() - 1] + Pi)) * 150, 15).draw(Palette::Red);
				}
				else
				{
					Circle(base + Vec2(Sin(handAngle[handAngle.size() - 1] + Pi), Cos(handAngle[handAngle.size() - 1] + Pi)) * 150, 15).draw(Palette::Lightgreen);
				}
			}

			Vec2 angleDiff = currentBodyPos[V1JointType::ElbowRight].xy() - currentBodyPos[V1JointType::HandRight].xy();
			handAngle.push_back(Atan2(angleDiff.x, angleDiff.y));

		}
		bodycount++;
	}

}