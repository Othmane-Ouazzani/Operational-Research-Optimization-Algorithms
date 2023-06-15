import random
import pandas as pd
infini=99999999
villesInput=pd.read_csv("input.txt",sep="\t")
output = open("output.txt", "w+")
villesInput.index=villesInput.columns
villeAleatoire=random.choice(list(villesInput.columns))
print("La ville de depart choisie de maniere aleatoire est : ",villeAleatoire)
output.write("La ville de depart choisie de maniere aleatoire est : "+villeAleatoire+"\n")
Chemin=[villeAleatoire]
cout=0
while(True):
    min=infini
    villeProche=None
    for ville in villesInput.columns:
        if ville not in Chemin:
            if (min> villesInput.loc[villeAleatoire,ville]):
                villeProche=ville
                min=villesInput.loc[villeAleatoire,ville]
    if min!=infini:
        villeAleatoire=villeProche
        Chemin.append(villeProche)
        cout+=min
    else:
        break
cout+=villesInput.loc[Chemin[-1],Chemin[0]]
path="Le chemin optimal est :\n" 
for v in Chemin:
    path+=v
    if v==Chemin[-1]:
        path+="=>" 
        path+=Chemin[0]
        break
    path+="=>" 
print(path," avec un cout de ",cout)      
output.write(path+" avec un cout de "+str(cout)+"\n")

    



    
    




