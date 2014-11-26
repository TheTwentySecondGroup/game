/*
 * io.h
 *
 *  Created on: 2014/11/25
 *      Author: chihiro
 */

#ifndef SOURCE_IO_H_
#define SOURCE_IO_H_


#define KEY_MAX 10
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


using namespace std;

class GameIO {
public:
	//0==off    0<key[i]  on
	int key[KEY_MAX];

	SDL_Joystick *joystick;

	void routine();
	GameIO();
	~GameIO();
};



#endif /* SOURCE_IO_H_ */
