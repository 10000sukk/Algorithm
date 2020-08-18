import sys
import re

arr = sys.stdin.readline().split('(')

def decompression(K,Q):
    return numberLenth(int(K/10)) + (K%10)*numberLenth(Q)

def decompression1(K,Q1):
    return numberLenth(int(K/10)) + (K%10)*Q1

def decompression


def numberLenth(n):
    a = 0
    while True:
        if n == 0:
            break
        n = int(n / 10)
        a += 1
    return a

print(decompression(arr,0))