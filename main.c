#include <stdio.h>
#include "maze.h"
int main()
{
int n;

   while(1) {
        printf("Press 1 to exit\n");
        printf("Tap size of maze(max:99) >> ");
        scanf("%d", &n);
        if(n == 1) break;
        solve(n);
   }
   return 0;
}
