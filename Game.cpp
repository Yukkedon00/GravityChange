#include "Include.h"

//ステージ
char stage[_Stage_h][_Stage_w];

//タイマー　秒数
int Time = 600*4;

// HP
int Life = 0;

//敵の残数 今のところ使わない
//int Stage_kill_Total = 0;

//キー入力状態
int Key[256];

//ボタンが押された瞬間の処理
int KeyInput() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] =  0;
		}
	}return 0;

}

//プレイヤー処理
void cPlayer::Init()
{

	Life = 1;

	//プレイヤー座標決定
	Player_UpperleftPosx = _window_w / 2 - Player_Size/3;
	Player_UpperleftPosy = _window_h / 2 - Player_Size/3;
	Player_BottomrightPosx = _window_w / 2 + Player_Size/3;
	Player_BottomrightPosy = _window_h / 2 + Player_Size/3;
	//プレイヤー中心座標
	Player_posx = Player_UpperleftPosx + (Player_Size / 2);
	Player_posy = Player_UpperleftPosy + (Player_Size / 2);
}

//プレイヤーの状態を更新
void cPlayer::Updata()
{
	//移動処理


		if (ThumbLX < -128) {
			Player_UpperleftPosx -= (int)(ThumbLX / (ThumbLX / 3));
			Player_BottomrightPosx -= (int)(ThumbLX / (ThumbLX / 3));
			Player_posx -= (int)(ThumbLX / (ThumbLX / 3));
		}
		if (ThumbLX > 128) {
			Player_UpperleftPosx += (int)(ThumbLX / (ThumbLX / 3));
			Player_BottomrightPosx += (int)(ThumbLX / (ThumbLX / 3));
			Player_posx += (int)(ThumbLX / (ThumbLX / 3));
		}



		if (ThumbLY < -128) {
			Player_UpperleftPosy += (int)(ThumbLY / (ThumbLY / 3));
			Player_BottomrightPosy += (int)(ThumbLY / (ThumbLY / 3));
			Player_posy += (int)(ThumbLY / (ThumbLY / 3));
		}
		if (ThumbLY > 128) {
			Player_UpperleftPosy -= (int)(ThumbLY / (ThumbLY / 3));
			Player_BottomrightPosy -= (int)(ThumbLY / (ThumbLY / 3));
			Player_posy -= (int)(ThumbLY / (ThumbLY / 3));
		}
	

	/*if (ThumbLX != 0) {
		if (ThumbLX < 0) {
			Player_UpperleftPosx -= (int)(ThumbLX / (ThumbLX / 3));
			Player_BottomrightPosx -= (int)(ThumbLX / (ThumbLX / 3));
			Player_posx -= (int)(ThumbLX / (ThumbLX / 3));
		}
		if (ThumbLX > 0) {
			Player_UpperleftPosx += (int)(ThumbLX / (ThumbLX / 3));
			Player_BottomrightPosx += (int)(ThumbLX / (ThumbLX / 3));
			Player_posx += (int)(ThumbLX / (ThumbLX / 3));
		}
	}

	if (ThumbLY != 0) {
		if (ThumbLY < 0) {
			Player_UpperleftPosy += (int)(ThumbLY / (ThumbLY / 3));
			Player_BottomrightPosy += (int)(ThumbLY / (ThumbLY / 3));
			Player_posy += (int)(ThumbLY / (ThumbLY / 3));
		}
		if (ThumbLY > 0) {
			Player_UpperleftPosy -= (int)(ThumbLY / (ThumbLY / 3));
			Player_BottomrightPosy -= (int)(ThumbLY / (ThumbLY / 3));
			Player_posy -= (int)(ThumbLY / (ThumbLY / 3));
		}
	}*/

	/*if (pad[XINPUT_BUTTON_DPAD_RIGHT] != 0) {
		Player_UpperleftPosx+=3;
		Player_BottomrightPosx+=3;
		Player_posx+=3;
	}
	if (pad[XINPUT_BUTTON_DPAD_LEFT] != 0) {
		Player_UpperleftPosx-=3;
		Player_BottomrightPosx-=3;
		Player_posx-=3;
	}

	if (pad[XINPUT_BUTTON_DPAD_UP] != 0) {
		Player_UpperleftPosy-=3;
		Player_BottomrightPosy-=3;
		Player_posy -= 3;
	}
	if (pad[XINPUT_BUTTON_DPAD_DOWN] != 0) {
		Player_UpperleftPosy+=3;
		Player_BottomrightPosy+=3;
		Player_posy += 3;
	}*/

	//座標確認と更新
	if (Check_ContactArea() == -1) {
		Player_UpperleftPosy--;
		Player_BottomrightPosy--;
		Player_posy--;
	}
	if (Check_ContactArea() == 0) {
		Player_UpperleftPosy++;
		Player_BottomrightPosy++;
		Player_posy++;
	}
	//プレイヤー中心座標更新
	Player_posx = Player_UpperleftPosx + (Player_Size / 2);

}

