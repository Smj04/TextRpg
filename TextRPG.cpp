#include <iostream>
#include<time.h>
#include <Windows.h>

using namespace std;

void gotoxy(int x, int y) {

	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

#define LIGHTRED 12 
#define BLACK 0 
#define YELLOW 14

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}



enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};
enum MAP_TYPE {
	MT_NON,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};
enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};
enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};
enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX	20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3
#define LEVEL_MAX 10



struct _Item {
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int iMin;
	int iMax;
	int iPrice;
	int iSell;
	char strDesc[ITEM_DESC_LENGTH];
};

struct _Inventory {
	_Item tItem[INVENTORY_MAX];
	int iItemCount;
	int iGold;
};

struct _Player {
	char strName[NAME_SIZE];
	char strJobName[NAME_SIZE];
	JOB eJob;
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;	//방어력,체력
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iExp;
	int iLevel;
	_Item tEquip[EQ_MAX];
	bool bEquip[EQ_MAX];
	_Inventory tInventory;
};
struct _Monster {		//_tagMonster
	char strName[NAME_SIZE];
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iLevel;
	int iExp;
	int iGoldMin;
	int iGoldMax;

};

struct LevelUpstatus {
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHPMin;
	int iHPMax;
	int iMPMin;
	int iMPMax;
};
int main() {

	srand((unsigned int)time(0));

	//레벨업에 필요한 경험치 목록을 만든다.
	const int iLevelUpExp[LEVEL_MAX] = { 400, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000,400000};

	//JOB_END 는 4. 그런데 직업은 3개이므로 -1해서 배열을 각 직업별로
	//생성하도록 한다.

	LevelUpstatus tLvUpTable[JOB_END - 1] = {};

	tLvUpTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvUpTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMin = 8;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMax = 16;
	tLvUpTable[JOB_KNIGHT - 1].iHPMin = 50;
	tLvUpTable[JOB_KNIGHT - 1].iHPMax = 100;
	tLvUpTable[JOB_KNIGHT - 1].iMPMin = 10;
	tLvUpTable[JOB_KNIGHT - 1].iMPMax = 20;

	tLvUpTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvUpTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvUpTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvUpTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvUpTable[JOB_ARCHER - 1].iHPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iHPMax =60;
	tLvUpTable[JOB_ARCHER - 1].iMPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iMPMax = 50;

	tLvUpTable[JOB_WIZARD - 1].iAttackMin = 15;
	tLvUpTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvUpTable[JOB_WIZARD - 1].iArmorMin = 3;
	tLvUpTable[JOB_WIZARD - 1].iArmorMax = 7;
	tLvUpTable[JOB_WIZARD - 1].iHPMin = 20;
	tLvUpTable[JOB_WIZARD - 1].iHPMax = 50;		//40
	tLvUpTable[JOB_WIZARD - 1].iMPMin = 40;
	tLvUpTable[JOB_WIZARD - 1].iMPMax = 100;


	//이름
	_Player tPlayer = {}; //null
	/*system("mode con cols=119 lines=30 | title Text RPG");*/
	
	textcolor(LIGHTRED, BLACK);
	gotoxy(28, 5);
	cout << " _______  _______  __   __  _______    ______    _______  _______ " << endl;
	gotoxy(28, 6);
	cout << "|       ||       ||  |_|  ||       |  |    _ |  |       ||       |" << endl;
	gotoxy(28, 7);
	cout << "|_     _||    ___||       ||_     _|  |   | ||  |    _  ||    ___|" << endl;
	gotoxy(28, 8);
	cout << "  |   |  |   |___ |       |  |   |    |   |_||_ |   |_| ||   | __ " << endl;
	gotoxy(28, 9);
	cout << "  |   |  |    ___| |     |   |   |    |    __  ||    ___||   ||  |" << endl;
	gotoxy(28, 10);
	cout << "  |   |  |   |___ |   _   |  |   |    |   |  | ||   |    |   |_| |" << endl;
	gotoxy(28, 11);
	cout << "  |___|  |_______||__| |__|  |___|    |___|  |_||___|    |_______|" << endl;
	
#define DARKGRAY 8
#define WHITE 15 
	/*cout << "\n\n\n\n";
	cout << "\t\t"; cout << "@@@@@@@@@@   @@@@@@@@@   @@@   @@@   @@@@@@@@@@   @@@@@@@@    @@@@@@@@   @@@@@@@\n";
	cout << "\t\t"; cout << "    @        @             @   @         @        @      @    @      @   @          \n";
	cout << "\t\t"; cout << "    @        @              @ @          @        @       @   @@@@@@@@   @         \n";
	cout << "\t\t"; cout << "    @        @@@@@@@@@      @@@          @        @       @   @          @    @@@@ \n";
	cout << "\t\t"; cout << "    @        @              @ @          @        @@@@@@@@@   @          @       @  \n";
	cout << "\t\t"; cout << "    @        @             @   @         @        @       @   @          @       @  \n";
	cout << "\t\t"; cout << "    @        @@@@@@@@@   @@@   @@@       @         @      @   @          @@@@@@@@\n\n\n\n\n";*/

	textcolor(DARKGRAY, BLACK);
	gotoxy(18, 18);
	cout << "                          게임을 시작하려면 <Enter>를 누르세요."<<endl;
	gotoxy(18, 19);
	cout << "                                TextRPG.0 By MinjeoungSeo"<<endl;

	textcolor(WHITE, BLACK);
	getchar(); // 아무키 입력 기다림

	system("cls");
	
	
	/*gotoxy(50, 0);
	cout << "이름을 입력해 주세요 : " << endl;*/
	gotoxy(12, 10);
	cout << " __    _  _______  __   __  _______    ___ " << endl;
	gotoxy(12, 11);
	cout << "|  |  | ||   _   ||  |_|  ||       |  |   |" << endl;
	gotoxy(12, 12);
	cout << "|   |_| ||  |_|  ||       ||    ___|  |___|" << endl;
	gotoxy(12, 13);
	cout << "|       ||       ||       ||   |___    ___    " << endl;
	gotoxy(12, 14);
	cout << "|  _    ||       ||       ||    ___|  |   |   " << endl;
	gotoxy(12, 15);
	cout << "| | |   ||    _   || ||_|| ||   |___  |___|  " << endl;
	gotoxy(12, 16);
	cout << "|_|  |__||__| |__||_|   |_||_______|          " << endl;
	textcolor(YELLOW, BLACK);

	gotoxy(58, 15);
	cin.getline(tPlayer.strName, NAME_SIZE - 1);
	system("cls");
	
	textcolor(WHITE, BLACK);
	cout << "어느 왕국에 정신나간 왕이 게임을 만들며 살고 있었습니다." << endl;
	cout << "그런데 갑자기 왕이 코딩이 너무나도 하기 싫어져서 망령을 소환하였습니다." << endl;
	cout << "하지만 망령도 역시나 농땡이만 쳤고, 결국 왕국은 멸망하였습니다." << endl;

	cout << "몇 십년이 흐르고..." << endl;
	
	cout << "용사 " << tPlayer.strName << "<은>는 왕국의 잊혀진 보물들을 찾아 모험을 시작합니다." << endl;
	textcolor(YELLOW, BLACK);
	cout << endl << endl << "환영합니다. 용사 " << tPlayer.strName << "님" << endl << endl << endl;

	int iJob = JOB_NONE;

	#define LIGHTBLUE 9

	while (iJob == JOB_NONE)
	{
		textcolor(WHITE, BLACK);
		system("pause");
		cout << endl;
		textcolor(YELLOW, BLACK);
		gotoxy(43, 12);
		cout << "직업을 선택하세요." << endl;
		
		gotoxy(43, 14);
		cout << "1. 기사    2. 궁수    3. 마법사"<<endl;

		cin >> iJob;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iJob <= JOB_NONE || iJob > JOB_END)
			iJob = JOB_NONE;
	}
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;

	switch (tPlayer.eJob) {
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "기사");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHPMax = 500;
		tPlayer.iHP = 500;
		tPlayer.iMP = 100;
		tPlayer.iMPMax = 100; break;


	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "궁수");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHPMax = 400;
		tPlayer.iHP = 400;
		tPlayer.iMP = 200;
		tPlayer.iMPMax = 200; break;

	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "마법사");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHPMax = 300;
		tPlayer.iHP = 300;
		tPlayer.iMP = 300;
		tPlayer.iMPMax = 300;  break;
	}
	//몬스터 생성
	_Monster tMonsterArr[MT_BACK - 1]{};

	//고블린 생성
	strcpy_s(tMonsterArr[0].strName, "고블린");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHP = 100;
	tMonsterArr[0].iHPMax = 100;
	tMonsterArr[0].iMP = 10;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldMin = 500;
	tMonsterArr[0].iGoldMax = 1500;


	//트롤 생성
	strcpy_s(tMonsterArr[1].strName, "트롤");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHP = 2000;
	tMonsterArr[1].iHPMax = 2000;
	tMonsterArr[1].iMP = 100;
	tMonsterArr[1].iMPMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldMin = 6000;
	tMonsterArr[1].iGoldMax = 8000;

	//드래곤 생성
	strcpy_s(tMonsterArr[2].strName, "드래곤");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHP = 30000;
	tMonsterArr[2].iHPMax = 30000;
	tMonsterArr[2].iMP = 20000;
	tMonsterArr[2].iMPMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldMin = 20000;
	tMonsterArr[2].iGoldMax = 50000;

	//상점에서 판매할 아이템 목록을 생성한다.
	_Item	tStoreWeapon[STORE_WEAPON_MAX] = {};
	_Item	tStoreArmor[STORE_ARMOR_MAX] = {};


	//(무기상점) 각 아이템 정보를 설정한다
	strcpy_s(tStoreWeapon[0].strName, "목검");
	strcpy_s(tStoreWeapon[0].strTypeName, "무기");
	strcpy_s(tStoreWeapon[0].strDesc, "나무로 만든 칼");
	tStoreWeapon[0].eType = IT_WEAPON;
	tStoreWeapon[0].iMin = 5;
	tStoreWeapon[0].iMax = 20;
	tStoreWeapon[0].iPrice = 4000;
	tStoreWeapon[0].iSell = 1500;

	strcpy_s(tStoreWeapon[1].strName, "활");
	strcpy_s(tStoreWeapon[1].strTypeName, "무기");
	strcpy_s(tStoreWeapon[1].strDesc, "쌍쌍한 활");
	tStoreWeapon[1].eType = IT_WEAPON;
	tStoreWeapon[1].iMin = 20;
	tStoreWeapon[1].iMax = 40;
	tStoreWeapon[1].iPrice = 7000;
	tStoreWeapon[1].iSell = 3500;

	strcpy_s(tStoreWeapon[2].strName, "지팡이");
	strcpy_s(tStoreWeapon[2].strTypeName, "무기");
	strcpy_s(tStoreWeapon[2].strDesc, "마법 지팡이");
	tStoreWeapon[2].eType = IT_WEAPON;
	tStoreWeapon[2].iMin = 90;
	tStoreWeapon[2].iMax = 150;
	tStoreWeapon[2].iPrice = 30000;
	tStoreWeapon[2].iSell = 15000;


	//(방어구 상점) 각 아이템 정보를 설정한다
	strcpy_s(tStoreArmor[0].strName, "천갑옷");
	strcpy_s(tStoreArmor[0].strTypeName, "방어구");
	strcpy_s(tStoreArmor[0].strDesc, "천으로 만든 허접한 갑옷");
	tStoreArmor[0].eType = IT_ARMOR;
	tStoreArmor[0].iMin = 2;
	tStoreArmor[0].iMax = 5;
	tStoreArmor[0].iPrice = 1000;
	tStoreArmor[0].iSell = 500;

	strcpy_s(tStoreArmor[1].strName, "가죽갑옷");
	strcpy_s(tStoreArmor[1].strTypeName, "방어구");
	strcpy_s(tStoreArmor[1].strDesc, "동물 가죽으로 만든 질긴 갑옷");
	tStoreArmor[1].eType = IT_ARMOR;
	tStoreArmor[1].iMin = 10;
	tStoreArmor[1].iMax = 20;
	tStoreArmor[1].iPrice = 7000;
	tStoreArmor[1].iSell = 3500;

	strcpy_s(tStoreArmor[2].strName, "플레이트아더");
	strcpy_s(tStoreArmor[2].strTypeName, "방어구");
	strcpy_s(tStoreArmor[2].strDesc, "강철로 만든 판금갑옷");
	tStoreArmor[2].eType = IT_ARMOR;
	tStoreArmor[2].iMin = 70;
	tStoreArmor[2].iMax = 90;
	tStoreArmor[2].iPrice = 10000;
	tStoreArmor[2].iSell = 15000;

	while (true) {
		system("cls");
		gotoxy(43, 1);
		cout << "--------------- LOBY --------------" << endl;
		gotoxy(43, 3);
		cout << "메뉴를 선택하세요." << endl;
		gotoxy(43, 5);
		cout << "1. 맵    ";
		cout << "2. 상점   ";
		cout << "3. 가방   ";

		textcolor(LIGHTRED, BLACK);
		cout << "4. 종료" << endl;

		#define LIGHTMAGENTA 13 
		/*MY PAGE 만들기*/

		textcolor(LIGHTMAGENTA, BLACK);

		gotoxy(80, 12);
		cout << "MY PAGE" << endl;
		gotoxy(80, 13);
		cout << "-------" << endl;
		//무기를 장착하고 있을 경우 공격력에 무기공격력을 추가하여 출력한다.

					gotoxy(80, 14);
					cout << "레벨 : " << "lv." << tPlayer.iLevel << endl;

					gotoxy(80, 15);
					cout << "게이지 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

					if (tPlayer.bEquip[EQ_WEAPON] == true) {
						gotoxy(80, 17);
						cout << "공격력 : " << tPlayer.iAttackMin << " + " <<		
							tPlayer.tEquip[EQ_WEAPON].iMax << " - " <<
							tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}

					else {
						gotoxy(80, 17);
						cout << "공격력 : " << tPlayer.iAttackMin << " - " <<
							tPlayer.iAttackMax;
					}

					////방어구를 장착하고 있을 경우 방어력에 방어구 방어력을 추가하여 출력한다.
					if (tPlayer.bEquip[EQ_ARMOR] == true) {
						gotoxy(80, 18);
						cout << "방어력 : " << tPlayer.iArmorMin << " - " <<
							tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}
					else {
						gotoxy(80, 18);
						cout << "방어력 : " << tPlayer.iArmorMin << " - " <<
							tPlayer.iArmorMax << endl;
					}

					if (tPlayer.bEquip[EQ_WEAPON]){
						gotoxy(80, 20);
						cout << "장착무기 : " << tPlayer.tEquip[EQ_WEAPON].strName;
					}

					else{
						gotoxy(80, 20);
						cout << "장착 무기 : 없음       ";
					}
					if (tPlayer.bEquip[EQ_ARMOR]){
						gotoxy(80, 21);

						cout << "장착 방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName;
					}
					else{
						gotoxy(80, 21);
						cout << "장착방어구 : 없음"<<endl;
					}
					
					gotoxy(80, 23);
					textcolor(WHITE, BLACK);
					cout << "보유골드 : " << tPlayer.tInventory.iGold << " Gold" << endl << endl;

		textcolor(YELLOW, BLACK);
		int iMenu;
		gotoxy(43, 6);
		cin >> iMenu;
		
		textcolor(YELLOW, BLACK);
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_MAP:
			while (true)
			{
				system("cls");
				gotoxy(43, 1);
				cout << "--------------- MAP --------------" << endl;
				gotoxy(43, 3);
				cout << "맵을 선택하세요." << endl;
				gotoxy(43, 5);
				cout << "1. 쉬움    ";
				cout << "2. 보통    ";
				cout << "3. 어려움  ";

				gotoxy(96, 27);
				cout << "4. 뒤로가기"<<endl;		

				gotoxy(43, 6);
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				//이 if문에 속한break는 맵 메뉴를 돌려주기 위한 while에 속해 있으므로
				//이 while문을 빠져나간다.

				if (iMenu == MT_BACK) break;

				//선택한 메뉴에서 1을 빼주면 몬스터 배열의 인덱스가 된다.
				//그렇게 해서 해당 맵의 몬스터를 생성해준다
				_Monster tMonster = tMonsterArr[iMenu - 1];

				while (true) {
					system("cls");
					switch (iMenu)
					{
					case MT_EASY:
						
						gotoxy(43, 2);
						cout << "--------------- " << tPlayer.strName<<" --------------" << endl; break;
						
						
							gotoxy(43, 2);
							cout << "--------------- " << "PLAYER" << " --------------" << endl; break;
						
					case MT_NORMAL:
						
							gotoxy(43, 2);
							cout << "--------------- " << tPlayer.strName << " --------------" << endl; break;
						
						
					case MT_HARD:
						
							gotoxy(43, 2);
							cout << "--------------- " << tPlayer.strName << " --------------" << endl; break;
						
					}
					//플레이어 정보 출력를 출력한다.

					/*gotoxy(43, 4);
					cout << "이름 : " << tPlayer.strName << endl;*/
					gotoxy(43, 4);
					cout << "직업 : " << tPlayer.strJobName << endl;
					gotoxy(43, 5);
					textcolor(WHITE, BLACK);
					
					 cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax << endl;
						
					
					
					textcolor(YELLOW, BLACK);
					gotoxy(43, 6);
					cout <<"경험치 : "<< tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;
					

					//몬스터 정보 출력
					gotoxy(43, 10);
					textcolor(LIGHTRED, BLACK);
					cout << "--------------- MONSTER ---------------" << endl;
					gotoxy(43, 11);
					cout << "종류 : " << tMonster.strName << endl;
					/*gotoxy(43, 15);
					cout <<"레벨 : " << "lv." << tPlayer.iLevel << endl;
					gotoxy(43, 16);
					cout << "공격력 : " << tMonster.iAttackMin << " - " <<
						tMonster.iAttackMin << " - " <<
						tMonster.iAttackMax << endl;
					gotoxy(43, 17);
						cout << "방어력 : " << tMonster.iArmorMin <<
						" - " << tMonster.iArmorMax << endl;*/
					gotoxy(43, 12);
					textcolor(WHITE, BLACK);
					cout << "체력 : " << tMonster.iHP << " / " << tMonster.iHPMax << endl;
					textcolor(LIGHTRED, BLACK);
					gotoxy(43, 13);
					cout << "마나 : " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
					gotoxy(43, 14);
					cout << "획득경험치 : " << tMonster.iExp << endl;
					gotoxy(43, 15);
					cout << "획득골드 : " <<tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;

					textcolor(YELLOW, BLACK);
					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl;
					cout << "3. 라운드 끝내기" << endl;
					cout << "메뉴를 선택하세요 : ";
					cin >> iMenu;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (iMenu == BATTLE_BACK) break;

					else if (iMenu == 3) break;

					switch (iMenu)
					{
					case BATTLE_ATTACK:
					{
						//예를 들어 Min 5 Max 15가정경우 
						//15 - 5+1을 하면 11이 된다. 11로 나눈 나머지는 0 ~10이
						//나오게 되고 여기에 Min값인 5를 더하게 되면
						//+1을 해서 5~15사이로 값이 나오게 되는것이다
						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iAttackMax;

						//무기를 장착하고 있을 경우 무기의 Min, Max를 더해준다.
						if (tPlayer.bEquip[EQ_WEAPON])
						{
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMax;
						}
						

						int iAttack = rand() % (iAttackMax -iAttackMin + 1) +
							iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
							tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						// 삼항연산자 : 조건식 ? true일때값 : false일때값;
						iDamage = iDamage < 1 ? 1 : iDamage;

						/*if (iDamage < 1)
							iDamage = 1;*/

							//몬스터 HP를 감소시킨다.

						
						tMonster.iHP -= iDamage;

						Sleep(300);
						cout << tPlayer.strName << " 가 " << tMonster.strName <<
							"에게 " << iDamage << " 피해를 입혔습니다." << endl;
						
						Sleep(300);
						//몬스터가 죽었을 경우를 처리한다.
						if (tMonster.iHP <= 0) {
							
							cout << tMonster.strName << " 몬스터가 사망하였습니다." << endl; 
							

							tPlayer.iExp += tMonster.iExp;
							int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
								tMonster.iGoldMin);
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iExp << " 경험치를 획득하였습니다. " << endl;
							cout << iGold << " Gold를 획득하였습니다." << endl;

							if (tMonster.iHP < 0){
								system("cls");
								//레벨업을 했는지 체크해본다.
								if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1]) {

									//플레이어 경험치를 레벨업에 필요한 경험치만큼 차감한다.
									tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];

									//레벨을 증가시킨다.
									++tPlayer.iLevel;

									cout << "레벨업 하였습니다." << endl;

									//능력치를 상승시킨다.
									//직업 인덱스를 구한다.
									int iJobIndex = tPlayer.eJob - 1;
									int AttackUp = rand() % (tLvUpTable[iJobIndex].iAttackMax - tLvUpTable[iJobIndex].iAttackMin + 1) +
										tLvUpTable[iJobIndex].iAttackMin;
									int iArmorUp = rand() % (tLvUpTable[iJobIndex].iArmorMax - tLvUpTable[iJobIndex].iArmorMin + 1) +
										tLvUpTable[iJobIndex].iArmorMin;
									int iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin + 1) +
										tLvUpTable[iJobIndex].iHPMin;
									int iMPUp = rand() % (tLvUpTable[iJobIndex].iHPMin - tLvUpTable[iJobIndex].iHPMin + 1) +
										tLvUpTable[iJobIndex].iMPMin;

									tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
									tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMax;
									tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
									tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

									tPlayer.iHPMax += iHPUp;
									tPlayer.iMPMax += iMPUp;

									//체력과 마나를 회복시킨다.
									tPlayer.iHP = tPlayer.iHPMax;
									tPlayer.iMP = tPlayer.iMPMax;
								}

								#define LIGHTCYAN 11
								textcolor(LIGHTCYAN, BLACK);
								gotoxy(20, 1);
								cout << " _______  _______  __   __  _______    _______  ___      _______  _______  ______   " << endl;
								gotoxy(20, 2);
								cout << "|       ||   _   ||  |_|  ||       |  |       ||   |    |       ||   _   ||    _ |  " << endl;
								gotoxy(20, 3);
								cout << "|    ___||  |_|  ||       ||    ___|  |       ||   |    |    ___||  |_|  ||   | ||  " << endl;
								gotoxy(20, 4);
								cout << "|   | __ |       ||       ||   |___   |       ||   |    |   |___ |       ||   |_||_ " << endl;
								gotoxy(20, 5);
								 cout <<"|   ||  ||       ||       ||    ___|  |      _||   |___ |    ___||       ||    __  |"<<endl;
								gotoxy(20, 6);
								cout << "|   |_| ||   _   || ||_|| ||   |___   |     |_ |       ||   |___ |   _   ||   |  | |"<<endl;
								gotoxy(20, 7);
								cout << "|_______||__| |__||_|   |_||_______|  |_______||_______||_______||__| |__||___|  |_|" << endl<<endl;

								textcolor(YELLOW, BLACK);
								cout << "게임으로 돌아가시겠습니까? " << endl;
								cout << "1. 돌아가기\t" << endl;

								cin >> iMenu;
								if (iMenu == 1) {
									break;		
								}
								
							}
							
							/*tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;  무한부활*/
							
						}
						// 몬스터가 살아있다면 플레이어를 공격한다.
						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
							tMonster.iAttackMin;

						int iArmorMin = tPlayer.iArmorMin;
						int iArmorMax = tPlayer.iArmorMax;

						if (tPlayer.bEquip[EQ_ARMOR]) {
							iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						}

						iArmor = rand() % (iArmorMax - iArmorMin + 1) +
							iArmorMin;


						iDamage = iAttack - iArmor;
						// 삼항연산자 : 조건식 ? true일때값 : false일때값;
						iDamage = iDamage < 1 ? 1 : iDamage;

						/*if (iDamage < 1)
							iDamage = 1;*/

						//몬스터 HP를 감소시킨다.
						tPlayer.iHP -= iDamage;

						Sleep(300);
						cout << tMonster.strName << " 가 " << tPlayer.strName <<
							"에게 " << iDamage << " 피해를 입혔습니다." << endl;

						Sleep(300);
						if (tPlayer.iHP <= 0) {
							cout << tPlayer.strName << " 플레이어가 사망하였습니다." << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << " 경험치를 잃었습니다." << endl;
							cout << iGold << " Gold를 잃었습니다." << endl;

							////플레이어의 HP 와 MP를 회복한다.
							/*tPlayer.iHP = tPlayer.iHPMax;
							tPlayer.iMP = tPlayer.iMPMax;*/

							system("cls");
							textcolor(LIGHTRED, BLACK);
							gotoxy(20, 1);
							cout << "_______  _______  __   __  _______    _______  __   __  _______  ______   " << endl;
							gotoxy(20, 2);
							cout << "|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  " << endl;
							gotoxy(20, 3);
							cout << "|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  " << endl;
							gotoxy(20, 4);
							cout << "|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ " << endl;
							gotoxy(20, 5);
							cout << "|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |" << endl;
							gotoxy(20, 6);
							cout << "|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |" << endl;
							gotoxy(20, 7);
							cout << "|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|" << endl<<endl;
							
							textcolor(YELLOW, BLACK);
							exit(0);

						}
						/*system("pause");*/

					}
					break;
					}

				}
		case MM_STORE:
			while (true)
			{
				system("cls");
				gotoxy(43, 1);
				cout << "---------------STORE---------------" << endl;
				gotoxy(43, 3);
				cout << "상점을 선택하세요.";
				gotoxy(43, 5);
				cout << "1. 무기상점        ";
				cout << "2. 방어구상점"<<endl;
				gotoxy(96, 27);
				cout << "3. 뒤로가기"<<endl;
				
				gotoxy(43, 6);
				cin >> iMenu;


				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == SM_BACK) break;

				switch (iMenu) {
				case SM_WEAPON:
					while (true) {
						system("cls");
						gotoxy(43, 1);
						cout << "--------------- 무기상점---------------" << endl;
						//판매목록을 보여준다
						for (int i = 0; i < STORE_WEAPON_MAX; ++i)
						{
							
							cout << i + 1 << ". 이름 : " << tStoreWeapon[i].strName <<
								"\t종류 : " << tStoreWeapon[i].strTypeName << endl;
							
							cout << "공격력 : " << tStoreWeapon[i].iMin << " - "
								<< tStoreWeapon[i].iMax << endl;
							
							cout << "판매가격 : " << tStoreWeapon[i].iPrice <<
								"\t구매가격 : " << tStoreWeapon[i].iSell << endl;
							
							cout << "설명 : " << tStoreWeapon[i].strDesc << endl << endl;
						}
						gotoxy(96, 15);
						cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;

						cout << endl;
						textcolor(WHITE, BLACK);
						cout << "보유금액 : " << tPlayer.tInventory.iGold << "Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl<<endl;

						textcolor(YELLOW, BLACK);
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> iMenu;

						if (cin.fail()) {
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == STORE_WEAPON_MAX + 1)
							break;

						else if (iMenu<1 || iMenu > STORE_WEAPON_MAX + 1) {
							textcolor(LIGHTRED, BLACK);
							cout << "잘못 선택하였습니다." << endl;
							textcolor(YELLOW, BLACK);
							system("pause");
							continue;
						}
						//상점 판매목록 배열의 인덱스를 구해준다.
						int iWeaponIndex = iMenu - 1;

						//인벤토리가 꽉찼는지 검사한다.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}

						//돈이 부족할 경우
						else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice) {
							cout << "보유금이 부족합니다." << endl;
							system("pause");
							continue;
						}
						//처음에 iItemCount는 하나도 추가되어 있지 않기 때문에 0으로 초기화
						//되어있으므로 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고
						//카운트가 1이 된다. 다음번에 추가할 때는 1번 인덱스에 추가하게 된다.
						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreWeapon[iWeaponIndex];
						++tPlayer.tInventory.iItemCount;

						//골드를 차감한다.
						tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;

						cout << tStoreWeapon[iWeaponIndex].strName << " 아이템을 구매하였습니다." << endl;
						system("pause");
					}
					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");
						gotoxy(43, 1);
						cout << "------------ 방어구상점 ------------" << endl;

						//판매 목록을 보여준다.
						for (int i = 0; i < STORE_ARMOR_MAX; ++i) {
							
							cout << i + 1 << ". 이름 : " << tStoreArmor[i].strName <<
								"\t종류 : " << tStoreArmor[i].strTypeName << endl;
							
							cout << "공격력 : " << tStoreArmor[i].iMin << " - " <<
								tStoreArmor[i].iMax << endl;
							
							cout << "판매가격 : " << tStoreArmor[i].iPrice <<
								"\t구매가격 : " << tStoreArmor[i].iSell << endl;
							
							cout << "설명 : " << tStoreArmor[i].strDesc << endl << endl;
						}
						gotoxy(96, 15);
						cout << STORE_ARMOR_MAX + 1 << ". 뒤로가기" << endl;
						cout << endl;

						textcolor(WHITE, BLACK);
						cout << "보유금액 : " << tPlayer.tInventory.iGold << " Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl<<endl;

						textcolor(YELLOW, BLACK);
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> iMenu;

						if (cin.fail()) {
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == STORE_ARMOR_MAX + 1)
							break;

						else if (iMenu<1 || iMenu > STORE_ARMOR_MAX + 1) {
							textcolor(LIGHTRED, BLACK);
							cout << "잘못 선택하였습니다." << endl;
							textcolor(YELLOW, BLACK);
							system("pause");
							continue;
						}

						//상점 판매목록 배열의 인덱스를 구해준다.
						int iArmorIndex = iMenu - 1;

						//인벤토리가 꽉찼는지 검사한다.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}

						//돈이 부족할 경우
						else if (tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice) {
							cout << "보유금이 부족합니다." << endl;
							system("pause");
							continue;
						}
						//처음에 iItemCount는 하나도 추가되어 있지 않기 때문에 0으로 초기화
						//되어있으므로 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고
						//카운트가 1이 된다. 다음번에 추가할 때는 1번 인덱스에 추가하게 된다.
						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreArmor[iArmorIndex];
						++tPlayer.tInventory.iItemCount;

						//골드를 차감한다.
						tPlayer.tInventory.iGold -= tStoreWeapon[iArmorIndex].iPrice;

						cout << tStoreArmor[iArmorIndex].strName << " 아이템을 구매하였습니다." << endl;
						system("pause");
					}
					break;
				}
			}
			break;
		case MM_INVENTORY:
			while (true)
			{

				system("cls");
				gotoxy(43, 1);
				cout << "------------------- BAG ------------------" << endl;

				gotoxy(43, 3);
				cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
					"\t마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

				gotoxy(43, 2);
				cout << "보유골드 : " << tPlayer.tInventory.iGold << " Gold" << endl << endl;

				
				for (int i = 0; i < tPlayer.tInventory.iItemCount; i++) {
					
					cout << i + 1 << ". 이름 : " << tPlayer.tInventory.tItem[i].strName <<
						"\t종류 : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
					
					cout << "공격력 : " << tPlayer.tInventory.tItem[i].iMin << " - "
						<< tPlayer.tInventory.tItem[i].iMax << endl;
					
					cout << "판매가격 : " << tPlayer.tInventory.tItem[i].iPrice <<
						"\t구매가격 : " << tPlayer.tInventory.tItem[i].iSell << endl;
					
					cout << "설명 : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
				}

				gotoxy(96, 10);
				cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
				cout << "장착할 아이템을 선택하세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == tPlayer.tInventory.iItemCount + 1)
					break;

				else if (iMenu<1 || iMenu > tPlayer.tInventory.iItemCount + 1) {

					textcolor(LIGHTRED, BLACK);
					cout << "잘못 선택하였습니다." << endl;
					textcolor(YELLOW, BLACK);
					system("pause");
					continue;
				}
				//아이템 인덱스를 구해준다.
				int idx = iMenu - 1;

				//제대로 선택했을 경우 해당 아이템의 종류에 따라 장착 부위를 결정


				EQUIP eq;


				switch (tPlayer.tInventory.tItem[idx].eType) {
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}
				//아이템이 장착되어 있을경우 장착되어있는 아이템과 장착할 아이템을 
				//교체해 주어야한다. Swap  알고리즘을 활용한다.
				if (tPlayer.bEquip[eq] == true)
				{
					_Item tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				//장착되어있지 않을 경우 인벤토리 아이템을 장착창으로 옮기로
				//인벤토리는 1칸 비워지게 된다.
				else {
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; ++i) {
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}
					--tPlayer.tInventory.iItemCount;

					//장착을 했기 때문에 true로 만들어준다.
					tPlayer.bEquip[eq] = true;
				}
				cout << tPlayer.tEquip[eq].strName << "아이템을 장착하였습니다." << endl;
				system("pause");
			}
			break;
		default:
			textcolor(LIGHTRED, BLACK);
			cout << "잘 못선택하셨습니다." << endl;
			textcolor(YELLOW, BLACK);
			break;
			}
		}
	}
	return 0;

}