#pragma once

class cCoin {
	int		posx, posy;
	int		image[2];
	int		imagechange;
	int		count;
public:
	cCoin() {
		LoadDivGraph("coin.bmp", 2, 2, 1, 32, 32, image);
	}
	bool	judge;
	void	Draw();
	void	Init();
	int		GetPosx() { return posx; }
	int		GetPosy() {	return posy; }
};