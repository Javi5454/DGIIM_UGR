'''Program that shows the evolution of the times that we get head
    when we charge a coin with 1 out of 2 times possibility

    Javier Gómez López '''

import subprocess
from random import randint
import matplotlib.pyplot as plt

throws = int(input("Set the number of throws that will do the coin:"))

head = 0
cross = 0
counter = 1
x=[0, 1]

m = randint(0,1)
y = [0, m]

if (m == 1):
    head +=1
else:
    cross += 1

for i in range(1, throws - 1):
    k = randint(0,1)
    
    if (k == 1):
        head +=1
    else:
        cross += 1

    counter +=1
    x.extend([counter])

    possiblity = head/counter
    y.extend([possiblity])



print("It has come out", head, "times head")
print ("It has come out", cross,"times cross")

plt.plot(x,y) #We create the function
plt.xlabel("Number of events") #X axis label
plt.ylabel("Head probability") #Y axis label
plt.title("Representation of the limit of the probability of \
     \n getting head in a non-fixed coin") #Title
plt.show()