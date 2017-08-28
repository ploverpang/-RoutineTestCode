#!/usr/bin/env python

print('hello world')

def debugTest():
    ll = [x+1 for x in range(10)]
    for idx, l in enumerate(ll):
        print("idx is %d, l is %s" %(idx, str(l)))


if __name__ == '__main__':
    debugTest()

