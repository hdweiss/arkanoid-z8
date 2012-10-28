/*
 *  arka_high.h
 *
 */

#ifndef _ARKHIGH_H_
#define _ARKHIGH_H_

int highscores(int putscore, int value, int index);
char *highscorenames(int putname, char *name, int index);
void initscores();
void showscores();
void putscore(int score);

#endif
