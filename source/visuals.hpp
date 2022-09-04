#ifndef VISUALS_H
#define VISUALS_H

extern SwkbdState swkbd;
extern char mybuf[10];

void accessElement(unsigned int accessedIndex);
void finishSorting();
void drawArray();
void drawTree();
void initArray();
unsigned int inputNum();

#endif