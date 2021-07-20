'''Program that shows the evolution of the times that we get head
    when we charge a coin with a custom probability till 
    we get a diff of the last 2 probabilities of {decimals} times

    Javier Gómez López '''

import subprocess
import random
import matplotlib.pyplot as plt
import os
import time
from prettytable import PrettyTable

start_time = time.time() #counter time

#Define the probability
chance = 1/2

#Define number of decimals
decimals = 1

#Define a method to convert seconds to hh:mm:ss
def convert(seconds):
    seconds = seconds % (24 * 3600)
    hour = seconds // 3600
    seconds %= 3600
    minutes = seconds // 60
    seconds %= 60
      
    return "%d:%02d:%02d" % (hour, minutes, seconds)


#Define truncate
def truncate(f,n):
    '''Truncate a float f to n decimal places without rounding'''
    s = '{}'.format(f)
    if 'e' in s or 'E' in s:
        return '{0:.{1}f}'.format(f,n)
    i, p, d = s.partition('.')
    return '.'.join([i, (d+'0'*n)[:n]])

head = 0
tail = 0
counter = 1
x=[0, 1]

table = PrettyTable(['Time','Probability'])
table.add_row([0,0])

m = random.random()
i=2

keep = True

if (m <= chance):
    head +=1
    y = [0, 1]
    table.add_row([1,1])
else:
    tail += 1
    y = [0, 0]
    table.add_row([1,0])

while keep:
    
    k = random.random()
        
    if (k <= chance):
        head +=1
    else:
        tail += 1

    counter +=1
    x.extend([counter])

    probability = head/counter
    y.extend([probability])

    one = float(truncate(probability,decimals))
    last = float(truncate(y[counter-1],decimals))


    table.add_row([i, one])
    i += 1
    time.sleep(0.00002) # wait in seconds

    if i > 10:
        table.del_row(0)

    if one == last:
        if i < 10:
            keep = True
        else:
            keep = False



print("It has come out", head, "times head")
print ("It has come out", tail,"times cross")
print(table)

elapsed_time = time.time() - start_time
print("It took ", convert(elapsed_time), "seconds")


plt.plot(x,y) #We create the function
plt.xlabel("Number of events") #X axis label
plt.ylabel("Head probability") #Y axis label
plt.title("Representation of the limit of the probability of \
     \n getting head in a non-fixed coin") #Title
plt.show()