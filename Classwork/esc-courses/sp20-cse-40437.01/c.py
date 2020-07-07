import json
import random

def measured_variables(SC): #find total # measured variables
	number = -1
	for key, vallist in SC.items():
		for value in vallist:
			if value > number:
				number = value
	return number

def sbk(SC, total): #calc s, b, k probabilities
	sd = dict()
	bd = dict()
	kd = dict()
	for key,val in SC.items():
		sd[key] = len(val)/total
		bd[key] = 0.5*sd[key]
		kd[key] = len(val)
	return sd, bd, kd

def calc_Z(a, b, k, totalmv, sources): #estimation maximization alg
	d = 0.5
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
				if j in SC[i]: mval = 1
				else: mval = 0
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

def jsonload():
	uid = dict() #"user_tweetid"
	idstr = dict() #"tweet_userid"
	count = dict()
	data = []
	for line in open("Tweets.txt", "r"):
		data.append(json.loads(line))
	usercount = 1
	for tweet in data:
		key = int(tweet["from_user_id"])
		val = int(tweet["id"])
		if key not in uid:
			uid[key] = []
			count[key] = usercount
			usercount += 1
		idstr[val] = key
		uid[key].append(val)
	#print(uid, idstr)
	return uid, idstr, count

def clusterparse(idstr):
	SC = dict()
	for line in open("Cluster_Result_Tweetsid.txt","r"):
		line = line.strip().replace(':', ',')
		tokens = line.split(',')
		measured_var = int(tokens.pop(0))
		tweetids = list(map(int, tokens))

		for tid in tweetids:
			from_user = idstr[tid]
			if from_user not in SC:
				SC[from_user] = []
			SC[from_user].append(measured_var)
	return SC


user_tweetid, tweet_userid, user_count_map = jsonload()
SC_temp = clusterparse(tweet_userid)
SC = dict()

for key,val in SC_temp.items():
	SC[user_count_map[key]] = val

tnmv = measured_variables(SC)
si, bi, ki = sbk(SC, tnmv)
#bi -> half si
#ki -> key = sourceid, value = num claimids they've posted
ai = si #si -> key = sourceid, value = si value

Z = calc_Z(ai, bi, ki, tnmv, len(SC)) #determine Z
outfile = 'task2.txt'
with open(outfile, 'w') as f: #calc results and send them to output file
	for k,v in sorted(Z.items(), key=lambda x: x[1], reverse=True): #put num 1 before 0
		f.write(str(k)+'\t'+str(v)+'\n')
