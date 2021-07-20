'''Program that shows the evolution of the times that we get head
    when we charge a coin with 1 out of 3 times possibility

    Javier Gómez López '''

import subprocess
import random
import matplotlib.pyplot as plt

throws = int(input("Set the number of throws that will do the coin:"))

head = 0
cross= 0
counter = 1
x = [0,1]
y = [0]

m = random.random()

if (m <= (1/3)):
    head += 1
else:
    cross += 1

possiblity = head/counter
y.extend([possiblity])

for i in range(1, throws - 1):
    k = random.random()

    if(k <= (1/3)):
        head += 1
    else:
        cross += 1

    counter+= 1
    x.extend([counter])

    possiblity = head/counter
    y.extend([possiblity])

print("It has come out", head, "times head")
print("It has come out", cross, "times cross")

plt.plot(x,y) #Create the function
plt.xlabel("Number of events") #X Axis Label
plt.ylabel("Head Probability") #Y Axis Label
plt.title("Representation of the limit of the probability of getting \
    \n head in a 1/3 fixed coin")
plt.show()

