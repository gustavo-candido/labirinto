#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED


int valid(int i, int j, int I, int J);
void init(int *comp, int n);
int find(int *comp, int u);
int same(int *comp, int u, int v);
void join(int *comp, int u, int v);
void swap(int *x, int *y);
void random_shuffle(int *v, int n);
void maze_gererator(char maze[][100], int n);
void solve(int n);

#endif // MAZE_H_INCLUDED
