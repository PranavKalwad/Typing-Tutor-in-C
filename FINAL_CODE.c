//Header files.
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<direct.h> 	
#include<stdlib.h>
#include<conio.h>
#include<string.h>


//Function declarations.
void get_score(int speed); 
void start_game();  
void scorecard();  
void about_us();
void help();


//We are setting the x coordinate of the cursor.
static int x=1; 


//Macros to change the position of the cursor.
#define pos gotoxy(11,x++);
//Macro to print a design.
#define ln printf("-------------------");


//Structure COORD contains the x and y values of the screen location.
//We set the coordinates to 0,0.
COORD coord={0,0};


//Function to set the new  x and y coordinate of the cursor.
void gotoxy(int x,int y)
{
    //Setting the x and y Coordinates.
    coord.X=x;
    coord.Y=y;
    //Set the  console  cursor position on the standard output (cmd) to the specified coordinates.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void ClearConsoleToColors(int ForgC, int BackC)
{
 WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
               //Get the handle to the current output buffer...
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                     //This is used to reset the carat/cursor to the top left.
 COORD coord = {0, 0};
                  //A return value... indicating how many chars were written
                    //   not used but we need to capture this since it will be
                      //   written anyway (passing NULL causes an access violation).
  DWORD count;

                               //This is a structure containing all of the console info
                      // it is used here to find the size of the console.
 CONSOLE_SCREEN_BUFFER_INFO csbi;
                 //Here we will set the current color
 SetConsoleTextAttribute(hStdOut, wColor);
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                          //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                          //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
 }
} 

 
int t=0; //Time starts from 0 seconds.


//Name of the player.
char name[50];


int main()
{	 
	int c=0;
    int n;
    //Record the time when the user opens the application.
    time_t t;
    time(&t);
    x=1;
    //To clear the output of the screen. 
    system("cls");
    pos;
    ClearConsoleToColors(4,0); // 4=red (foreground),0=black(background).
    pos;
    printf("%s",ctime(&t));
	printf("	   Welcome to Typing Tutor");
    pos;
    pos;
    if(c==0)
        {
            printf("Enter the player's name:");
            gets(name);
        }
    ++c;
    pos;
    ln pos;
    printf("*****Main Menu*****");pos;
    ln pos;
    printf("1.Start Game:");
    pos;
    printf("2.Scorecard:");
    pos;
    printf("3.Help:");
    pos;
    printf("4.About Us:");
    pos;
    printf("0.Exit:");
    pos;
    printf("Enter your choice:");
    scanf("%d",&n);
    pos;
    switch(n)
    {
        case 1:start_game();break;
        case 2:scorecard();break;
        case 3:help();break;
        case 4:about_us();break;
        case 0:system("cls");gotoxy(10,10);printf("Goodbye.See you later!");exit(1);break;
        default:main();
    }
    
}


void start_game()
{
	system("cls");
	gotoxy(30,30);
	ClearConsoleToColors(4,0);
	x=10; 
	int word_count=0;
	int word_count_user=0;
	int ch;
	clock_t begin ;//The begining of the clock.
	int time_spent;
	int speed; //wpm(words per minute.)
	pos;
	char inp_str[10000]="How much wood would a woodchuck chuck if a woodchuck could chuck wood";
	printf("%s",inp_str);
	char user_str[100000];
	fflush(stdin);
	printf("\nEnter the above shown text:\n");
	begin=clock(); //Clock starts when the user enters the window to type the displayed text.
	scanf("%[^\n]",user_str);
	
	char* token=strtok(inp_str," ");
	while(token != NULL)
	{
		word_count++;
		token=strtok(NULL," ");
	}
	
	char* token_user=strtok(user_str," ");
	while(token_user!= NULL)
	{
		word_count_user++;
		token_user=strtok(NULL," ");
	}
	

	
		time_spent=(int)(clock()-begin)/CLOCKS_PER_SEC;	
		speed=(word_count_user*60)/(time_spent); // This gives the words per minute.
	
		gotoxy(12,12);
		printf("\nGame Over!!\n");
		gotoxy(15,15);
		printf("\nTime spent is %d sec\n",time_spent);
		
		if((strcmp(inp_str,user_str))==0)
		{
			gotoxy(22,22);
			printf("\nCongratulations!.You typed at a speed of %d words per minutes :)\n",speed);
			pos;
		}
		else
		{
			gotoxy(22,22);
			printf("Looks like you got some errors :(\n");
		}
	
		get_score(speed); //Writing the name of the player and the score to a file.
		pos;
		
		gotoxy(16,16);
		printf("\n1.Play again\n");
		pos;
		gotoxy(17,17);
		printf("\n2.Main menu\n");
		pos;
		gotoxy(18,18);
		printf("\n3.exit\n"); 
		pos;
		gotoxy(19,19);
		printf("\nEnter your choice:\n");
		fflush(stdin);
		gotoxy(20,20);
		scanf("%d",&ch);
		switch(ch)
		{
		      case 1:start_game();break;//recursive call
		      case 2:main();break;
		      case 3:system("cls");gotoxy(17,10);printf("Goodbye.See you later!");exit(1);
		      default:main();
		}
}


void get_score(int speed)
{
	FILE *fp;
	fp=fopen("Score.txt","a");
	pos;
	if(fp==NULL)
		printf("error in opening file");
	else
	{
		fprintf(fp,"\nname=%s speed=%d words per min",name,speed);
		fclose(fp);
	}	
	pos;
}


void scorecard()
{
	char ch;
	FILE *fp;
	system("cls");
	x=3;
	printf(".........The scores are...........");
	fp=fopen("Score.txt","r");
	while((ch=fgetc(fp))!=EOF)
	{
		printf("%c",ch);
	}
	getch();  
	main();
}


void about_us()
{
	system("cls");
	gotoxy(8,8);
	ClearConsoleToColors(4,0);
	printf("Hello everyone we are Pranav,Nihal and Parth from PES University\n");
	getch(); 
	main();
}


void help()
{
	system("cls");
	gotoxy(8,5);
	ClearConsoleToColors(4,0);
	printf("#......Rules of the Game......#");gotoxy(8,6);
	printf("=>Enter your name as player name");gotoxy(8,7);
	printf("=>Text is displayed when you start the game and you have to type them as fast as you can.Best of luck!");gotoxy(8,10);
	getch();
	main();
}



