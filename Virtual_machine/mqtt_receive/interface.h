#include <string>
#include <cstdio>
#include <unistd.h>
#include <iostream>


void frame()
{
   printf("\033[20;10H");
   printf("\033[48;5;215m");
   printf("                                         ");
   printf("\033[21;10H");
   printf("\033[48;5;215m");
   printf("                                         ");
   printf("\33[22;10H");
   printf("   ");
   printf("\33[23;10H");
   printf("   ");
   printf("\33[24;10H");
   printf("   ");
   printf("\33[25;10H");
   printf("   ");
   printf("\33[22;48H");
   printf("   ");
   printf("\33[23;48H");
   printf("   ");
   printf("\33[24;48H");
   printf("   ");
   printf("\33[25;48H");
   printf("   ");

   printf("\33[26;10H");   
   printf("                                         ");
   printf("\33[27;10H");
   printf("                                         ");

   printf("\33[22;13H");
   printf("\033[48;5;84m");
   printf("                                   ");
   printf("\33[23;13H");
   printf("\033[48;5;84m");
   printf("\033[30;30m");
   printf("    Coming from ESP...             ");
   printf("\33[24;13H");
   printf("\033[48;5;84m");
   printf("\033[30;30m");
   printf("                                   ");
   printf("\33[25;13H");
   printf("\033[48;5;84m");
   printf("                                   ");

   printf("\33[19;10H");
   printf("\033[48;5;87m");
   printf("\033[30;30m");
   printf("                 Distance                ");


   //Second panel - compass
   printf("\033[20;60H");
   printf("\033[48;5;215m");
   printf("                                         ");
   printf("\033[21;60H");
   printf("\033[48;5;215m");
   printf("                                         ");
   printf("\33[22;60H");
   printf("   ");
   printf("\33[23;60H");
   printf("   ");
   printf("\33[24;60H");
   printf("   ");
   printf("\33[25;60H");
   printf("   ");
   printf("\33[22;98H");
   printf("   ");
   printf("\33[23;98H");
   printf("   ");
   printf("\33[24;98H");
   printf("   ");
   printf("\33[25;98H");
   printf("   ");

   printf("\33[26;60H");   
   printf("                                         ");
   printf("\33[27;60H");
   printf("                                         ");

   printf("\33[22;63H");
   printf("\033[48;5;84m");
   printf("                                   ");
   printf("\33[23;63H");
   printf("\033[48;5;84m");
   printf("\033[30;30m");
   printf("    Coming from ESP...             ");
   printf("\33[24;63H");
   printf("\033[48;5;84m");
   printf("\033[30;30m");
   printf("                                   ");
   printf("\33[25;63H");
   printf("\033[48;5;84m");
   printf("                                   ");

   printf("\33[19;60H");
   printf("\033[48;5;87m");
   printf("\033[30;30m");
   printf("                 Compass                 ");


   //Command panel
   printf("\033[32;35H");
   printf("\033[48;5;215m");
   printf("                                         ");
   printf("\033[33;35H");
   printf("\033[48;5;215m");
   printf("                                         ");
   printf("\33[34;35H");
   printf("   ");
   printf("\33[35;35H");
   printf("   ");
   printf("\33[36;35H");
   printf("   ");
   printf("\33[37;35H");
   printf("   ");
   printf("\33[34;73H");
   printf("   ");
   printf("\33[35;73H");
   printf("   ");
   printf("\33[36;73H");
   printf("   ");
   printf("\33[37;73H");
   printf("   ");

   printf("\33[38;35H");   
   printf("                                         ");
   printf("\33[39;35H");
   printf("                                         ");

   printf("\33[34;38H");
   printf("\033[48;5;84m");
   printf("                                   ");
   printf("\33[35;38H");
   printf("\033[48;5;84m");
   printf("\033[30;30m");
   printf(" >                                 ");
   printf("\33[36;38H");
   printf("\033[48;5;84m");
   printf("\033[30;30m");
   printf("                                   ");
   printf("\33[37;38H");
   printf("\033[48;5;84m");
   printf(" Sent:     -------                 ");

   printf("\33[31;35H");
   printf("\033[48;5;87m");
   printf("\033[30;30m");
   printf("           Car drive command             ");


   printf("\033[35;41H");
   printf("\033[5;0m");
   printf("\033[48;5;84m");
   printf("\033[30;30m");
   printf("");



//   printf("\33[0m");
   fflush(stdout);
}

void print_moded (int mode)
{
   printf("\33[3;25H");
   if (mode == 1)
      printf("\033[31;47m1");
   else if (mode == 2)
      printf("\033[31;47m2");
   else
      printf("\033[31;47m3");

}


void abuild_droad ()
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


