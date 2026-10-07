#include <stdint.h>

//############################################################################################################//
//#                                                                                                          #//
//#   SIDBOX SYSTEMS API — v0.525                                                                            #//
//#   Written by Wayne H. (2025)                                                                             #//
//#                                                                                                          #//
//############################################################################################################//
//                                                                                                            //
//  Applets are intended to be small and self-contained.                                                      //
//                                                                                                            //
//  While the system provides ample external RAM for larger programs,                                         //
//  developers should be mindful of stack usage:                                                              //
//                                                                                                            //
//  • Local variables inside functions consume stack space.                                                   //
//  • The stack is intentionally small (~1 KB) and optimized for speed.                                       //
//  • Large buffers or persistent data should be allocated globally,                                          //
//    where they will reside in external RAM.                                                                 //
//                                                                                                            //
//  The stack is kept within the L2 cache on SIDBOX for maximum performance.                                  //
//  Use it wisely.                                                                                            //
//                                                                                                            //
//############################################################################################################//

	
#ifndef SIDBOX_OS_API_H_
#define SIDBOX_OS_API_H_

#define FILESYSAPI

#define __weak __attribute__((weak)) 

/* These types MUST be 16-bit or 32-bit */
typedef int				INT;
typedef unsigned int	UINT;

/* This type MUST be 8-bit */
typedef unsigned char	BYTE;

/* These types MUST be 16-bit */
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types MUST be 32-bit */
typedef long			LONG;
typedef unsigned long	DWORD;

/* This type MUST be 64-bit (Remove this for ANSI C (C89) compatibility) */
typedef unsigned long long QWORD;
typedef DWORD FSIZE_t;
typedef char TCHAR;

#define MAX_DEPTH 256

extern long _Randseed;
/* @brief Returns a signed pseudo-random value in the range -range to +range. */
int16_t randomi(unsigned short range);		// random from -range to +range
/* @brief Returns an unsigned pseudo-random value from 0 up to the requested range. */
uint16_t urandomi(unsigned short range);	// random from 0 to range
/* @brief Seeds the SIDBOX pseudo-random number generator. */
void urandomseed(long seed);

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

// Align to 4 byte memory location
#define ALIGN4(x) (((x) + 3) & ~3)

// SIDBOX EXTERNAL RAM STARTS AT 0xD0000000
#define RAMLOCATION		0xD0000000
// Exported applet entry point function (must match ENTRY in ld script)
extern const char _largest_modfile;
/* @brief Initialises the applet heap range used by the runtime allocator. */
void initMalloc(void);


// ## MEMORY ALIGNMENT FOR DMA AND PERFORMANCE ##
// These alignment attributes help ensure that memory structures are placed at
// boundaries compatible with DMA hardware and faster memory access.
// Use them for large graphics buffers, tightly timed variables, and
// anywhere unaligned memory access may cause issues or slowdowns.
#define MEMALIGN4    __attribute__((aligned(4)))    // Align to 4-byte  boundary (basic word alignment)
#define MEMALIGN8    __attribute__((aligned(8)))    // Align to 8-byte  boundary (often used for 64-bit types)
#define MEMALIGN16   __attribute__((aligned(16)))   // Align to 16-byte boundary (good for SIMD and cache lines)
#define MEMALIGN32   __attribute__((aligned(32)))   // Align to 32-byte boundary (ideal for DMA transfers and large buffers)


// STM32H743 REGISTER ADDRESSES  (DO NOT EDIT THESE VALUES)
#define SCB_CCR              (*(volatile uint32_t *)0xE000ED14)
#define SCB_CCR_DIV_0_TRP    (1 << 4)

// USE THESE
#define DIVZEROON			SCB_CCR |=  SCB_CCR_DIV_0_TRP;
#define DIVZEROOFF			SCB_CCR &= ~SCB_CCR_DIV_0_TRP;


// --------- ADD THIS IF YOU WANT IT ------------------
// all this does is press and hold a button to exit a program, not strictly required, but handy for a quick QUIT :)
#define EXITME	\
	uint8_t exiter = ExitCode();\
	if(exiter) return(exiter); 




//// [ SODBOX STDLIB ] ////////////////////////////////////////////////////////
// EXTREME BASICS                                                           ///
////////////////////////////////////////////////////////////////////////////////////////////////
// graphics hardware-access
#include "graphics/graphics.h"

