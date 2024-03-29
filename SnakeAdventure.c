#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
int mainagain();


struct coordinate{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

int main()
{

    Print();

    system("cls");

    load();

    length=5;

    head.x=25;

    head.y=20;

    head.direction=RIGHT;

    Boarder();

    Food();

    life=3;

    bend[0]=head;

    Move();




    return 0;

}

void Move()
{
    int a,i;

    do{

        Food();
        fflush(stdin);

        len=0;

        for(i=0;i<30;i++)

        {

            body[i].x=0;

            body[i].y=0;

            if(i==length)

            break;

        }

        Delay(length);

        Boarder();

        if(head.direction==RIGHT)

            Right();

        else if(head.direction==LEFT)

            Left();

        else if(head.direction==DOWN)

            Down();

        else if(head.direction==UP)

            Up();

        ExitGame();

    }while(!kbhit());

    a=getch();

    if(a==27)

    {

        system("cls");

        exit(0);

    }
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))

    {

        bend_no++;

        bend[bend_no]=head;

        head.direction=key;

        if(key==UP)

            head.y--;

        if(key==DOWN)

            head.y++;

        if(key==RIGHT)

            head.x++;

        if(key==LEFT)

            head.x--;

        Move();

    }

    else if(key==27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        Move();

    }
}

void gotoxy(int x, int y)
{

 COORD coord;

 coord.X = x;

 coord.Y = y;

 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
 }
void load(){

   int r,q;
    gotoxy(36,14);
    printf("Loading...");
    gotoxy(30,15);

    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);
    printf("%c",177);
    }
    gotoxy(40,16);
    printf("\t\t\nPlease press any key...");

    getch();
}

