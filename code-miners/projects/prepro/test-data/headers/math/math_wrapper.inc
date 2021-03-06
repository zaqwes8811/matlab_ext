; #include <../headers/math_wrapper.inc>

;/// /// ///
;///
;/// �������, ������ ������� ��� MATH
;// ������ ����� ���������� ������������ ����
;#ifdef	_MATH_WRAPPER;INFO_INC_UTEST
	extern 	_v#v(2)_MATH_SETdw_fK_to_Barg
	extern 	_v#v(2)_MATH_SETdw_FPM32
	extern	_v#v(2)_MATH_SETdw_INT32
	;extern 	Vremen
;#endif	;INFO_INC_UTEST


;// ��� ��� ���� !���� ������ �� ������ ������! �� ����� �� �����
;// ����������� ������ ����� ���������� � �������������� �����		
mMov_A_B	macro
	call	_v#v(DOWN)_MATH_SETdw_mov_A_B
endm

BankSelMath	macro
endm

;/// �������������� ����� v
mIntFlo	macro
	call	_v#v(DOWN)_MATH_SETdw_FLO32
endm

mFloInt	macro
	;#ifdef	_MATH_WRAPPER;INFO_INC_UTEST
		call	_v#v(2)_MATH_SETdw_INT32
	;#endif	;INFO_INC_UTEST
	;#ifndef	_MATH_WRAPPER;INFO_INC_UTEST
	;	call	_v#v(DOWN)_MATH_SETdw_INT32
	;#endif	;INFO_INC_UTEST
endm
;/// �������������� ����� ^

;// ���������
mFPM	macro
;	#ifdef	_MATH_WRAPPER;INFO_INC_UTEST
		call	_v#v(2)_MATH_SETdw_FPM32
;	#endif	;INFO_INC_UTEST
;	#ifndef	_MATH_WRAPPER;INFO_INC_UTEST
;		call	_v#v(DOWN)_MATH_SETdw_FPM32
;	#endif	;INFO_INC_UTEST
endm

mFPD	macro
	call	_v#v(DOWN)_MATH_SETdw_FPD32
endm

mWord_to_Aarg macro locat, locat2
	banksel	Vremen
	movff	locat,	Vremen
	movff	locat2,	Vremen+1
	lfsr	0,Vremen
	call	_v#v(DOWN)_MATH_SETdw_fWord_to_Aarg;(*FSR0/void)
endm

;// �������� ������� ��������?
mK_to_Barg	macro n1, n2, n3, n4
	banksel	Vremen
	movlw	n1
	movwf	Vremen
	movlw	n2
	movwf	Vremen+1
	movlw	n3
	movwf	Vremen+2
	movlw	n4
	movwf	Vremen+3
	;// �� ������ ������� 4 ���������
	lfsr	0,Vremen

;	#ifdef	_MATH_WRAPPER;INFO_INC_UTEST
		call	_v#v(2)_MATH_SETdw_fK_to_Barg;(*FSR0/void)	
;	#endif	;INFO_INC_UTEST
;	#ifndef	_MATH_WRAPPER;INFO_INC_UTEST
;		call	_v#v(DOWN)_MATH_SETdw_fK_to_Barg;(*FSR0/void)	
;	#endif	;INFO_INC_UTEST
endm

;// ������ �������� �����������
mDig_separ_H	macro locat
	lfsr	0,	locat
	call	_v#v(DOWN)_MATH_SETdw_fDig_separH;(*FSR0/void)	
endm
mDig_separ_L	macro locat
	lfsr	0,	locat
	call	_v#v(DOWN)_MATH_SETdw_fDig_separL;(*FSR0/void)
endm

;// �����-�� ��������������
mByte_to_Aarg macro locat
	banksel	locat
	
	;// ������ ����������� �������� � �����������
	movf	locat, 	w  
	
	;// ���������� ���������� ��� ������ ������� �������������� �����
	call	_v#v(DOWN)_MATH_SETdw_wByte_to_Aarg;(byte/void)
endm
	
mShift_A		macro
	call	_v#v(DOWN)_MATH_SETdw_shift_A;(void/void)
endm



;#endif
