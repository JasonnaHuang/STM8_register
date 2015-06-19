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
  MONO = 0,     //����
  POLY_ON = 1,  //��������
  POLY_OFF = 2  //�ػ�����
}Tone_Type;  //��������������
 
typedef struct
{
  FREQ_Type Freq;    //Ƶ��
  unsigned char OSCTime; //�񵴳���ʱ��,��С��λΪ10ms
  unsigned char PWRTime; //�������ʱ��,��С��λΪ10ms
} TONE_Def; //�����ṹ��
 
void BuzzerStart(Tone_Type ToneType);
void BuzzerCtrl(void);

#endif