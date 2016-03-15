
from matplotlib.pyplot import plot
from matplotlib.pyplot import show
from matplotlib.pyplot import grid
from matplotlib.pyplot import xlabel, ylabel, title, xlim

from scipy import signal
from numpy.fft import fft
import numpy as np

from numpy import ones
from numpy import zeros

def single_side_ampl_spectrum( S, Fs ):
    Fs *= 1.0
    L = len( S )             # Length of signal
    
    Y = fft(S)

    P2 = np.abs(Y/L);
    P1 = P2[ (1-1):(L/2+1-1) ]
    end = 0
    P1[ 2-1:end-1-1 ] = 2*P1[2-1:end-1-1]

    f = Fs*np.arange( 0, (L/2) )/L

    return f, P1

# http://www.mathworks.com/help/matlab/ref/fft.html
def test_single_side_ampl_spectrum():
    Fs = 1000.0;            # Sampling frequency
    T = 1/Fs;             # Sampling period
    L = 1000;             # Length of signal
    t = np.arange(0, L) * T;        # Time vector
    S = 0.7*np.sin(2*np.pi*50*t) + np.sin(2*np.pi*120*t)
    X = S

    #plot(1000*t[1-1:50-1],X[1-1:50-1])
    #title('Signal Corrupted with Zero-Mean Random Noise')
    #xlabel('t (milliseconds)')
    #ylabel('X(t)')

    Y = fft(S);
    P2 = abs(Y/L);
    P1 = P2[ (1-1):(L/2+1-1) ]
    end = 0
    P1[ 2-1:end-1-1 ] = 2*P1[2-1:end-1-1]

    f = Fs*np.arange( 0, (L/2) )/L
    plot(f,P1)
    title('Single-Sided Amplitude Spectrum of S(t)')
    xlabel('f (Hz)')
    ylabel('|P1(f)|')

    grid()
    show()

def freqz_plot( b, a, fs ):
    def f(ar, name): 
        def aa(npv): 
            if npv < 0: 
                return str(npv)  
            else: 
                return " " + str(npv)
        return name + " = [\n    "+",\n    ".join(map(aa, ar)) + "\n]"

    print f(b, "b")
    print f(a, "a")
    
    n = 1024*4
    w, h = signal.freqz(b, a, n)  # w = [0, pi]
    f = w / np.pi * 0.5 * fs

    # Ampl
    plot(f, 20 * np.log10(10*abs(h)), 'b')

    # Ph
    angles = np.unwrap(np.angle(h)) * 180 / np.pi

    plot(f, angles, 'g')
    title('Digital filter frequency response')
    xlabel('freq, (Hz)')
    ylabel('|H(s)|, dB')
    xlim([0, max( f )])

    return b, a