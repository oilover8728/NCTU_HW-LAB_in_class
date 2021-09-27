# -*- coding:utf-8 -*-
''' 
This is an example for students to learn how to write a python script.
And here is a multiple line comments example.
'''

import io

def printTheText (text): #don’t for get the “:”
    # four spaces for next level, contents of printTheText
    print(text, ' - PTT') # print belong to printTheText function

def main(printit):
    if (printit):
        printTheText("This is the printTheText definition.")
    else:
        printTheText("I don't want to print but print.")

if __name__ == '__main__':
    main(1)
    main(0)
