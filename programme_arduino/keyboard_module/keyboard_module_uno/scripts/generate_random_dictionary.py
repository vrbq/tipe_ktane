# -*- coding: utf-8 -*-
#!/usr/bin/python

from __future__ import print_function
import random

notes = ['DO', 'RE', 'MI', 'FA', 'SOL']

code_length = 9
code_db_size = 7

code_db = [[random.choice(notes) for i in range(code_length)] for j in range(code_db_size)]

print('const byte CODE_LENGTH={};'.format(code_length))
print('const byte CODE_DB_SIZE={};'.format(code_db_size))
print('const byte CODE_DB[CODE_LENGTH * CODE_DB_SIZE] = ')

for code_index, code in enumerate(code_db):
    for elt_index, elt in enumerate(code):
        if(code_index == 0 and elt_index == 0):
            print('    {', end='')
        elif(elt_index == 0):
            print('     ', end='')
            
        print('{}'.format(elt), end='')
        
        if(code_index == code_db_size-1 and elt_index == code_length-1):
            print('};')
        else:
            print(', '.format(elt), end='')           
        
    if(code_index < code_db_size-1):
        print()