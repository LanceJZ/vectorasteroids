#pragma once

class Controllers
{
protected:
	int m_ScreenHeight;
	int m_ScreenWidth;	
	int GetRandomX(void);
	int GetRandomY(void);

private:


public:
	Controllers(void);
	~Controllers(void);

	void SetScreenSize(int Width, int Height);
};

