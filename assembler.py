#!/usr/bin/env python3

import sys

OPCODES = {
	'HLT':  0,
	'NOP':  1,
	'PSI':  2,
	'PSF':  3,
	'DUP':  4,
	'ISP':  5,
	'FSP':  6,
	'IFS':  7,
	'FIS':  8,
	'POP':  9,
	'IAD': 10,
	'ISB': 11,
	'IML': 12,
	'IDV': 13,
	'IMD': 14,
	'ING': 15,
	'FAD': 16,
	'FSB': 17,
	'FML': 18,
	'FDV': 19,
	'FMD': 20,
	'FNG': 21,
	'IEQ': 22,
	'INE': 23,
	'ILT': 24,
	'ILE': 25,
	'IGT': 26,
	'IGE': 27,
	'INT': 28,
	'IAN': 29,
	'IOR': 30,
	'FEQ': 31,
	'FNE': 32,
	'FLT': 33,
	'FLE': 34,
	'FGT': 35,
	'FGE': 36,
	'FNT': 37,
	'FAN': 38,
	'FOR': 39,
	'ILD': 40,
	'IST': 41,
	'FLD': 42,
	'FST': 43,
	'ITF': 44,
	'FTI': 45,
	'JMP': 46,
	'JPZ': 47,
	'JNZ': 48,
	'CAL': 49,
	'RET': 50,
	'SYSCALL': 51,
}

ONE_ARG_OPCODES = [
	'PSI',
	'PSF',
	'JMP',
	'JPZ',
	'JNZ',
	'CAL',
	'SYSCALL',
]

LABEL_ARG_OPCODES = [
	'JMP',
	'JPZ',
	'JNZ',
	'CAL',
]

SYSCALLS = {
	'%EXIT': 0,
	'%OUT_INT': 1,
	'%OUT_CHAR': 2,
	'%SLEEP': 3 
}

def get_file_lines(file):
	try:
		with open(file, 'r') as f:
			source = f.read()
	except FileNotFoundError:
		print(f'file `{file}` not found.')
		exit(1)
	
	return source.split('\n')

def get_line_instructions(line):
	column = 0
	instructions = []  # ((start, end), instruction)

	reading_instruction = False
	instruction = ''
	instruction_start = None

	for char in line:
		if char == ';':
			break
		
		elif char in ' \t\r':
			if reading_instruction:
				instructions.append(((instruction_start, column - 1), instruction))
				reading_instruction = False
				instruction = ''
		else:
			if not reading_instruction:
				instruction_start = column

			reading_instruction = True
			instruction += char

		column += 1
	
	if reading_instruction:
		instructions.append(((instruction_start, column - 1), instruction))

	return instructions

def int_to_bytes(value):
	return [
		(value >> 0) & 0xFF,
		(value >> 8) & 0xFF,
		(value >> 16) & 0xFF,
		(value >> 24) & 0xFF,
	]

# ERROR
class Error:
	def __init__(self, position, message):
		self.position = position
		self.message = message
	
	def format_line(self, line):
		new_line = ''

		index = 0
		for char in line:
			if index == self.position.start:
				new_line += '\033[1;31m'
			
			new_line += char

			if index == self.position.end:
				new_line += '\033[0;0m'
			
			index += 1

		return new_line.strip()

	def emit(self):
		print(f'\033[1;31merror:\033[0;0m {self.message}.')

		line = get_file_lines(self.position.file)[self.position.line-1]
		line = self.format_line(line)

		print(f'  {self.position}: {line}')
		exit(1)

class UnknownInstructionError(Error):
	def __init__(self, position, instruction):
		super().__init__(position, f'unknown instruction `{instruction}`')

class UnexpectedError(Error):
	def __init__(self, position, unexpected):
		super().__init__(position, f'unexpected `{unexpected}`')

class ExpectedGotError(Error):
	def __init__(self, position, expected, got):
		message = f'expected `{expected}`'
		if got != None:
			message += f' but got `{got}`'

		super().__init__(position, message)

class LabelIsNotDefined(Error):
	def __init__(self, position, label):
		super().__init__(position, f'label `{label}` is not defined')

class Position:
	def __init__(self, file, line, start, end):
		self.file = file
		self.line = line
		self.start = start
		self.end = end
	
	def __repr__(self):
		return f'{self.file}:{self.line}'

class TokenType:
	INSTR   = '<instr>'
	NUMBER  = '<number>'
	LABEL   = '<label>'
	SYSCALL = '<syscall>'
	EOF     = '<eof>'

class Token:
	def __init__(self, position, typ, literal):
		self.position = position
		self.type = typ
		self.literal = literal

	def __repr__(self):
		return f'{self.position}: {self.type} {self.literal}'

