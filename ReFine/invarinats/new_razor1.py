import itertools

def getTraceStartLines(dtrace_filename): 
	lookup = "input-language C/C++"
	trace_start_lines = []
	with open(dtrace_filename) as main_dtrace:
		for num, line in enumerate(main_dtrace, 1):
			if lookup in line:
				trace_start_lines.append(num)
	return trace_start_lines


def genTrace(function_name, lower_cnt, upper_cnt):

<<<<<<< HEAD
	dtrace_filename = "program.dtrace"
=======
	dtrace_filename = "program.dtrace1"
>>>>>>> 69a8c79f39e027cae164a7adeff1865414cb26b9
	trace_start_lines = getTraceStartLines(dtrace_filename)

	it = 1
	alert = False
	keep_lines = [0]
	
	for it in range (1, len(trace_start_lines)-1):	#inside "a" trace
		
		function_read = False
		read_count = 0
		
		with open(dtrace_filename) as main_dtrace:
			for num, line in enumerate(itertools.islice(main_dtrace, trace_start_lines[it]-1, trace_start_lines[it+1]-1),trace_start_lines[it]):
				if "read_" in line:
					read_count += 1
<<<<<<< HEAD
				if function_name in line : #and "ENTER" in line
=======
				if function_name in line:
>>>>>>> 69a8c79f39e027cae164a7adeff1865414cb26b9
					if function_read == False:
						function_read = True
						func_first_read_in_line = num
						func_first_read_in_time = read_count-1

					func_last_read_in_line = num
					func_last_read_in_time = read_count-1


		with open(dtrace_filename) as main_dtrace:
			if (func_first_read_in_time>=lower_cnt and func_last_read_in_time <=upper_cnt):
				print "This Trace OK"
				keep_lines.append(it)
			else:
				print "This trace cancelled"
			"""
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
			"""
	new_dtrace = "new_program.dtrace"
	f = open(new_dtrace, "w+") 
	for it in keep_lines:
		with open(dtrace_filename) as main_dtrace:
			for num, line in enumerate(itertools.islice(main_dtrace, trace_start_lines[it]-1, trace_start_lines[it+1]-2),trace_start_lines[it]):
				f.write(line)
<<<<<<< HEAD
		f.write("\n")


genTrace("read_i22", 0, 5)
=======


genTrace("read_i2", 0, 1)
>>>>>>> 69a8c79f39e027cae164a7adeff1865414cb26b9
