#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono_literals;

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeigth = 18;
unsigned char* pField = nullptr;

int nScreenWidth = 80;
int nScreenHeight = 30;

//旋转
int Rotate(int px, int py, int r)
{
	switch (r % 4)
	{
	case 0: return py * 4 + px;			// 0 degrees
	case 1: return 12 + py - (px * 4);	// 90 degrees
	case 2: return 15 - (py * 4) - px;	// 180 degrees
	case 3: return 3 - py + (px * 4);		// 270 degrees
	}
	return 0;
}

//位置是否适合
bool DoesPieceFit(int nTetromino, int nRotation, int nPoseX, int nPoseY)
{
	for (int px = 0; px < 4; px++)
	{
		for (int py = 0; py < 4; py++)
		{
			//在快中获得索引
			int pi = Rotate(px, py, nRotation);

			//Get index into field
			int fi = (nPoseY + py) * nFieldWidth + (nPoseX + px);

			if (nPoseX + px >= 0 && nPoseX + px < nFieldWidth)
			{
				if (nPoseY + py > -0 && nPoseY + py < nFieldHeigth)
				{
					if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
						return false;
				}
			}
		}
	}

	return true;
}

int main()
{
	// create assets
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");

	pField = new unsigned char[nFieldHeigth * nFieldWidth];

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeigth; y++)
		{
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeigth - 1) ? 9 : 0;
		}
	}

	//展示框
	/*  创建控制台缓冲区
		设置为活动缓冲区
		读取窗口大小
		更新 nScreenWidth / nScreenHeight
		再 new screen
	*/
	HANDLE hConsole = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	SetConsoleActiveScreenBuffer(hConsole);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	// 获取当前可见窗口大小
	nScreenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	nScreenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// 设置缓冲区大小等于窗口大小，防止横向滚动条
	COORD bufferSize = { (short)nScreenWidth, (short)nScreenHeight };
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

	for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
		screen[i] = L' ';

	DWORD dwBytesWritten = 0;

	bool bGameOver = false;

	//哪一块
	int nCurrentPiece = 1;
	//旋转
	int nCurrentRotation = 0; 
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	bool bKey[4];
	bool bRotateHold = false;

	int nSpeed = 20;
	int nSpeedCounter = 0;
	bool bForceDown = false;
	int nPieceCount = 0;
	int nScore = 0;

	vector<int> vLines;

	while (!bGameOver)
	{
		//游戏时间
		this_thread::sleep_for(50ms);
		nSpeedCounter++;
		bForceDown = (nSpeedCounter == nSpeed);

		//获取输入	
		for (int k = 0; k < 4; k++)							//R L D Z (左 右 下 旋转)
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;

		//游戏逻辑
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		if (bKey[3])
		{
			nCurrentRotation += (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = true;
		}
		else
			bRotateHold = false;

		if (bForceDown)
		{
			//看是否还能下降
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
			{
				nCurrentY++;
			}
			else
			{
				//锁定当前块
				for (int px = 0; px < 4; px++)
				{
					for (int py = 0; py < 4; py++)
					{
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
					}
				}

				nPieceCount++;
				if (nPieceCount % 10 == 0)
				{
					if (nSpeed >= 10)
						nSpeed--;
				}

				//有没有成一行的
				for (int py = 0; py < 4; py++)
				{
					if (nCurrentY + py < nFieldHeigth - 1)
					{
						bool bLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

						if (bLine)
						{
							//移除一行并换成 =
							for (int px = 1; px < nFieldWidth - 1; px++)
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;

							vLines.push_back(nCurrentY + py);
						}
					}
				}

				nScore += 25;
				if (!vLines.empty()) nScore += (1 << vLines.size()) * 100;

				//选择下一块
				nCurrentX = nFieldWidth / 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				//如果下一块放不下了就结束了
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}

			nSpeedCounter = 0;
		}

		//渲染输出
			 
		//画边框
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeigth; y++)
			{
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];
			}
		}

		//画初当前的内容块
		for (int px = 0; px < 4; px++)
		{
			for (int py = 0; py < 4; py++)
			{
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
			}
		}

		//显示分数
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %d", nScore);

		//重新展示缓冲区
		if (!vLines.empty())
		{
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
			this_thread::sleep_for(400ms);

			//把线条去了并向下移动线条以上的所有部分
			for (auto &v : vLines)
			{
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
					{
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					}
					pField[px] = 0;
				}
			}
			vLines.clear();
		}

		// 展示框架
		WriteConsoleOutputCharacter(hConsole, screen, nScreenHeight * nScreenWidth, { 0, 0 }, &dwBytesWritten);
	}
	
	CloseHandle(hConsole);
	cout << "Game Over !! Score:" << nScore << endl;
	system("pause");

	return 0;
}