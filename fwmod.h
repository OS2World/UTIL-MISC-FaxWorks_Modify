/* v.h   - MYVIEW include file */

typedef struct {
  ULONG  summary;
  ULONG  processes;
  ULONG  semaphores;
  ULONG  unknown1;
  ULONG  sharedmemory;
  ULONG  modules;
  ULONG  unknown2;
  ULONG  unknown3;
} PROCSTAT;

typedef struct {
  ULONG  type;
  ULONG  threadlist;
  USHORT processid;
  USHORT parentid;
  USHORT sessiontype;
  USHORT unknown1;
  ULONG  unknown2;
  USHORT sessionid;
  USHORT unknown3;
  USHORT modulehandle;
  USHORT threads;
  /* lots of other unknown data */
} PROCESS;

typedef struct {
  ULONG  unknown1;
  USHORT threadid;
  USHORT threadsysid;
  ULONG  blockid;
  USHORT priority;
  USHORT unknown2;
  ULONG  unknown3;
  ULONG  unknown4;
  USHORT status;
  USHORT unknown5;
} THREAD;


/* DosQProcStatus() = DOSCALLS.154 */
#pragma linkage(DosQProcStatus, far16 pascal )
USHORT DosQProcStatus(PVOID pBuf, USHORT cbBuf);

#define BUFFER_SIZE             0x8000

#define ID_menuReceiveOff       0x0074
#define ID_menuReceiveNow       0x0075
#define ID_menuReceiveOne       0x0076
#define ID_menuReceiveAll       0x0077
#define ID_menuQuit             0x0080

