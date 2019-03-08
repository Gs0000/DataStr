#pragma once
#ifndef _FIFO_H_
#define _FIFO_H_

#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC
#endif
#include <pthread.h>
#include <semaphore.h>

#include "GsDEF.h"

GI32 Create_Circular_Queue();


#endif