#include "crt/crt.h"
// gui
#include "gui/console.h"
#include "gui/window.h"
#include "gui/gadgets.h"
#include "gui/dialogs.h"
#include "gui/timers.h"
#include "sys/timers.h"
#include "gui/menus.h"

// hardware levels
#include "touch/touch.h"



// USING THIS YOU open up an area of 1MB of CACHED and BUFFERED memory (SPEED)
// and must follow an offset profile, ANY Music is loaded at 0xD0000000 (SDRAM) so if your program starts at 128k off set, use profile 1
// eg. program uses 256k of mod music, your program would start at offset 256k, use profile 2...
#define GAMEMODE_BANKSIZE		(256 * 2048)			// bytes
#define GAMEMODE_PROFILE_0		(0 * GAMEMODE_BANKSIZE)	// 0kb
#define GAMEMODE_PROFILE_1		(1 * GAMEMODE_BANKSIZE)	// 1  - 512k; 
#define GAMEMODE_PROFILE_2		(2 * GAMEMODE_BANKSIZE) // 2  - 1 meg
#define GAMEMODE_PROFILE_3		(3 * GAMEMODE_BANKSIZE)	// 3  - 1.5 Meg
#define GAMEMODE_PROFILE_4		(4 * GAMEMODE_BANKSIZE)	// 4  - 2 meg
#define GAMEMODE_PROFILE_5		(5 * GAMEMODE_BANKSIZE)	// 5  - 2.5 meg
#define GAMEMODE_PROFILE_6		(6 * GAMEMODE_BANKSIZE)	// 6  - 3 meg
#define GAMEMODE_PROFILE_7		(7 * GAMEMODE_BANKSIZE) // 7  - 3.5 meg
#define GAMEMODE_PROFILE_8		(7 * GAMEMODE_BANKSIZE) // 8  - 4 meg
#define GAMEMODE_PROFILE_9		(7 * GAMEMODE_BANKSIZE) // 9  - 4.5 meg
#define GAMEMODE_PROFILE_10		(7 * GAMEMODE_BANKSIZE) // 10 - 5 meg
#define GAMEMODE_PROFILE_11		(7 * GAMEMODE_BANKSIZE) // 11 - 5.5 meg
#define GAMEMODE_PROFILE_12		(7 * GAMEMODE_BANKSIZE) // 12 - 6 meg



//// # JOYSTICK PORT # ////
#define BTN_NULL	0x00
#define BTN_FIRE 	0x01
#define BTN_FIRE2 	0x02
#define BTN_UP 		0x04
#define BTN_DOWN 	0x08
#define BTN_LEFT 	0x10
#define BTN_RIGHT 	0x20



//// # HARDWARE LEVEL # ///////#
typedef struct {
	/*
	gamemode setsup the MPU to allow for cached ram access to software loaded in the selected offset. gives speed and higher access
	it comes with some caution: cached ram instructions need care
	*/
    void     (*gamemode)         (uint32_t offset);  // MPU 256k exec memory offset location.
    void     (*exitgamemode)     (void);
	uint32_t (*getTicks)         (void);			// get system ticks
	void     (*dbug)		     (char *string);


	uint8_t  (*getmousepos)      (int16_t *mx, int16_t *my);
	void     (*setmousepos)      (int16_t  mx, int16_t  my);
	void     (*getmousedelta)    (int32_t *dx, int32_t *dy);
	void     (*clrmousedelta)    (void);
	
	uint8_t  (*getjoyport)	     (void);

	uint16_t *(*get32kmem)       (void);  // 16 bit memory specific
    uint8_t  *(*get16kmem8)      (void);  // 8 bit memory specific

	// internal IRQ's - use these to turn everything off from the OS
	void     (*lcd_disp_disable) (void);    // to disarm the LCD
    void     (*lcd_disp_enable)  (void);    // to re-enable the LCD

    void     (*irq_usb_disable)  (void);
    void     (*irq_usb_enable)   (void);
    void     (*irq_joy_disable)  (void);
    void     (*irq_joy_enable)   (void);
    void     (*irq_audio_disable)(void);
    void     (*irq_audio_enable) (void);
    void     (*irq_emu_disable)  (void);
    void     (*irq_emu_enable)   (void);
    void     (*irq_uart_disable) (void);
    void     (*irq_uart_enable)  (void);
    void     (*irq_mdma_disable) (void);
    void     (*irq_mdma_enable)  (void);
	/* ------------------------------------------------------------*/

	void     (*rtc_gettime)      (uint8_t* hour, uint8_t* min, uint8_t* sec);
    void     (*rtc_getdate)      (uint8_t* year, uint8_t* month, uint8_t* day, uint8_t* weekday);

    const API_TIMERS *timers;
	
} API_HW ;



