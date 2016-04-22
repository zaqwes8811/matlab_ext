# -*- coding: utf-8 -*-
"""
Created on Thu Apr 21 22:48:19 2016

@author: zaqwes
"""

import copy

from control import tf, series
from control import impulse_response, step_response

from matlab_ext.plotter import *
from matlab_ext.r_ext import *

if __name__ == '__main__':
    cls()
    
    Kt = 1.    
    Jt = 1.  # [?]
    
    u1 = tf([Kt], [1])
    u2 = tf([1/Jt], [1])
    
    # fixme: как добавить сигнал шума?
    u12 = series(u1, u2)
    u3 = tf([1], [1, 0])
    u4 = copy.deepcopy( u3 )
    u34 = series(u3, u4)
    u14 = series(u12, u34)
    
    print u14

    ts, xs = step_response(u14)
    
    plot(ts, xs)
    grid()    
    show()