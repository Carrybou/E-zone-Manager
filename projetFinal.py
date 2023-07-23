##
# @author Ioen Blanchetot / Thomas Guibert 
# @brief Ceci est un logiciel realisé pour un projet de NF06 a l'utt
# @mainpage E-Zone manager
# @section consigne_sec Consignes 
# Vous travaillez au sein du departement informatique de l’entreprise de e-commerce E-Zone qui vend des produits Hi-tech en ligne. Votre responsable vous a demande de creer les commandes des clients.
# @section catalogue_des_produits_sec Catalogue des produits 
# La premiere partie de l’application (ecrite en Python) vous permet de suivre les produits disponibles, d’en ajouter des nouveaux, d’afficher des statistiques utiles sur les ventes et de preparer les commandes pour l’equipe d’expedition.
# @section expedition_sec Expedition
# La deuxieme partie de l’application (ecrite en C) est d´ediee a l’equipe d’expedition.Comme nous disposons d’un nombre limite de camions, nous voulons donner la priorite aux produits couteux pour les livrer dans notre camion le plus rapide. Neanmoins, ce camion a une capacite limitee et ne peut contenir que jusqu’a un certain poids C (saisi par l’equipe d’expedition). Ce probleme est connu sous le nom : probleme de sac a dos 3 . Il existe plusieurs methodes pour resoudre le probleme a savoir : brute force, programmation dynamique, methode gloutonne...
import ctypes
Projet_C = ctypes.CDLL("C:/Users/ioen/Documents/NF06/Projet_NF06/Projet_C.dll")

function_c = Projet_C.main

function_c.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_float]
function_c.restype = ctypes.c_int


from operator import itemgetter
from matplotlib import pyplot
import numpy as np
## @brief La base de donnee est sous forme d'un fichier texte que l'on va lire en passant ligne par ligne en isolant les parametres un par un et en les mettant dans un tableau
# @param lire_prod Permet d'ouvrir le fichier texte et lire les produits 
# @details Chaque ligne correspond a un produit sous forme UID/Nom/Prix/Categorie/Marque/Annee/Quantite/Poid/Nombre de commandes/Avis
# On utilise la fonction split pour isoler chaque parametre d'un produit et enlever les "/"
# @param prod Tableau a double entree qui permet de manipuler la liste de produit 
# @details Prod[i][u] avec i chaque produit et u chaque parametre de chaque produit
# @param file_read permet d'ouvrir le fichier contenant les produits
# @param file_nb_articles permet d'ouvir le fichier contenant le nombre d'article 
    
# @return prod un tableau a double entree et n le nombre de produit dans le tableau
def lire_prod():

    file_read = open("fichier_texte.txt", "r")
    file_nb_articles = open("fichier_nb_articles.txt", "r")
    
    n = int(file_nb_articles.readline().split('/')[0])
    
    
    prod=[[0]*10 for i in range(n)]
    
    j=0
    for i in range(n):
        
        file_read.seek(j)
        UID=str(file_read.readline().split('/')[0])
        prod[i][0]=UID
        
        file_read.seek(j)
        
        nom=str(file_read.readline().split('/')[1])
        prod[i][1]=nom

        file_read.seek(j)
        prix=int(file_read.readline().split('/')[2])
        prod[i][2]=prix

        file_read.seek(j)
        categorie=str(file_read.readline().split('/')[3])
        prod[i][3]=categorie

        file_read.seek(j)
        marque=str(file_read.readline().split('/')[4])
        prod[i][4]=marque

        file_read.seek(j)
        annee=int(file_read.readline().split('/')[5])
        prod[i][5]=annee

        file_read.seek(j)
        quantite=int(file_read.readline().split('/')[6])
        prod[i][6]=quantite

        file_read.seek(j)
        poid=int(file_read.readline().split('/')[7])
        prod[i][7]=poid

        file_read.seek(j)
        nb_commandes=int(file_read.readline().split('/')[8])
        prod[i][8]=nb_commandes

        file_read.seek(j)
        avis=int(file_read.readline().split('/')[9])
        prod[i][9]=avis
        
        j =file_read.tell()#position dans le fichier
        
    
    
    
    file_read.close()
    file_nb_articles.close()
    
    return prod,n
