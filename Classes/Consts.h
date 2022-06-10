/**
* @file Hero.h
* @author wukef
*/

#ifndef __Consts_H__
#define __Consts_H__

/* bitmasks */
#define PlayerBulletAndEnemyBitmask  0x1 //0001
#define EnemyBulletAndPlayerBitmask  0x2 //0010

/* tags */
#define PlayerBulletTag 1
#define EnemyBulletTag 2
#define PlayerTag 3
#define EnemyTag 4
#define EnergyTag 5

/* shootspeed */
#define ShootSpeed 1000

/*smokespeed*/
#define SmokeSpeed 1
#define SmokeDamage 10

/* UI */
#define HpSliderPosY 50
#define MpSliderPosY 45
#define SpSliderPosY 40

#define bulletFull 20
#define ultiFull 100

/* HERO */
#define HealthRecovery 0.1
#define BulletRecovery 0.1

#endif