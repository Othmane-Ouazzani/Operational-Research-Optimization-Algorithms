import random

file = open("input.txt", "r")
circuit = []
Chemin = []
Couts = []
Villes = file.readline().strip().split("\t")

for line in file:
    cost = line.strip().split("\t")
    Couts.append(cost)

VillesCopy = Villes.copy()
v = random.choice(Villes)
Villes.remove(v)
Chemin.append(v)

while(True):
    Villeprochaine = random.choice(Villes)
    Villes.remove(Villeprochaine)
    index = 999999999
    minCost = 99999999
    for c in Chemin:
        if(float(Couts[VillesCopy.index(c)][VillesCopy.index(Villeprochaine)]) < minCost):
            index = Chemin.index(c) + 1
            minCost = float(Couts[VillesCopy.index(c)][VillesCopy.index(Villeprochaine)])
        if(float(Couts[VillesCopy.index(Villeprochaine)][VillesCopy.index(c)]) < minCost):
            index = Chemin.index(c)
            minCost = float(Couts[VillesCopy.index(Villeprochaine)][VillesCopy.index(c)])
    Chemin.insert(index, Villeprochaine)
    if(len(Villes) == 0):
        break
cheminCout = 0
for i in range(len(Chemin) -1):
    cheminCout += float(Couts[VillesCopy.index(Chemin[i])][VillesCopy.index(Chemin[i+1])])
cheminCout += float(Couts[VillesCopy.index(Chemin[-1])][VillesCopy.index(Chemin[0])])
output = open("output2.txt", "w+")
output.write("Le cout est: "+str(cheminCout))
output.write("\nLe Chemin optimal est: ")
output.write(str(Chemin))

print("\nLe Chemin optimal est: ")
print(Chemin)
print("Le cout  est: ",cheminCout)
