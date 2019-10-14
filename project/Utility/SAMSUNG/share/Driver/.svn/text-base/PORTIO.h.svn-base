#ifndef PORTIO_H
#define PORTIO_H
                   

typedef unsigned short USHORT;
typedef unsigned char UCHAR;
typedef unsigned long ULONG;

#ifdef  FOR_REAL_MODE_MS_DOS
    #define  LOBYTE(arg)     (*( unsigned char *)&arg)
    #define  HIBYTE(arg)     (*((unsigned char *)&arg + 1))

    #define  LOINT(arg)      (*( unsigned int *)&arg)
    #define  HIINT(arg)      (*((unsigned int *)&arg + 1))

    #define VOID void
    typedef char CHAR;
    typedef short SHORT;
    typedef int  INT ;
    typedef long LONG;



    typedef unsigned int  UINT;
    typedef unsigned long ULONG_PTR;
    typedef void huge *PVOID;



    typedef CHAR *PCHAR;
    typedef SHORT *PSHORT;
    typedef INT  *PINT;
    typedef LONG *PLONG;

    typedef UCHAR *PUCHAR;
    typedef USHORT *PUSHORT;
    typedef UINT  *PUINT;
    typedef ULONG *PULONG;




    //Following is defined for the Pang's MS-DOS IDE bus Sending Procedure.
    //Make sure the BC3.1 compiler memory model is huge.
    //
    typedef int   HANDLE ;
    typedef int   BOOL;
    typedef ULONG DWORD ;
    typedef void  huge *LPVOID;
    typedef unsigned int  *LPWORD;
    typedef unsigned long *LPDWORD;
    typedef int  LPOVERLAPPED;


#endif

//#define offsetof(s,m)  ( (UINT) &(((s*)0)->m) )

#define AtapiInquiry                0x12
#define LoadUnloadCD                0xA6
#define MechanismStatus             0xBD
#define ModeSelect                  0x55
#define ModeSense                   0x5A
#define PauseResume                 0x4B
#define PlayAudio                   0x45
#define PlayAudioMSF                0x47
#define PlayCD                      0xBc
#define PreventAllowMediumRemoval   0x1E
#define Read10                      0x28
#define Read12                      0xA8
#define ReadCDRomCapacity           0x25
#define ReadCD                      0xBE
#define ReadCDMSF                   0xB9
#define ReadHeader                  0x44
#define ReadSubChannel              0x42
#define ReadTOC                     0x43
#define RequestSense                0x03
#define Scan                        0xBA
#define Seek                        0x2B
#define SetCDSpeed                  0xBB
#define StopPlayScan                0x4E
#define StartStopUnit               0x1B
#define TestUnitReady               0x00



