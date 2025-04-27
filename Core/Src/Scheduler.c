/*
 * Scheduler.c
 *
 *  Created on: Apr 19, 2025
 *      Author: ethan
 */
#include "Scheduler.h"

static uint32_t scheduledEvents;


uint32_t getScheduledEvents(void)
{
	return scheduledEvents;
}


void addSchedulerEvent(uint32_t event)
{
	scheduledEvents |= event;
}

void removeSchedulerEvent(uint32_t remove)
{
	scheduledEvents &= ~(remove);
}


