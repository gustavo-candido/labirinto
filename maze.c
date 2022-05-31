#include "pilha.h"
#include "pair.h"
#include "maze.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


int valid(int i, int j, int I, int J) {
    return !(i<0 || i>=I || j<0 || j>=J);
}

void init(int *comp, int n) {
    int i, j, x=0;

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            comp[x] = x;
            x++;
        }
    }
    return;
}
int find(int *comp, int u) {
    return comp[u] = (comp[u] == u)?u:find(comp, comp[u]);
}

int same(int *comp, int u, int v) {
    return (find(comp, u) == find(comp, v));
}

void join(int *comp, int u, int v) {
    if(same(comp, u,v)) return;
     comp[find(comp, u)] = comp[find(comp,v)];
     return;
}

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
    return;
}

void random_shuffle(int *v, int n) {
    int c = 5*n;
    int i, j;

    srand(time(NULL));
    while(c--) {
        i = rand() % n;
        j = rand() % n;
        swap(&v[i], &v[j]);
    }
}

void maze_gererator(char maze[][100], int n) {
    int di[] = {-1,  0, 0,  1};
    int dj[] = { 0, -1, 1,  0};
    int comp[100*100], index[100*100];
    int i, j, x, y, u, v, k, K;
    ii inicio,final;

    init(comp, n);
    init(index, n);


    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            maze[i][j] = '@';
        }
        maze[i][n] = '\0';
    }

    if(n == 2) {
        srand(time(NULL));
        i = rand() % 2;
        j = rand() % 2;

        for(k=0; k<4; k++) {
            if(valid(i+di[k], j+dj[k], n,n)) {
                maze[i][j] = 'F';
                maze[i+di[k]][j+dj[k]] = 'S';
                break;
            }
        }
        return;
    }
    srand(time(NULL));
    if(n > 15)  K = rand() % ((6*n*n)/100);
    else K = n/2;

     final.first = final.second = -1000;
     random_shuffle(index, n*n);
     u = comp[index[0]];
     y = u%n;
     x = (u-y)/n;

     inicio.first = x;
     inicio.second = y;

    random_shuffle(index, n*n);
    for(i=1; i<K; i++) {
        u = comp[index[i]];
        y = u%n;
        x = (u-y)/n;

        srand(time(NULL));
        k = rand() % 4;

        y = y + dj[k];
        x = x + di[k];

        if(!valid(x,y,n,n)) continue;
        v = x * n + y;
        if(same(comp, u, v)) continue;
        final.first = x;
        final.second = y;
        join(comp, u, v);
        maze[x][y] = maze[x - di[k] ][y - dj[k]] = '.';
    }

    if((final.first == -1000 && final.second == -1000)|| equal_ii(final,inicio)) {
        for(i=0; i<4; i++) {
            if(!valid(inicio.first+di[i], inicio.second+dj[i],n,n)) continue;
            final.first = inicio.first+di[i];
            final.second = inicio.second+dj[i];
            break;
        }
    }


   if(n>20) K = rand() % ((6*n*n)/300);
   if(K<n/2) K = n/2;
    for(k=0; k<K; k++) {
        i = rand() % n;
        j = rand() % n;
        u =  rand() % n;
        v =  rand() % n;
        if(!same(comp,i*n+j, u*n+v)) {
            while(i < u) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                i++;
             }
             while(i > u) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                i--;
             }
            while(j < v) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                j++;
             }
             while(j > v) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                j--;
             }
         }
    }


     srand(time(NULL));
     k = rand() % 100;

    if(k<=100) {
        i = inicio.first;
        j = inicio.second;
        u = final.first;
        v = final.second;
        if(!same(comp,i*n+j, u*n+v)) {
            while(i < u) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                i++;
             }
             while(i > u) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                i--;
             }
            while(j < v) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                j++;
             }
             while(j > v) {
                join(comp,i*n+j, u*n+v);
                maze[i][j] = '.';
                j--;
             }
         }
    }

    maze[final.first][final.second] = 'F';
    maze[inicio.first][inicio.second] = 'S';
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(!same(comp, inicio.first*n+inicio.second, i*n+j))maze[i][j] = '@';
        }
    }
}

void solve(int n)
{

    int i, j, flag;
    double delay, acc;
    char maze[100][100];
    int forbidden[100][100], can_solve;
    int di[] = { 0, -1, 0, 1}; // current to neighbor direction in line
    int dj[] = {-1,  0, 1, 0}; // current to neighbor direction in column
    ii start, finish, current, neighbor;
    pilha *stk;


    clean_screen();
    delay = 0.1;

    start.first = start.second = finish.first = finish.second = 10000;


    maze_gererator(maze, n);
    for(i=0; i<n; i++) { // read maze
        for(j=0; j<n; j++) {
            if(maze[i][j] == 'S') {start.first = i; start.second = j;}
            if(maze[i][j] == 'F') {finish.first = i; finish.second = j;}
        }
    }

    memset(forbidden, 0, sizeof forbidden);

    stk = cria();

    insere(stk, start);
    forbidden[start.first][start.second] = 1;
    maze[start.first][start.second] = 'o';
    can_solve = 0;

    clean_screen();
    print(maze, n);
    wait(2);
    while(!can_solve && stk->size) { // start searching
        acc+=delay;
        if(acc > 3) {
            delay/=2;
            acc=0;
        }
        current = stk->topo->c;
        if(equal_ii(current, finish)) { // find exit
            maze[current.first][current.second] = 'o';
            can_solve = 1;
            break;
        }
        flag = 0;
        for(i=0; i<4; i++) { // current to neighbor
            neighbor.first = current.first+di[i];
            neighbor.second = current.second+dj[i];
            if(!valid(neighbor.first, neighbor.second, n, n)) continue;
            if(maze[neighbor.first][neighbor.second] == '@') continue;
            if(forbidden[neighbor.first][neighbor.second]) continue; ///Check valid position

            if(stk->size) {
                maze[stk->topo->c.first][stk->topo->c.second] = (i%2==0)?'-':'|';
                reprint(maze,stk->topo->c,n);
            }
            insere(stk, neighbor);
            maze[neighbor.first][neighbor.second] = 'o';
            forbidden[neighbor.first][neighbor.second] = 1;
            flag = 1;
            reprint(maze, neighbor, n);
            wait(delay);
            break;
        }
        if(!flag) { //if current dont have valid neighbor remove from stack
            maze[current.first][current.second] = ' ';
            reprint(maze,current,n);
            retira(stk);
            if(stk->size) {
                    maze[stk->topo->c.first][stk->topo->c.second] = 'o';
                    reprint(maze,stk->topo->c, n);
            }
            wait(delay);
        }
    }
    delay = 0.1;
    clean_screen();
    print(maze, n);
    if(can_solve){
        char s[] = {"I can find the exit from the maze!!"};

        for(j=0; j<strlen(s); j++) {
            printf("%c", s[j]);
            wait(0.02);
        }
        puts("");
    }
    else { // Just for the animation
        char s[50];

        strcpy(s, "Hey,\n");
        for(i=0; i<strlen(s); i++) {
            printf("%c", s[i]);
            wait(0.12);
        }
        wait(1);
        strcpy(s, "This is a trap!!!\n");
        for(i=0; i<strlen(s); i++) {
            printf("%c", s[i]);
            wait(0.06);
        }
    }
    wait(2);
    while(stk->size) retira(stk);
    destroi(stk);
    getchar();
    clean_screen();
}

