/*
 * io.h
 *
 *  last update 2015/02/12
 *      Author: Murokawa
 */

#ifndef SOURCE_IO_H_
#define SOURCE_IO_H_


#define KEY_MAX 20
#define KEY_MAX_COUNT 4000

//keylist
#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_RIGHT 2
#define KEY_LEFT 3
#define KEY_A 4
#define KEY_B 5
#define KEY_C 6
#define KEY_D 7
#define KEY_E 8

using namespace std;

class GameIO {
public:
	//0==off    0<key[i]  on
	int key[KEY_MAX];//キー情報

	SDL_Joystick *joystick;//ジョイスティックハンドル

	void routine();//処理ルーチン
	GameIO();
	~GameIO();
};



#endif /* SOURCE_IO_H_ */