//プレイヤー位置を判定
//0  下に下がる
//-1 上に上がる
int cPlayer::Check_ContactArea()
{
	if (stage[_Stage_h][Player_posx /16 -40] ==0) {
		return -1;
	}
	else { return 0; }
}

//プレイヤーが上下に行くと死亡させる関数
int cPlayer::Check_Life(int y)
{
	//縦処理
	if (y >= _window_h || y <= 0) {
		return 1;
	}
	else return 0;
}

//プレイヤーに弾が当たったか判定する関数
int cPlayer::Check_Bullet(int x, int y)
{
	if ((Player_UpperleftPosx <= x) && (Player_BottomrightPosx >= x) && (Player_UpperleftPosy <= y) && (Player_BottomrightPosy >= y)) {
		return 1;
	}
	else { return 0; }
}

//プレイヤー描画処理
void cPlayer::Draw()
{
	DrawBox(Player_UpperleftPosx, Player_UpperleftPosy, Player_BottomrightPosx, Player_BottomrightPosy, GetColor(255, 0, 0), TRUE);
}

//敵　処理
void cEnemy::Init()
{
	

	radius = 90;
	enemy_move = radius * PI / 180;

	enemy_attack_time = 0;					//攻撃までの時間 
	enemy_attack_flag = 0;					//攻撃フラグ 
	enemy_life = 1;							//敵のライフ 
	enemy_attack_bullet_posx = 0;			//敵の弾の座標 
	enemy_attack_bullet_posy = 0;			//
	enemy_attack_add_time = GetRand(1000);	//乱数取得

	
}

