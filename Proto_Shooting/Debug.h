#pragma once

#ifndef DEBUG_H
#define DEBUG_H

#include <d3d9.h>

#define FVF_DEBUG_CIRCLE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)	//í∏ì_èÓïÒÇÃê›íË

void Debug_Init(void);

void Debug_Uninit(void);

void Debug_Begin(void);

void Debug_End(void);

void Debug_DrawCircle(float x,float y,float radius);

void Debug_SetColor(D3DCOLOR color);

#endif