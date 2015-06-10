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

def judgeCNumber():
    ans = ['yes', 'no']
    i = int(raw_input('Input a number(10000-99999):'))
    if i<10000 or i>99999:
	print("input Error")
    else:
	i = str(i)
	flag = 0
	for j in range(0,2):
	    if i[j] != i[4-j]:
		flag = 1
		break
	print("%s" %ans[flag])

def getShu():
    a = [0]*101
    for i in range(2,11):
	for j in range(i+1,101,i):
	    a[j] = -1
    for i in range(2,101):
	if a[i] != -1:
	    print(' ', i) 

def sortNumber():
    print 'input 10 numbers please:'
    l = []
    for i in range(10):
	l.append(int(raw_input('input a number:')))
    for i in range(9):
	for j in range(i+1,10):
	    if l[j] < l[i]:
		temp = l[j]
		l[j] = l[i]
		l[i] = temp
    print l

def calcTotalOfMatrix():
    l = []
    for i in range(3):
	for j in range(3):
	    l.append(int(raw_input('Input a number')))
    s = 0
    for i in range(3):
	s += l[3*i+i]
    print(s)

def calcNewSort():
    l = [0,10,20,30,40,50]
    
    print('the sorted list is:',l)
    cnt = len(l)
    n = int(raw_input('input a number:'))
    l.append(n)
    for i in range(cnt):
	if n<l[i]:
	    for j in range(cnt,i,-1):
		l[j] = l[j-1]
	    l[i] = n
	    break
    print('the new sorted list is:',l)

if __name__ == "__main__":
    calcNewSort() 
