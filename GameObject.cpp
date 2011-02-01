/*
 * GameObject.cpp
 *
 *  Created on: Jan 24, 2011
 *      Author: Doug
 */

#include "GameObject.h"

GameObject::GameObject() {
	// TODO Auto-generated constructor stub

}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
}

void GameObject::startup(int width, int height, BITMAP *bm, BITMAP *buff){
	x_pos = -50; //start off screen
	y_pos = -50;
	shadow_x = -50;
	shadow_y = -50;
	sprite = bm;
	buffer = buff;
    shadow=create_bitmap_ex(32,width,height);
    rectfill(shadow,0,0,width,height,makecol(0,0,0));
    alive = 1;
}

void GameObject::setX(int x) {

	if (alive == 0) return;
	draw_sprite(buffer, shadow, shadow_x,shadow_y);
	x_pos = x;
	draw_sprite(buffer,sprite,x_pos,y_pos);
	shadow_x=x_pos;
	shadow_y=y_pos;
}

void GameObject::setY(int y){
	if (alive == 0) return;
	draw_sprite(buffer, shadow, shadow_x,shadow_y);
	y_pos = y;
	draw_sprite(buffer,sprite,x_pos,y_pos);
	shadow_y=y_pos;
	shadow_x=x_pos;
}

int GameObject::getX(){
	return x_pos;
}

int GameObject::getY(){
	return y_pos;
}

void GameObject::setSprite(BITMAP *bm){
	sprite = bm;
}

void GameObject::setAlive(int al){
	alive = al;
}

int GameObject::getAlive(){
	return alive;
}

void GameObject::setShadow(BITMAP* sh){
	shadow = sh;
}
