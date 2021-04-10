import os
import platform
import sys
import shutil
import difflib

if len(sys.argv) != 3:
	print("[Usage] python execute_sample_case.py station.exe 3")
	exit()

program_name = sys.argv[1]
num_sample = int(sys.argv[2])

extension_dot = program_name.find('.')
problem_name = program_name[0:extension_dot]
ext = program_name[extension_dot + 1:]

if ext == "py":
	exe_format = "python " + program_name
elif ext == "class":
	exe_format = "java " + program_name
else:
	exe_format = program_name

inp_format = problem_name + ".inp"
out_format = problem_name + ".out"

for i in range(1, num_sample + 1):
	sample_inp = "{}.inp".format(i)
	sample_out = "{}.out".format(i)

	shutil.copy(sample_inp, inp_format)
	os.system(exe_format)

	with open(sample_out) as answer: 
	    answer_text = answer.readlines() 
	with open(out_format) as mine: 
	    mine_text = mine.readlines()
	difference = list(difflib.unified_diff(answer_text, mine_text, fromfile=sample_out, tofile=out_format, lineterm=''))
	if difference:
		print("Differece between {} and {}".format(out_format, sample_out)) 
		for line in difference:
			print(line)
	else:
		print("Matched between {} and {}".format(out_format, sample_out)) 