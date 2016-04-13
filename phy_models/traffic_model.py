# encoding: utf-8

# fixme: outliners - Kalman must be robust

import numpy as np
from numpy.random import randn  # too weak

from matlab_ext.plotter import *

class Car(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.vx = 0.
        self.vy = 10.1
        self.ax = 0.
        self.ay = 0.

class Mover(object):
    def __init__( self ):
        vmax = 60  # kph
        self.car = Car( 0, 0 ); 
        self.car.vx = vmax / 3.6  # m/s
        self.iter = 0
        
    def think(self):
        if self.iter == 20:
            self.car.ax = 10.5       
        self.iter += 1
        
    def move(self, dt=1.):
        def rnd():
            std = 1.5
            return randn() * std
            
        self.think()
        
        # X
        self.car.x += self.car.vx * dt + self.car.ax * dt**2 / 2.
        self.car.vx += self.car.ax * dt
        
        # Y
        self.car.y += self.car.vy * dt + self.car.ay * dt**2 / 2.
        self.car.vy += self.car.ay * dt
        
        return self.car.x + rnd(), self.car.y+rnd()

# coord sys as in image
#
#   http://www.autonomoustuff.com/uploads/9/6/0/5/9605198/sms_type_29_data_sheet.pdf
class WorldSpace(object):
    def __init__( self, w, h ):
        self.w = w
        self.h = h
  
    def check_accessory( self, car ):
        return car.x < w and car.y < self.h


if __name__=='__main__':
    world_space = WorldSpace( 10, 120 )
    mover = Mover()
    
    N = 50
    fps = 11
    dt = 1./fps
    xs = np.zeros( N )
    ys = np.zeros( N )
    ts = np.zeros( N )
    t = 0
    for i in range( N ):
        xs[i], ys[i] = mover.move( dt )
        t += dt
        ts[i] = t
        
    figure()
    plot( xs, ys, '-o' )
    xlabel('x, m')
    ylabel('y, m')
    grid()
    show()
    
    figure()
    plot( ts, xs, '-o' )
    xlabel('t, s')
    ylabel('x, m')
    grid()
    show()

    
        
         



