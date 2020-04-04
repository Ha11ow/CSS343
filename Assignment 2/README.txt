TOTAL GRADE EARNED: 97/100
Reason: Encoding missing

Description:
This project is to create a binary search tree class called BinTree along with some additional
functions (remove function is not required).

Your code should be able to read a data file consisting of many lines (an example file called
data2.txt will be given containing lines as shown below) to build binary search trees.
iii not tttt eee r not and jj r eee pp r sssss eee not tttt ooo ff m m y z $$
b a c b a c $$
c b a $$
Each line consists of many strings and terminates with the string “$$”. Each line will be used to
build one tree. The duplicated strings (i.e., having equal values with existing node data) are
discarded, smaller strings go left, and bigger go right. For instance, the internal tree built from the
first line of data2.txt should look like in Figure 1 in the PDF.
iii
/ \
eee not
/ \ / \
and ff jj tttt
\ / \
m r y
/ \ \
pp sssss z
/
ooo
Figure 1. example binary search tree


You will also be given nodedata.h and nodedata.cpp files which implements a NodeData class.
You must define your tree nodes using NodeData (i.e., each node holds a NodeData* for the
data).

