import os
import platform
import sys
import shutil
import difflib

if len(sys.argv) != 3:
	print("[Usage] python execute_sample_case.py station 3")
	exit()

problem_name = sys.argv[1]
num_sample = int(sys.argv[2])
if platform.system() == "Windows":
	exe_format = problem_name + ".exe"
else:
	exe_format = "./" + problem_name + ".out"

inp_format = problem_name + ".inp"
out_format = problem_name + ".out"

for i in range(1, num_sample + 1):
	sample_inp = "{}.inp".format(i)
	sample_out = "{}.out".format(i)

	shutil.copy(sample_inp, inp_format)
	os.system(exe_format)
	shutil.copy(out_format, sample_out)