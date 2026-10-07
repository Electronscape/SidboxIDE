
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>






/* @brief Runs the GUI/OS background event service; call regularly when the applet owns its main loop. */
#define sysevents()	(API->gui->osupdate())	// call this if you want OS background service feedback
