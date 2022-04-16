#include <string>
#include <cstdio>
#include <unistd.h>
#include <iostream>


void yellow(int x, int y)
{
   printf("\33[%d;%dH", x, y);
   printf("\33[30;103m");
   printf("  ");
   printf("\33[0m");
   fflush(stdout);
}

void print_mode (int mode)
{
   printf("\33[3;25H");
   if (mode == 1)
      printf("\033[31;47m1");
   else if (mode == 2)
      printf("\033[31;47m2");
   else
      printf("\033[31;47m3");

}


void tfl1 (int mode)
{

   printf("\33[11;37H");
   printf("\033[30;100m      ");

   if (mode == 1)
   {
      printf("\33[11;41H");
      printf("\33[30;102m  ");
   }
   else if (mode == 2)
   {
      printf("\33[30;103m");
      printf("\33[11;39H  ");
   }
   else
   {
      printf("\33[11;37H");
      printf("\33[30;101m  ");
   }

   fflush(stdout);
}

void tfl2 (int mode)
{
   printf("\033[30;100m");
   printf("\33[17;37H  ");
   printf("\33[18;37H  ");
   printf("\33[19;37H  ");

   if (mode == 1)
   {
      printf("\33[19;37H");
      printf("\33[30;102m  ");
   }
   else if (mode == 2)
   {
      printf("\33[30;103m");
      printf("\33[18;37H  ");
   }
   else 
   {
      printf("\33[17;37H");
      printf("\33[30;101m  ");

   }

   printf("\33[29;1H");
   fflush(stdout);
}

void control (void)
{
   print_mode(1);
   tfl1(3);
   tfl2(1);
   printf("\33[29;1H");
   usleep(1000000);
   print_mode(2);
   tfl1(2);
   tfl2(2);
   usleep(1000000);
   print_mode(3);
   tfl1(1);
   tfl2(3);
   printf("\33[29;1H");
   usleep(1000000);
}



void build_road ()
{

   for (int i=2; i<28; i++)
   {
      if (i<13 || i>15) {
         printf("\33[%d;30H",i);
         printf("\33[31;47m  |  ");
      }
   }

   printf("\33[13;1H");
   for (int i=0; i<62; i++)
   {
      printf(" ");
   }

   printf("\33[14;1H");
   for (int i=0; i<62; i++)
   {
      printf("-");
   }

   printf("\33[15;1H");
   for (int i=0; i<62; i++)
   {
      printf(" ");
   }

}


int main(int argc, char  *argv[]) {

   build_road();

   for (int i=0; i<4; i++)
   {

   control();


   }
   printf("\33[0m\n");
   printf("\n");

   return 0;

}
