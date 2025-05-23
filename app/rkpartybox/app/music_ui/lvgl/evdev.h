/**
 * @file evdev.h
 *
 */

#ifndef EVDEV_H
#define EVDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------
 * Mouse or touchpad as evdev interface (for Linux based systems)
 *------------------------------------------------*/
#ifndef USE_EVDEV
#  define USE_EVDEV           1
#endif

#ifndef USE_BSD_EVDEV
#  define USE_BSD_EVDEV       0
#endif

#if USE_EVDEV || USE_BSD_EVDEV
#  define EVDEV_NAME   "/dev/input/event2"        /*You can use the "evtest" Linux tool to get the list of devices and test them*/
#  define EVDEV_SWAP_AXES         0               /*Swap the x and y axes of the touchscreen*/

#    define DEFAULT_EVDEV_HOR_MIN         0               /*to invert axis swap EVDEV_XXX_MIN by EVDEV_XXX_MAX*/
#    define DEFAULT_EVDEV_HOR_MAX       1024              /*"evtest" Linux tool can help to get the correct calibraion values>*/
#    define DEFAULT_EVDEV_VER_MIN         0
#    define DEFAULT_EVDEV_VER_MAX       600
#endif  /*USE_EVDEV*/

#if USE_EVDEV || USE_BSD_EVDEV

#include <lvgl/lvgl.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the evdev
 */
int evdev_init(lv_disp_drv_t *drv, int rot);
void evdev_deinit(int rot);
/**
 * reconfigure the device file for evdev
 * @param dev_name set the evdev device filename
 * @return true: the device file set complete
 *         false: the device file doesn't exist current system
 */
int evdev_set_file(lv_disp_drv_t *drv, char *dev_name);
/**
 * Get the current position and state of the evdev
 * @param data store the evdev data here
 * @return false: because the points are not buffered, so no more data to be read
 */
void evdev_read(lv_indev_drv_t *drv, lv_indev_data_t *data);


/**********************
 *      MACROS
 **********************/

#endif /* USE_EVDEV */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* EVDEV_H */
