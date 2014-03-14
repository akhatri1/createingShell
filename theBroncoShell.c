#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<sys/types.h>

int executeCommand(char *);


int main(int argc,char *argv[]){
/* Declaring variables most of them array and array pointers of size 512*/
char Command[512];
char *Com;
char Com1[512];
char *iCom[512];
char bCommand[512];
FILE *fp;
//char bCommand2D[512][10];
char *bCom;
char bCom1[512];
char *bCom2[512];
int i=1;
int j,l=0;
int k=0,flag=0;

/*Checking for the number of the arguments passed at the command line*/
if(argc > 2){
printf("Too many arguments\n");
exit(1);
}
/*This if and else statements identifies the mode in which the shell is going i.e either Batch or Interactive*/
 if(argc == 2){         /* For the Batch file*/
     /*Read the file name from the console*/
   fp = fopen(argv[1],"r");
   if(fp == NULL){
    perror("ERROR :");
     exit(0);
   }           // open the Batch Command file for read in the commands.
    /*Read each line at a time and tokenize it*/
   while(fgets(bCommand,512,fp)){
     /*Echoing every line back to the user*/
       i=0; 
       printf("%s\n",bCommand);
    
    /*For lines in the Batch file which ends with \n*/
      if(bCommand[strlen(bCommand)-1] == '\n'){
      strncpy(bCom1,bCommand,strlen(bCommand)-1);
        bCom1[strlen(bCommand)-1]='\0';
     } 
      else{
       strcpy(bCom1,bCommand);
        bCom1[strlen(bCommand)-1]='\0';
          } 
      
        /*Start tokenizing the line read from the file*/
    bCom = strtok(bCom1,";"); 
        while(bCom != NULL){
       bCom2[i] = bCom;i++;
      // printf("%s:%d\n",bCom,strlen(bCom));
       bCom = strtok(NULL,";");   /* Send bCom to the Library*/
      }
         /*Save it into a buffer called "bCom2" and pass it to executeCommand for processing*/
         for(j=0;j<i;j++){
         // printf("Value:%s%d\n",bCom2[j],strlen(bCom2[j]));
          if(bCom2[j]!= NULL){
         executeCommand(bCom2[j]);}
         } 
      }
       fclose(fp);
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  /*For the interactive call*/
else
 {
while(1){
/*defining my shell*/
printf("BroncoShell>>");
/*Inputting the entire string*/
 gets(Command);
                /*Check if it is only a ;*/
                if(strcmp(Command,";") != 0){ 
                 /*Tokenize the input string*/
                   Com = strtok(Command,";");
                             j=0;
                       while(Com != NULL){
                            iCom[j] = Com; j++;
                           Com = strtok(NULL,";");
                             // if(Com != NULL){ 
                           //for(i=1;i<= strlen(Com);i++){ Com1[i-1]= Com[i]; }
                           // iCom[j] = Com; printf("\n%s",iCom[j-1]);j++;} 
                            }    
                    /*Put the tokens into the buffer and pass them to executeCommand fuction*/
                          for(i=0;i<j;i++){
			 //printf("\nVALUE:%s",iCom[i]);
                          executeCommand(iCom[i]);
 	                  }
 }
 else
   printf("Not proper command\n");
   j=0;
}
}
}



/*This fuction takes the string token from the caller and further tokenize them into command and the arguments, then forks the child process to run the command.*/
/*This is a common fuction for both Batch and interactive* mode*/ 
int executeCommand(char *Command){
   //printf("\nHere\n");
   char *CommandTok=NULL, *ComAgvr[512]={};
   int i=0,j,Success=0;
   /*Tokenizing the Command string keeping space as delimiter and then putting this into a list */
    int pid;    
   CommandTok = strtok(Command," ");
    while(CommandTok != NULL){
   //printf("%s%d\n",CommandTok,strlen(CommandTok));
     if(strcmp("quit",CommandTok)==0){
         exit(0);
      }
    ComAgvr[i] = CommandTok; i++;
    CommandTok = strtok(NULL," ");
    }
     
   /*Producing a child process to run the command*/
   pid = fork();
   if(pid == 0){
    // system("ls");
    	Success = execvp(*ComAgvr,ComAgvr);
        if(Success<0){
        printf("\n ERROR: Cannot find the Command %s\n",*ComAgvr);
        }
    }
   else{
     wait();
     }  
  return 0;
 }
