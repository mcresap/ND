#!/usr/bin/env python3

import multiprocessing
import os
import requests
import sys
import time


# Globals

PROCESSES = 1
REQUESTS  = 1
VERBOSE   = False
URL       = None
TIME_REQUEST = 0
AVERAGE_TIME = 0

# Functions

def usage(status=0):
	print('''Usage: {} [-p PROCESSES -r REQUESTS -v] URL
	-h              Display help message
	-v              Display verbose output

	-p  PROCESSES   Number of processes to utilize (1)
	-r  REQUESTS    Number of requests per process (1)
	'''.format(os.path.basename(sys.argv[0])))
	sys.exit(status)

def do_request(pid):
	''' Perform REQUESTS HTTP requests and return the average elapsed time. '''
	global URL
	time_total=0
	# Must loop since we are performing multiple requests per process
	for request in range(REQUESTS):
		begin=time.time()
		re=requests.get(URL)
		end=time.time()
		if VERBOSE:
			print(re.text)
		dif=end-begin
		time_total += dif
		print ("Process: {}, Request: {}, Elapsed Time: {}".format(pid, request, round(end-begin, 2)))
	avg = time_total/REQUESTS
	print("Process: {}, AVERAGE   , Elapsed Time: {}".format(pid, round(avg,2)))
	return avg
	pass


# Main execution

if __name__ == '__main__':
	# Parse command line arguments
	args = sys.argv[1:]
	while len(args) and args[0].startswith('-') and len(args[0]) > 1:
		flag = args.pop(0)
		if flag=="-h":
			usage(0)
		elif flag=="-p":
			PROCESSES=int(args.pop(0))
		elif flag=="-r":
			REQUESTS=int(args.pop(0))
		elif flag=="-v":
			VERBOSE= True
		else:
			usage(1)

	if len(args):
		URL=args.pop(0)
	else:
		usage(1)



	#handle verbose flag
	# if VERBOSE == True:
	# 	r=requests.get(URL)
	# 	print(r.text)

	# Create pool of workers and perform requests
	pool = multiprocessing.Pool(PROCESSES)
	TIME_REQUEST =pool.imap(do_request, range(PROCESSES))

	for r in TIME_REQUEST:
		AVERAGE_TIME = AVERAGE_TIME + r

	AVERAGE_TIME = AVERAGE_TIME / PROCESSES
	print("TOTAL AVERAGE ELAPSED TIME: {}".format(round(AVERAGE_TIME,2)))
# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