//// # GUI INTERFACING # //////#
typedef struct  {
    const API_GUI_Console *console;
	const API_GUI_Windows *windows;
	void (*osupdate) (void);
	const API_GUI_Gadgets *gadgets;
	const API_GUI_DIALOGS *dialogs;
	const API_SYS_TIMERS  *timers;
	const API_GUI_Menus   *menus;
} API_GUI;

#include "audio/audio.h"
#include "crt/crt.h"

typedef struct {
	const API_AUDIO_HARDWARE *audhl;
	const API_MUSIC 		 *music;
	const API_SOUND 		 *sound;

	const API_AUDIO_MIDI     *midi;
} API_AUDIO;



#include "graphics/sb3dapi.h"

typedef struct {
    int     (*clipTriangleToFrustum)     (Vec3_api a, Vec3_api b, Vec3_api c, Vec3_api *outVerts, const Camera_api *cam, Vec3_api *src, Vec3_api *dst );
	uint8_t (*entitySweepRaycastTestAPI) (int movingId, int targetId, Vec3_api *hitPos, Tri_api *triHit, Entity_api *worldEntities);
} API_3D_RENDER;

typedef struct {
    const API_3D_RENDER *renderer;
} API_3D;





typedef struct  {
	void (*IRQ_LCD_VBL) (void (*isr)(void));
	void (*IRQ_MIDI_RX) (void (*isr)(uint8_t byte));
} API_IRQ_BANK;

#define API_JPEG_OK             0
#define API_JPEG_ERR_ARG       -1
#define API_JPEG_ERR_FORMAT    -2
#define API_JPEG_ERR_UNSUP     -3
#define API_JPEG_ERR_NOMEM     -4
#define API_JPEG_ERR_HW        -5

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t components;
    uint8_t subsampling;
} API_JPEG_INFO;

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t *pixels;
} API_JPEG_IMAGE8;

typedef struct {
    int  (*info)          (const uint8_t *jpeg, uint32_t len, API_JPEG_INFO *info);
    int  (*decode_rgb332) (const uint8_t *jpeg, uint32_t len, API_JPEG_IMAGE8 *image);
    void (*free_image)    (API_JPEG_IMAGE8 *image);
} API_JPEG;

typedef struct {
    const API_JPEG *jpeg;
} API_MEDIA;


#include "sys/sys.h"

#define alignmem4 	__attribute__((aligned(4)))
#define align32 	__attribute__((aligned(32)))

//// # API ROOT DIRECTORY # ///#
typedef struct __attribute__((aligned(4))) {
	const API_HW 		*hwl;		// hardware level flaps
	const API_SYSTEMS 	*system;	// operating system stuffs
    const API_GUI     	*gui;   	// always here
	const API_GFX     	*gfx;   	// graphics library system
	const API_3D        *sb3d;		// the 3D graphics system
	const API_AUDIO   	*audio;		// audio systems
	const API_TOUCH     *touch;     // touch screen systems
	const API_CRT       *crt;       // CRT RGBI output
	const API_IRQ_BANK	*irq;		// interrupt call backs
	const API_MEDIA     *media;     // image/media helpers
	
} API_Root;

//// memory assignment /////////////////////////////////////////////////////////////////////////
extern const char __sidbox_api_location;   // const char is the classic “linker symbol” type
#define SIDBOX_API_BASE ((uintptr_t)&__sidbox_api_location)
#define API ((volatile const API_Root *)SIDBOX_API_BASE)

#include "gui/os.h"


//// API CONTROL END ///////////////////////////////////////////////////////////////////////////

///////////-------------- HELPERS -----------------//////
/////////////////// hardware level stuff ################
#define HWKERNAL	(API->hwl)

