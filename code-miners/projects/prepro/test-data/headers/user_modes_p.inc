;rev...1 ����� �������� ������ �� �., ���� ���� ��� �� ������ - �� ������ �� ���������� � RETURN
;		����� ��� �� T ���� ��� �����. ���������� ��� ������ �� ��������  _ON. ������� �������� ���������� ���. ����� 
;		�������� �������� 20���. ���� ���� ��� ���������� ������ � DS, �� ������� ���� ��������� -(����������)  
;rev.1.2 ��������� ��������� ����������� �� ������ ��� � ������� ������������. ����������� ����� ����������� (HOT)
;        ����� ������ �� � ������ (00-04) ������� ������ EEPROM -�� �����������!!!
;
;rev.1.3	???��7150990/2
;rev.1.4	��7150990/3
;	� ������ ������� 2-� ������������ ���� 033. ������(MODE_OLD033) � ����� (MODE_NEW_033)- � ����� 
;	������� ������� ���������� ���������� ������ ���-� ��������������� � 033 �����. ����� 
;	������, ��������� ������� �� 032. 
;NOTE: � ������ 202 ������ 1ms ����������� (PORTB,1)���
;��������� ����� ������� �� ��.

#include "p18f2520.inc"
radix dec
#include	<../headers/init_data.inc>

#define _TEST
#ifdef _TEST
	#define SHIFT_CORRECTION_TEST
	#define NO_ALRMS
	;#define CURRENT_MOCK_VALUE	; ���������
	#ifdef CURRENT_MOCK_VALUE
		#define TEST_MOCK_CURRENT 0x01FE	;48.0 V; bits - 10
	#endif
	;#define VOLTAGE_MOCK_VALUE	; ���������
	#ifdef VOLTAGE_MOCK_VALUE
		#define TEST_MOCK_VOLTAGE 0x01FE	;48.0 V; bits - 10
	#endif
#endif
;#define bootloader
	;no implement
	
#define PATHES
#ifdef PATHES
	#define PATH_UKV_ALRMS	; �� ��������� ���� 
	;#define LOCAL_DATA_PROC
#endif ;PATH

;/// /// ///
;///
;/// Modes - �� ����������� �� ����� �����. �� ������ �� ���� ����, � ��� ��������� ������?
;#define MODE_4U ; ����� ����������, �����, ���� ������ ������ ������ �� ����������
#define MODE_3U

;����� ������ ��� �� ���������� (MODE_3U_OLD)
;#define MODE_3U_OLD

;����� ������ ��� �� ������������ D12-D13 (MODE_3U_NEW_ALU
#define	MODE_3U_NEW_ALU
	; � I2C.asm ��������� ������ (167),���������� ��� 1-�� ���� 089  :	���!!!!! ���!!!03122010	
	; bcf	P ORTA,7,0	
	; RS activate		
	; -10112010,  for only old ver 089 !!! 

; ��� ����� 3U, ����� ����� 033, � �������� "�������� ���������� ������� ���"

;#define MODE_OLD
#define	MODE_NEW_033
;///
;///
;/// /// ///

; ��� 033 ������� ������ �� ����������
#ifdef MODE_NEW_033
	;#define MIP_42V
		; ������ ������ �� ��� 42V (+13%/-15%)
	
	#define MIP_48V
		; ������ ����� �� ��� 48V (+13%/-15%)
	;#define MODE_CONTROL_CH_MIP - ���������� �������� ��� ��� 3U (new033)
#endif

; ����� �� ����������
#ifdef	MIP_42V 
	#define POWER_SOURSE_THR 0x0DA5 ;ref=3,89V
#endif
#ifdef	MIP_48V
	;#define POWER_SOURSE_THR 0x0F9C ;ref=4,45V
	#define POWER_SOURSE_THR d'3864' ;ref=4,45V
	;#define ZERO_VOLTAGE_CORRECT 0x0000	;0 V; bits - 10
	;const double TA_VOLTAGE_MUL = 0.0941176470588;
#endif

; ����� �� ����
#define HALL_SENSORS
#ifdef MODE_4U
#ifdef HALL_SENSORS
		#define CURRENT_THR 0x075D
#else
		#define CURRENT_THR 0x075D
#endif
#endif

#ifdef MODE_3U
#ifdef HALL_SENSORS
	#define ZERO_HALL_CORRECT 0x005C	;0 A; bits - 10
	;#define CURRENT_THR 0x0B17	;16 A  bits - 12
	;#define CURRENT_THR 0x0D77	;20 A  bits - 12
	#define CURRENT_THR 0x0EA8	;22 A  bits - 12
;const double TA_CURRENT_MUL = 0.028818443804;
#endif ;HALL_SENSOR

	;#define CURRENT_THR 0x08E3
#endif


; ��� �����-�� ������ �� ���������� - �� ������� ��������, ��� ��� ������ �� ����. ���� �����
;#ifdef	MODE_4U
	;#define U_HEIGHT d'235'	; 46V - ��� 4U;   4,9V	(d'251') - ��� 3U   (�����: +2%/- 10%) ���� d'189'
;#endif
;#ifdef	MODE_3U_OLD
	;#define U_HEIGHT d'251'	; 49V	(d'251') - ��� 3U 
;#endif
;#ifdef	MODE_4U
	;#define U_LOW	d'194'		; 38v 4U,	43V ( d'220' -3U )     ���� d'189'; 37V
;#endif
;#ifdef	MODE_3U
	;#define U_LOW	d'220'		; 43V ( d'220' -3U )
;#endif
;#define U_LOW	d'220'		; 43V ( d'220' -3U )
;#define U_HEIGHT d'251'	; 49V	(d'251') - ��� 3U 

; �����-�� ������������� ������
#define ONE_THRESH 90 ;84;80 
#define TWO_THRESH 80 ;75;70

; ����� ����� �� �����, ����� ����� ��� ������������ ���� �������
#define		LENGTH	13
#define		VOID 0
#include	<../pic18_mc_asm_lib/headers/DELAY14.INC>

	
