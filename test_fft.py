#!/usr/bin/env python
# coding: utf-8

import sys
sys.path.append( ".." )  # fixme: bad!
from matlab_ext import *

import numpy as np

def main():
	#FFT
	Fs = 1000            #% Sampling frequency
	T = 1./Fs             #% Sampling period
	L = 1000             #% Length of signal

	t = colon(0, L-1)*T        #% Time vector
	#Form a signal containing a 50 Hz sinusoid of amplitude 0.7 and a 120 Hz sinusoid of amplitude 1.

	S = 0.7*sin(2*pi*50*t) + sin(2*pi*120*t)
	#Corrupt the signal with zero-mean white noise with a variance of 4.

	X = S #+ 2*randn( size(t) )
	#Plot the noisy signal in the time domain. It is difficult to identify the frequency components by looking at the signal X(t).

	# plot( 1000 * t[1-1:50-1], X[1-1:50-1] )
	# title('Signal Corrupted with Zero-Mean Random Noise')
	# xlabel('t (milliseconds)')
	# ylabel('X(t)')
	# show()

	P1, f = fft_one_side( X, L, Fs )

	plot( f,P1 )
	title('Single-Sided Amplitude Spectrum of X(t)')
	xlabel('f (Hz)')
	ylabel('|P1(f)|')
	grid()
	show()

if __name__ == '__main__':
 	main()