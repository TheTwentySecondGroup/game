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

	Title();

	~Title();
	void routine();
	void drawTitle();
	//void delTitle();
	void drawMenuCube(int x, int y, GLuint *texture, double sw);
};
}
#endif
