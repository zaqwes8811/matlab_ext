; file : #include <../headers/i2c_macroses.inc>
; WARNING
I2CMErrBusCollision EQU    7                    ;I2C Bus collision occured
I2CMErrBusBusy      EQU    6                    ;I2C Bus is Busy
I2CMErrNoAck        EQU    5                    ;Slave did'nt acknowledge
I2CMDataReady       EQU    4                    ;I2C Rx Data is ready
;
I2CMBusy            EQU    3                    ;I2CM Communication going on
I2CMBufOverFlow     EQU    2                    ;I2CM Buffer Over flow
I2CMBufFull         EQU    1                    ;I2CM Buffer Full
I2CMBufEmpty        EQU    0                    ;I2CM Buffer Empty
extern	vI2CMIntStatus
#include <../headers/delay_lib.inc>
#define I2C_WAIT_DELAY_US	250

; �������� ��������� ������
I2C_WAIT_RX_READY	macro
	;Wait till Data is ready
	btfss	vI2CMIntStatus,I2CMDataReady
	goto	$-2
endm

; 
I2C_WAIT_TX_BUF_FULL	macro
	btfss	vI2CMIntStatus,I2CMBufFull
	goto	$-2
endm

; ��������� �������� � ��������
I2C_END_WR	macro
	; ����� �������
	mCall	_v2_PIO_SETdw_I2CMIntStop
		
	
	;To Write to be happened 10ms is required.
	;btfsc	vI2CMIntStatus,I2CMBusy
	;goto	$-2
	
	; �������������
	DelayUs	I2C_WAIT_DELAY_US
	DelayUs	I2C_WAIT_DELAY_US
	DelayUs	I2C_WAIT_DELAY_US
	DelayUs	I2C_WAIT_DELAY_US
endm

; ���������� � �������� �����
I2C_PUT	macro WHAT
	movlw	WHAT
	mCall	_v2_PIO_SETdw_I2CMIntPut
endm

; start sending
I2C_PUT_HEAD	macro	ADDR_UNIT, ADDR_REG_IN_UNIT
	; �������� �������
	mCall	_v2_PIO_SETdw_I2CMIntStart	;

	; ����� ��������������� ����������
	I2C_PUT	ADDR_UNIT	; ����� �����
	
	; ������ ����� �������� ������ ����������
	I2C_PUT	ADDR_REG_IN_UNIT
endm

; �������� ��������
I2C_PUT_TRI_BYTE	macro	ADDR_UNIT, ADDR_REG_IN_UNIT, DATA0
	; �������� ����� ����. � ������� ������ ����
	I2C_PUT_HEAD	ADDR_UNIT, ADDR_REG_IN_UNIT
	
	; ������� ������ ��� �����
	I2C_PUT	DATA0
	
	; ���������
	I2C_END_WR
	mRETURN
endm

; ������� �������� ������ � ������� �����
I2C_PUT_FOUR_BYTE	macro	ADDR_UNIT, ADDR_REG_IN_UNIT, DATA0, DATA1
	; �������� ����� ����. � ������� ������ ����
	I2C_PUT_HEAD	ADDR_UNIT, ADDR_REG_IN_UNIT
	
	; ������� ������ ��� �����
	I2C_PUT	DATA0
	
	; ������� ������ ��� �����
	I2C_PUT	DATA1
	
	; ���������
	I2C_END_WR
	mRETURN
endm