#ifdef  FOR_REAL_MODE_MS_DOS
    #define  UNKNOWN_DRQ           0
    #define  MICROPROCESSOR_DRQ    1
    #define  INTERRUPT_DRQ         2
    #define  ACCELERATED_DRQ       3

    #define FILE_SHARE_READ        1
    #define FILE_SHARE_WRITE       2

    #define GENERIC_READ           1
    #define GENERIC_WRITE          2

    #define OPEN_EXISTING          1

    #define INVALID_HANDLE_VALUE  -1

    #define IOCTL_SCSI_PASS_THROUGH             0
    #define IOCTL_SCSI_PASS_THROUGH_DIRECT      1

    #define SCSI_IOCTL_DATA_OUT                 0
    #define SCSI_IOCTL_DATA_IN                  1


    #define IOCTL_SCSI_PASS_THROUGH             0
    #define IOCTL_SCSI_PASS_THROUGH_DIRECT      1



        /* Define the steps of the AtapiPacketCommand */
                      #define   OnlyA0        0
        //(1)Send 0xA0->return

                      #define   HalfPacket    1
        //(2)Send 0xA0->6 byte of packet command ->return ;

                      #define   WholePacket   2
        //(3)Send 0xA0->12 byte of packet command->return ;

                      #define   HalfRead      3
        //(4)Send 0xA0->12 byte of packet command->(if any) Read 6 byte-> return ;

                      #define   HalfWrite     4
        //(5)Send 0xA0->12 byte of packet command->(if any) write 6 byte-> return ;

                      #define   DataPhase     5
        //(6)Send 0xA0->12 byte of packet command->(if any) data phase-> return ;

                      #define   WholeCommand  6
        //(7)Send 0xA0->12 byte of packet command->(if any) data phase-> Status pahse->return ;


        // Error Code for Global Error: uiGlobalError
        #define IO_CONTROL_NO_ERROR                 0
        #define CREATE_FILE_NO_ERROR                0
        #define INVALID_IO_CONTROL_CODE             1
        #define INVALID_INPUT_BUFFER_LENGTH         2
        #define INVALID_PATH_ID                     3
        #define INVALID_TARGET_ID                   4
        #define INVALID_CDB_LENGTH                  5
        #define CREATE_FILE_WITH_INVALID_FILE_NAME  6

        #define  BSY_DRQ_HI     0x10   // Error when select drive phase.
        #define  BSYAfterA0     0x11
        #define  LoDRQAfterA0   0x12
        #define  IllegalIntRegAfterA0 0x13
        #define  IntTimeOut     0x14
        #define  BSYAfterInt    0x15
        #define  IllegalPhase   0x16
        #define  IllegalPhaseForDataOutCommand 0x17
        #define  IllegalPhaseForDataInCommand  0x18

        #define  BSY_DRQ_HI_IN_AUTO_RQSENSE  0x20
        #define  BSYAfterA0_IN_AUTO_RQSENSE  0x21
        #define  IllegalIntRegAfterA0_IN_AUTO_RQSENSE  0x22
        #define  CheckAfterA0_IN_AUTO_RQSENSE 0x23
        #define  StatusAfterA0_IN_AUTO_RQSENSE  0x24
        #define  IntTimeOut_IN_AUTO_RQSENSE     0x25
        #define  BSYAfterInt_IN_AUTO_RQSENSE    0x26
        #define  DataOutPhase_FOR_AUTO_RQSENSE  0x27
        #define  IllegalPhase_IN_AUTO_RQSENSE   0x28
        #define  AUTO_RQSENSE_RETURN_ZERO_DATA  0x29





        // Status after A0, i.e. drive treat A0 as the ATA command.
        //
        #define  StatusAfterA0  0x2A
        #define  CheckAfterA0   0x2B
        #define  USER_TERMINATED 0x2C

        HANDLE CreateFile ( PCHAR pcName,      // Name string of the device.
                            DWORD dwAccessMode,// access (read-write) mode.
                            DWORD dwShareMode, // share mode
                            PVOID pSecurity,   // pointer to security attribute.
                            DWORD dwCreationDisposition, //how to create.
                            DWORD dwFileAttr,  //File attribute.
                            HANDLE hTemplateFile // Handle to file with attributes to copy
                          );

        BOOL DeviceIoControl(   HANDLE hDevice,           //For Cpang's Pure MS-DOS this is of no use.
                                DWORD dwIoControlCode,    //control code for the operation to perform.
                                LPVOID lpInBuffer,        //pointer to buffer to supply input data.
                                DWORD nInBufferSize,      //size, in byte, of input buffer.
                                LPVOID lpOutBuffer,       //pointer to buffer to receive output data.
                                DWORD nOutBufferSize,     //size, in byte, of output buffer.
                                LPDWORD lpBytesReturned,   //pointer to variable to receive byte count.
                                LPOVERLAPPED lpOverlapped //pointer to structure for asynchronous operation.
                             );
        DWORD GetLastError(void) ;
        // For host program set primary_used   :  means host waiting for intrq.
        // For host program set secondary_used :  means host waiting for intrq.
        // For host program read intrq_actived :  means Intrq is generated.
        // For host counter5 is Read/Write.
        void Access_counter0( int );
        void Access_counter1( int );
        void Access_counter5( int );
        void Access_primary_used(int)  ;
        void Access_secondary_used(int);
        void Access_third_used(int)    ;
        void Access_intrq_actived(int) ;

        #ifdef _PORTIO_
            #define EXTERN
                    UINT PortAddress[][9] =
                     {   0X1F0,    0X1F1,     0X1F1,       0X1F2,   0X1F4,
                         0X1F5,           0X1F6,        0X1F7,      0X1F7,
                         0X170,    0X171,     0X171,       0X172,   0X174,
                         0X175,           0X176,        0X177,      0X177,
                         0X1E8,    0X1E9,     0X1E9,       0X1EA,   0X1EC,
                         0X1ED,           0X1EE,        0X1EF,      0X1EF  } ;
                    UINT  DrqType[6] =
                    { UNKNOWN_DRQ, UNKNOWN_DRQ, UNKNOWN_DRQ, UNKNOWN_DRQ,
                      UNKNOWN_DRQ, UNKNOWN_DRQ, } ;
        #else
            #define EXTERN  extern
            extern  UINT PortAddress[][9] ;
            extern  UINT  DrqType[6]      ;
        #endif

        EXTERN  UINT uiGlobalError ;
        EXTERN  int primary_used,secondary_used,third_used ;
        EXTERN  int intrq_actived, counter5 ;
        EXTERN  int counter0 ,counter1;
        EXTERN  int  iDebugMode ;

        #undef EXTERN
