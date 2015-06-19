/* BUZZER.H file
 * Date:2015.6.5
 * Auth:Jason.H_{
 */
#ifndef __BUZZER_H
#define __BUZZER_H

#define FREQ_NO  0
#define FREQ_2K  2120
#define FREQ_2K3 2440
#define FREQ_2K6 2760
#define FREQ_2K9 3080


typedef  unsigned short  FREQ_Type;

typedef enum
{
  MONO = 0,     //单音
  POLY_ON = 1,  //开机和弦
  POLY_OFF = 2  //关机和弦
}Tone_Type;  //蜂鸣器声音类型
 
typedef struct
{
  FREQ_Type Freq;    //频率
  unsigned char OSCTime; //振荡持续时间,最小单位为10ms
  unsigned char PWRTime; //供电持续时间,最小单位为10ms
} TONE_Def; //音调结构体
 
void BuzzerStart(Tone_Type ToneType);
void BuzzerCtrl(void);

#endif