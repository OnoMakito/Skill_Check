#pragma once

#ifndef PATTERN_H
#define PATTERN_H


#define FIGHTER_PATTERN_MAX (2)
#define EXPLOSION_PATTERN_MAX (8)
#define EXPLOSION2_PATTERN_MAX (16)
#define ENEMY_BULLET_PATTERN_MAX (2)
#define TITLE_ENTER_PATTERN_MAX (2)
#define EFFECT_PATTERN_MAX (11)

void PatternAnimation_Init(void);

void PatternAnimation_Draw_Player(float dx, float dy, int FrameCount);

void PatternAnimation_Draw_Explosion(float dx, float dy, int FrameCount);

void PatternAnimation_Draw_EnemyBullet(float dx, float dy, int FrameCount);

void PatternAnimation_Draw_TitleEnter(float dx, float dy, int FrameCount);

void PatternAnimation_Effect(float dx, float dy, int FrameCount);

void PatternAnimation_NewScore(float dx, float dy, int FrameCount);

void PatternAnimation_Pose(float dx, float dy, int FrameCount);

//void PatternAnimation_DrawProto(float dx, float dy, int FrameCount);	//座標ｘ、座標ｙ、フレーム、方向

#endif