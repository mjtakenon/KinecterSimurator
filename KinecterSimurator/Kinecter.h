#pragma once

#include <Siv3D.hpp>

#include "Kinect.h"
#include "Guitar.h"

using namespace std;

class Kinecter
{
public:

	Kinecter();
	~Kinecter();

	void Run();

private:

	void Update();
	void Draw();

	String getSerialMessage();
	String getWiFiMessage();
	vector<vector<bool>> getButtonState(vector<vector<bool>> state);

	void drawGuitar();

	void playSound();

private:

	Guitar* m_Guitar;
	Kinect* m_Kinect;

	vector<int> soundTime;
	vector<int> playingPitch;

	vector<int> basePitch;

	Serial	serial;
	vector<vector<bool>> buttonState;


	Rect Board;
	vector<Line> Str;
	vector<Line> Flet;

	Point boardPos;
	Point boardSize;
	int	fletSpace;
	int fletMarginLeft;


	const int fletMax = 6;
	const int rowMax = 5;

	const int baudrate = 115200;
	const int comPort = 3;
	const int midiCh = 0;

	
	//è‚ª”½‰‚·‚éŠp“x
	vector<double> fletAngle;

	vector<PitchName> pitchTable;

	vector<Key>	inputKeyAssign;



	//Wi-Fi’ÊMŠÖŒW
	const uint16 port = 58620;
	const IPv4 serverAddress = IPv4(192, 168, 43, 226);

	TCPClient client;

	
};
