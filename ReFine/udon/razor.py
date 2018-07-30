import itertools

lookup = "input-language C/C++"
dtrace_filename = "program.dtrace"
trace_start_lines = []
with open(dtrace_filename) as main_dtrace:
	for num, line in enumerate(main_dtrace, 1):
		if lookup in line:
			trace_start_lines.append(num)


it = 1
alert = False
keep_lines = []
for it in range (1, len(trace_start_lines)-1):

	with open(dtrace_filename) as main_dtrace:
		for num, line in enumerate(itertools.islice(main_dtrace, trace_start_lines[it]-1, trace_start_lines[it+1]-1),trace_start_lines[it]):
			if "t1_inloop01" in line:
				func_last_read_in_line = num

	with open(dtrace_filename) as main_dtrace:
		for num, line in enumerate(itertools.islice(main_dtrace, func_last_read_in_line, func_last_read_in_line + 25), func_last_read_in_line):
			if alert == True:
				i_call_count = int(line)
				alert = False

			if "i_calls" in line:
				alert = True
				catch_line_no = num

		print "In this trace, i is called last time in loop of thread 1 at time ",i_call_count, " at line no ", catch_line_no+2
		if i_call_count < 5:
			print "Therefore, Keep"
			keep_lines.append(it)
		else:
			print "Remove"
	
new_dtrace = "01.dtrace"
f = open(new_dtrace, "w+") 
for it in keep_lines:
	with open(dtrace_filename) as main_dtrace:
		for num, line in enumerate(itertools.islice(main_dtrace, trace_start_lines[it]-1, trace_start_lines[it+1]-2),trace_start_lines[it]):
			f.write(line)