## @brief Pour afficher une certaine liste de produit a l'utilisateur on utilise une fonction dediees
# @param[in] prod,n le tableau et son nombre d'article qu'on va afficher a l'utilisateur
# @param k on va afficher les produits un par un avec tous ses parametres donc k est la variable qui permet de changer de colonne dans le tableau donc de produit
#@return affiche tous les articles sous forme d'une description 
def print_prod(prod,n):

    for k in range (n):
        print("\nProduit n°",k+1,": \nUID:",prod[k][0],"\nNom : ",prod[k][1],"\nPrix :",prod[k][2],"\nCatégorie :",prod[k][3],"\nMarque :",prod[k][4],"\nAnnée :",prod[k][5],"\nQuantité :",prod[k][6],"\nPoid :",prod[k][7],"\nNombre de commandes :",prod[k][8],"\nAvis clients sur 5:",prod[k][9])

## @brief Pour que le manager puisse ajouter un produit a la liste de ceux disponible. On lui demande les parametres du produit un a un pour ensuite les ecrire sur le fichier
#@param file ouvre le fichier contenant les produits en mode "a" ce qui permet d'ecrire a la suite et ne pas supprimer les autres produits
#@param file_nb_art_read ouvre le fichier qui contient le nombre d'article en mode "w" pour remplacer le nombre apres l'avoir lu et modifié 
def ajt_prod(): #sous fonction qui permet d'ajouter des produits à la liste des produits dispo
    print('Ajouter un produit :')
    file = open("fichier_texte.txt", "a") #on ouvre le fichier qui sert d'archive
    
    nouvel_ajt='y'
    while(nouvel_ajt=='y' ): 
        UID=int(input("Ecrire l'UID du produit : "))
        nom=str(input("Ecrire le nom du produit : "))
        prix=int(input("Ecrire le prix du produit : "))
        pre_categorie=int(input("Ecrire la catégorie du produit : \n 1-Télephone \n 2- Ordinateur Portable \n 3-Télévision \n 4-Console de jeu \n 5-Autres \n"))
        if pre_categorie == 1:
            categorie = "Telephone"
        elif pre_categorie == 2:
            categorie ="Ordinateur Portable"
        elif pre_categorie == 3:
            categorie = "Television"
        elif pre_categorie == 4:
            categorie = " Console de jeu"
        elif pre_categorie == 5:
            categorie = "Autres"
        else :
            print("Erreur") # erreur non prise en compte

        marque=str(input("Ecrire la marque du produit : "))
        annee=int(input("Ecrire l'année du produit : "))
        quantite=int(input("Ecrire la quantité du produit : "))
        poids=int(input("Ecrire le poid du produit en g : "))
        nb_commandes=int(input("Ecrire le nombre de commandes déjà effectuées du produit : "))
        avis=int(input("Ecrire la note du produit sur 5 : "))

        file.write(str(UID)+"/"+str(nom)+"/"+str(prix)+"/"+str(categorie)+"/"+str(marque)+"/"+str(annee)+"/"+str(quantite)+"/"+str(poids)+"/"+str(nb_commandes)+"/"+str(avis)+"\n") #ecrire dans le fichier
         
        file_nb_art_read = open("fichier_nb_articles.txt", "r")
        n = int(file_nb_art_read.readline().split('/')[0])
        n = n+1
        file_nb_art_read.close()
        file_nb_art_write = open("fichier_nb_articles.txt","w")

        file_nb_art_write.write(str(n))
        file_nb_art_write.close()

        nouvel_ajt=str(input("Voulez vous ajouter un nouveau produit y/n : ")) # permet de rester dans la boucle while et ajouter des produits
    file.close()
    
##@brief Permet de filtrer une liste de produits donnée : par la categorie, la marque, l'annee de sortie
#@return prod_filtre,k le tableau apres avoir été filtré et k sa nouvelle taille
def Filtrer(prod,n):
    prod_filtre=[[0]*10 for i in range(n)]
    filtre=int(input("Filtrer par :\n1-Catégorie\n2-Marque\n3-Année minimale de sortie\n"))
    if filtre ==1:
        k=0

        pre_categorie=int(input("Quelle catégorie : \n 1-Télephone \n 2-Ordinateur Portable \n 3-Télévision \n 4-Console de jeu \n 5-Autres \n"))
        if pre_categorie == 1:
            categorie = "Telephone"
        elif pre_categorie == 2:
            categorie ="Ordinateur Portable"
        elif pre_categorie == 3:
            categorie = "Television"
        elif pre_categorie == 4:
            categorie = "Console de jeu"
        elif pre_categorie == 5:
            categorie = "Autres"
        else :
            print("Erreur") # erreur non prise en compte
        for u in range (n):
            
            if prod[u][3]==categorie:
                
                for v in range(10):
                    prod_filtre[k][v]=prod[u][v]
                    
                k+=1       
        return prod_filtre,k
        
    elif filtre==2:
        k=0

        marque=str(input("Quelle marque :\n"))

        for u in range (n):
            
            if prod[u][4]==marque:
                
                for v in range(10):
                    prod_filtre[k][v]=prod[u][v]
                    
                k+=1
        return prod_filtre,k

    elif filtre==3:
        k=0
        annee=int(input("Année minimum :\n"))
        for u in range (n):
            
            if prod[u][5]>=annee:
                
                for v in range(10):
                    prod_filtre[k][v]=prod[u][v]
                    
                k+=1
        return prod_filtre,k

    else :
        print("Erreur")

        
