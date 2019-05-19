#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define LEFT 104
#define UP 107
#define RIGHT 108
#define DOWN 106
#define UNDO 117
#define NEW  110
#define REPLAY 114
#define EXIT 101
#define SAVE 115
#define FILE_LOAD 102
#define DISPLAY_HELP 100
#define TOP 116
#define LF 10
#define CR 13

#define WALL 35
#define EMPTY 46
#define GOLD 36
#define PLAYER 64
#define STORAGE 79

#define NUMBER_OF_MAPS 5

#define MAPSIZE 31


// 위치 정보를 가지는 구조체
typedef struct _tagPosition {
	int x;
	int	y;
}POSITION, * PPOSITION;

// 맵의 정보를 가지고 있는 구조체
typedef struct _tagMapData {
	int map[MAPSIZE][MAPSIZE];	// 맵 정보를 저장하는 배열
	int width, height;			// 맵의 높이와 길이
	POSITION playerInitPos;		// 플레이어의 시작점

}MAPDATA, * PMAPDATA;

int getch();				// 화면에 문자를 출력하지 않고 입력을 받는 함수
void gotoxy(int x, int y);		// 화면의 커서를 움직이는 함수
int MapLoading();				// map파일로부터 맵을 로딩하는 함수
int SetMap(int level);			// 현재 플레이할 맵을 레벨이 level인 맵으로 변경
void Render();					// 화면 출력을 담당하는 함수

// 저장되어야할 정보
int			currentLevel = 0;	// 현재 맵의 레벨 0 ~ 4
MAPDATA		cMapData;			// 여기의 map 변수에는 금의 위치만 표시
POSITION	cPos;				// 캐릭터의 현재 위치

// 저장되지 않아도 되는 정보
MAPDATA		mapData[NUMBER_OF_MAPS];		// File로 부터 받아온 맵 정보

/*
- h(왼쪽), j(아래), k(위), l(오른쪽) : 왼쪽 아래 위 오른쪽 창고지기 조정
- f(file load) : sokoban save 파일에서 저장된 내용을 읽어 시점에서부터 이어서 게임하게 함
*/

int main() {
	// map 파일로 부터 맵 정보를 읽어옴
	if (!MapLoading()) {
		fprintf(stderr, "MapLoading() Error\n");
		return 0;
	}

	// 처음 맵의 정보를 가져와서 적용함
	if (!SetMap(0)) {
		fprintf(stderr, "Init SetMap() Error\n");
		return 0;
	}

	Render(); // 화면에 맵 출력

}


// 화면에 맵을 출력하는 함수
void Render() {
	gotoxy(0, 0);

	for (int y = 0; y < mapData[currentLevel].height; y++, printf("\n")) {
		for (int x = 0; x < mapData[currentLevel].width; x++) {
			if (cPos.x == x && cPos.y == y)
				printf("%c", PLAYER);
			else if (cMapData.map[y][x] != EMPTY)
				printf("%c", GOLD);
			else if (mapData[currentLevel].map[y][x] == WALL || mapData[currentLevel].map[y][x] == STORAGE)
				printf("%c", mapData[currentLevel].map[y][x]);
			else
				printf(" ");
		}
	}
}

int MapLoading() {
	FILE* mapFile;

	if (access("map.txt", 0) == -1) {
		fprintf(stderr, "map.txt 파일이 존재하지 않습니다.\n");
		return 0;
	}

	if ((mapFile = fopen("map.txt", "r")) == 0) {
		printf("map.txt 파일을 불러오지 못 했습니다.\n");
		return 0;
	}

	char s[MAPSIZE];	// 한 줄씩 받아오기 위한 변수
	int returnValue = 1;	// 리턴 값 1 == 정상작동, 0 == 비정상작동

	int strLength = 0;	// 현재 읽어드린 문자열의 길이 
	int level = -1;		// 현재 로드하는 맵의 레벨
	int currentY = 0;	// 현재 로드 중인 맵의 Y축 위치

	int goldCount = 0, storageCount = 0; // 금괴 개수와 저장소 개수가 맞는 확인하는 변수
	while (fscanf(mapFile, "%s", s) != EOF) { // 입력이 존재하면
		strLength = strlen(s);
		if (strLength > 30) {
			printf("적합하지 않은 map파일입니다.\n");
			returnValue = 0;
			break;
		}

		if (strLength == 1) {
			if (s[0] == 'e')
				break;
			else if (s[0] - '0' > 0) {
				if (goldCount != storageCount) {
					printf("%d번 맵의 골드와 보관장소의 개수가 맞지 않습니다.\n", level);
					returnValue = 0;
				}
				goldCount = 0;
				storageCount = 0;

				level = s[0] - '0';
				currentY = 0;
			}
		}
		else {
			if (level - 1 >= 0) {
				if (currentY == 0)
					mapData[level - 1].width = strLength;
				for (int i = 0; i < strLength; i++) {
					if (s[i] == GOLD)
						goldCount++;
					else if (s[i] == STORAGE)
						storageCount++;

					if (s[i] == PLAYER) {
						mapData[level - 1].playerInitPos.x = i;
						mapData[level - 1].playerInitPos.y = currentY;
						mapData[level - 1].map[currentY][i] = EMPTY;
					}
					else
						mapData[level - 1].map[currentY][i] = s[i];
				}
				mapData[level - 1].height = ++currentY;
				if (currentY + 1 > 30) {
					printf("적합하지 않은 map파일입니다.\n");
					returnValue = 0;
					break;
				}
			}
		}
		//printf("%s\n", s);
	}

	fclose(mapFile);
	return returnValue;
}

int SetMap(int level) {
    	
	currentLevel = level; // 현재 게임 레벨을 level로 설정
	if (!(mapData[currentLevel].width > 0 && mapData[currentLevel].height > 0)) // level에 해당하는 맵이 존재하지 않으면 게임 종료
		return 0;

	cMapData.width = mapData[currentLevel].width; // 현재 맵의 금괴 정보를 담는 cMapData의 width, height 설정
	cMapData.height = mapData[currentLevel].height;

	// cMapData는 금괴의 정보를 담고 있는 배열로 
	// 원본 맵에서 금괴위치 말고는 EMPTY로 초기화
	for (int y = 0; y < cMapData.height; y++) {
		for (int x = 0; x < cMapData.width; x++) {
			if (mapData[currentLevel].map[y][x] == GOLD)
				cMapData.map[y][x] = mapData[currentLevel].map[y][x];
			else
				cMapData.map[y][x] = EMPTY;
		}
	}
	cMapData.playerInitPos = mapData[currentLevel].playerInitPos; // 플레이어 초기 위치 설정
	cPos = cMapData.playerInitPos; // 플레이어의 현재 위치를 초기 위치로 설정

	system("clear"); // 화면 비우기
	Render(); // 맵 출력
	return 1;
}

void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);		// 터미널 상에서 x, y좌표로 커서를 이동
	fflush(stdout);				// 출력 버퍼를 비움
}

int getch() {
	int c;
	struct termios oldattr, newattr;

	tcgetattr(STDIN_FILENO, &oldattr);		// 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO); 	// CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;			// 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;			// 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);	// 터미널에 설정 입력
	c = getchar();				// 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);	// 원래의 설정으로 복구
	return c;
}
