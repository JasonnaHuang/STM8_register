
#include "buzzer.h"
#include "beep.h"

const TONE_Def Tone0 = {FREQ_NO, 0, 0};
const TONE_Def Tone1[] = {{FREQ_2K6, 100, 40},{FREQ_NO, 0, 0}};//单音  
const TONE_Def Tone2[] = {{FREQ_2K3, 20, 30},{FREQ_2K6, 20, 30},{FREQ_2K9, 220, 40},{FREQ_NO, 0, 0}};//开机和弦音
const TONE_Def Tone3[] = {{FREQ_2K9, 20, 30},{FREQ_2K6, 20, 30},{FREQ_2K3, 220, 40},{FREQ_NO, 0, 0}};//关机和弦音

/*
const TONE_Def Tone1[] = {{FREQ_2K6, 100, 20},{FREQ_NO, 0, 0}};//单音  
const TONE_Def Tone2[] = {{FREQ_2K3, 20, 20},{FREQ_2K6, 20, 20},{FREQ_2K9, 210, 10},{FREQ_NO, 0, 0}};//开机和弦音
const TONE_Def Tone3[] = {{FREQ_2K9, 20, 20},{FREQ_2K6, 20, 20},{FREQ_2K3, 210, 10},{FREQ_NO, 0, 0}};//关机和弦音
*/
static TONE_Def * pTone = (TONE_Def *)&Tone0;
static unsigned char BuzzerStatus = 0;
 
//蜂鸣器启动，需要发声时调用
void BuzzerStart(Tone_Type ToneType)
{
  switch (ToneType)
  {
	case MONO:
	  pTone = (TONE_Def *)Tone1;
	  break;
	case POLY_ON:
	  pTone = (TONE_Def *)Tone2;
	  break;
	case POLY_OFF:
	  pTone = (TONE_Def *)Tone3;
	  break;
	default:
	  pTone = (TONE_Def *)Tone1;
	  break;
  }
  BuzzerStatus = 0;
}
//蜂鸣器控制，每10ms执行一次
void BuzzerCtrl(void)
{
  static TONE_Def Tone;
 
  switch (BuzzerStatus)
  {
	case 0:
	  Tone = *pTone;
	  if (Tone.Freq != FREQ_NO) //非结束符
	  {
		//先判断供电持续时间
		if (Tone.PWRTime != 0)
		{
		  Tone.PWRTime --;
		  BeepPwrOn();
		}
		else 
		{
		  BuzzerStatus = 2;
		  break;
		}
		//再判断振荡持续时间
		if (Tone.OSCTime != 0)
		{
		  Tone.OSCTime --;
		  BEEP_SetFreq(Tone.Freq);
		  BEEP_On();
		}
		else 
		{
		  BeepPwrOff();
		  BuzzerStatus = 2;
		  break;
		}
		//判断完成，开始递减计时
		BuzzerStatus = 1;
	  }
	  else // Tone.Freq == FREQ_NO  //是结束符
	  {
		BuzzerStatus = 2;
	  }
	  break;
	case 1:
	  if (Tone.PWRTime != 0)
	  {
		Tone.PWRTime --;
	  }
	  else
	  {
		BeepPwrOff();
	  }
	  if (Tone.OSCTime != 0)
	  {
		Tone.OSCTime --;
	  }
	  else
	  {
		BEEP_Off();
		pTone ++;   //取下一个音调
		BuzzerStatus = 0;
	  }
	  break;
	default:
	  break;
  }
  return;
}