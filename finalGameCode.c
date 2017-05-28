/*************** Libraries ***************/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>
/*************** Global Variables and Constant ***************/
#define SIZE 100
typedef int bool;
#define true 1
#define false 0
#define size 25
int count = 0; 
int count1 = 0;
int shm_id;
char *shm_ptr;
char *s;
key_t key;
char name [50];
char nam [50];
int randomI;
sem_t mutex;
/*************** Function Prototypes ***************/
void *myFunc();
void *myFunc1();
void home();
void rules();
void userAccount();
void welcome();
void menu();
void signup();
void signin();
int getPassword(char password[]);
int functionScore(int score); // Score checking
void startGame(); // startGame declaration
/*************** Main Function ***************/
int main()
{
  /*************** Home ***************/
 sem_init(&mutex,0,1);
 int id = fork();
 if(id < 0)
 {
  printf("\nFork Failed\n");
  exit(1);
 }
 else if(id > 1)
 {
    key = 1234;
    //creating shared memory
   shm_id = shmget(key, SIZE, IPC_CREAT | 0666);
   if(shm_id < 0)
   {
    perror("shmget error (parent)\n");
    exit(1);
   }
   //attaching shared memory
   shm_ptr = shmat(shm_id, NULL, 0);
   if(shm_ptr == (char*)-1)
   {
     perror("shmat error (parent)\n");
     exit(1);
   }
   waitpid(id, 0, 0);
   int con = 0;
   //reading from shared memory
  // printf("\nUser name is "); 
   for(s = shm_ptr; *s != '0'; s++)
   {
    //printf("%c", *s);
    nam[con] = *s;
    con++;
   }
   //deattaching shared memory
   shmdt(shm_ptr);
   //removing shared memory
   shmctl(shm_id, IPC_RMID, NULL);
   char option;
   do
   {
    printf("\033[2J"); // Clear screen
    startGame();
    printf("\n Do you want to continue program (y/n) ?");
    scanf("%c",&option);
   }while(option=='y' || option=='Y');
   printf("\nGame is executing\n");
 }
 else if(id == 0)
 {
   home();
   //creating shared memory
   key = 1234;
   shm_id = shmget(key, SIZE, 0666);
   if(shm_id < 0)
   {
    perror("shmget error (child)\n");
    exit(1);
   }
   //attaching shared memory
   shm_ptr = shmat(shm_id, NULL, 0);
   if(shm_ptr == (char*)-1)
   {
    perror("shmat error (child)\n");
    exit(1);
   }
   s = shm_ptr;
   //printf("\nWriting on shared memory\n");
   for(int i = 0; i < strlen(name)-1; i++)
   {
    *s = name[i];
     s++;
     //printf("%c", name[i]);
   }
   // printf("\n");
    *s = '0';
  // printf("\nIt's done from child\n");
   //deattaching shared memory  
   shmdt(shm_ptr);
 
   //printf("\nChild executing\n");
   exit(0);
}
 return 0;
}
/*************** Function Definitions ***************/
void *myFunc(void *value)
{
   sem_wait(&mutex);   
    randomI=1+rand()%6;
    sem_post(&mutex);
    pthread_exit(0);
}
/////////////////////////////////////////
void *myFunc1(void *value)
{ 
    sem_wait(&mutex);
    randomI=1+rand()%6; 
    sem_post(&mutex); 
   pthread_exit(0);
}
// Start the game after authentication
void startGame()
{
 printf("*************************************************************************\n");
 printf("*************************** Game is running *****************************\n");
 printf("*************************************************************************\n\n\n");
  srand(time(NULL)); // Generate unique random number each time
  //for(int i=0;i<5;i++)
   //{ 
    // int random=1+rand()%6; // Generate random number between 1 and 6
   //  printf("The number is %d \n",random);  
  // }
   int array[100];
   int temp=100;
  for(int i=0; i<100; i++) // inserting values, at index 0 is 100, and at index 99 is 1 
  {
   array[i]=temp;
   temp--;
  }  
  printf("\n");
  for(int i=0;i<100;i++)
  {
    if(i==10)
    {
         printf("\n");
         for(int J=19;J>=i;J--)
         printf("%d \t",array[J]);
         i+=9;
         
    }
    else if(i==30)
    {
        printf("\n");
        for(int J=39;J>=i;J--)
        printf("%d \t",array[J]);
        i+=9;
    }
    else if(i==50)
    {
         printf("\n");
         for(int J=59;J>=i;J--)
         printf("%d \t",array[J]);
         i+=9;
    }
    else if(i==70)
    {
         printf("\n");
         for(int J=79;J>=i;J--)
         printf("%d \t",array[J]);
         i+=9;
    }
    else if(i==90)
    {
         printf("\n");
         for(int J=99;J>=i;J--)
         printf("%d \t",array[J]);
         i+=9;
    }
   if(i==19 || i==39 || i==59  || i==79  || i==99)
   {
      printf("\n");
    }
     else
    {
     printf("%d \t",array[i]);
    }
  } // loop end
  printf("\n Snake is piosonous :( \n");
  int snake[8][2]={{17,7},{54,34},{62,19},{64,60},{87,24},{93,73},{95,75},{99,78}};
  for(int I=0; I<8; I++)
  {
     printf("%d ",snake[I][0]);
     printf(" step down ");
     printf("%d \t",snake[I][1]);
     printf("\n");
  }
  printf("\n Ladder is Helpfull :) \n");
  int ladder[8][2]={{4,14},{9,31},{20,38},{28,84},{40,59},{51,67},{63,81},{71,91}};
  for(int I=0; I<8; I++)
  {
    printf("%d ",ladder[I][0]);
    printf(" step up ");
    printf("%d \t",ladder[I][1]);
    printf("\n");
  }
   // User playing game
   printf("\n %s playing game \n", nam);
   int score=0;
   int score1=0;
   int flag=0;
   srand(time(NULL));
   pthread_t thread1,thread2;
   
   do
   {
     printf("\n ");
     pthread_create(&thread1,NULL,myFunc,NULL);
     pthread_join(thread1,NULL);
     printf("\n %s's dice score is %d ",nam,randomI); 
     score+=randomI;
     // Editing
     score=functionScore(score); 
     int temp1=score;
      if(temp1>100)
      {
       printf("\n %s's score exceeds 100, try again :O ", nam);
       score-=randomI;   
      }
      printf("\n %s's total score is %d ",nam,score);
      pthread_create(&thread2,NULL,myFunc1,NULL); 
      pthread_join(thread2,NULL);
      printf("\n Computer's dice score is %d ",randomI);
      score1+=randomI;
      score1=functionScore(score1);
      temp1=score1;
      if(temp1>100)
      {
      printf("\n Computer's score exceeds 100, try again :O ");
      score1-=randomI;
      }
      printf("\n Computer's total score is  %d ",score1);
       if(score==100 || score1==100)
       {
          flag=1;
       }    
 }while(flag!=1);
 if(score==100 && score1!=100)
 {
  printf("\n %s wins the game ;) \n", nam);
 }
 else if(score1==100 && score!=100)
 {
  printf("\n Computer wins the game :P \n");
 }
 else
 {
  printf("\n Matach has been drawn :D \n");
 }
 } // end Startgame function

