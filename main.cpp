#include <allegro.h>
#include "GameObject.h"
//#include <time.h>

const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 600;
const int OBJ_HEIGHT = 75;
const int OBJ_WIDTH = 75;

volatile int speed_counter = 0;

//starting pos
int speed = 1200;

BITMAP *buffer;
BITMAP *mycircle;
BITMAP *myshadow;
BITMAP *mysquare;
GameObject player;
GameObject ball[32];
int score;
int highscore;
int GFXMODE;
int level;
int goal;
int dead;
int menu;

void increment_speed_counter(){
	speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter)

void moveCircle(){


	clear_keybuf();
	//move player
	if (key[KEY_LEFT] && player.getX() > 0)
		player.setX(player.getX()-1);
	if (key[KEY_RIGHT] && player.getX() < MAX_WIDTH - OBJ_WIDTH)
		player.setX(player.getX()+1);

	//move circles
	for(int i = 0; i<32;i++){
		if (ball[i].getY() < -MAX_HEIGHT){
			ball[i].setX(rand() % MAX_WIDTH - 50);
			ball[i].setY(-1*(rand() % MAX_HEIGHT));
		}
		else
			ball[i].setY(ball[i].getY()+1);

		if (ball[i].getY() > MAX_HEIGHT){
			ball[i].setY(-(MAX_HEIGHT+1));
			score++;
		}

		//collision!

		if ((ball[i].getY()+OBJ_HEIGHT >player.getY() && ball[i].getX()+OBJ_WIDTH > player.getX() &&
				ball[i].getY()+OBJ_HEIGHT < player.getY()+OBJ_HEIGHT && ball[i].getX()+OBJ_WIDTH < player.getX() + OBJ_HEIGHT) ||
				(ball[i].getY()+OBJ_HEIGHT >player.getY() && ball[i].getX()> player.getX() &&
						ball[i].getY()+OBJ_HEIGHT <player.getY()+OBJ_HEIGHT && ball[i].getX()< player.getX()+OBJ_WIDTH ) ||
						(ball[i].getY() > player.getY() && ball[i].getX() > player.getX() &&
								ball[i].getY() < player.getY()+OBJ_HEIGHT && ball[i].getX() < player.getX()+OBJ_WIDTH) ||
								(ball[i].getY() > player.getY() && ball[i].getX()+OBJ_WIDTH > player.getX() &&
										ball[i].getY() < player.getY()+OBJ_HEIGHT && ball[i].getX()+OBJ_WIDTH < player.getX()+OBJ_WIDTH))
			dead = 1;
	}

	if (ball[level].getAlive()==0)
		ball[level].setAlive(1);

	if (score > goal){
		goal = goal + (level+1)*10;
		level++;
		if (level > 31)
			level = 31;
	}

}

void Draw(){
	acquire_screen();
	draw_sprite(screen,buffer,0,0);
	release_screen();
}

void initialize(){
	srand(time(NULL));
	//draw objects
	mycircle = create_bitmap_ex(32,OBJ_WIDTH,OBJ_HEIGHT);
	rectfill(mycircle,0,0,OBJ_WIDTH,OBJ_HEIGHT,makecol(255,0,255)); //make it black
	circlefill(mycircle,OBJ_WIDTH/2,OBJ_HEIGHT/2,OBJ_WIDTH/2,makecol(0,255,0));

	myshadow = create_bitmap_ex(32,OBJ_WIDTH,OBJ_HEIGHT);
	rectfill(myshadow,0,0,OBJ_WIDTH,OBJ_HEIGHT,makecol(255,0,255)); //make it black
	circlefill(myshadow,OBJ_WIDTH/2,OBJ_HEIGHT/2,OBJ_WIDTH/2,makecol(0,0,0));

	mysquare = create_bitmap_ex(32,OBJ_WIDTH,OBJ_HEIGHT);
	rectfill(mysquare,0,0,OBJ_WIDTH,OBJ_HEIGHT,makecol(0,0,255));

	player.startup(OBJ_WIDTH,OBJ_HEIGHT,mysquare,buffer);
	for (int i = 0; i<32;i++){
		ball[i].startup(OBJ_HEIGHT,OBJ_WIDTH,mycircle,buffer);
		ball[i].setShadow(myshadow);
	}
	highscore = 0;
	menu = 1;
}

