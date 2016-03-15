#!/usr/bin/env python
# coding: utf-8

import numpy as np

def flatmap( vs, f ):
	r = []
	for v in vs:
		r.extend( f(v) )
	return r

def try_parse(string, fail=None):
    try:       
        a = float(string)        
        return a 
    except Exception:
        return fail

def write_csv_spec( fn, arr, titles=None ):
    # http://stackoverflow.com/questions/6081008/dump-a-numpy-array-into-a-csv-file
    if titles:
        title = ','.join( titles )
        
        np.savetxt( fn, arr, 
                   comments="",
                   header=title, fmt='%10.5f',  delimiter=',') 
    else:
        np.savetxt( fn, arr, 
                   comments="",
                   fmt='%10.5f',  delimiter=',') 


def read_csv_spec( fn, sep=',' ):
    """ 
    		Args: "f:a:10,b:90, 18.9:67"
    
    		Returns: [[10, 90, 18.9, 67]]
    """
    lines = []
    with open( fn ) as f:
        lines = f.read().splitlines()
    tmp = []
    for k in lines:
        s = k.replace(' ', sep).replace('\t', sep).replace(sep+sep,sep).replace(sep+sep,sep)
        s = s.replace('=', ':')        
        a = s.split(',')
        a = flatmap( a, lambda x: x.split(':'))
        a = filter( lambda x: try_parse( x ) != None, a )
        
        if a:
            tmp.append( map( lambda x: float(x), a) )

    return np.array( tmp )

if __name__=='__main__':
	data = read_csv_spec( '/home/zaqwes/to_r.csv' )
	print data

#	write_csv_("tests/r_ext_out.csv", ["a", 'b', 'c', 'd', 'e'], data)
#	print read_csv_spec( "tests/r_ext_out.csv")