#else //For Windows 2000

    typedef void *PVOID;

    #define   WholeCommand  FALSE

    /* ********* Following is copied from ntddk\inc\ntddscsi.h  ****** */

    #define IOCTL_SCSI_BASE                 FILE_DEVICE_CONTROLLER

    #define DD_SCSI_DEVICE_NAME "\\Device\\ScsiPort"


    //
    // NtDeviceIoControlFile IoControlCode values for this device.
    //
    // Warning:  Remember that the low two bits of the code specify how the
    //           buffers are passed to the driver!
    //

    #define IOCTL_SCSI_PASS_THROUGH         CTL_CODE(IOCTL_SCSI_BASE, 0x0401, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
    #define IOCTL_SCSI_MINIPORT             CTL_CODE(IOCTL_SCSI_BASE, 0x0402, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
    #define IOCTL_SCSI_GET_INQUIRY_DATA     CTL_CODE(IOCTL_SCSI_BASE, 0x0403, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define IOCTL_SCSI_GET_CAPABILITIES     CTL_CODE(IOCTL_SCSI_BASE, 0x0404, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define IOCTL_SCSI_PASS_THROUGH_DIRECT  CTL_CODE(IOCTL_SCSI_BASE, 0x0405, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
    #define IOCTL_SCSI_GET_ADDRESS          CTL_CODE(IOCTL_SCSI_BASE, 0x0406, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define IOCTL_SCSI_RESCAN_BUS           CTL_CODE(IOCTL_SCSI_BASE, 0x0407, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define IOCTL_SCSI_GET_DUMP_POINTERS    CTL_CODE(IOCTL_SCSI_BASE, 0x0408, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define IOCTL_SCSI_FREE_DUMP_POINTERS   CTL_CODE(IOCTL_SCSI_BASE, 0x0409, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define IOCTL_IDE_PASS_THROUGH          CTL_CODE(IOCTL_SCSI_BASE, 0x040a, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

    #define SCSI_IOCTL_DATA_OUT          0
    #define SCSI_IOCTL_DATA_IN           1
    #define SCSI_IOCTL_DATA_UNSPECIFIED  2

#endif

//
// Define the SCSI pass through structure.
//

typedef struct _SCSI_PASS_THROUGH {
    USHORT Length;
    UCHAR ScsiStatus;
    UCHAR PathId;
    UCHAR TargetId;
    UCHAR Lun;
    UCHAR CdbLength;
    UCHAR SenseInfoLength;
    UCHAR DataIn;
    ULONG DataTransferLength;
    ULONG TimeOutValue;
//  ULONG_PTR DataBufferOffset;
    ULONG DataBufferOffset;     //By Cpang
    ULONG SenseInfoOffset;
    UCHAR Cdb[16];
}SCSI_PASS_THROUGH, *PSCSI_PASS_THROUGH;

//
// Define the SCSI pass through direct structure.
//

typedef struct _SCSI_PASS_THROUGH_DIRECT {
    USHORT Length;
    UCHAR ScsiStatus;
    UCHAR PathId;
    UCHAR TargetId;
    UCHAR Lun;
    UCHAR CdbLength;
    UCHAR SenseInfoLength;
    UCHAR DataIn;
    ULONG DataTransferLength;
    ULONG TimeOutValue;
    PVOID DataBuffer;
    ULONG SenseInfoOffset;
    UCHAR Cdb[16];
}SCSI_PASS_THROUGH_DIRECT, *PSCSI_PASS_THROUGH_DIRECT;

typedef struct _SCSI_PASS_THROUGH_WITH_BUFFERS {
    SCSI_PASS_THROUGH spt;
    ULONG             Filler;      // realign buffers to double word boundary
    UCHAR             ucSenseBuf[32];
    UCHAR             ucDataBuf[512];
} SCSI_PASS_THROUGH_WITH_BUFFERS, *PSCSI_PASS_THROUGH_WITH_BUFFERS;

typedef struct _SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER {
    SCSI_PASS_THROUGH_DIRECT sptd;
    ULONG             Filler;      // realign buffer to double word boundary
    UCHAR             ucSenseBuf[32];
} SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, *PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER;

typedef SCSI_PASS_THROUGH_WITH_BUFFERS       SPTWB  ;
typedef SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER SPTDWB ;

#endif