void cEnemy::Updata()
{
	
	if (enemy_life == 1) {
		//動き処理
		enemy_posy =float(enemy_posy + (0.8 * sin(enemy_move)));
		if (radius == 360) {
			radius = 0;
		}
		radius++;
		enemy_move = radius* PI / 180;	

		//攻撃フラグがたっていないとき
		if (enemy_attack_flag == 0) {

			if (enemy_attack_time + enemy_attack_add_time < _enemy_attack_flag_time) {
				enemy_attack_time+=10;
			}

			if (enemy_attack_time + enemy_attack_add_time >= _enemy_attack_flag_time) {
				enemy_attack_flag = 1;
				enemy_attack_bullet_posx = enemy_posx;
				enemy_attack_bullet_posy = enemy_posy;
				PlaySoundMem(enemy_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		
		//攻撃フラグがたったら
		if (enemy_attack_flag == 1) {
			if (enemy_posx > 320) {
				enemy_attack_bullet_posx-= 5;
				
			}
			else {
				
				enemy_attack_bullet_posx+= 5;
			}
			if (enemy_attack_bullet_posx <= 0 || enemy_attack_bullet_posx >= _window_w) {
				enemy_attack_add_time = GetRand(300);
				enemy_attack_flag = 0;
				enemy_attack_time = 0;
			}
		}

	}	
}

void cEnemy::EasyUpdata()
{
	if (enemy_life == 1) {
		//動き処理
		enemy_posy = float(enemy_posy + (0.8 * sin(enemy_move)));
		if (radius == 360) {
			radius = 0;
		}
		radius++;
		enemy_move = radius* PI / 180;

		//攻撃フラグがたっていないとき
		if (enemy_attack_flag == 0) {

			if (enemy_attack_time + enemy_attack_add_time < _enemy_attack_flag_time) {
				enemy_attack_time += 10;
			}

			if (enemy_attack_time + enemy_attack_add_time >= _enemy_attack_flag_time) {
				enemy_attack_flag = 1;
				enemy_attack_bullet_posx = enemy_posx;
				enemy_attack_bullet_posy = enemy_posy;
				PlaySoundMem(enemy_attack_sound, DX_PLAYTYPE_BACK);
			}
		}

		//攻撃フラグがたったら
		if (enemy_attack_flag == 1) {
			if (enemy_posx > 320) {
				enemy_attack_bullet_posx -= 5;

			}
			else {

				enemy_attack_bullet_posx += 5;
			}
			if (enemy_attack_bullet_posx <= 0 || enemy_attack_bullet_posx >= _window_w) {
				enemy_attack_add_time = GetRand(300);
				enemy_attack_flag = 0;
				enemy_attack_time = 0;
			}
		}

	}
}

//敵を描画
void cEnemy::Draw()
{
	if (enemy_life == 1) {
		if (enemy_attack_flag == 1) {
			DrawRotaGraph((int)enemy_posx, (int)enemy_posy, 1.0, 0, Load_enemy_graph[1], TRUE, TRUE);
		}
		else {
			DrawRotaGraph((int)enemy_posx, (int)enemy_posy, 1.0, 0, Load_enemy_graph[0], TRUE, TRUE);
		}
	}
	else{}
}

//敵を反転して描画する処理
void cEnemy::Draw_Inverted()
{
	if (enemy_life == 1) {
		if (enemy_attack_flag == 1) {
			DrawRotaGraph((int)enemy_posx, (int)enemy_posy, 1.0, 0, Load_enemy_graph[1], TRUE, FALSE);
		}
		else {
			DrawRotaGraph((int)enemy_posx, (int)enemy_posy, 1.0, 0, Load_enemy_graph[0], TRUE, FALSE);
		}
	}
	else {}
}

//敵の弾の処理
void cEnemy::Draw_Bullet()
{
	if (enemy_attack_flag == 1) {
		DrawCircle((int)enemy_attack_bullet_posx, (int)enemy_attack_bullet_posy, 6, GetColor(125, 125, 125), TRUE);
	}
	else{}
}

//ステージセレクト画面　処理
void cStageSelectMenu::Init()
{
	Play_Level = 1;			//難易度設定

	box_upperleftx = 80;	//十字キーで移動できる四角い枠の座標
	box_upperlefty = 160;	//
	box_bottomrightx = 160;	//
	box_bottomrighty = 320;	//
	
	box_gap = 40;			//画面左の空白部分
}

//ステージセレクト　移動と決定の処理
void cStageSelectMenu::Updata()
{
	if (pad[XINPUT_BUTTON_DPAD_RIGHT] == 1 || (ThumbLX != 0 && judgeThumbLX == 1)) {
		if (Play_Level == 3) {		//移動できないようにする
			box_bottomrightx -= ((_window_w / 4) + box_gap) * 2;
			box_upperleftx -= ((_window_w / 4) + box_gap) * 2;
			Play_Level = 1;
		}
		else {
			box_bottomrightx += (_window_w / 4) + box_gap;
			box_upperleftx += (_window_w / 4) + box_gap;
			Play_Level++;
		}
	}
	if (pad[XINPUT_BUTTON_DPAD_LEFT] == 1 || (ThumbLX != 0 && judgeThumbLX == -1)) {
		if (Play_Level == 1) {
			box_bottomrightx += ((_window_w / 4) + box_gap) * 2;
			box_upperleftx += ((_window_w / 4) + box_gap) * 2;
			Play_Level = 3;
		}
		else {
			box_bottomrightx += -(_window_w / 4) - box_gap;
			box_upperleftx += -(_window_w / 4) - box_gap;
			Play_Level--;
		}
	}

}

// ステージ描画
void cStageSelectMenu::Draw()
{
	DrawBox((int)box_upperleftx, (int)box_upperlefty, box_bottomrightx, box_bottomrighty, GetColor(255, 255, 255), FALSE);
	DrawString((int)(_window_w * 0.18), (int)(_window_h / 3), "イ\n｜\nジ\n｜\nモ\n｜\nド",GetColor(255,255,255));
	DrawString((int)(_window_w * 0.49), (int)(_window_h / 3), "ノ\n｜\nマ\nル\nモ\n｜\nド", GetColor(255, 255, 255));
	DrawString((int)(_window_w * 0.8), (int)(_window_h / 3), "ハ\n｜\nド\nモ\n｜\nド\n", GetColor(255, 255, 255));
}

// コイン処理
void cCoin::Init() {
	srand((unsigned int)time(NULL));
	posx = GetRand(640 - 96) + 32;
	posy = GetRand(480 - 96) + 32;
	imagechange = 0;
	count = 0;
	judge = false;
}

void cCoin::Draw() {
	count++;
	if (count == 50) {
		if (imagechange == 0)imagechange = 1;
		else imagechange = 0;
		count = 0;
	}
	
	DrawGraph(posx, posy, image[imagechange], TRUE);
}

//タイマー処理
int Timer()
{
	
	DrawFormatString(_window_w / 2, 0, GetColor(0, 255, 0), "%2d:%2d", Time * 3 / 180, (Time*3 % 180) /2);
	Time--;
	if (Time == 0) {
		return 1;
	}
	else return 0;
}


//モード
enum Mode {
	ModeTitle,
	ModeStageSelect,
	ModeTutorial,
	ModeGame,
	ModeGameHard,
	ModeGameEazy,
	ModeClear,
	ModeOver,
};
//ステージ処理
void DrawStage()
{
	memset(stage, 0, sizeof(stage));
	int stage_Size = 16;												//上下の四角の大きさ
	int stage_UpperleftPosx = 0;										//四角の左上X座標
	int stage_UpperleftPosy = _window_h - stage_Size * _Stage_h;		//四角の左上Y座標
	int stage_BottomrightPosx = stage_Size;								//四角の右上X座標
	int stage_BottomrightPosy = _window_h - stage_Size * (_Stage_h - 1);//四角の右上Y座標

	for (int i = 0; i < _Stage_h; i++) {
		for (int j = 0; j < _Stage_w; j++) {
			if (j % 8  < 4) {
				//塗りつぶしで描画
				if (i < _Stage_h / 2) {
					DrawBox(j * stage_Size, i * stage_Size, (j + 1) *stage_Size, (i + 1)*stage_Size, GetColor(255, 255, 255), TRUE);
				}
				//枠だけ描画
				else {
					DrawBox(stage_UpperleftPosx, stage_UpperleftPosy, stage_BottomrightPosx, stage_BottomrightPosy, GetColor(255, 255, 255), TRUE);
				}
				stage[i][j] = 1;
			}
			else {
				if (i < _Stage_h / 2) {
					DrawBox(j * stage_Size, i * stage_Size, (j + 1) *stage_Size, (i + 1)*stage_Size, GetColor(255, 255, 255), FALSE);
				}
				else {
					DrawBox(stage_UpperleftPosx, stage_UpperleftPosy, stage_BottomrightPosx, stage_BottomrightPosy, GetColor(255, 255, 255), FALSE);
				}
			}
			stage_UpperleftPosx += stage_Size;
			stage_BottomrightPosx += stage_Size;
		}
		stage_UpperleftPosy += stage_Size;
		stage_BottomrightPosy += stage_Size;

		stage_UpperleftPosx = 0;
		stage_BottomrightPosx = stage_Size;
	}

}


// 敵の数をセットする
void EnemySet(cEnemy *cenemy, int num, Mode mode);


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	SetGraphMode(640,480,16);
	DxLib_Init(), ChangeWindowMode(TRUE), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
	
	// 解像度変更
	/*int DesktopSizeX;	// デスクトップの大きさ
	int DesktopSizeY;

	GetDefaultState(&DesktopSizeX, &DesktopSizeY, NULL);
	SetWindowStyleMode(4);						// ウインドウスタイルを枠なしに変更
	SetWindowSize(DesktopSizeX, DesktopSizeY);	// ウインドウのサイズをデスクトップと同じにする
	SetWindowPosition(0, 0);					// ウインドウの位置を画面左上に変更
	SetWindowZOrder(DX_WIN_ZTYPE_TOPMOST, TRUE);*/

	// フォント宣言
	int FontHandle;
	FontHandle = CreateFontToHandle("メイリオ", 20, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	//変数宣言
	cPlayer cplayer[1];
	cEnemy cenemy[_enemy_number];
	cStageSelectMenu cstageselectmenu;
	cCoin ccoin[5];

	//BGM　格納
	static int MainMusic = LoadSoundMem("シューティングゲーム　タイトル　ループ.wav");
	static int BattleMusic = LoadSoundMem("シューティング　戦闘.wav");
	static int CoinGSe = LoadSoundMem("getcoin.mp3");
	static int WinMusic = LoadSoundMem("シューティング　戦闘　勝利.wav");
	static int LoseMusic = LoadSoundMem("シューティング　戦闘　敗北.wav");

	// ハードモード　カウント
	short hardcount = 0;

	//音量調整
	ChangeVolumeSoundMem(100,MainMusic);
	ChangeVolumeSoundMem(100,BattleMusic);
	ChangeVolumeSoundMem(150, CoinGSe);
	ChangeVolumeSoundMem(100, WinMusic);
	ChangeVolumeSoundMem(100, LoseMusic);

	SetVolumeMusic(10);

	int MusicFlag = 0;
	int Init_Flag = 0;
	int Tutorial_number = 0;
	int getcoin = 0;
	
	Mode mode;	
	mode = ModeTitle;

	bool moreHard = false;
	bool secret = false;

	cstageselectmenu.Init();

	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && KeyInput() == 0 && PadInput() == 0 && JudgeThumbLX() == 0) {
		
		// デバッグ
		// DrawFormatString(0, 100, 0xffffff, "%05d , %05d", ThumbLX, ThumbLY);

		DrawStage();
		switch (mode) {
			//タイトル画面
		case ModeTitle:
			DrawStringToHandle(320, 400, "push [B] Button", 0xfffff, FontHandle);
			LoadGraphScreen(_window_w / 4,_window_h / 4, "Gravity Change.bmp", TRUE);
			if (Init_Flag == 0) {
				getcoin = 0;
				hardcount = 0;
				for (int i = 0; i <= _enemy_number - 1; i++) {
					cenemy[i].Init();
					if (i <= 9) {
						cenemy[i].enemy_posx = 16.f;
						cenemy[i].enemy_posy = (48 * i) + 16.f;
					}
					else if (i >= 10) {
						cenemy[i].enemy_posx = _window_w - 16.f;
						cenemy[i].enemy_posy = (48 * (i - 10)) + 16.f;
					}
				}
				for (int i = 0; i <= 5; i++) {
					ccoin[i].Init();
				}
				Init_Flag++;
			}

			if (CheckSoundMem(MainMusic) == 0) {
				PlaySoundMem(MainMusic, DX_PLAYTYPE_LOOP);
			}
			Time = 600 * 4;
			cplayer[0].Init();
			// cstageselectmenu.Init();
			if (pad[XINPUT_BUTTON_B] == 1) {
				mode = ModeStageSelect;
				Init_Flag = 0;
			}
			break;
			//ステージセレクト画面
		case ModeStageSelect:

			if (pad[XINPUT_BUTTON_RIGHT_SHOULDER] != 0 && pad[XINPUT_BUTTON_RIGHT_SHOULDER] != 0) {
				moreHard = true;
			}
			if (pad[XINPUT_BUTTON_RIGHT_SHOULDER] != 0 && pad[XINPUT_BUTTON_RIGHT_SHOULDER] != 0 && pad[XINPUT_BUTTON_A] != 0) {
				moreHard = false;
			}

			if (moreHard) {
				DrawCircle(640, 0, 100, 0xfffff, TRUE);
			}

			if (CheckSoundMem(MainMusic) == 0) {
				PlaySoundMem(MainMusic, DX_PLAYTYPE_LOOP);
			}

			cstageselectmenu.Updata();
			cstageselectmenu.Draw();
			if (cstageselectmenu.Play_Level == 1 && pad[XINPUT_BUTTON_B] == 1) {
				mode = ModeGameEazy;
				StopSoundMem(MainMusic);
			}
			else if (cstageselectmenu.Play_Level == 2 && pad[XINPUT_BUTTON_B] == 1) {
				mode = ModeGame;
				StopSoundMem(MainMusic);
			}
			else if (cstageselectmenu.Play_Level == 3 && pad[XINPUT_BUTTON_B] == 1 && moreHard == false) {
				mode = ModeGameHard;
				StopSoundMem(MainMusic);
			}
			else if (cstageselectmenu.Play_Level == 3 && pad[XINPUT_BUTTON_B] == 1 && moreHard == true) {
				moreHard = true;
				mode = ModeGameHard;
				StopSoundMem(MainMusic);
			}
			break;
			//操作方法を選択した時
		case ModeTutorial:
			if (pad[XINPUT_BUTTON_DPAD_RIGHT] == 1) {
				if (Tutorial_number != 2) {
					Tutorial_number++;
				}
			}
			if (pad[XINPUT_BUTTON_DPAD_LEFT] == 1) {
				if (Tutorial_number != 0) {
					Tutorial_number--;
				}
			}
			if (Tutorial_number == 0) {
				LoadGraphScreen(0, 0, "チュートリアル1.png", TRUE);
			}
			if (Tutorial_number == 1) {
				LoadGraphScreen(0, 0, "チュートリアル2.png", TRUE);
			}
			if (Tutorial_number == 2) {
				LoadGraphScreen(0, 0, "チュートリアル3.png", TRUE);
			}

			if (pad[XINPUT_BUTTON_A] == 1) {
				Tutorial_number = 0;
				mode = ModeStageSelect;
			}
			break;
			//ノーマルモードを選択した時
		case ModeGame:
			if (CheckSoundMem(BattleMusic) == 0) {
				PlaySoundMem(BattleMusic, DX_PLAYTYPE_BACK);
			}

			if (getcoin == 5) {
				mode = ModeClear;
				StopSoundMem(BattleMusic);
			}

			for (int i = 0; i < 5; i++) {
				if (ccoin[i].judge == false && ccoin[i].GetPosx() < cplayer[0].Player_posx && ccoin[i].GetPosx() + _chip_size > cplayer[0].Player_posx &&
					ccoin[i].GetPosy() < cplayer[0].Player_posy && ccoin[i].GetPosy() + _chip_size > cplayer[0].Player_posy) {
					ccoin[i].judge = true;
					getcoin++;
					PlaySoundMem(CoinGSe, DX_PLAYTYPE_BACK);
				}
				if (ccoin[i].judge == false) {
					ccoin[i].Draw();
				}
			}

			Timer();
			for (int i = 0; i < _enemy_number; i++) {
				cenemy[i].Updata();
				cenemy[i].Draw_Bullet();
				if (i <= 9) {
					cenemy[i].Draw();
				}
				if (i >= 10) {
					cenemy[i].Draw_Inverted();
				}
				if (cplayer[0].Check_Bullet((int)cenemy[i].enemy_attack_bullet_posx, (int)cenemy[i].enemy_attack_bullet_posy) == 1) {
					StopSoundMem(BattleMusic);
					mode = ModeOver;
				}
			}
			cplayer[0].Draw();
			cplayer[0].Updata();
			
			if (cplayer[0].Check_Life(cplayer[0].Player_posy) == 1) {

				StopSoundMem(BattleMusic);
				mode = ModeOver;
			}
			if (Timer() == 1) {
				StopSoundMem(BattleMusic);
				mode = ModeOver;
			}
			
			break;
			//ハードモードを選択した時
		case ModeGameHard:

			if (CheckSoundMem(BattleMusic) == 0) {
				PlaySoundMem(BattleMusic, DX_PLAYTYPE_BACK);
			}

			if (getcoin == 5) {
				if (moreHard == false) secret = true;
				mode = ModeClear;
				// moreHard = false;
				StopSoundMem(BattleMusic);
			}

			// コインとプレイヤーのコリジョン
			if (ccoin[hardcount].judge == false && ccoin[hardcount].GetPosx() < cplayer[0].Player_posx && ccoin[hardcount].GetPosx() + _chip_size > cplayer[0].Player_posx &&
				ccoin[hardcount].GetPosy() < cplayer[0].Player_posy && ccoin[hardcount].GetPosy() + _chip_size > cplayer[0].Player_posy) {
				ccoin[hardcount].judge = true;
				getcoin++;
				hardcount++;
				PlaySoundMem(CoinGSe, DX_PLAYTYPE_BACK);
			}
			if (ccoin[hardcount].judge == false) {
				ccoin[hardcount].Draw();
			}
	
			Timer();
			for (int i = 0; i < _enemy_number; i++) {

				if (moreHard == true) cenemy[i].Updata();
				cenemy[i].Updata();
				cenemy[i].Draw_Bullet();
				if (i <= 9) {
					cenemy[i].Draw();
				}
				if (i >= 10) {
					cenemy[i].Draw_Inverted();
				}
				if (cplayer[0].Check_Bullet((int)cenemy[i].enemy_attack_bullet_posx, (int)cenemy[i].enemy_attack_bullet_posy) == 1) {
					mode = ModeOver;
					// moreHard = false;
					StopSoundMem(BattleMusic);
				}
			}
			cplayer[0].Draw();
			cplayer[0].Updata();
			cplayer[0].Updata();
			cplayer[0].Updata();
			if (cplayer[0].Check_Life(cplayer[0].Player_posy) == 1) {
				mode = ModeOver;
				StopSoundMem(BattleMusic);
				// moreHard = false;
			}
			if (Timer() == 1) {
				mode = ModeOver;
				StopSoundMem(BattleMusic);
				// moreHard = false;
			}
			break;

		case ModeGameEazy:
			if (CheckSoundMem(BattleMusic) == 0) {
				PlaySoundMem(BattleMusic, DX_PLAYTYPE_BACK);
			}

			if (getcoin == 5) {
				mode = ModeClear;
				StopSoundMem(BattleMusic);
			}

			for (int i = 0; i < 5; i++) {
				if (ccoin[i].judge == false && ccoin[i].GetPosx() < cplayer[0].Player_posx && ccoin[i].GetPosx() + _chip_size > cplayer[0].Player_posx &&
					ccoin[i].GetPosy() < cplayer[0].Player_posy && ccoin[i].GetPosy() + _chip_size > cplayer[0].Player_posy) {
					ccoin[i].judge = true;
					getcoin++;
					PlaySoundMem(CoinGSe, DX_PLAYTYPE_BACK);
				}
				if (ccoin[i].judge == false) {
					ccoin[i].Draw();
				}
			}

			Timer();
			for (int i = 0; i < _enemy_number / 2; i++) {
				cenemy[i].Updata();
				cenemy[i].Draw_Bullet();
				if (i <= 9) {
					cenemy[i].Draw();
				}
				if (i >= 10) {
					cenemy[i].Draw_Inverted();
				}
				if (cplayer[0].Check_Bullet((int)cenemy[i].enemy_attack_bullet_posx, (int)cenemy[i].enemy_attack_bullet_posy) == 1) {
					StopSoundMem(BattleMusic);
					mode = ModeOver;
				}
			}
			cplayer[0].Draw();
			cplayer[0].Updata();
			
			if (cplayer[0].Check_Life(cplayer[0].Player_posy) == 1) {
				StopSoundMem(BattleMusic);
				mode = ModeOver;
			}
			if (Timer() == 1) {
				StopSoundMem(BattleMusic);
				mode = ModeOver;
			}
			break;

			//ゲームクリア処理
		case ModeClear:
			DrawStringToHandle(320, 400, "push [B] Button", 0xfffff, FontHandle);
			LoadGraphScreen(_window_w / 4, _window_h / 4, "GameClear.bmp", TRUE);
			if (secret)DrawStringToHandle(_window_w / 4, _window_h / 2, "ステージセレクト画面で[L][R]を押して\nハードモードを選ぶと…", 0xffffff, FontHandle);
			if (MusicFlag == 0) {
				PlaySoundMem(WinMusic, DX_PLAYTYPE_BACK);
				MusicFlag++;
			}
			if (pad[XINPUT_BUTTON_B] == 1) {
				StopSoundMem(WinMusic);
				MusicFlag = 0;
				mode = ModeTitle;
				secret = false;
			}
			break;
			//ゲームオーバー処理
		case ModeOver:
			DrawStringToHandle(320, 400, "push [B] Button", 0xfffff, FontHandle);
			LoadGraphScreen(_window_w / 4, _window_h / 4, "GameOver.bmp", TRUE);
			if (MusicFlag == 0) {
				PlaySoundMem(LoseMusic, DX_PLAYTYPE_BACK);
				MusicFlag++;
			}
			if (pad[XINPUT_BUTTON_B] == 1) {
				StopSoundMem(LoseMusic);
				mode = ModeTitle;
				MusicFlag = 0;
			}
			break;
		}
	}
	DeleteFontToHandle(FontHandle);
	DeleteSoundMem(MainMusic);
	DeleteSoundMem(CoinGSe);
	DeleteSoundMem(WinMusic);
	DeleteSoundMem(LoseMusic);
	DeleteSoundMem(BattleMusic);
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}

void EnemySet(cEnemy *cenemy, int num,Mode mode) {

	switch (mode)
	{
	case ModeGame:
		break;
	case ModeGameHard:
		break;
	case ModeGameEazy:
		break;
	}
}