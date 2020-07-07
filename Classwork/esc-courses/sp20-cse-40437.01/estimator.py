#!/usr/bin/env python3
import random

def measured_variables(SC): #find total # measured variables
	number = -1
	for k, vallist in SC.items():
		for value in vallist:
			if value > number:
				number = value
	return number

def s_b_k(SC, total): #calc s, b, k probabilities
	s = dict()
	b = dict()
	k = dict()
	for x,v in SC.items():
		s[x] = len(v)/ total
		b[x] = 0.5*s[x]
		k[x] = len(v)
	return s, b, k

def calc_Z(a, b, k, totalmv, sources): #estimation maximization alg
	d = random.uniform(0, 1)
	Z = dict() #Z is set of latent variables
	count = 0
	while count < 20:
		count += 1
		j = 1
		while j <= totalmv:
			i = 1
			a_j = 1
			b_j = 1
			while i < sources:
				if j in SC[i]: 
					mval = 1
				else:          
					mval = 0
				a_j *= pow(a[i], mval)*pow((1-a[i]), (1-mval))
				b_j *= pow(b[i], mval)*pow((1-b[i]), (1-mval))
				i += 1
			Z[j] = (a_j*d) / float(a_j*d + b_j*(1-d))
			j+=1
		totalZ = sum(Z.values())
		i = 0
		while i < sources:
			i += 1
			z = 0
			for claim_id in SC[i]:
				z += Z[claim_id]
			try:
				a[i] = z / float(totalZ)
			except ZeroDivisionError:
				a[i] = 0
			try:
				b[i] = (k[i] - z) / float(totalmv - totalZ)
			except ZeroDivisionError:
				b[i] = 0
			d = totalZ/totalmv
	return Z

SC = dict()
fname = 'SCMatrix_Submit'
with open(fname, 'r') as f:
	for line in f:
		sourceid, claimid = map(int, line.strip().split(','))
		if sourceid not in SC:
			SC[sourceid] = []
		SC[sourceid].append(claimid)

totalmv = measured_variables(SC)
si = s_b_k(SC, totalmv) #key = sourceid, value = si val
bi = s_b_k(SC, totalmv) #half si
ki = s_b_k(SC, totalmv) #key = sourceid, value = num claimids they've posted
ai = si

Z = calc_Z(ai, bi, ki, totalmv, len(SC)) #determine Z

outputname = 'estimatorresults.txt'
with open(outputname, 'w') as f: #calc results and send them to output file
	for x,v in Z.items():
		if v>=0.5: output = 1
		else:      output = 0
		f.write(str(x)+", "+str(output)+"\n")
