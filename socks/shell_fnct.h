/* 
 * File:   shell_fnct.h
 * Author: flynn
 *
 * Created on October 20, 2011, 7:48 AM
 */


extern void clear(void)
{
        printf("\e[H\e[2J");
}
 
extern void setcolor(int recv)
{
        int x=0;
        int y=0;
 
        if (recv>=0 && recv<=8)
        {
                x=recv+30;
        }
        if (recv>=10 && recv<=18)
        {
                        y=1;
                        x=recv+20;
         }
        printf("\33[%d;%dm",y,x);
}
 
extern void setfont(int bg, int fg)
{
        int x, y, z;
 
        z=y=0;
        if (bg>=0 && bg<=8)
                x=bg+40;
        if (fg>=0 && fg<=8)
                z=fg+30;
        else if (fg>=10 && fg<=18)
                {
                        y=1;
                        z=fg+20;
                }
 
        printf("\33[%d;%d;%dm",y,x,z);
}

void wait(void){
	printf("\n");
	system("read b");
}