// conf and hardware setups
#define IRQSERVICE  (API->irq)
/* @brief Registers a callback for the LCD vertical-blank interrupt. */
#define irq_lcd_vbl(isr)			(IRQSERVICE->IRQ_LCD_VBL(isr))	// the IRQ is internally cleared, so dont need to do this
/* @brief Registers a MIDI receive callback; pass 0 to remove the callback. */
#define irq_midi(isr)				(IRQSERVICE->IRQ_MIDI_RX(isr))	// pass 0 to remove the MIDI byte callback

/* @brief Selects the cached executable SDRAM run-mode/profile for the applet. */
#define configure_runmode(profile)	(HWKERNAL->gamemode(profile))
/* @brief Disables the LCD display hardware while the applet needs direct control. */
#define hw_disarm_lcd()				(HWKERNAL->lcd_disp_disable())
/* @brief Re-enables the LCD display hardware after it has been disarmed. */
#define hw_rearm_lcd()				(HWKERNAL->lcd_disp_enable())
/* @brief Disables the SIDBOX USB interrupt service. */
#define hw_disable_irq_usb()		(HWKERNAL->irq_usb_disable())
/* @brief Enables the SIDBOX USB interrupt service. */
#define hw_enable_irq_usb()			(HWKERNAL->irq_usb_enable())
/* @brief Disables joystick-port interrupt handling. */
#define hw_disable_irq_joystick()	(HWKERNAL->irq_joy_disable())
/* @brief Enables joystick-port interrupt handling. */
#define hw_enable_irq_joystick()	(HWKERNAL->irq_joy_enable())
/* @brief Disables mouse/joystick-port interrupt handling. */
#define hw_disable_irq_mouse()		(HWKERNAL->irq_joy_disable())
/* @brief Enables mouse/joystick-port interrupt handling. */
#define hw_enable_irq_mouse()		(HWKERNAL->irq_joy_enable())
/* @brief Disables the audio-sampler interrupt service. */
#define hw_disable_irq_audiosampler() (HWKERNAL->irq_audio_disable())
/* @brief Enables the audio-sampler interrupt service. */
#define hw_enable_irq_audiosampler()	(HWKERNAL->irq_audio_enable())
/* @brief Disables the emulator interrupt service. */
#define hw_disable_irq_emulator()	(HWKERNAL->irq_emu_disable())
/* @brief Enables the emulator interrupt service. */
#define hw_enable_irq_emulator()	(HWKERNAL->irq_emu_enable())
/* @brief Disables UART interrupt handling. */
#define hw_disable_irq_uart()		(HWKERNAL->irq_uart_disable())
/* @brief Enables UART interrupt handling. */
#define hw_enable_irq_uart()		(HWKERNAL->irq_uart_enable())
/* @brief Disables MDMA interrupt handling. */
#define hw_disable_irq_mdma()		(HWKERNAL->irq_mdma_disable())
/* @brief Enables MDMA interrupt handling. */
#define hw_enable_irq_mdma()		(HWKERNAL->irq_mdma_enable())

/* @brief Alias for hw_disable_irq_usb(). */
#define disable_irq_usb()			hw_disable_irq_usb()
/* @brief Alias for hw_enable_irq_usb(). */
#define enable_irq_usb()			hw_enable_irq_usb()
/* @brief Alias for hw_disable_irq_joystick(). */
#define disable_irq_joystick()		hw_disable_irq_joystick()
/* @brief Alias for hw_enable_irq_joystick(). */
#define enable_irq_joystick()		hw_enable_irq_joystick()
/* @brief Alias for hw_disable_irq_mouse(). */
#define disable_irq_mouse()			hw_disable_irq_mouse()
/* @brief Alias for hw_enable_irq_mouse(). */
#define enable_irq_mouse()			hw_enable_irq_mouse()
/* @brief Alias for hw_disable_irq_audiosampler(). */
#define disable_irq_audiosampler()	hw_disable_irq_audiosampler()
/* @brief Alias for hw_enable_irq_audiosampler(). */
#define enable_irq_audiosampler()	hw_enable_irq_audiosampler()
/* @brief Alias for hw_disable_irq_emulator(). */
#define disable_irq_emulator()		hw_disable_irq_emulator()
/* @brief Alias for hw_enable_irq_emulator(). */
#define enable_irq_emulator()		hw_enable_irq_emulator()
/* @brief Alias for hw_disable_irq_uart(). */
#define disable_irq_uart()			hw_disable_irq_uart()
/* @brief Alias for hw_enable_irq_uart(). */
#define enable_irq_uart()			hw_enable_irq_uart()
/* @brief Alias for hw_disable_irq_mdma(). */
#define disable_irq_mdma()			hw_disable_irq_mdma()
/* @brief Alias for hw_enable_irq_mdma(). */
#define enable_irq_mdma()			hw_enable_irq_mdma()