void Delay(long double k)
{
    Score();
    long double i;
    if(length >=5 && length <=10){
    for(i=0;i<=(50000000);i++);
    }else if(length > 10 && length <=20){
        for(i=0;i<=(25000000);i++);
    }
    else if(length > 20){
        for(i=0;i<=(12500000);i++);
    }

}
void Down()
{
    int i;
    for(i=0;i<=(head.y-bend[bend_no].y)&&len<length;i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("W");
            else
                printf("o");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Up()
{
   int i;
   for(i=0;i<=(bend[bend_no].y-head.y)&&len<length;i++)
   {
       GotoXY(head.x,head.y+i);
       {
           if(len==0)
                printf("M");
            else
                printf("o");
       }
       body[len].x=head.x;
       body[len].y=head.y+i;
       len++;
   }
   Bend();
   if(!kbhit())
       head.y--;
}
void Right()
{
    int i;
    for(i=0;i<=(head.x-bend[bend_no].x)&&len<length;i++)
    {

        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf("X");
            else
                printf("o");
        }

        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Left()
{
    int i;
    for(i=0;i<=(bend[bend_no].x-head.x)&&len<length;i++)
    {
        GotoXY((head.x+i),head.y);
       {
              if(len==0)
                printf("X");
            else
                printf("o");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;

}
void ExitGame()
{
    int i,check=0;
    char ans;
    for(i=4;i<length;i++)
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else if(life<0)
        {
            system("cls");

            printf("All lives completed\nPress 'Y' to play again or 'N' to see the record : ");
            scanf("%c", &ans);

            if(ans == 'Y' || ans == 'y'){

                system("cls");
                mainagain();

              }else if (ans == 'N' || ans == 'n'){

                record();
                exit(0);

            }

        }
    }
}
void Food()
{
      GotoXY(food.x,food.y);
       printf("+");
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}

void Bend()
{
    int i,j,diff;
    for(i=bend_no;i>=0&&len<length;i--)
    {
            if(bend[i].x==bend[i-1].x)
            {
                diff=bend[i].y-bend[i-1].y;
                if(diff<0)
                    for(j=1;j<=(-diff);j++)
                    {
                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y+j;
                        GotoXY(body[len].x,body[len].y);
                        printf("o");
                        len++;
                        if(len==length)
                            break;
                    }
                else if(diff>0)
                    for(j=1;j<=diff;j++)
                    {

                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y-j;
                        GotoXY(body[len].x,body[len].y);
                        printf("o");
                        len++;
                        if(len==length)
                            break;
                    }
            }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1;j<=(-diff)&&len<length;j++)
                {

                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                        printf("o");
                   len++;
                   if(len==length)
                           break;
               }
           else if(diff>0)
               for(j=1;j<=diff&&len<length;j++)
               {

                   body[len].x=bend[i].x-j;
                   body[len].y=bend[i].y;
                   GotoXY(body[len].x,body[len].y);
                       printf("o");
                   len++;
                   if(len==length)
                       break;
               }
       }
   }
}
void Boarder()
{
   system("cls");
    int i;

   for(i=10;i<71;i++)
   {
       GotoXY(i,10);
           printf("=");
       GotoXY(i,30);
           printf("=");
   }
   for(i=10;i<31;i++)
   {
       GotoXY(10,i);
           printf("|");
       GotoXY(70,i);
       printf("|");
   }
}
void Print()
{


   printf("\n====================================================================================");
   printf("\n************************************************************************************");
   printf("\n              Welcome to the Snake game.(press any key to continue)                *\n");
   printf("\n                      *******                                                      *");
   printf("\n                    *** oo   ***                                                   *");
   printf("\n                   ***         **                                                  *");
   printf("\n               *******         **                                                  *");
   printf("\n                     ***     **                                                    *");
   printf("\n                      **    **                                                     *");
   printf("\n                     **    **       *****          *****          *******          *");
   printf("\n                    **     **     **    **        **   **       **  *              *");
   printf("\n                   **     **     **       **     **      **    **  *               *");
   printf("\n                    **     **   **          **  **        **  **  *                *");
   printf("\n                      **     ***    *****    ***    ****   ***   *                 *");
   printf("\n                        **        **     **       **    **      *                  *");
   printf("\n                          ********         ********      *******                   *");
   printf("\n======================================================================================");
   printf("\n*************************************************************************************\n");
   getch();
   system("cls");
   printf("\n================================================================================================");
   printf("\n************************************************************************************************");
   printf("\t\nGame instructions :\n");
   printf("1.Use arrow keys to move the snake.\n");
   printf("\n2.You will be provided foods at the several coordinates of the screen which you have to eat.\n");
   printf("\n3.Everytime you eat a food the length of the snake will be increased by 1 .\n");
   printf("\n4.Your life will decrease as you hit the wall or snake's body\n");
   printf("\n5.You can pause the game by pressing any key.\n");
   printf("\n\nPress any key to play game..");
   printf("\n================================================================================================");
   printf("\n************************************************************************************************");

   if(getch()==27)
   exit(0);
}
void record(){
   char plname[20],nplname[20],cha,c,new_g;
   int i,j,px;
   FILE *info;
   info=fopen("record.txt","a+");
   getch();
   system("cls");
   printf("Enter your name :");
   scanf("%[^\n]",plname);

   for(j=0;plname[j]!='\0';j++){
   nplname[0]=toupper(plname[0]);
   if(plname[j-1]==' '){
   nplname[j]=toupper(plname[j]);
   nplname[j-1]=plname[j-1];}
   else nplname[j]=plname[j];
   }
   nplname[j]='\0';

   fprintf(info,"Player Name :%s \n",nplname);


   time_t mytime;
  mytime = time(NULL);
  fprintf(info,"Played Date:%s",ctime(&mytime));

     fprintf(info,"Score:%d\n",px=Scoreonly());
   for(i=0;i<=50;i++)
   fprintf(info,"%c",'_');
   fprintf(info,"\n");
   fclose(info);
   printf("Do you want to see past record ? press 'y'\n");
   new_g=getch();
   cha=getch();
   system("cls");

   if(cha=='y'){
   info=fopen("record.txt","r");
   do{
       putchar(c=getc(info));
       }while(c!=EOF);}
     fclose(info);
}
int Score()
{
   int score;
   GotoXY(20,8);
   score=length-5;
   printf("SCORE : %d",(length-5));
   score=length-5;
   GotoXY(50,8);
   printf("Life : %d",life);
   return score;
}
int Scoreonly()
{
int score=Score();
system("cls");
return score;
}
int mainagain()
{

    char key;

    Print();

    system("cls");

    load();

    length=5;

    head.x=25;

    head.y=20;

    head.direction=RIGHT;

    Boarder();

    Food();
    life=3;

    bend[0]=head;

    Move();

    return 0;

}


