#include "headers/putc.h"

unsigned short *vram = (unsigned short*)VIDEO; // Base address of video mem
int color = CW; // white text on black background
int x = 0;
int y = 0;

//function takes in ascii code for char to write to screen.
void putc(int data)
{
	switch(data)
	{
		case '\r': //carriage return
			x = 0;
			break;
		case '\n': //new line
			y += 1;
			x = 0;
			break;
		case 0x08: //backspace
			if(x != 0)
			{
				x -=1;
			}
			else
			{
				y -=1;
				x = 79;
			}
			vram[x + COLUMNS * y] = 0x0720;
			break;
		case 0x09: //tab
			x += 4;
			break;
		case 0x20: //space
			if(x != 80)
			{
				x += 1;
			}
			else
			{
				x = 0;
				y += 1;
			}
			break;
		case 0x101: //up arrow
			if(y != 0)
				y -= 1;
			break;
		case 0x102: //left arrow
			if(x != 0)
                        {
                                x -=1;
                        }
                        else
                        {
                                y -=1;
                                x = 79;
                        }
			break;
		case 0x104: //down arrow
			if(y != 25)
				y += 1;
			break;
		case 0x103: //right arrow
			if(x != 80)
                        {
                                x += 1;
                        }
                        else
                        {
                                x = 0;
                                y += 1;
                        }
                        break;
		default:
			vram[x + COLUMNS * y] = color; //white color for char
			vram[x + COLUMNS * y] = vram[x + COLUMNS * y] << 8; //shifts 8 bits to be able to place ascii code after
			vram[x + COLUMNS * y] += data; //adds char
	
			x += 1; //moves to next place in video memory;
		
			if(x >= COLUMNS)
			{
				x = 0;
				y += 1;
			}
	}
	//checks if written over 24 lines and moves each line up once
        if(y == ROWS)
        {
                moveLines();
        }
}

//inserts char at specific location
void insertc(int _x, int _y, int data)
{
	vram[_x + COLUMNS * _y] = color;
	vram[_x + COLUMNS * _y] = vram[_x + COLUMNS * _y] << 8;
	vram[_x + COLUMNS * _y] += data;
}

//moves lines up once reached end of video memory
void moveLines()
{
	unsigned short *temp = (unsigned short*)VIDEO;

	//for every line does it 24 times
	for(int z = 0; z < ROWS; z++)
	{
		//80 chars per line
		for(int w = 0; w < COLUMNS; w++)
		{
			temp[w + COLUMNS * z] = color;
			temp[w + COLUMNS * z] = temp[w + COLUMNS] << 8;
			temp[w + COLUMNS * z] += temp[w + COLUMNS * z + COLUMNS];
		}
	}

	//removes anything left in current line
	for(int w = 0; w < COLUMNS; w++)
	{
		temp[w + COLUMNS * ROWS] = 0x0720;
	}

	//moves one line up to give scrolling effect
	y -= 1;
}
