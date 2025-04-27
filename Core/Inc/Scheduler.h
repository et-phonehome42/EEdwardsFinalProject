/*
 * Scheduler.h
 *
 *  Created on: Apr 19, 2025
 *      Author: ethan
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#ifndef Scheduler_H_
#define Scheduler_H_

#include <stdint.h>

//#define LED_TOGGLE_DELAY (1 << 1)
//#define BUTTON_POLL      (1 << 0)

#define APP_DELAY_FLAG_EVENT (1 << 0)
#define DEVICE_ID_AND_TEMP_EVENT (1 << 1)

uint32_t getScheduledEvents(void);
void addSchedulerEvent(uint32_t event);
void removeSchedulerEvent(uint32_t remove);

#endif


#endif /* INC_SCHEDULER_H_ */
