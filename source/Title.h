#ifndef __TITLE_H__
#define __TITLE_H__

#define CHOICE_MIN 1
#define CHOICE_MAX 3

//#include "system.h"

namespace std {

class Title {
public:

	int sel;
	int KeyFlag;
	GLuint *titleImage[7];
	string menuString[CHOICE_MAX];
	Title();

	~Title();
	void routine();
	void drawTitle();
	//void delTitle();
	void drawMenuCube(int x, int y, GLuint *texture, double sw);
	void drawMenu(int x, int y, int w, int h,string mes) ;
};
}
#endif
