import os
import re
import string

def print_to_file(lines_of_file, new_file_name):
	c_code_with_inv  = open("new_c_code.c", "w+")


	for line in lines_of_file:
		print "[CPRINT ] " + line
		print>>c_code_with_inv, line

	c_code_with_inv.close()

	# c_code_name = "c_code_00"

	os.system("cp new_c_code.c ./ccode/"+ new_file_name)


# c_code_new = [daikon_output.rstrip('\n') for daikon_output in open("daikon_result")]
# print_to_file(c_code_new,"c_code_000")




def print_invariants_to_file(lines_of_file, target_file):
	code_with_sound_invarint = open(target_file,"w+")

	for line in lines_of_file:
		if "udon_dummy" not in line:
			print "[INVARIANT PRINT ] " + line
			print>>code_with_sound_invarint, line

	code_with_sound_invarint.close()




def invariant_to_assert(line):
	if(re.search("= [0-9]",line)):		#eita gonjamil ache. chaper somosya 
		return ""

	if ("orig" in line ):
		line = string.replace(line, "orig(","opu_")							
		line = string.replace(line, "::","")							
		line = string.replace(line, ")","")							

	if(line.startswith("::")):
		line = line[2:]
	if("return" in line) or ("argc" in line) or ("argv" in line) or ("null" in line):
		return ""
	if("::" in line):
		line = string.replace(line, "::","")
		# line_braeak = line.split("::")
		# line = ''
		# for item in line_braeak: 
		# 	line += item
	if("one of" in line):
		var = line .split("one")[0]
		line = (line.split("{")[1]).split("}")[0]
		line = string.replace(line, " ","")
		values = ""
		for items in re.split(",| ", line):
			values = values + var + "==" + items + " || "
		line = values + "False"
		line = string.replace(line, "|| False","")
	
	print "[INV2ASRT] Says: "+ line
	return "assert(" + line + ");"

# s = "::j one of { 7, 9, 11 }"
# print invariant_to_assert(s)


#"""

def isDeclaration(line):
	datatypes = ["int","char", "float", "long", "void"]
	line_break = set(re.split(';|,| ',line)) - set([''])
	type = list(set(datatypes).intersection(line_break))
	if "udon_dummy" in line and ");" not in line:
		return False
	if type != []:
		return True
	else:
		return False

def copy_variables(line):
	datatypes = ["int","char", "float", "long", "void"]
	line = string.replace(line, "= ", "=")
	line = string.replace(line, " =", "=")
	if not line.startswith("//"): 
		line = line.split("//")[0]
	if '(' not in line:
		print "[DEBUG] Type 1 detected"
		line_break = set(re.split(';|,| ',line)) - set([''])
		# print line_break
		type = list(set(datatypes).intersection(line_break))
		# if(type != []):
		# 	# print "[DEBUG] Type found "+ type[0]
		variables = line_break - set(type)
		opu_variables = type[0]+' '
		for item in variables:
			if "*" not in item:
				item = item.split("=")[0]
				opu_item = "opu_"+item
				opu_variables += opu_item+" = "+item+","
			
		opu_variables += "mjo;"
		return (1,[opu_variables]) #1 to denote first type

	else:
		print "[DEBUG] Type 2 detected"

		line_break = re.split(';|,|\(|\)| ',line)
		# print line_break
		it = -1
		type_cnt = 0
		while type_cnt<2:
			it += 1
			if (it == len(line_break) - 1):
				return (2,[])
			if line_break[it] in datatypes:
				type_cnt += 1
		opu_variables = []
		while it < len(line_break):
			if line_break[it] in datatypes:
				opu_item_type = line_break[it]
			elif line_break[it] == '' or line_break[it] == ' ' or "*" in line_break[it]:
				pass
			else:
				opu_variables.append(opu_item_type+" opu_"+line_break[it]+" = "+line_break[it]+";")
			it += 1	
			 			
		return (2,opu_variables)  #2 to denote second type



# print copy_variables("int x, y, z;")
# print copy_variables("void f (float x, int y, int z);")



def instrument_to_retain_orig_variable(orig_filename, new_filename):
	c_code_lines = [c_code.rstrip('\n') for c_code in open(orig_filename)]
	instrmented_code = open(new_filename, "w+")


	it = 0

	while it < len(c_code_lines):
		line = c_code_lines[it]
		print "[DEBUG] "+line

		if("return " in line):
			pass							#TODO Return Processing




		if(isDeclaration(line)):
			print "[DEBUG] line given to instrument"

			to_insert = copy_variables(line)
			print "[DEBUG B) ] "+str(to_insert)
			if to_insert[0] == 2:
					it += 1
			for item in to_insert[1]:
				it += 1
				c_code_lines.insert(it, item)
		it += 1		






	for line in c_code_lines:
		print "[CPRINT ] " + line
		print>>instrmented_code, line

	instrmented_code.close()
	print "file printed in : "+new_filename





#instrument_to_retain_orig_variable("c_code.c", "opu_c_code.c")


"""



def instrument_to_block(orig_filename, new_filename):
	c_code_lines = [c_code.rstrip('\n') for c_code in open(orig_filename)]
	instrmented_code = open(new_filename, "w+")

	instrmented_lines = []










	for line in instrumented_lines:
		print "[CPRINT ] " + line
		print>>instrmented_code, line

	instrmented_code.close()
"""