/* @brief Sends a string to the SIDBOX low-level debug output. */
#define dbug(s) 	        (API->hwl->dbug(s))

// Mouse interfacing
/* @brief Reads the current mouse pointer position into x and y. */
#define getmousepos(x, y)   (HWKERNAL->getmousepos(x,y))
/* @brief Sets the current mouse pointer position. */
#define setmousepos(x, y)   (HWKERNAL->setmousepos(x,y))
/* @brief Returns accumulated mouse movement since the last delta clear. */
#define getmousedelta(x, y) (HWKERNAL->getmousedelta(x,y))
/* @brief Clears the accumulated mouse movement delta. */
#define clrmousedelta()	    (HWKERNAL->clrmousedelta())

//#define CPU_HZ 480000000.0f
#define CPU_HZ 480000000.0f
#define TICK_TO_SECONDS     (1.0f / CPU_HZ)
/* @brief Returns the current low-level system tick counter. */
#define getTicks()			(HWKERNAL->getTicks())

// joy stick interfacing (usually just for the port Y1, Y2, X1, X2, BTn1, BTn2, up/down/left/right/fire1/fire2)
/* @brief Reads the current joystick-port button/direction bitfield. */
#define getjoyport()   		(HWKERNAL->getjoyport())

/* @brief Returns the SIDBOX 16-bit temporary memory buffer exposed by the hardware API. */
#define get32kmem()	   		(HWKERNAL->get32kmem())
/* @brief Returns the SIDBOX 8-bit temporary memory buffer exposed by the hardware API. */
#define get16k8mem()		(HWKERNAL->get16kmem8())

// touch screen interfacing
#ifndef apiTouchInit
/* @brief Initialises the touchscreen interface. */
#define apiTouchInit()      (API->touch->init())
#endif
#ifndef apiTouchDown
/* @brief Returns whether the touchscreen is currently pressed. */
#define apiTouchDown()      (API->touch->ispressed())
#endif
#ifndef apiTouchGetXY
/* @brief Reads calibrated touchscreen coordinates into x and y. */
#define apiTouchGetXY(x, y) (API->touch->getxy(x,y))
#endif
#ifndef apiTouchGetRawXY
/* @brief Reads raw touchscreen coordinates into x and y. */
#define apiTouchGetRawXY(x,y) (API->touch->getrawxy(x,y))
#endif
#ifndef apiTouchPressure
/* @brief Returns the current touchscreen pressure reading. */
#define apiTouchPressure()  (API->touch->getpressure())
#endif

// system clock API
//void     (*rtc_gettime)      (uint8_t* hour, uint8_t* min, uint8_t* sec);
//void     (*rtc_getdate)      (uint8_t* year, uint8_t* month, uint8_t* day, uint8_t* weekday);
/* @brief Reads the real-time clock hour, minute and second values. */
#define API_GetTime(hour, min, sec)				(API->hwl->rtc_gettime(hour, min, sec))
//#define API_GetDate(year, month, day, weekday)


// dedicated 3D math
/* @brief Clips a 3D triangle against the camera viewing frustum and writes the resulting vertices. */
#define sb3D_clipTriangleToFrustum(a, b, c, outVerts, cam, src, dst) (API->sb3d->renderer->clipTriangleToFrustum(a, b, c, outVerts, cam, src, dst))
/* @brief Tests a moving 3D entity against a target entity and reports the hit position/triangle. */
#define sb3D_entitySweepRaycastTestAPI(movingId, targetId, hitPos, triHit, worldEntities) (API->sb3d->renderer->entitySweepRaycastTestAPI(movingId, targetId, hitPos, triHit, worldEntities))




#endif //SIDBOX_OS_API_H_
