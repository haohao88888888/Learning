#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "olcConsoleGameEngine.h"

class OneLoneCoder_FormulaOLC : public olcConsoleGameEngine
{
public:
	OneLoneCoder_FormulaOLC()
	{
		m_sAppName = L"Formula OLC";
	}

private:
	float fCarPos = 0.0f;
	float fDistance = 0.0f;
	float fSpeed = 0.0f;

	//表示轨道在给定时间点的曲率
	float fCurvature = 0.0f;
	float fTrackCurvature = 0.0f;
	float fPlayerCurvature = 0.0f;
	float fTrackDistance = 0.0f;

	float fCurrentLapTime = 0.0f;

	vector<pair<float, float>> vecTrack; //曲率，距离
	list<float> listLapTimes;
protected:

	virtual bool OnUserCreate()
	{
		vecTrack.push_back(make_pair(0.0f, 10.0f)); // 短距离部分关于开始/结束
		vecTrack.push_back(make_pair(0.0f, 200.0f)); 
		vecTrack.push_back(make_pair(1.0f, 200.0f)); 
		vecTrack.push_back(make_pair(0.0f, 400.0f)); 
		vecTrack.push_back(make_pair(-1.0f, 100.0f)); 
		vecTrack.push_back(make_pair(0.0f, 200.0f)); 
		vecTrack.push_back(make_pair(-1.0f, 200.0f)); 
		vecTrack.push_back(make_pair(1.0f, 200.0f)); 
		vecTrack.push_back(make_pair(0.2f, 500.0f)); 
		vecTrack.push_back(make_pair(0.0f, 500.0f)); 

		for (auto t : vecTrack)
			fTrackDistance += t.second;

		listLapTimes = { 0, 0, 0, 0, 0 };


		return true;
	}


	virtual bool OnUserUpdate(float fElapsedTime)
	{
		if (m_keys[VK_UP].bHeld)
			fSpeed += 2.0f * fElapsedTime;
		else
			fSpeed -= 1.0f * fElapsedTime;

		int nCarDirection = 0;

		if (m_keys[VK_LEFT].bHeld)
		{
			fPlayerCurvature -= 0.7f * fElapsedTime;
			nCarDirection = -1;
		}

		if (m_keys[VK_RIGHT].bHeld)
		{
			fPlayerCurvature += 0.7f * fElapsedTime;
			nCarDirection = +1;
		}

		if (fabs(fPlayerCurvature - fTrackCurvature) >= 0.8f)
			fSpeed -= 5.0f * fElapsedTime;

		//锁速度
		if (fSpeed < 0.0f) fSpeed = 0.0f;
		if (fSpeed > 1.0f) fSpeed = 1.0f;

		//根据车的速度来移动车
		fDistance += (70.0f * fSpeed) * fElapsedTime;

		//获取轨道上的点
		float fOffset = 0;
		int nTrackSection = 0;

		//累计时间
		fCurrentLapTime += fElapsedTime;
		//跑完一圈
		if (fDistance >= fTrackDistance)
		{
			fDistance -= fTrackDistance;
			listLapTimes.push_front(fCurrentLapTime);
			listLapTimes.pop_back();
			fCurrentLapTime = 0.0f;
		}

		//遍历轨道上的部分
		while (nTrackSection < vecTrack.size() && fOffset <= fDistance)
		{
			fOffset += vecTrack[nTrackSection].second;
			nTrackSection++;
		}

		float fTargetCurvature = vecTrack[nTrackSection - 1].first;

		float fTrackCurveDiff = (fTargetCurvature - fCurvature) * fElapsedTime * fSpeed;
		fCurvature += fTrackCurveDiff;

		//轨道曲率
		fTrackCurvature += (fCurvature) * fElapsedTime * fSpeed;

		//画出天空
		for (int y = 0; y < ScreenHeight() / 2; y++)
		{
			for (int x = 0; x < ScreenWidth(); x++)
			{
				Draw(x, y, y < ScreenHeight() / 4 ? PIXEL_HALF : PIXEL_SOLID, FG_DARK_BLUE);
			}
		}

		//画出背景的山脉-使用sin函数
		//计算轨道曲率
		for (int x = 0; x < ScreenWidth(); x++)
		{
			int nHillHeight = (int)(fabs(sinf(x * 0.01f + fTrackCurvature) * 16.0f));
			for (int y = (ScreenHeight() / 2) - nHillHeight; y < ScreenHeight() / 2; y++)
				Draw(x, y, PIXEL_SOLID, FG_DARK_YELLOW);
		}



		for (int y = 0; y < ScreenHeight() / 2; y++)
		{
			for (int x = 0; x < ScreenWidth(); x++)
			{
				float fPerspective = (float)y / (ScreenHeight() / 2.0f);

				float fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 3);
				float fRoadeWidth = 0.1f + fPerspective * 0.8f;
				//马路牙子的宽度
				float fClipWidth = fRoadeWidth * 0.15f;

				fRoadeWidth *= 0.5f;

				int nLeftGrass = (fMiddlePoint - fRoadeWidth - fClipWidth) * ScreenWidth();
				int nLeftClip = (fMiddlePoint - fRoadeWidth) * ScreenWidth();
				int nRightClip = (fMiddlePoint + fRoadeWidth) * ScreenWidth();
				int nRightGrass = (fMiddlePoint + fRoadeWidth + fClipWidth) * ScreenWidth();

				int nRow = ScreenHeight() / 2 + y;

				int nGrassColour = sinf(20.0f * powf(1.0f - fPerspective, 3) + fDistance * 0.1f) > 0.0f ? FG_GREEN : FG_DARK_GREEN;
				int nClipColour = sinf(80.0f * powf(1.0f - fPerspective, 2) + fDistance) > 0.0f ? FG_RED : FG_WHITE;

				int nRoadColour = (nTrackSection - 1) == 0 ? FG_WHITE : FG_GREY;

				if (x >= 0 && x < nLeftGrass)
					Draw(x, nRow, PIXEL_SOLID, nGrassColour);
				if (x >= nLeftGrass && x < nLeftClip)
					Draw(x, nRow, PIXEL_SOLID, nClipColour);
				if (x >= nLeftClip && x < nRightClip)
					Draw(x, nRow, PIXEL_SOLID, nRoadColour);
				if (x >= nRightClip && x < nRightGrass)
					Draw(x, nRow, PIXEL_SOLID, nClipColour);
				if (x >= nRightGrass && x < ScreenWidth())
					Draw(x, nRow, PIXEL_SOLID, nGrassColour);
			}
		}

