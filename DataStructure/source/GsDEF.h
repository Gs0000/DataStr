#pragma once
#ifndef _GSDEF_H_
#define _GSDEF_H_

#if 1
#define Gs_WIN
#else
#define Gs_LINUX
#endif

typedef char      				GCH8;
typedef short  			   	   	GI16;
typedef int						GI32;
typedef long long		     	GI64;

typedef unsigned char      		GUC8;
typedef unsigned short     	   	GU16;
typedef unsigned int			GU32;
typedef unsigned long long     	GU64;

typedef float                   GFLT;
typedef double                  GDBL;

#define Gs_SUCCESS                0
#define Gs_ERROR                 -1
#define Gs_FAILURE               -2
#define Gs_ILLEGAL               -3

#endif