##@brief Permet de trier une liste de produits donnee : par le nombre de commande, quantité disponible et l'avis client
#@return prod_trie,n il renvoie le tableau trié grace a la fonction "sorted"

def Trier(prod,n):

    trie=int(input("Trier par :\n1-Nombre de commandes croissant \n1-Nombre de commandes decroissant\n3-Quantité disponible croissant \n4-Quantité disponible decroissant \n5-Avis croissant\n6-Avis decroissant\n"))
    if trie==1:
        print("trie par commandes croissant")
        prod_trie = sorted(prod,key=itemgetter(8))
    elif trie ==2:
        print("trie par commandes decroissant")
        prod_trie = sorted(prod,key=itemgetter(8), reverse=True)
    elif trie == 3:
        print("trie par quantité croissante")
        prod_trie = sorted(prod,key=itemgetter(6))
    elif trie ==4:
        print("trie par quantité decroissante")
        prod_trie = sorted(prod,key=itemgetter(6), reverse=True)
    elif trie == 5:
        print("trie par avis croissant")
        prod_trie = sorted(prod,key=itemgetter(9))
    elif trie == 6 :
        print("trie par avis decroissant")
        prod_trie = sorted(prod,key=itemgetter(9), reverse=True)
    else :
        print("erreur")
    return prod_trie,n

