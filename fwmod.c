/* Modify FaxWorks */

#define INCL_PM
#define INCL_DOSMODULEMGR
#define INCL_DOSSESMGR
#define INCL_DOSPROCESS
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fwmod.h"


/* Declare some forwards */
PID get_faxworks_pid(void);
void send_to_faxworks(PID pidFaxWorks,USHORT menuId);


/* Go for main routine */
int main (int argc, char *argv[]) {
   PID pid;
   USHORT command=0,wait=0;
   int i;

   printf("FaxWorks Modify \n");
   printf("by Nils Meier 08.01.97\n");
   printf("   meier2@athene.informatik.uni-bonn.de\n");

   if (argc==1) {
      printf("\nUsage   : fwmod.exe [Options] \n");
      printf("Options :\n");
      printf(" -0  AutoReceive Off\n");
      printf(" -!  AutoReceive Now\n");
      printf(" -1  AutoReceive One\n");
      printf(" -a  AutoReceive All\n");
      printf(" -sx Set secs to wait before MessagePosting\n");
      printf(" -q  Quit FaxWorks  \n");
      return(0);
      }

   for (i=1;i<argc;i++) {
      if ((*argv[i]!='-')||(*(argv[i]+1)==0)) {
         printf("*** Sorry, illegal options <%s> !",argv[i]);
         exit(1);
         }
      switch (*(argv[i]+1)) {
         case '0' : command=ID_menuReceiveOff;
                    break;
         case '!' : command=ID_menuReceiveNow;
                    break;
         case '1' : command=ID_menuReceiveOne;
                    break;
         case 'a' : command=ID_menuReceiveAll;
                    break;
         case 'q' : command=ID_menuQuit;
                    break;
         case 's' : {
                    wait=atoi(argv[i]+2);
                    if (wait==0) {
                       printf("*** Sorry, bad waittime <%s> !",argv[i]);
                       exit(1);
                       }
                    }
                    break;
         default  : {
                    printf("*** Sorry, illegal option <%s> !",argv[i]);
                    exit(1);
                    }
         }
      }

   if (command==0) {
      printf("Try using a command option !");
      return(1);
   }
   if (wait>0)
      DosSleep(wait*1000);

   pid = get_faxworks_pid();
   if (pid==0) {
      printf("*** Sorry, FaxWorks isn't running \n");
      return(1);
      }
   else {
      send_to_faxworks(pid,command);
      }
   return(0);
}

/* Send Commands to FaxWorks */
void send_to_faxworks(PID pidFaxWorks,USHORT menuId) {
   HMQ hmq;
   HWND hwnd;
   PID pid=0;
   TID tid;
   USHORT wid=0;
   HENUM henum;
   ULONG x,y,w,h;
   ULONG size;
   HAB hab;

   hab=WinInitialize(0);
   hmq=WinCreateMsgQueue(hab,0);

   hwnd = HWND_DESKTOP;
   henum = WinBeginEnumWindows(hwnd);
   while (((wid!=1)||(pid!=pidFaxWorks))&&((hwnd = WinGetNextWindow(henum))!=NULLHANDLE)) {
      WinQueryWindowProcess(hwnd,&pid,&tid);
      wid=WinQueryWindowUShort(hwnd,QWS_ID);
      }
   if ((pid==pidFaxWorks)&&(wid==1)) {
      WinPostMsg(hwnd,WM_COMMAND,MPFROMSHORT(menuId),MPFROMSHORT(0));
      }
   else {
      printf("*** Sorry, found no FaxWorks Windows !?");
      }
   WinEndEnumWindows(henum);
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
}


/* Get FaxWorks processId */
PID get_faxworks_pid() {
   PID pid=0;
   PROCSTAT *procstat;
   SHORT error;
   PROCESS *proc;
   char name[512];

   /* Allocate BUFFER_SIZE memory - aligned at 64k tmalloc() */
   procstat=(PROCSTAT*)malloc(BUFFER_SIZE);

   /* Call 16-bit function DosQProcStat */
   error=DosQProcStatus(procstat,BUFFER_SIZE);

   if (!error) { /* go through the returned data */
      for ( proc = (PROCESS*)procstat->processes ; proc->type != 3 ;
            proc = (PROCESS*)(proc->threadlist + proc->threads*sizeof(THREAD)) ) {
          DosQueryModuleName(proc->modulehandle,sizeof(name),name);
          if (strstr(name,"FAXWORKS.EXE")!=NULL) pid=proc->processid;
         }
      }

   /* Done */
   free(procstat);
   return(pid);
}

