/* BAO DOAN
   CIS 142
   Truman College
   FINAL PROGRAMMING ASSIGNMENT: THE WONDERFUL WORLD OF SHAKEY
    Desciption; A program to direct an imaginary robot through some simple tasks
*/

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <stdlib.h>

#define VMAX 25
#define HMAX 25


/*Global variables */
int x,y;
char *next;
char *position;
char direction;
char garden[HMAX][VMAX];

/*Protocol Functions */
void initGarden();
void printGarden();
void turn(char d);
bool plant(void);
bool step(void);


/*Main function*/
int main(void)
{
/*Declare variable */
char command[10];
bool loop=true;

/* Innitialize the Garden */
initGarden();

/* Read from the file input.txt to innitialize the garden and Shakey's position*/
FILE *fp= fopen("input.txt", "r");
    if(fp==NULL)
        {
        printf("The file cannot open");
        return 0;
        }
    else
{
char coordinate1[10];
char coordinate2[10];

    /* Read the first line for Shakey's first position */
    fscanf(fp,"%s",&coordinate1);
    x= atoi(coordinate1); // Atoi is a function to convert a string to an integer

    fscanf(fp,"%s",&coordinate2);
    y= atoi(coordinate2);

// Check and set the first position for Shakey
if(x<=0 || x>=HMAX || y<=0|| y>=VMAX)
    {
        x=1;
        y=1;
        position = &garden[x][y];
    }

else
position = &garden[x][y];

*position='S';

/* Read the second line for Shakey's direction*/
fscanf(fp,"%s", &direction);

   //Check innitializing valid direction, if not then set direction to North (default)
if(direction!='N' && direction!='E' && direction!='W' && direction!='S')
direction ='N';

/* Read the remainding lines are trees */
while (!feof(fp))
    {
        fscanf(fp, "%s %s", &coordinate1 , &coordinate2);

        /* Initialize trees if input is valid, else ignore planting*/
        if( atoi(coordinate1)>0 && atoi(coordinate1) <HMAX  &&  atoi(coordinate2)>0  &&  atoi(coordinate2)<VMAX && (atoi(coordinate1)!=x || atoi(coordinate2)!=y))
        garden[atoi(coordinate1)][atoi(coordinate2)]='T';
    }

//Close the input file
fclose (fp);
}

/*************************************/
printf("Ready\n");
turn (direction);
printf("Welcome to the Wonderful World of Shakey\n");

while (loop)
{
/* Get command from user */
printf("Command>");
gets(command);

/* Display the garden*/
if (strcmp (command,"display")==0)
    printGarden();

/*Step*/
else if (strcmp (command,"step")==0)
    step();


/*Turn Left*/
else if (strcmp (command,"left")==0)

{
    if (direction == 'E')
    turn('N');
    else if (direction == 'W')
    turn('S');
    else if (direction == 'S')
    turn('E');
    else if (direction == 'N')
    turn('W');
}

/*Turn Right*/
else if (strcmp (command,"right")==0)

{
    if (direction == 'E')
    turn('S');
    else if (direction == 'W')
    turn('N');
    else if (direction == 'S')
    turn('W');
    else if (direction == 'N')
    turn('E');
}

/*Plant A Flower in front of current position*/
else if (strcmp (command,"plant")==0)
    plant ();

/*Home. Back to the original position [1][1], face North*/
else if (strcmp (command,"home")==0)
{
     x=1;
     y=1;
    *position = '-';
     position = &garden[x][y];
    *position = 'S';
    turn('N');
}

/*Stop the program_ Shakey go to sleep*/
else if (strcmp (command,"halt")==0)
{
    printf("GOOD NIGHT EVERYONE!!\n");
    loop=false;
    //End loop
}


else
    printf("Invalid command\n");

}

return 0;
}



/* Function to innitialize the Garden*/
void initGarden()
{
    int i, j;

    for(i = 0; i < HMAX ; ++i)
    {
        for(j = 0; j < VMAX ; ++j)
        {
            if(i == 0 || i == (HMAX-1) || j == (VMAX-1) || j == 0 || (i == HMAX && j < VMAX ))
            garden[i][j]='T';
            else
            garden[i][j]='-';
        }

    }


}

/* A Function used to display the garden */
void printGarden()
{
    int i,j;

    for(i = 0; i < HMAX ; ++i)
    {
        for(j = 0; j < VMAX ; ++j)
        {
            printf("%c",garden[i][j]);
        }
        printf("\n");
    }


}

/*Turn! A Function used to face the robot to following direction by recognize the NEXT POSTION */
void turn(char d)
{
 int n1,n2;
    if (d=='E')
    {
    n1=x;
    n2=y+1;
    }

    else if (d=='W')
    {
    n1=x;
    n2=y-1;
    }
    else if (d=='S')
    {
    n1=x+1;
    n2=y;
    }
    else if (d=='N')
    {
    n1=x-1;
    n2=y;
    }

  direction = d;
  next= &garden[n1][n2];
}

/*Plant. A Functino used to plant flowers in the NEXT POSITION */
bool plant(void)
{
if(*next=='T')
{
    printf("OOOPS, there is a tree in my way- no flower planted\n");
    return false;
}
else if (*next =='F')
{
    printf("OOOPS, there has been a flower already- can't plant another\n");
    return false;
}

else
{
    //Put F to in front of Shakey
  *next='F';
  return true;
}


}

/*Step. A Function used to step to the NEXT POSITION*/
bool step(void)
{
//There is tree => Ouch and don’t move
if (*next == 'T')
    {
    printf("Ouch!!! You gore a tree\n");
    return false;
    }

else
{
    //{If there is flower => Print the response
    if (*next == 'F')
    printf("OOOOH, you made me step on a flower…… poor flower\n");

    /*Implement new POSITION*/
    *position = '-';
    position=next;
    *position = 'S';

  // Implement x,y coordinates of position
   if (direction=='E')
    y=y+1;
   else if (direction=='W')
    y=y-1;
   else if (direction=='S')
    x=x+1;
   else if (direction=='N')
    x=x-1;

   /* Implement new NEXT*/
   turn(direction);
   return true;
 }
}