## @brief C'est ici que le manager pourra passer une commande, il va saisir les produits qu'il veut envoyer avec avoir pu les filtrer et trier. Le python va faire appel au C pour definir les meilleurs produits a envoyer pour une plus grosse rentabilité
# @param[in] prod,n le tableau de produit et le nombre d'article 
#@param fileC le fichier que le C va lire
#@details un version simplifiee de "prod" avec seulement les informations necessaires au C
# @param prod_trie,t un tableau a double entree trié
#@param prod_filtre,k un tableau a double entree filre et k le nouveau nombre de produit apres le filtre et le trie
# @param prod_commande l'utilisateur choisit les produits qu'il veut expedier qui sont stockes dans un tableau a double entree
# @details si une trop grande quantité de certains produits sont demandés, alors seulement ceux presents dans le stock sont envoyés
# @param i la capcité du camion qui va etre communiquée au C 
# @param test lorsque l'on fait appel au C, il nous renvoie une confirmation de reussite du programme ou une erreur comprise en 1 et 4, 0 est la reussite du programme  
#@param fileCommandeFinal fichier remplie par le C, avec les produits a envoyer dans le camion 
#@param prod_expedie un tableau que l'on remplie avec le contenue du fichier remplie par le C
def commande(prod,n):
    fileC = open("fichier_pour_C.txt", "w") #on ouvre le fichier pour communiquer avec le C
    print('Passer une commande')
    print_prod(prod,n)
    trie = input("\nVoulez vous tier ? y/n : ")
    if trie == "y":
        prod_trie,t=Trier(prod,n)
        print_prod(prod_trie,t)
    else :
        prod_trie,t=prod,n

    filtre=input("\nVoulez vous filtrer ? y/n : ")
    if filtre=="y":
        prod_filtre,k = Filtrer(prod_trie,t)

        nouveau_filtre=str(input("\nVoulez vous ajouter un nouveau filtre ? y/n : "))
        while nouveau_filtre=="y" :
            prod_filtre,k = Filtrer(prod_filtre,k)
            nouveau_filtre=str(input("\nVoulez vous ajouter un nouveau produit ? y/n : "))
        print_prod(prod_filtre,k)
    else:
        prod_filtre=prod_trie

    z=0
    choix='y'
    while (choix=='y'):
        prod_commande=int(input("\nQuel produit voulez vous choisir ? (son numéro) : "))-1
        nombre=input(f"\nCombien de {prod_filtre[prod_commande][1]} ont été commandé(es) ?")
        if int(nombre) > int(prod_filtre[prod_commande][6]):
            print(f"Seulement {prod_filtre[prod_commande][6]} {prod_filtre[prod_commande][1]} disponiblent en stock, elles ont été ajoutées à la liste")
            nombre = prod_filtre[prod_commande][6]
        fileC.write(str(prod_filtre[prod_commande][0])+"/"+str(nombre)+"/"+str(prod_filtre[prod_commande][2])+"/"+str(prod_filtre[prod_commande][7])+"\n")
        z=z+1
        choix=input("\nVoulez vous choisir un autre produit ? y/n")
    i=float(input("\nQuelle est la capacité en g du camion : "))
    fileC.close()
    print("Lancement du C")
    test=function_c(b"fichier_pour_C.txt", b"fichier_commande_finale.txt", i)
    test = 0
    if test != 0:
        print("Erreur lors du lancement du C")
        return

    fileCommandeFinal=open("fichier_commande_finale.txt","r")
    prod_expedie=[[0]*4 for i in range(z)]
    
    j=0
    for i in range(z):
        
        fileCommandeFinal.seek(j)
        UID=str(fileCommandeFinal.readline().split('/')[0])
        prod_expedie[i][0]=UID

        fileCommandeFinal.seek(j)
        quantite_expedie=str(fileCommandeFinal.readline().split('/')[1])
        prod_expedie[i][1]=quantite_expedie

        fileCommandeFinal.seek(j)
        prix=str(fileCommandeFinal.readline().split('/')[2])
        prod_expedie[i][2]=prix

        fileCommandeFinal.seek(j)
        poid=str(fileCommandeFinal.readline().split('/')[3])
        prod_expedie[i][3]=poid

        j =fileCommandeFinal.tell()#position dans le fichier
    for b in range(z):
        u=0
        while (prod_expedie[b][0]!=prod[u][0]):
            u=u+1
            
        prod[u][6]=int(prod[u][6])-int(prod_expedie[b][1])
        prod[u][8]=int(prod[u][8])+int(prod_expedie[b][1])
    file=open("fichier_texte.txt","w")
    
    for k in range(n):
        file.write(str(prod[k][0])+"/"+str(prod[k][1])+"/"+str(prod[k][2])+"/"+str(prod[k][3])+"/"+str(prod[k][4])+"/"+str(prod[k][5])+"/"+str(prod[k][6])+"/"+str(prod[k][7])+"/"+str(prod[k][8])+"/"+str(prod[k][9])+"\n")
    fileCommandeFinal.seek(j)
    prix_final=fileCommandeFinal.readline()
    print("\nLe prix total de la commande est ",prix_final)
    list=input("\nVoulez vous afficher les produits mis a jour ?y/n")
    if list=="y":
        print_prod(prod,n)
    
    file.close()
    fileCommandeFinal.close()

## @brief Menu principal est le debut de l'interface pour l'utilisateur. C'est par la qu'il va naviguer entre les différentes options du logiciel
# @details L'utilisateur voit les options affichees et choisit grace a leur numero. Il va ensuite naviguer comme ca pour choisir ce qu'il veut faire
menu_principale = int(input("Bienvenue sur E-zone \n 1-Suivre les produit disponibles \n 2-Ajouter un produit\n 3-Faire une commande \n 4-Afficher les statistiques\n"))

if menu_principale == 1 :
    production=int(input("1-Trier\n2-Filtrer\n3-Filtrer et trier\n4-Afficher dans l'ordre\n"))
    prod,n =lire_prod()
    if production == 1:

       prod_trie,n=Trier(prod,n)
       print_prod(prod_trie,n)

    elif production == 2:
        prod_filtre,k = Filtrer(prod,n)
        
        nouveau_filtre=str(input("Voulez vous ajouter un nouveau filtre ? y/n : "))
        while nouveau_filtre=="y" :
            prod_filtre,k = Filtrer(prod_filtre,k)
            nouveau_filtre=str(input("Voulez vous ajouter un nouveau produit y/n : "))
        
        print_prod(prod_filtre,k)

    elif production==3:
        
        prod_trie,n=Trier(prod,n)
        print_prod(prod_trie,n)
        prod_filtre,k = Filtrer(prod_trie,n)

        nouveau_filtre=str(input("Voulez vous ajouter un nouveau filtre ? y/n : "))
        while nouveau_filtre=="y" :
            prod_filtre,k = Filtrer(prod_filtre,k)
            nouveau_filtre=str(input("Voulez vous ajouter un nouveau produit y/n : "))
        print_prod(prod_filtre,k)
        
    elif production == 4:
        
        print_prod(prod,n)
    else:
        print("Erreur")

