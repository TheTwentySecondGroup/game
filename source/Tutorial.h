#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#define SLIDE_MAX 1
class Tutorial {
public:
	//System *sys;
	int Slide;

	void routine();
	void draw(int n);

	Tutorial();
	~Tutorial();


	void drawText();
};
#endif
