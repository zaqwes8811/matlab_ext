;/**
;  ������� ���������� �� ������������ ��������
;*/
	variable	Number_Static=0
	variable	Number_Public=0
	variable	Number_Ext_Functions=0
	variable	Number_Ext_Variables=0

mPUBLIC			macro	klass,name,size
	ifdef	klass
name	res	#v(size)
		global	name
Number_Public++
	else
		extern	name
	endif	
				endm

mSTATIC				macro	klass, name, size
	ifdef	klass
name	res	#v(size)
Number_Static++
	endif
				endm

mObject_var	macro	klass
;	ifdef	klass
;	messg	/// ������ klass ������� ///
klass		idata
klass#v(0)	res	0
;	endif
				endm

mObject_end	macro	klass
	ifdef	klass
	messg � ������ klass �������:
	messg 1. ����������� ����������____#v(Number_Static)
	messg 2. �������� ����������_______#v(Number_Ext_Variables)
	messg 3. ���������� ����������_____#v(Number_Public) 
	messg 4. �������� �������__________#v(Number_Ext_Functions)
;	if	Number_Static > 0
;klass#v(0)	res	0
;	endif
	endif
				endm

;///
mObject_sel		macro	klass
	ifdef	klass
	banksel	klass#v(0)
;	clrwdt
	endif
endm
;///
				
mPUBL_FUNC		macro	klass,name
	ifdef	klass
		global	name
Number_Ext_Functions++
	else
		extern	name
	endif
				endm

mSHARED			macro	klass_s,klass_d,name,size
	ifdef	klass_s
name	res	#v(size)
		global	name
Number_Ext_Variables++
	endif
	ifdef	klass_d
		extern	name
	endif
				endm


;/// /// ///
mEXTENDS		macro	klass_s, klass_d, name
	ifdef	klass_s
		global	name
Number_Ext_Functions++
	endif
	ifdef	klass_d
		extern	name
	endif
				endm
;///

;/// ������ ����� �������?
mSlideTo	macro	Link
	goto	Link
endm
;/// ///

;// ������ �����������
mRetIfF?	macro	link
	call	link
	xorlw	TRUE
	btfss	STATUS,Z
	retlw	FALSE
			endm

mFunction	macro	link
	call	link
			endm

mASK		macro	link
	call	link
			endm
mGET		macro	link
	call	link
			endm
mSET		macro	link
	call	link
			endm
mRUN		macro	link
	call	link
			endm
			
mRETURN		macro
	return
			endm

; igor 170512
; ����� � ������� � ����������� �����
;Syntax: CALL k {,s}
;Operands: 0 ? k ? 1048575
;	s ? [0,1]
;Operation: (PC) + 4 > TOS,
;	k > PC<20:1>,
;	if s = 1
;		(W) > WS,
;		(STATUS) > STATUSS,
;		(BSR) > BSRS
;Syntax: RETURN {s}
;Operands: s ? [0,1]
;Operation: 
;	(TOS) > PC,
;	if s = 1
;		(WS) > W,
;		(STATUSS) > STATUS,
;		(BSRS) > BSR,
;		PCLATU, PCLATH are unchanged
mCallSave	macro	link
	call	link, FAST
			endm
mReturnSave	macro
	return	FAST
			endm
mCall		macro 	link
	call link
			endm