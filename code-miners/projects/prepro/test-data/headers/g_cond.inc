; condition logic
; #include <../headers/g_cond.inc>

SET_BIT	macro nameReg, POSITION
	mObject_sel	THIS
	bsf	nameReg,	POSITION	; 0000_000!1
	mRETURN
endm

CLR_BIT	macro nameReg, POSITION
	mObject_sel	THIS
	bcf	nameReg,	POSITION	; 0000_000!1
	mRETURN
endm

;
BIT_TEST_0	macro nameReg, POSITION, link0
	mObject_sel	THIS
	btfss	nameReg, POSITION	; ���� 1 �� �� ������ ����
		goto	link0
endm

;
BIT_TEST_1	macro nameReg, POSITION, link1
	mObject_sel	THIS
	btfsc	nameReg, POSITION	; ���� 1 �� �� ������ ����
		goto	link1
endm


; ������� ���� �� ����� ����
SLIDE_IF_W_NO_ZERO	macro	link
	btfss	STATUS,Z	; ������ ���� ���� ���� �����������, �.�. � ���. ����
		goto	link
endm

; ������� �� ����� ���� ��� ����� �������
SLIDE_IF_BIT_SET	macro	nameReg, POS, linkSet
	mObject_sel	THIS
	btfss	nameReg,POS
		goto	linkSet
endm

; ������� �� ����� ���� ��� ����� ����
SLIDE_IF_BIT_CLR	macro	nameReg, POS, linkSet
	mObject_sel	THIS
	btfsc	nameReg,POS
		goto	linkSet
endm
; ������� �� ����� ���� ��� ����� �������
CALL_IF_BIT_CLR	macro	nameReg, POS, linkSet
	mObject_sel	THIS
	btfss	nameReg,POS
		call	linkSet
endm
; ������� �� ����� ���� ��� ����� ����
CALL_IF_BIT_SET	macro	nameReg, POS, linkSet
	mObject_sel	THIS
	btfsc	nameReg,POS
		call	linkSet
endm

;Danger!!! ������ ������ ���������� � ������������!!
; ���� ����� �������
mIfSlide	macro	cond, link
	xorlw	cond
	btfsc	STATUS,Z
	goto	link
endm
			
; ������� �� ����� ���� �����
SLIDE_IF_EQU	macro	cond, link
	xorlw	cond
	btfsc	STATUS,Z
	goto	link
endm
;Danger!!!