class CodeGenerator:
	def __init__(self, tokens):
		self.tokens = tokens
		
		self.program = []
		
		self.labels = {}          # name: address of a label
		self.labels_to_link = {}  # name: (label token position, program position that need link)
		
		self.token = self.tokens[-1]  # current token; [-1] EOF token
		self.position = -1
		self.update()
	
	# update current token
	def update(self):
		self.position += 1
		if self.position < len(self.tokens):
			self.token = self.tokens[self.position]
		else:
			self.token = self.tokens[-1]

	def token_match(self, expected):
		if self.token == None:
			got = None
		
		elif self.token.type != expected:
			got = self.token.literal
		
		else:
			self.update()
			return
		
		ExpectedGotError(self.token.position, expected, got).emit()

	def push_byte(self, byte):
		self.program.append(byte)
	
	def push_int(self, i):
		bytes_ = int_to_bytes(i)
		for byte in bytes_:
			self.push_byte(byte)

	def link_labels(self):
		for label in self.labels_to_link:
			token_position, program_position = self.labels_to_link[label]
			if not label in self.labels:
				LabelIsNotDefined(token_position, label).emit()
			
			bytes_ = int_to_bytes(self.labels[label])

			i = 0
			for byte in bytes_:
				self.program[program_position+i] = byte
				i += 1

	def generate(self):
		while self.position < len(self.tokens):
			if self.token.type == TokenType.INSTR:
				if self.token.literal in ONE_ARG_OPCODES:
					instruction = self.token
					self.push_byte(OPCODES[instruction.literal])
					self.update()

					if instruction.literal in LABEL_ARG_OPCODES:
						label = self.token
						self.token_match(TokenType.LABEL)

						self.labels_to_link[label.literal] = (label.position, len(self.program))
						self.push_int(0)  # temporary address
					
					elif instruction.literal == 'SYSCALL':
						syscall = self.token
						self.token_match(TokenType.SYSCALL)

						self.push_byte(SYSCALLS[syscall.literal])
					
					else:
						number = self.token
						self.token_match(TokenType.NUMBER)

						self.push_int(number.literal)

				else:
					self.push_byte(OPCODES[self.token.literal])
					self.update()
			
			elif self.token.type == TokenType.EOF:
				break
			
			elif self.token.type == TokenType.LABEL:
				self.labels[self.token.literal] = len(self.program)
				self.update()
			
			else:
				UnexpectedError(self.token.position, self.token.literal).emit()

		self.link_labels()
		return self.program
	
	def show_program(self):
		program_as_string = ''
		column = 1
		max_column = 5
		index = 0

		for op in program:
			if column == 1:
				program_as_string += '%.3d: ' %(index)

			program_as_string += '%.3d ' %(op)

			if column == max_column:
				column = 1
				program_as_string += "\n"
			else:
				column += 1

			index += 1
		
		print(program_as_string)

def tokenize(file):
	source_lines = get_file_lines(file)
	tokens = []
	line = 1

	for source_line in source_lines:
		instructions = get_line_instructions(source_line)

		for instruction in instructions:
			start = instruction[0][0]
			end = instruction[0][1]
			instruction = instruction[1]

			position = Position(file, line, start, end)
			typ = None

			if instruction[0] == ';':
				break
			
			elif instruction[0] == '$':
				typ = TokenType.LABEL

			elif instruction.upper() in OPCODES:
				instruction = instruction.upper()
				typ = TokenType.INSTR

			elif instruction.upper() in SYSCALLS:
				instruction = instruction.upper()
				typ = TokenType.SYSCALL
			
			else:
				try:
					instruction = int(instruction)
					typ = TokenType.NUMBER
			
				except ValueError:
					UnknownInstructionError(position, instruction).emit()
			
			tokens.append(Token(
				position,
				typ,
				instruction
			))

		line += 1

	tokens.append(Token(Position(file, line-1, -1, -1), TokenType.EOF, None))
	return tokens

def usage(error=None):
	if error != None:
		print(f'error: {error}.')
	
	print('Usage: ./assembler.py [options] File...')
	print('Options:')
	print('  --help      Display this information.')
	print('  -o <file>   Place the output file into <file>.')
	print('  -b          Display binary.')

	if error != None:
		exit(1)

def parse_options():
	options = {
		'--help': False,
		'--version': False,
		'-b': False,
		'-o': 'a.out',
		'-f': None
	}

	sys.argv.pop(0)  # ./assembler.py
	
	while len(sys.argv) != 0:
		option = sys.argv.pop(0)

		if option == '-o':
			if len(sys.argv) == 0:
				usage('missing output file')
			
			options['-o'] == sys.argv.pop(0)
		
		# -f cant be passed
		elif option in options and option != '-f':
			options[option] = True

		else:
			if options['-f'] != None:
				usage('the file has already been provided')
			
			options['-f'] = option

	return options


if __name__ == '__main__':
	options = parse_options()
	file = options['-f']

	if options['--help']:
		usage()
		exit()

	if file == None:
		print('no input file. compilation terminated.')
		exit(1)

	tokens = tokenize(file)

	cg = CodeGenerator(tokens)
	program = cg.generate()

	if options['-b']:
		cg.show_program()
	
	else:
		with open(options['-o'], 'wb') as f:
			f.write(bytes(program))