void reset(){
	clear_to_color(buffer, makecol(0,0,0));
	score = 0;
	player.setX(MAX_WIDTH/2);
	player.setY(MAX_HEIGHT-OBJ_HEIGHT);
	level = 0;
	goal=10;
	dead=0;
	for (int i = 0; i<32;i++){
		ball[i].setX(-(MAX_WIDTH+1));
		ball[i].setY(-(MAX_HEIGHT+1));
		ball[i].setAlive(0);
	}
	ball[0].setAlive(1);
}

void gameOver(){

	textprintf_centre_ex( buffer, font,MAX_WIDTH/2,MAX_HEIGHT/2,makecol(255,255,0),makecol( 0, 0, 0),"Game over! You got: %d",score);
	if (score > highscore){
		textprintf_centre_ex( buffer, font,MAX_WIDTH/2,MAX_HEIGHT/2+10,makecol(255,0,0),makecol( 0, 0, 0),"New High Score!");
		highscore = score;
	}
	textprintf_centre_ex( buffer, font,MAX_WIDTH/2,MAX_HEIGHT/2+20,makecol(255,255,0),makecol( 0, 0, 0),"Press [ENTER] to try again;");
	textprintf_centre_ex( buffer, font,MAX_WIDTH/2,MAX_HEIGHT/2+30,makecol(255,255,0),makecol( 0, 0, 0),"[ESC] to quit.");

}
int main(){

	allegro_init();
	install_keyboard();
	set_color_depth(32);
	GFXMODE=GFX_AUTODETECT_WINDOWED;
	set_gfx_mode( GFXMODE, MAX_WIDTH, MAX_HEIGHT, 0, 0);
	buffer = create_bitmap_ex(32,MAX_WIDTH,MAX_HEIGHT);

	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(speed));

	initialize();
	reset();

	while (!key[KEY_ESC]){


		while (menu == 1){

			textprintf_centre_ex( buffer, font,MAX_WIDTH/2,MAX_HEIGHT/2,makecol(255,255,0),makecol( 0, 0, 0),"Doug's Dodge Game");
			textprintf_centre_ex( buffer, font,MAX_WIDTH/2,MAX_HEIGHT/2+10,makecol(255,255,0),makecol( 0, 0, 0),"Press [ENTER] to start and [ESC] to quit.");

			if (key[KEY_ENTER] || key[KEY_ESC]){
				menu = 0;
				reset();
			}

			Draw();
		}

		while (speed_counter > 0){

			if (dead != 1)
				moveCircle();
			else {
				gameOver();
				if (key[KEY_ENTER])
					reset();
			}

			if(key[KEY_EQUALS] && speed < 5000) {
				speed++;
				install_int_ex(increment_speed_counter, BPS_TO_TIMER(speed));
			}
			else if (key[KEY_MINUS] && speed > 0) {
				speed--;
				install_int_ex(increment_speed_counter, BPS_TO_TIMER(speed));
			}

			if((key[KEY_ALT] || key[KEY_ALTGR]) && key[KEY_ENTER]){
				if(GFXMODE == GFX_AUTODETECT_WINDOWED)
					GFXMODE = GFX_AUTODETECT_FULLSCREEN;
				else
					GFXMODE = GFX_AUTODETECT_WINDOWED;
				set_gfx_mode( GFXMODE, MAX_WIDTH, MAX_HEIGHT, 0, 0);
			}

			textprintf_right_ex( buffer, font,790,590,makecol(255,255,0),makecol( 0, 0, 0),"%d",speed);
			if (highscore > 0)
				textprintf_right_ex( buffer, font,MAX_WIDTH-10,10,makecol(255,0,0),makecol( 0, 0, 0),"High Score: %d",highscore);
			textprintf_ex( buffer, font,10,10,makecol(255,255,0),makecol( 0, 0, 0),"Score: %d",score);
			speed_counter--;
		}

		Draw();
	}
	return 0;
}
END_OF_MAIN()
