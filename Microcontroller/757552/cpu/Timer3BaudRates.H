/*Timer 3 baud rade constants 
  REV. -  created  March 2011
  REV. A  added 14.7456MHz defines  
          sr 10/14/2020
	For ADuC841 */

/*  20MHZ clock */
				#define	t3con_20M_9600   0x87 //9600 
				#define t3fd_20M_9600    0x01 
				#define	t3con_20M_19200  0x86 //19200
				#define t3fd_20M_19200   0x01 
				#define	t3con_20M_28800  0x85 //28800
				#define t3fd_20M_28800   0x17 
				#define	t3con_20M_38400  0x85 //38400 
				#define t3fd_20M_38400   0x01 
				#define	t3con_20M_57600  0x84	 //57600
				#define t3fd_20M_57600   0x17 
				#define	t3con_20M_76800  0x84 //76800
				#define t3fd_20M_76800   0x01 
				#define	t3con_20M_93750  0x83 //93750
				#define t3fd_20M_93750   0x2b 
				#define	t3con_20M_115200 0x83 //115200
				#define t3fd_20M_115200  0x17 
				#define	t3con_20M_153600 0x83 //153600
				#define t3fd_20M_153600  0x01 
				#define	t3con_20M_230400 0x82 //230400
				#define t3fd_20M_230400  0x17 
				#define	t3con_20M_921600 0x80 //921600
				#define t3fd_20M_921600  0x17 

/*  14.7456MHZ clock */
				#define	t3con_14M_9600   0x86 //9600     div = 6   t3fd = 32   actual = 9600
				#define t3fd_14M_9600    0x20 
				#define	t3con_14M_12800  0x86 //12800    div = 6   t3fd = 8   actual = 12800
				#define t3fd_14M_12800   0x08 
				#define	t3con_14M_19200  0x85 //19200    div = 5   t3fd = 32   actual = 19200
				#define t3fd_14M_19200   0x20 
				#define	t3con_14M_28800  0x85 //28800    div = 5   t3fd = 0    actual = 28800
				#define t3fd_14M_28800   0x00 
        #define	t3con_14M_38400  0x84 //38400    div = 4   t3fd = 32   actual = 38400
        #define t3fd_14M_38400   0x20 
        #define	t3con_14M_57600  0x84 //57600    div = 4   t3fd = 0    actual = 57600
				#define t3fd_14M_M57600  0x00 
				#define	t3con_14M_76800  0x83 //76800    div = 3   t3fd = 32   actual = 76800
				#define t3fd_14M_76800   0x20 
				#define	t3con_14M_3750   0x83 //93750    div = 3   t3fd = 15   actual = 93326 don't know about this one.
				#define t3fd_14M_93750   0x0F 
				#define	t3con_14M_115200 0x83 //115200   div = 3   t3fd = 0    actual = 115200
				#define t3fd_14M_115200  0x00 
				#define	t3con_14M_153600 0x82 //153600   div = 2   t3fd = 32   actual = 153600
				#define t3fd_14M_153600  0x20 
				#define	t3con_14M_230400 0x82 //230400   div = 2   t3fd = 0    actual = 230400
				#define t3fd_14M_230400  0x00 
				#define	t3con_14M_921600 0x80 //921600   div = 0   t3fd = 0    actual = 921600
				#define t3fd_14M_921600  0x00 

/*  11.0592MHZ clock */
				#define	t3con_11M_9600   0x86 //9600 
				#define t3fd_11M_9600    0x08 
				#define	t3con_11M_19200  0x85 //19200
				#define t3fd_11M_19200   0x08 
				#define	t3con_11M_28800  0x84 //28800
				#define t3fd_11M_28800   0x16 
				#define	t3con_11M_38400  0x84 //38400 
				#define t3fd_11M_38400   0x08 
				#define	t3con_11M_57600  0x83	//57600
				#define t3fd_11M_57600   0x20 
				#define	t3con_11M_76800  0x83 //76800
				#define t3fd_11M_76800   0x08 
				#define	t3con_11M_93750  0x82 //93750
				#define t3fd_11M_93750   0x36 
				#define	t3con_11M_115200 0x82 //115200
				#define t3fd_11M_115200  0x20 
				#define	t3con_11M_153600 0x83 //153600
				#define t3fd_11M_153600  0x01 
				#define	t3con_11M_230400 0x81 //230400
				#define t3fd_11M_230400  0x20 
// not possible				#define	t3con11M921600 0x80 //921600
// not possible				#define t3fd11M921600 0x17 