elif menu_principale == 2 :
    ajt_prod()

elif menu_principale == 3 :
    prod,n =lire_prod()
    commande(prod,n)

elif menu_principale ==4:
    ## @brief Les statistiques sont realisees grace au tableau de produit qui va permetre que l'on compare les elements d'apres un certain critere. Les graphiques sont realises avec matplotlib 
    stat=int(input("1-Le meilleur/pire produit par marque en termes de ventes\n2-Le meilleur/pire produit par categorie en termes de ventes\n3-Le total des ventes en euros realisees par le magasin\n4-Le graphique de nombre de produits par categorie\n5-Le graphique de total des ventes par marque de produits\n"))
    prod,n =lire_prod()
    if stat==1:
            
            test_marque=[]
            u=0
            marque=0
            verif_marque =True
            while verif_marque == True:
                marque=prod[u][4]
                if marque not in test_marque :
                    test_marque.append(prod[u][4])
                    

                    meilleur=[0,0]
                    pire=[10000000000,0]
                    for i in range(n):
                        
                        if prod[i][4]==marque:
                            if prod[i][2]*prod[i][8] > meilleur[0]:
                                meilleur[0]=prod[i][2]*prod[i][8]
                                meilleur[1]=prod[i][1]
                            if prod[i][2]*prod[i][8] < pire[0]:
                                pire[0]=prod[i][2]*prod[i][8]
                                pire[1]=prod[i][1]
            
                    print(f"\nLe meilleur produit de la marque {marque} est {meilleur[1]} avec {meilleur[0]}€ de chiffre d'affaire et le pire est {pire[1]} avec {pire[0]}€ de chiffre d'affaire !")
                u=u+1
          
                if u==n:
                    verif_marque=False

    elif stat==2:

        meilleur=[0,0]
        pire=[10000000000,0]

        for u in range(4):
            cat=["Telephone","Ordinateur Portable","Television","Console de jeu","Autres"]
            meilleur=[0,0]
            pire=[10000000000,0]
            for i in range(n):
                
                if prod[i][3]==cat[u]:
                    if prod[i][2]*prod[i][8] > meilleur[0]:
                        meilleur[0]=prod[i][2]*prod[i][8]
                        meilleur[1]=prod[i][1]
                    if prod[i][2]*prod[i][8] < pire[0]:
                        pire[0]=prod[i][2]*prod[i][8]
                        pire[1]=prod[i][1]
            
            print(f"\nLe meilleur produit de la catégorie {cat[u]} est {meilleur[1]} avec {meilleur[0]}€ de chiffre d'affaire et le pire est {pire[1]} avec {pire[0]}€ de chiffre d'affaire !")

    elif stat==3:
        
        prod,n =lire_prod()
        tot_recette=0
        for i in range(n):
            tot_recette=tot_recette+ prod[i][2]*prod[i][8]
        print(f"\nLe total des ventes est {tot_recette}€ ")

    elif stat==4:
        x=[]    
        for i in range(n):
             x.append(prod[i][3])   
        pyplot.hist(x,  range = (0, 5),color = 'yellow', edgecolor = 'red')
        pyplot.xlabel('Categories')
        pyplot.ylabel('Nombres')
        pyplot.title('Nombre de produit par categorie')
        pyplot.show() 
    elif stat ==5:
        print("ventes par marques")
        x=[]
        y=[]
        test_marque=[]
        u=0
        marque=0
        verif_marque =True
        
        while verif_marque == True:
            marque=prod[u][4]
            tot_vente=0
            if marque not in test_marque :
                test_marque.append(prod[u][4])

                for i in range(n):
                    
                    if prod[i][4]==marque:
                        tot_vente= float(tot_vente +prod[i][8]*prod[i][2])
                
                x.append(marque)
                y.append(tot_vente)    
                     
            u=u+1
          
            if u==n:
                verif_marque=False

        pyplot.bar(x,y)
        pyplot.xlabel('Marques')
        pyplot.ylabel('Ventes en €')
        pyplot.title('Total des ventes par marque ')
        pyplot.show() 

    else:
        print("erreur")

else :
    print("Mauvais chiffre")