// function
int functionScore(int score)
{
switch(score)
     {
        case 4: // Ladder calls # 1
        {
        printf("\n  Score is %d , and step up to 14 ",score);
        score=14;
        sleep(2);
        break;
        }
        case 9: // Ladder calls # 2
        {
         printf("\n Score is %d , and step up to 31 ",score);
         score=31;
         sleep(2);
         break;
        }
        case 17: // Snakes calls # 1
        {
         printf("\n Score is %d , and step down to 7 ",score);
         score=7;
         sleep(2);
        break;
        }
        case 20: // Ladder calls # 3
        {
         printf("\n Score is %d , and step up to 38 ",score);
         score=38;
         sleep(2);
         break;
        }
        case 28: // Ladder calls # 4
        {
         printf("\n Score is %d , and step up to 84 ",score);
         score=84;
         sleep(2);
         break;
        }
         case 40: // Ladder calls # 5
        {
         printf("\n Score is %d , and step up to 59 ",score);
         score=59;
         sleep(2);
         break;
        }
        case 51: // Ladder calls # 6
        {
         printf("\n Score is %d , and step up to 67 ",score);
         score=67;
         sleep(2);
         break;
        }
        case 54: // Snakes calls # 2
        {
         printf("\n Score is %d , and step down to 34 ",score);
         score=34;
         sleep(2);
         break;
        }
        case 62: // Snakes calls # 3
        {
         printf("\n Score is %d , and step down to 19 ",score);
         score=19;
         sleep(2);
         break;
        }
        case 63: // Ladder calls # 7
        {
         printf("\n Score is %d , and step up to 81 ",score);
         score=81;
         sleep(2);
         break;
        }
        case 64: // Snakes calls # 4
        {
         printf("\n Score is %d , and step down to 60 ",score);
         score=60;
         sleep(2);
         break;
        }
        case 71: // Ladder calls # 8
        {
         printf("\n Score is %d , and step up to 91 ",score);
         score=91;
         sleep(2);
         break;
        }
        case 87: // Snakes calls # 5
        {
         printf("\n Score is %d , and step down to 24 ",score);
         score=24;
         sleep(2);
         break;
        }
        case 93: // Snakes calls # 6
        {
         printf("\n Score is %d , and step down to 73 ",score);
         score=73;
         sleep(2);
         break;
        }
        case 95: // Snakes calls # 7
        {
         printf("\n Score is %d , and step down to 75 ",score);
         score=75;
         sleep(2);
         break;
        }
        case 99: // Snakes calls # 8
        {
         printf("\n Score is %d , and step down to 78 ",score);
         score=78;
         sleep(2);
         break;
        }
        default:
         {  // Skip this step 
         } 
     }
 return score;
}
void welcome()
{
 printf("**************************************************************************\n");
 printf("****************** Welcome To Snakes and Ladders Game ********************\n");
 printf("**************************************************************************\n\n\n");
}
//////////////////////////////////////////////////////
void home()
{
 printf("\033[2J");
 welcome();
 char option;
 char a;
 if(count == 0)
   printf("Press enter to continue");
 scanf("%c", &a);
 count++;
 do
 {
  printf("\nPress 1 for Game Rules\n");
  printf("Press 2 for User Account\n");
  printf("Press 3 to exit the game\n");
  scanf("%c", &option);
  switch(option)
  {
   case '1':
   {
     rules(); 
     break;
   }
   case '2':
   {
    userAccount();
    return;
   }
   case '3':
   {
    exit(1);
   } 
   default:
      printf("\nWrong Input!\n");
  }
  
 }while(option != '3');
}
///////////////////////////////////////////////////////////////
void rules()
{
 printf("\033[2J");
 printf("\n\n**************************************************************************\n");
 printf("******************************** Game Rules ******************************\n");
 printf("**************************************************************************\n\n\n");
 int op;
 printf("Here's a Snakes and ladders board game to play with your friends and family.");
 printf("You need to print the board game, and you can print counters and dice for the game too.\n");
 printf("Press 1 to go back to home\n");
 printf("Press 2 to exit\n");
 scanf("%d", &op);
 if(op == 1)
   home();
 else
   exit(1);
}
///////////////////////////////////////////////////////////////
void userAccount()
{
 printf("\033[2J");
 printf("\n\n**************************************************************************\n");
 printf("******************************* User Account *****************************\n");
 printf("**************************************************************************\n\n\n");
 int option;
 do
 {
  printf("Press 1 to Sign Up\n");
  printf("Press 2 to Sign In\n");
  printf("Press 3 to go back to home\n");
  printf("Press 4 to exit\n");
  scanf("%d", &option);
  switch(option)
  {
   case 1:
    {
      signup();
      break;
    }
   case 2:
    {
      signin();
      return;
    }
   case 3:
    {
      home();
      break;
    }
   case 4:
    {
      exit(1);
    }
   default:
      printf("\nWrong Input!\n");
  }
 }while(option != 4);
}
////////////////////////////////////////////////////////////////
void signup()
{
 printf("\033[2J");
 printf("\n\n**************************************************************************\n");
 printf("********************************* Sign Up ********************************\n");
 printf("**************************************************************************\n\n\n");
 int fd=open("userdata.txt",O_CREAT|O_WRONLY,0600); 
 if(fd==-1)
  {
   printf("Failed to create and open file.\n");
   exit(1);
  }
 char name[25];
 char password[SIZE];
 char email[25];
 int i=0;
 char temp='a';
 printf("\nEnter your name : \n");
 scanf("%c",&temp); // I do not know why? It is essential requirement whenevenr two input string are required
 do
  {
   scanf("%c",&temp);
   name[i]=temp;
   i++;
  }while(name[i-1]!='\n' && i<25);
 name[25]='\0'; // To make charater array into string
 //printf("Writing Name in file\n");
 write(fd,name,i);
 //printf("\nUser name is %s\n",name);
 i=0;
 printf("\n Enter your email :\n");
 do
  {
   scanf("%c",&temp);
   email[i]=temp;
   i++;
  }while(email[i-1]!='\n' && i<25);
 email[25]='\0'; // To make character array into string
 //printf("Writing Email in file\n");
 write(fd,email,i);
 //printf("\nUser email is %s\n",email);
 i=0;
 printf("\n Enter the password  \n"); 
 i=getPassword(password);
 //printf("\nWriting Password in file\n");
 write(fd,password,i); 
 //printf("\n Password is %s\n",password);
 close(fd);
 printf("\nAccount sucessfully created! \n\n");
 sleep(2); 
}
////////////////////////////////////////////////////////////////
int getPassword(char password[])
{
    static struct termios oldt, newt;
    int i = 0;
    int c;

    /*saving the old settings of STDIN_FILENO and copy settings for resetting*/
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;

    /*setting the approriate bit in the termios struct*/
    newt.c_lflag &= ~(ECHO);          

    /*setting the new bits*/
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    /*reading the password from the console*/
    while ((c = getchar())!= '\n' && c != EOF && i < SIZE){
          printf("%c",'*');
         password[i++] = c;
        
    }
    password[i] = '\0';

    /*resetting our old STDIN_FILENO*/ 
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return i;
}
////////////////////////////////////////////////////////////////
void signin()
{
 printf("\033[2J");
 printf("\n\n**************************************************************************\n");
 printf("********************************* Sign In ********************************\n");
 printf("**************************************************************************\n\n\n");
 char email[25];
 char temp='a';
 printf("\n Enter the email :\n");
 int i=0;
 scanf("%c",&temp);
 do
  {
   scanf("%c",&temp);
   email[i]=temp;
   i++;
  }while(email[i-1]!='\n' && i<25);
 email[i]='\0';
 printf("\nYou entered: %s\n",email);
 int ch = 0;
 FILE *file = fopen ("userdata.txt", "r" );
 if ( file != NULL )
  {
    char line [ 128 ]; /* or other suitable maximum line size */
    bool flag=false;
    bool flag2=false;
    
    while ( fgets ( line, sizeof line, file ) != NULL) /* read a line */
     {
       int temp=0;
       if(ch == 0)
       {
         
         int ij;
        for(ij = 0; ij < strlen(line); ij++)
          name[ij] = line[ij];
       }
       ch++;
       while(line[temp]!='\0' && temp<i)
        {
          if(line[temp]==email[temp])
           {
             flag=true;
           }
          else
           {
             flag=false;
           }
          temp++;
            
        }
       if(flag==true)
        {
          flag2=true;
        }
      }
    fclose ( file );
    if(flag2==true)
     {
       printf("\nSuccessfully login in account :) \n\n");
     }
    else
     {
       printf("\n Login failed! \n\n");
       sleep(3);
      }
      
  }

}
