#!/usr/bin/env python

def calcHight():
    s = 100
    h = 50.0

    for i in range(2,11):
        s += h
        h /= 2

    print("the sum length of path:%f" %s)
    print("the last height is:%f " %s)

def calcPeath():
    n = 1
    for i in range(9,0,-1):
        n = (n+1)<<1
    print("%d peath totally" %n)

def printDiamond():
    for i in range(1,8,2):
	print ' '*(4-(i+1)/2)+'*'*i
    for i in range(5,0,-2):
	print ' '*(4-(i+1)/2)+'*'*i

def calcList():
    u = 2.0
    d = 1.0
    s = 0.0
    
    for i in range(0,20):
	s = s + u/d
	u = u + d
	d = u - d
    print("sum of 20 data is %f" %s)

def calcFactorial():
    s = 0
    t = 1
    for i in range(1,21):
	t *= i
	s += t
    print s
 
if __name__ == "__main__":
   calcFactorial()
