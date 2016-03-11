# encoding: utf-8

import sys
print sys.path

import numpy as np
from matlab_ext.plotter import *

class Car(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.vx = 0.
        self.vy = 0.
        self.ax = 0.
        self.ay = 0.

class MoveAlgorithm(object):
    def __init__( self ):
        self.car = Car( 0, 0 ); 
        self.car.vx = 1  # m/s
        self.iter = 0
        
    def move(self, dt=1.):
        if self.iter == 4:
            self.car.ax = -1.5
        
        self.iter += 1
        self.car.x += self.car.vx * dt + self.car.ax * dt**2 / 2.
        return self.car.x, self.car.y

# coord sys as in image
#
# Umrr:
#   http://www.autonomoustuff.com/uploads/9/6/0/5/9605198/sms_type_29_data_sheet.pdf
class UmrrSpace(object):
    def __init__( self, w, h ):
        self.w = w
        self.h = h
  
    def check_accessory( self, car ):
        return car.x < w and car.y < self.h


if __name__=='__main__':
    umrr_space = UmrrSpace( 10, 120 )
    move_alg = MoveAlgorithm()
    N = 10
    xs = np.zeros( N )
    for i in range( N ):
        xs[i], a = move_alg.move()
        
    print xs
    plot( xs )
    grid()
    show()
    
        
         



