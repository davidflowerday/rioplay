// Rioplay - Replacement Rio Receiver player software
// Copyright (C) 2002 David Flowerday
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 2 as published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <stdio.h>
#include <string.h>
#include "StatusScreen.hh"
#include "NumbersBitmaps.h"
#include "Tag.h"

StatusScreen::StatusScreen(void) {
    Minutes = 0;
    Seconds = 0;
    Title[0] = '\0';
    Artist[0] = '\0';
    TitleArtistChanged = false;
}

StatusScreen::~StatusScreen(void) {
}


void StatusScreen::Update(char *Display) {
    if(TitleArtistChanged == true) {
        bzero(Display, 4096);
        TitleArtistChanged = false;
    }
    DrawTime(Display, Minutes, Seconds);
    StatusFont.DrawString(Display, Title, 0, 5);
    StatusFont.DrawString(Display, Artist, 0, 17);
    StatusFont.DrawString(Display, Album, 0, 27);
    DrawHorizontalLine(Display, 0, 15, 128);
}

void StatusScreen::SetTime(unsigned short NewMinutes, unsigned short NewSeconds) {
    Minutes = NewMinutes;
    Seconds = NewSeconds;
}

void StatusScreen::SetAttribs(Tag TrackTag) {
    strcpy(Title, TrackTag.Title);
    strcpy(Artist, TrackTag.Artist);
    strcpy(Album, TrackTag.Album);
    TitleArtistChanged = true;
}

void StatusScreen::DrawTime(char *Display, int minutes, int seconds) {
    /* Draw minute */
    DrawNum(Display, minutes % 10, 74, 40);
    
    /* Draw colon */
    DrawColon(Display, 90, 40);
    
    /* Draw seconds */
    DrawNum(Display, seconds / 10, 96, 40);
    DrawNum(Display, seconds % 10, 112, 40);
}

void StatusScreen::DrawNum(char *Display, int number, int x, int y) {
    int tempx, tempy;
    unsigned char fillvalue;
    
    for(tempy = y; tempy < y + 23; tempy++) {
        for(tempx = x; tempx < x + 16; tempx++) {
            if(tempx & 1)
                fillvalue = 0xf0;
            else
                fillvalue = 0x0f;

            if(NumberBitmaps[number][(tempx - x) + ((tempy - y) * 17)] == 0) {
                /* Pixel shouuld be filled */
                Display[(tempx >> 1) + (64 * tempy)] |= fillvalue;
            }
            else {
                /* Pixel should be clear */
                Display[(tempx >> 1) + (64 * tempy)] &= ~(fillvalue);
            }
        }
    }
}

void StatusScreen::DrawColon(char *Display, int x, int y) {
    int tempx, tempy;
    unsigned char fillvalue;
    
    for(tempy = (y + 6); tempy < (y + 10); tempy++) {
        for(tempx = (x + 2); tempx < (x + 6); tempx++) {
            if(tempx & 1)
                fillvalue = 0xf0;
            else
                fillvalue = 0x0f;
            
            Display[(tempx >> 1) + (64 * tempy)] |= fillvalue;
        }
    }

    for(tempy = (y + 16); tempy < (y + 20); tempy++) {
        for(tempx = (x + 2); tempx < (x + 6); tempx++) {
            if(tempx & 1)
                fillvalue = 0xf0;
            else
                fillvalue = 0x0f;
            
            Display[(tempx >> 1) + (64 * tempy)] |= fillvalue;
        }
    }
}