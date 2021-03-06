; format - Ok
#include 	P18F8722.inc
	radix dec
constant		UPNUM		=		1
; aUnit testing
;#define testI2C_INT
	; ����������� ����.
	; Step0:
	;   1.��������
	;   2. ����������� ��������
	;      ��������� ���������� �������
	;   3. ���������� �������
	;   4. ������� �������� ������ ������
	;     Point : �������� � ������
	; Step1:
	;   1. Point
	;   2. �������� � ���������
	; Step2:
	;   1. Point
	;   2. ����� �� ���������� �������
#define ZOND
;#define ATT_6DB
;#define ATT_3DB

; aDebug directives
;#define DBG_USM	; ����� � ���� �� �������� ���� � ������
;#define DBG_ACS
;#define DBG_U_MIP
;#define VUM_DBG	; ������� ������ +igor
#define VUM_TEMPER_DBG	; ������� ������ +igor �������� ����� ������ �� ������.
#ifdef VUM_TEMPER_DBG
	#define TERM_THRESHOLD 32 ; oC ����� ������������ ������ �� ����������
#else
	#define TERM_THRESHOLD 86 ; oC ����� ������������ ������ �� ����������
#endif
;#define otladka
;#define otladka_INFO_ASKdw_CurShiftedW	; ���� �� �������� ������� ���������(�������� �� ����� ����. �� i 2c)

;/// ������� ��������� �������
;#define bootloader
;#define WithDetector

#define	_2Ublock
;#define _3Ublock	;��� �������� 3U ����� �������������� ���� ������!!! +180511
;#define _3U_polovina_block	; +180511 andrey +ifdef in _V3_INFO.asm
;#define PEEP_ON		; ��������� ���������

; ���������� ������� 
#define _Umip42V		;��� ������ ������ �� ��� �� +42(+13%/-15%) V	 +020312
;#define _Umip48V		;��� ������ ������ �� ��� �� +48(+13%/-15%) V	 +020312
;#define TM_500W		; ��������
#define TM_250W
;#define TM_100W

; ������ �� ����
#ifdef TM_500W
	#define CURRENT_THRESHOLD 0xA9F	; ����� �� ����
#endif
#ifdef TM_250W
	#define CURRENT_THRESHOLD 0x855	; 10 �
#endif
#ifdef TM_100W
	#define CURRENT_THRESHOLD 0x49B	; ����� �� ����
#endif

#define TH_TATT 0xFFF;4095;

; ����� �� ����������
#ifdef	_Umip42V
	#define VOLTAGE_THRESHOLD 0xDA5
#endif
#ifdef	_Umip48V
	#define VOLTAGE_THRESHOLD 0xF9C
#endif

; �������������
#define VUM		; +igor
#define UKV_ARU		; ����� ����� ���� ��� ��������� - 

; /// ������! ���������� ����
; ������ ��������
;#define _Uniplex	; ��� ������������� ������������ ����/�������� - ������� ����������.
					;   ��� ����������� ����� ����/�������� ���������� � _duplex
#define _duplex		; (��� ���������� _Uniplex)��� ������������� ���������� �� ���. 
					;   DUX �����. ��� 0 (�������=const)/��� ����������� �� DUX ��� 1(��������). 
					;   �� ������� ��������� �� ������� 
;#define DVBT2bred_		;�������� ��������� ��� (����� 6,0 �) ��� ��������� ��� (_V3_BUM)
#define	manyBUM_OFF_bDE		; ������������!!!, ��� ������������ ��� 
							;   (����������� ����������485 ��� ������������, ��� >1 ����,� ��� 100�� - 
							;   MAX1485 ��� �� �������� ���������!
;#define NO_BOARD
;#define RawDetData

; ������� � �������������
;#define fullspeed
;#define liqiud600
;#define air600
#define air100

; ������ ������� �� �����������


#include <../headers/g_consts.inc>
#include <../headers/objects_macro.inc>
#include <../headers/registry.inc>


