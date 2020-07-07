import random

def measured_variables(SC):
	num = -1
	for k, v_list in SC.items():
		for val in v_list:
			if val > num:
				num = val
	return num

def get_si_bi_ki(SC, total_MV):
	si_dict = dict()
	bi_dict = dict()
	ki_dict = dict()
	for k,v in SC.items():
		si_dict[k] = len(v)/total_MV
		bi_dict[k] = 0.5*si_dict[k]
		ki_dict[k] = len(v)
	return si_dict, bi_dict, ki_dict

def calc_Z(a, b, k, tnmv, numSources):
	d = random.uniform(0,1)
	Z = dict()
	counter = 0
	while counter < 20:
		counter += 1
		j = 1
		while j <= tnmv:
			i = 1
			Atj = 1
			Btj = 1
			while i < numSources:
				if j in SC[i]: mval = 1
				else: mval = 0
				Atj *= pow(a[i], mval)*pow((1-a[i]), (1-mval))
				Btj *= pow(b[i], mval)*pow((1-b[i]), (1-mval))
				i += 1
			Z[j] = (Atj*d) / float(Atj*d + Btj*(1-d))
			j+=1
		totalZ = sum(Z.values())
		i = 0
		while i < numSources:
			i += 1
			obsZ = 0
			for claim_id in SC[i]:
				obsZ += Z[claim_id]
			try:
				a[i] = obsZ / float(totalZ)
			except ZeroDivisionError:
				a[i] = 0
			try:
				b[i] = (k[i] - obsZ) / float(tnmv - totalZ)
			except ZeroDivisionError:
				b[i] = 0
			d = totalZ/tnmv
	return Z


SC = dict()
fname = 'SCMatrix_Submit'
with open(fname, 'r') as f:
	for line in f:
		sourceid, claimid = map(int, line.strip().split(','))
		if sourceid not in SC:
			SC[sourceid] = []
		SC[sourceid].append(claimid)

tnmv = measured_variables(SC)
si, bi, ki = get_si_bi_ki(SC, tnmv)

ai = si

Z = calc_Z(ai, bi, ki, tnmv, len(SC))

ofname = 'task1.txt'
with open(ofname, 'w') as f:
	for k,v in Z.items():
		if v>=0.5: output = 1
		else: output = 0
		f.write(str(k)+","+str(output)+"\n")
