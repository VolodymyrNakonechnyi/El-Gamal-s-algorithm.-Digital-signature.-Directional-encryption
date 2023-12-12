# Python program to illustrate ElGamal encryption

import random 
from math import pow

a = random.randint(2, 10)

def gcd(a, b): #stackoverflow with recursion, so loop way, but it sooooo slow 
	if a < b:
		return gcd(b, a)
	elif a % b == 0:
		return b;
	else:
		return gcd(b, a % b)

def gen_key(from_q,q):
	key = random.randint(from_q, q)
	while gcd(q, key) != 1:
		key = random.randint(from_q, q)

	return key

def power(a, b, c):
	x = 1
	y = a

	while b > 0:
		if b % 2 != 0:
			x = (x * y) % c;
		y = (y * y) % c
		b = int(b / 2)

	return x % c

def encrypt(msg, p, a, g):

	en_msg = []

	k = gen_key(10**120, p)
	s = power(a, k, p)
	y = power(g, k, p)
	
	for i in range(0, len(msg)):
		en_msg.append(msg[i])

	print("k : ", y)
 
	for i in range(0, len(en_msg)):
		en_msg[i] = s * ord(en_msg[i])

	return en_msg, y

def decrypt(en_msg, y, a, p):

	dr_msg = []
	s = power(y, a, p)
	for i in range(0, len(en_msg)):
		dr_msg.append(chr(int(en_msg[i]/s)))
		
	return dr_msg

def main():

	message = 'encryption'
	print("Original Message :", message)

	p = random.randint(10**120, 10**122) #random.getrandbits(4096)
	g = random.randint(2, p)
 
	a = gen_key(10**120, p) #private key
	b = power(g, a, p) #public key
	print("public key ", b)
	print("private key : ", a)

	encrypted_message, y = encrypt(message, p, b, g)
	decrypted_message = decrypt(encrypted_message, y, a, p)
	dmsg = ''.join(decrypted_message)
	print("Decrypted Message :", dmsg);


if __name__ == '__main__':
	main()
