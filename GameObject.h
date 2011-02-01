/*
 * GameObject.h
 *
 *  Created on: Jan 24, 2011
 *      Author: Doug
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <allegro.h>

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	void startup(int width, int height, BITMAP *bm, BITMAP *buff);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void draw(BITMAP *buffer);
	void setSprite(BITMAP *bm);
	void setAlive(int al);
	int getAlive();
	void setShadow(BITMAP *sh);

protected:
	int x_pos;
	int y_pos;
	int shadow_x;
	int shadow_y;
	int alive;
	BITMAP *sprite;
	BITMAP *shadow;
	BITMAP *buffer;
};

#endif /* GAMEOBJECT_H_ */
