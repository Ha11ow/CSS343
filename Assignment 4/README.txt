Grade Earned: 100/100

Description: 
The performance of a hash table depends critically on the quality of the hash function used. 
A poor hash function will result in many collisions (for open addressing) or long chains (for separate chaining). 
In general, hash functions are generated experimentally, based on the structure and statistics of the data to be stored. 
This assignment asks you to develop a hash function for a separate chaining hash table.

The file phonebook.txt contains 46,332 names and telephone numbers, one per line,
  with the name separated from the phone number by a tab character.

Write a program which reads this file, stores its contents into a hash table with 4177 entries using separate chaining, 
  and then outputs information necessary to produce a histogram as described below. 
You will use this program to investigate the performance of different hash functions.

Consider and discuss first what the performance of the ideal hash function would be under these circumstances 
  (include a complete answer to this question in your report). 
Experiment with three different hash functions and produce the following for each:
  *	Pseudocode (or a mathematical equation) describing how it is computed.
  *	A visual histogram showing chain length distribution. The histogram's X axis should be "chain length" 
		its Y axis should be the number of table entries that have that length of chain.
  *	An explanation or hypothesis for why the hash function was less than ideal. 
	  This should make it obvious why you chose the subsequent hash function you tried and submitted in code.

Your report will be evaluated as would one produced for CSS 301, in terms of general quality of writing, professional style and format, 
  and presentation of results, as described in the rubric below. Because of the report element, 
  50% of the grade for this assignment will be program and 50% will be for the report.