		//画车
		fCarPos = fPlayerCurvature - fTrackCurvature;
		int nCarPos = ScreenWidth() / 2 + ((int)(ScreenWidth() * fCarPos) / 2.0f) - 7;

		switch (nCarDirection)
		{
		case 0:
			DrawStringAlpha(nCarPos, 80, L"   ||####||   ");
			DrawStringAlpha(nCarPos, 81, L"      ##      ");
			DrawStringAlpha(nCarPos, 82, L"     ####     ");
			DrawStringAlpha(nCarPos, 83, L"     ####     ");
			DrawStringAlpha(nCarPos, 84, L"|||  ####  |||");
			DrawStringAlpha(nCarPos, 85, L"|||########|||");
			DrawStringAlpha(nCarPos, 86, L"|||  ####  |||");
			break;

		case -1:
			DrawStringAlpha(nCarPos, 80, L"\\\ #### \\\   ");
			DrawStringAlpha(nCarPos, 81, L"     ##      ");
			DrawStringAlpha(nCarPos, 82, L"     ####     ");
			DrawStringAlpha(nCarPos, 83, L"      ####     ");
			DrawStringAlpha(nCarPos, 84, L" \\\\   ####  \\\\");
			DrawStringAlpha(nCarPos, 85, L"  \\\\######## \\\\");
			DrawStringAlpha(nCarPos, 86, L"   \\\\  ####   \\\\");
			break;

		case +1:
			DrawStringAlpha(nCarPos, 80, L"     //####//");
			DrawStringAlpha(nCarPos, 81, L"        ##    ");
			DrawStringAlpha(nCarPos, 82, L"      ####    ");
			DrawStringAlpha(nCarPos, 83, L"     ####     ");
			DrawStringAlpha(nCarPos, 84, L"/// ####////  ");
			DrawStringAlpha(nCarPos, 85, L"//#######///O ");
			DrawStringAlpha(nCarPos, 86, L"/// #### //// ");
			break;
		}

		

		//展示状态
		DrawString(0, 0, L"Distance: " + to_wstring(fDistance));
		DrawString(0, 1, L"Target Curvature: " + to_wstring(fCurvature));
		DrawString(0, 2, L"Player Curvature: " + to_wstring(fPlayerCurvature));
		DrawString(0, 3, L"Player Speed: " + to_wstring(fSpeed));
		DrawString(0, 4, L"Track Curvature: " + to_wstring(fTrackCurvature));

		auto disp_time = [](float t)
		{
			int nMinutes = t / 60.0f;
			int nSeconds = t - (nMinutes * 60.0f);
			int nMilliSeconds = (t - (float)nSeconds) * 1000.0f;
			return to_wstring(nMinutes) + L"." + to_wstring(nSeconds) + L":" + to_wstring(nMilliSeconds);
		};

		DrawString(10, 8, disp_time(fCurrentLapTime));

		//展示最新的5圈圈速
		int j = 10;
		for (auto l : listLapTimes)
		{
			DrawString(10, j, disp_time(l));
			j++;
		}

		return true;
	}
};


int main()
{
	//使用olcConsoleGameEngine derived app
	OneLoneCoder_FormulaOLC game;
	game.ConstructConsole(160, 100, 8, 8);
	game.Start();

	return 0;
}