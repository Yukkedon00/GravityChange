#pragma once
//ÉvÉåÉCÉÑÅ[ê›íË
const int Player_Size = 32;
extern int Life;

class cPlayer {
private:
	int Player_UpperleftPosx;
	int Player_UpperleftPosy;

	int Player_BottomrightPosx;
	int Player_BottomrightPosy;

public:

	int Life;

	int Player_posx;
	int Player_posy;

	void Init();
	void Updata();
	void Draw();
	bool BombEffect();

	int Check_ContactArea();
	int Check_Bullet(int x, int y);
	int Check_Life(int y);
};
