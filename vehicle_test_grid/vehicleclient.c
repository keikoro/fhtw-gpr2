/*  vehicle_grid_server program
    vehicleclient.c

    GPR2 UE4

    if13b070 - K Kollmann
    if13b076 - Linda Spindler
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <signal.h> 

#define PERM 0660
#define KEY 87

#define MAX_DATA 255

typedef struct
{
	long mType;
	char mText[MAX_DATA];
} message_t;

int main(int argc, char* argv[])
{
   message_t msg;	/* Buffer fuer Message */
   int msgid = -1;	/* Message Queue ID */

   /* Argument Handling */
   if (argc!=2)
   {
      fprintf(stderr,"Usage: %s <Message>\n",argv[0]);
      return EXIT_FAILURE;
   }
   
   /* Message Queue oeffnen */
   if( (msgid = msgget(KEY,PERM))==-1 )
   {
      /* error handling */
      fprintf(stderr,"%s: Can't access message queue\n",argv[0]);
      return EXIT_FAILURE;
   }

   /* Nachricht verschicken */
   msg.mType=1;
   strncpy(msg.mText,argv[1],MAX_DATA);
   if (msgsnd(msgid,&msg,sizeof(msg)-sizeof(long), 0) == -1)
   {
         /* error handling */
         fprintf(stderr,"%s: Can't send message\n",argv[0]);
         return EXIT_FAILURE;
   }
   printf("Message sent: %s\n",msg.mText);
   return EXIT_SUCCESS;
}

