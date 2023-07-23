/**
 * @file Projet_C.c
 * @author Thomas Guibert et Ioen Blanchetot (thomas.guibert@utt.fr et ioen.blanchetot@utt.fr)
 * @brief Projet de NF06 E-zone Manager - A22 - Programme C permettant une application du problème du sac à dos (problème d'optimisation)
 * @version 4.5
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief nombre maximum de produits acceptés par le C; défini au début pour pouvoir être modifié facilement par l'uitilisateur
 */
#define MAX_PRODUITS 1000

/**
 * @brief Nombre de chiffres max que contiennent les UID des articles ainsi que leur quantité, poids et prix; défini au début pour pouvoir être modifié facilement par l'uitilisateur
 */
#define TAILLE 5

/**
 * @brief Les produits dans le programme C ne seront répertoriés qu'avec les 4 informations essentielles suivantes
 */
struct Produit {
    int UID;
    int quantité;
    float prix;
    float poids;
};


/**
 * @brief   Fonction appelée par genetique() et brute_force()
 *          On n'attribue plus qu'un seul article par ligne dans 'commande' (au lieu de regrouper 6 objets similaires sur la même ligne, on les divise en 6 lignes différentes de quantité 1 chacune) afin de sélectionner plus facilement les objets à mettre dans le camion
 * 
 * @param commande Tableau de structure de produit contenant tous les produits parmis lesquels on choisira les meilleurs à commander
 * @param nouvelle_commande Tableau de structure de produit initialement vide, qui contiendra les produits à commander, séparés en quantité unitaire
 * @param nb_article Nombre d'éléments contenus dans 'commande' = le nombre de produits différents
 * @param quantite_tot Nombre d'éléments qui seront contenus dans 'nouvelle_commande' = le nombre de produits totaux à traiter
 * @return struct Produit : Retourne 'nouvelle_commande' ne contenant plus que des articles de quantité unitaire, prête à être traitée dans les autres fonctions
 */
struct Produit diviser_objets_par_qtte(struct Produit *commande,struct Produit *nouvelle_commande, int nb_article, int *quantite_tot) {

    /**
     * @brief On initialise 'nouvelle_commande' à 0
     */
    for (int i=0; i<*quantite_tot; i++) {
        nouvelle_commande[i].UID=0;
        nouvelle_commande[i].quantité=0;
        nouvelle_commande[i].prix=0;
        nouvelle_commande[i].poids=0;
    }

    /**
     * @brief On commence par remplir 'nouvelle_commande' avec les éléments de 'commande'
     */
    for (int ligne=0; ligne<nb_article; ligne++) {
        nouvelle_commande[ligne].UID=commande[ligne].UID;
        nouvelle_commande[ligne].quantité=commande[ligne].quantité;
        nouvelle_commande[ligne].prix=commande[ligne].prix;
        nouvelle_commande[ligne].poids=commande[ligne].poids;
    }

    /**
     * @brief On parcourt l'ensemble du tableau 'nouvelle_commande' et lorsque la quantité de l'article est superieure à 1, on le met sur une autre ligne et on décale tous les autres éléments du tableau
     */
    for (int nvelle_ligne=0; nvelle_ligne<*quantite_tot; nvelle_ligne++) {
        if (nouvelle_commande[nvelle_ligne].quantité>1) {
            for (int l=nb_article-1; l>=nvelle_ligne ; l--) {
                nouvelle_commande[l+1].UID = nouvelle_commande[l].UID;
                nouvelle_commande[l+1].quantité = nouvelle_commande[l].quantité;
                nouvelle_commande[l+1].prix = nouvelle_commande[l].prix;
                nouvelle_commande[l+1].poids = nouvelle_commande[l].poids;
            }
            nb_article++;
            nouvelle_commande[nvelle_ligne].quantité = 1;
            nouvelle_commande[nvelle_ligne+1].quantité -= 1;
        }
    }
    
    return *nouvelle_commande;
}

/**
 * @brief   Fonction appelée par genetique() et brute_force()
 *          On regroupe tous les articles similaires sur la même ligne afin de traiter les données proprement ensuite
 * 
 * @param commande tableau de structure de produit contenant les produits à commander, séparés en quantité unitaire
 * @param quantite_tot nombre d'éléments contenus dans 'commande' = le nombre de produits à commander
 */
void regrouper_objets_par_qtte(struct Produit *commande, int *quantite_tot) {

    int supp, quantite_temporaire;

    /**
     * @brief On parcourt l'ensemble du tableau 'commande' et lorsque l'IUD de l'article suivant est similaire, on le met sur la même ligne et on décale tous les autres éléments du tableau
     * Les variables avec la mention temporaire permettent simplement de faire 
     */
    for (int i=0; i<*quantite_tot-1; i++) {
        while (commande[i].UID == commande[i+1].UID) {
            quantite_temporaire = commande[i+1].quantité;
            for (supp=i+1; supp<*quantite_tot-1; supp++) {
                commande[supp].UID = commande[supp+1].UID;
                commande[supp].quantité = commande[supp+1].quantité;
                commande[supp].poids = commande[supp+1].poids;
                commande[supp].prix = commande[supp+1].prix;
            }
            *quantite_tot -= 1;
            commande[i].quantité += quantite_temporaire;
            commande[*quantite_tot].UID=0;
            commande[*quantite_tot].quantité=0;
            commande[*quantite_tot].poids=0;
            commande[*quantite_tot].prix=0;
        }
    }
}

/**
 * @brief Méthode de résolution par algorithme génétique - Pas au point - Méthode efficace pour les très grands échantillons
 * Fonctionne par définition en copiant le principe de base de la génétique : on crée une population aléatoire, on effectue une sélection naturelle pour ne garder que les meilleurs et on les reproduit ensemble. On effectue cela sur un certain nombre de générations. Cette méthode ne permet pas d'avoir le résultat le plus optimal mais un résultat acceptable en temps convenable pour de gros échantillons. On peut alors varier la taille de la population de départ ou le nombre de générations en fonction de la taille de l'échantillon, du temps que prendra le programme et de la qualité du résultat attendu.
 * La particularité de cette solution est qu'il y a des chances d'obtenir un résultat différent à chaque exécution contrairement aux autres méthodes de résolution.
 * Malheureusement nous n'avons pas eu le temps de le rendre effectif, n'est ici qu'une maquette inachevée de la résolution attendue.
 * 
 * @param C Capacité en kg du camion à remplir
 * @param nb_article Nombre d'éléments contenus dans 'commande' = le nombre de produits différents
 * @param commande Tableau de structure de produit contenant tous les produits parmis lesquels on choisira les meilleurs à commander
 * @param prix_total Prix qu'atteindra la commande du chargement final du camion
 * @return int :    Retourne 0 si tout s'est passé correctement
 *                  Retourne 1 s'il n'y a pas assez d'articles dans la commande pour utiliser cette méthode
 */
int genetique(float C, int nb_article, struct Produit *commande, float* prix_total) {

    printf("Methode algorithme genetique:\n");

    /**
     * @brief Paramètres à déterminer en fonction de la taille de l'échantillon, du temps que prendra le programme et de la qualité du résultat attendu.
     */
    int nb_parents = 100, nb_generation = 20, nb_parents_a_garder_par_generation = 50;
    
    int quantite_tot = 0;
    for (int i=0; i<nb_article; i++) quantite_tot += commande[i].quantité;

    if (quantite_tot < nb_parents) {
        printf("Pas assez d'articles pour utiliser cette méthode de resolution\n");
        return 1;
    }

    struct Produit nouvelle_commande[quantite_tot];

    *nouvelle_commande = diviser_objets_par_qtte(commande, nouvelle_commande, nb_article, &quantite_tot);

    int parents[nb_parents][quantite_tot];
    int parent_supprime = 0;
    int permutation_objet[quantite_tot];
    float permutation_poid_chrgmt, permutation_prix_chrgmt;
    int k;
    int nb_parent_restant;
    int parent1, parent2;
    float poid_de_ce_chargement[nb_parents];
    float prix_de_ce_chargement[nb_parents];

    on_recommence :

    /**
     * @brief Création des premiers parents par choix aléatoire de prendre ou non chacun des articles
     */
    for (int parent=0; parent<nb_parents; parent++) {
        printf("\nparent numero %d :  ", parent);
        for (int article=0; article<quantite_tot; article++) {
            parents[parent][article] = rand() % 2;
            printf("%d ", parents[parent][article]);
        }
        prix_de_ce_chargement[parent] = 0;
    }

    /**
     * @brief La sélection naturelle se produira un nombre 'nb_generation' de fois
     */
    for (int generation=0; generation<nb_generation; generation++) {
        
        parent_supprime = 0;

        /**
         * @brief On calcule dans cette boucle le poid associé à chaque parent (combinaison d'article déterminée aléatoirement précédemment) et on abandonne celles qui ne respectent pas la condition maximale
         */
        for (int parent=0; parent<nb_parents; parent++) {
            printf("\nparent numero %d : ", parent);
            poid_de_ce_chargement[parent] = 0;
            for (int article=0; article<quantite_tot; article++) {
                poid_de_ce_chargement[parent] = poid_de_ce_chargement[parent] + (parents[parent][article]*nouvelle_commande[article].poids);    //Calculer le poid associé à ce parent
            }
            printf("%f", poid_de_ce_chargement[parent]);
            if (poid_de_ce_chargement[parent]>C) {  //Si le parent ne respecte pas le chargement maximal
                printf("   parent supprime");
                for (int ligne=parent; ligne<nb_parents-1 ; ligne++) {
                    for (int article=0; article<quantite_tot; article++) parents[ligne][article] = parents[ligne+1][article];   //Le parent est supprimé et les autres le remplacent dans la liste
                    poid_de_ce_chargement[ligne] = poid_de_ce_chargement[ligne+1];
                }
                for (int article=0; article<quantite_tot; article++) parents[nb_parents-1][article] = 0;
                poid_de_ce_chargement[nb_parents-parent_supprime]=0;
                parent_supprime++;
                if (parent_supprime == nb_parents-1) goto on_recommence;    //Si on n'a plus assez de parents pour continuer
            }
        }

        /**
         * @brief On remplit 'prix_de_ce_chargement' dans cette boucle en calculant le prix que représente chacun des chargements restants afin de déterminer les chargements les plus optimaux
         */
        for (int parent=0; parent<nb_parents; parent++) {
            prix_de_ce_chargement[parent] = 0;
            for (int article=0; article<quantite_tot; article++) {
                prix_de_ce_chargement[parent] = prix_de_ce_chargement[parent] + (parents[parent][article]*nouvelle_commande[article].prix);
            }
        }

        /**
         * @brief On trie ici par permutation 'prix_de_ce_chargement' afin de déterminer les pires chargements
         */
        for (int parent=1; parent<nb_parents; parent++) {
            for (int article=0; article<quantite_tot; article++) {
                prix_de_ce_chargement[parent] = prix_de_ce_chargement[parent] + (parents[parent][article]*nouvelle_commande[article].prix);
            }
            if (prix_de_ce_chargement[parent]<prix_de_ce_chargement[parent-1]) { //si l’élément est mal placé
                k=0;
                while (prix_de_ce_chargement[k]>prix_de_ce_chargement[parent]) k++; // cette boucle sort par k la nouvelle position de l’élément
                permutation_poid_chrgmt = poid_de_ce_chargement[parent];
                permutation_prix_chrgmt = prix_de_ce_chargement[parent];
                for (int article=0; article<quantite_tot; article++) permutation_objet[0] = parents[parent][article];
                for (int l=parent-1; l>=k ; l--) {
                    poid_de_ce_chargement[l+1] = poid_de_ce_chargement[l];
                    prix_de_ce_chargement[l+1] = prix_de_ce_chargement[l];
                    for (int article=0; article<quantite_tot; article++) parents[l+1][article] = parents[l][article];
                }
                poid_de_ce_chargement[k] = permutation_poid_chrgmt; // l'insertion
                prix_de_ce_chargement[k] = permutation_prix_chrgmt;
                for (int article=0; article<quantite_tot; article++) parents[k][article] = permutation_objet[article];
            }
        }

        /**
         * @brief On supprime les chargements les moins optimisés afin de n'en garder que 'nb_parents_a_garder_par_generation' 
         */
        nb_parent_restant = nb_parents - parent_supprime;
        while (nb_parent_restant > nb_parents_a_garder_par_generation) {
            for(int i=0; i<quantite_tot; i++) parents[nb_parent_restant-1][i]=0;
            poid_de_ce_chargement[nb_parent_restant]=0;
            prix_de_ce_chargement[nb_parent_restant]=0;
            nb_parent_restant--;
        }
        
        /**
         * @brief On assemble de manière aléatoire les chargements restants pour en créer de nouveaux.
         * Si les deux chargements contiennent un certain article, le chargement créé le contiendra également. Si un seul des deux le contient, il sera décidé de manière aléatoire si le chargement créé le contiendra ou pas.
         */
        while (nb_parent_restant < nb_parents) {
            parent1 = rand() %nb_parent_restant;
            parent2 = rand() %nb_parent_restant;
            for (int gene = 0; gene<quantite_tot; gene++) {
                if (parents[parent1][gene] == parents[parent2][gene]) parents[nb_parent_restant][gene] = parents[parent1][gene];
                else parents[nb_parent_restant][gene] = rand() %2;
            } 
            nb_parent_restant++;
        }
    }

    /**
     * @brief On recompose 'nouvelle_commande' à l'aide du chargement le plus optimisé déterminé par 'prix_de_ce_chargement' trié précédemment
     */
    for (int article = 0; article<quantite_tot; article++) if (parents[0][article] == 0) nouvelle_commande[article].quantité = 0;

    for (int i=0; i<quantite_tot; i++) {
        commande[i].UID=0;
        commande[i].quantité=0;
        commande[i].prix=0;
        commande[i].poids=0;
    }

    regrouper_objets_par_qtte(nouvelle_commande, &quantite_tot);

    for (int i=0; i<quantite_tot; i++) {
        commande[i].UID=nouvelle_commande[i].UID;
        commande[i].quantité=nouvelle_commande[i].quantité;
        commande[i].prix=nouvelle_commande[i].prix;
        commande[i].poids=nouvelle_commande[i].poids;
    }

    return 0;
}

/**
 * @brief Méthode de résolution par force brute. Méthode efficace pour les petits échantillons
 * Fonctionne en testant toutes les possibilités existantes pour l'échantillon donné.
 * 
 * @param C Capacité en kg du camion à remplir
 * @param nb_article Nombre d'éléments contenus dans 'commande' = le nombre de produits différents
 * @param commande Tableau de structure de produit contenant tous les produits parmis lesquels on choisira les meilleurs à commander
 * @param prix_total Prix qu'atteindra la commande du chargement final du camion
 * @return int :    Retourne 0 si tout s'est passé correctement
 */
int brute_force(float C, int nb_article, struct Produit *commande, float* prix_total) {

    printf("Methode brute force:\n");

    /**
     * @brief Afin de s'assurer de tester toutes les combinaisons possibles, nous avons matérialisé un nombre binaire avec ce tableau 'binaire' qui sera agrémenté de 1 à chaque test de chargement effectué. S'il y a un 1 à l'emplacement i, alors l'article i est compris dans le chargement; s'il y a un 0 à la place, l'article n'est pas compris dedans.
     * La première colonne correspond au chargement qui est en train d'être testé, et la deuxième, au meilleur chargement jusqu'à maintenant
     */
    int binaire[MAX_PRODUITS][2], nombre, nombre_temporaire;

    float poids_temporaire, prix_temporaire;

    int quantite_tot = 0;
    for (int i=0; i<nb_article; i++) quantite_tot += commande[i].quantité;
   
    struct Produit nouvelle_commande[quantite_tot];

    *nouvelle_commande = diviser_objets_par_qtte(commande, nouvelle_commande, nb_article, &quantite_tot);

    /**
     * @brief On parcourt les '2^quantite_tot' possibilités en incrémentant 'nombre' qui constitue 'binaire' puis on teste le chargement ainsi défini.
     * Si le prix correspondant à ce chargement est superieur au meilleur observé jusque là, ces deux données sont gardées en mémoire dans la deuxième colonne de 'binaire' et dans 'prix_total'
     */
    for (nombre = 1; nombre <= (pow(2,quantite_tot)); nombre ++) {
        nombre_temporaire = nombre;
        poids_temporaire = 0;
        prix_temporaire = 0;
        for (int i=0; i<MAX_PRODUITS; i++) binaire[i][0]=0;
        for(int i=0; nombre_temporaire > 0; i++)  {
            binaire[i][0] = nombre_temporaire%2;
            nombre_temporaire = nombre_temporaire/2;
            if (binaire[i][0]==1) {
                poids_temporaire = poids_temporaire + nouvelle_commande[i].poids;
                prix_temporaire = prix_temporaire + nouvelle_commande[i].prix;
            }
        }
        if (poids_temporaire <= C && prix_temporaire>*prix_total) {
            for (int i=0; i<quantite_tot; i++) binaire[i][1]=binaire[i][0];
            *prix_total=prix_temporaire;
        }
    }

    /**
     * @brief On recompose 'nouvelle_commande' à l'aide du chargement le plus optimisé gardé en mémoire
     */
    for (int i=0; i<quantite_tot; i++) nouvelle_commande[i].quantité = binaire[i][1];

    for (int i=0; i<quantite_tot; i++) {
        commande[i].UID=0;
        commande[i].quantité=0;
        commande[i].prix=0;
        commande[i].poids=0;
    }

    regrouper_objets_par_qtte(nouvelle_commande, &quantite_tot);

    for (int i=0; i<quantite_tot; i++) {
        commande[i].UID=nouvelle_commande[i].UID;
        commande[i].quantité=nouvelle_commande[i].quantité;
        commande[i].prix=nouvelle_commande[i].prix;
        commande[i].poids=nouvelle_commande[i].poids;
    }

    return 0;
}

/**
 * @brief Méthode de résolution par algorithme glouton. Méthode efficace pour les échantillon de petite à grande taille
 * Fonctionne en identifiant les éléments les plus optimisés par ratio prix/poids appelé ici "prix massique"
 * 
 * @param C Capacité en kg du camion à remplir
 * @param nb_article Nombre d'éléments contenus dans 'commande' = le nombre de produits différents
 * @param commande Tableau de structure de produit contenant tous les produits parmis lesquels on choisira les meilleurs à commander
 * @param prix_total Prix qu'atteindra la commande du chargement final du camion
 * @return int :    Retourne 0 si tout s'est passé correctement
 */
int gloutonne(float C, int nb_article, struct Produit *commande, float* prix_total) {
  
    printf("Methode gloutonne\n");

    /**
     * @brief On détermine ici le 'prix_massique' de chacun des objets commandés
     */
    float prix_massique[MAX_PRODUITS];
    for (int i=0; i<MAX_PRODUITS; i++) prix_massique[i]=commande[i].prix/commande[i].poids;
    
    int k;
    float permutation[5];

    /**
     * @brief On trie par permutation le tableau 'commande' en fonction du prix massique de chacun des éléments
     */
    for (int j=1; j<nb_article; j++) {
        if (prix_massique[j]>prix_massique[j-1]) { // si l’élément est mal placé
            k = 0;
            while (prix_massique[k]>prix_massique[j]) k++; // cette boucle sort par k la nouvelle position de l’élément
            permutation[0] = prix_massique[j];
            permutation[1] = commande[j].UID;
            permutation[2] = commande[j].quantité;
            permutation[3] = commande[j].prix;
            permutation[4] = commande[j].poids;
            for (int l=j-1; l>=k ; l--) {
                prix_massique[l+1] = prix_massique[l];
                commande[l+1].UID = commande[l].UID;
                commande[l+1].quantité = commande[l].quantité;
                commande[l+1].prix = commande[l].prix;
                commande[l+1].poids = commande[l].poids;
            }
            prix_massique[k] = permutation[0]; // l'insertion
            commande[k].UID = permutation[1];
            commande[k].quantité = permutation[2];
            commande[k].prix = permutation[3];
            commande[k].poids = permutation[4];
        }
    }

    int qtté = 1;
    float poids = 0;

    /**
     * @brief On détermine alors quels éléments rentreront dans le camion avant de dépasser la capacité maximale du camion selon l'ordre déterminé par 'prix_massique'. On fixe alors la quantité des autres articles à 0
     */
    for (int l=0; l<nb_article; l++) {
        poids += commande[l].poids;
        while (qtté != commande[l].quantité && (poids+commande[l].poids)<=C) {  // Tenir compte des éléments demandés en plusieurs exemplaires
            poids += commande[l].poids;
            qtté += 1;
        }
        commande[l].quantité = qtté;
        qtté = 1;
        if (poids > C){
            poids -= commande[l].poids;
            commande[l].quantité = 0;
        }
    }

    /**
     * @brief On calcule alors le prix total du chargement qu'on a formé avec cette solution
     */
    for (int m=0; m<nb_article; m++) *prix_total += (float)commande[m].quantité * commande[m].prix;

    return 0;
}

/**
 * @brief Fonction principale
 * 
 * @param entree Nom et emplacement du fichier texte transmit par le programme python dans lequel sont renseignés les articles commandés et leurs infos principales
 * @param sortie Nom et emplacement du fichier texte qui sera récupéré par le programme python dans lequel seront renseignés les articles retenus pour la commande à effectuer et leurs infos principales
 * @param C Capacité en kg du camion à remplir
 * @return int :    Retourne 0 si tout s'est passé correctement
 *                  Retourne 1 si le fichier d'entrée n'a pu s'ouvrir correctement
 *                  Retourne 2 si l'utilisateur n'a pas rentré de méthode d'utilisation existant
 *                  Retourne 3 si la resolution n'a pas pu s'effectuer correctement (problème interne à la fonction correspondant à la méthode de résolution en question)
 *                  Retourne 4 si le fichier de sortie n'a pas pu s'ouvrir correctement
 */
int main(char* entree, char* sortie, float C) {

    FILE* fichier_demande = fopen(entree,"r");
    if (!fichier_demande) {
        printf("Erreur d'ouverture du fichier d'entree\n");
        return 1;
    }

    /**
     * @brief On déclare et remplit un tableau qui répertoriera les informations contenues dans le fichier 'entree'
     */
    struct Produit commande[MAX_PRODUITS];

    /**
     * @brief On déclare un tableau de charactères (string) permettant de copier petit à petit les informations du fichier texte dans 'commande'
     */
    char string[TAILLE];
    for (int i = 0; i<TAILLE; i++) string[i] = 0;
    
    char caractère;
    int article=0, categorie=0, i=0;

    /**
     * @brief On copie petit à petit les éléments du fichier 'entree' dans 'commande'
     */
    while(!feof(fichier_demande)) {
        caractère = fgetc(fichier_demande);
        if (caractère == '\n') {
            commande[article].poids = atof(string);
            i=0;
            for(int j=0; j<TAILLE; j++) string[j]=0;
            article ++;
            categorie = 0;
        }
        else if (caractère == '/') {
            if (categorie == 0) commande[article].UID = atoi(string);
            else if (categorie == 1) commande[article].quantité = atoi(string);
            else if (categorie == 2) commande[article].prix = atof(string);
            i=0;
            for(int j=0; j<TAILLE; j++) string[j]=0;
            categorie ++;
        }
        else {
            string[i]=caractère;
            i=i+1;
        }
    }

    int methode_resolution, test;
    float prix_final = 0;

    /**
     * @brief On propose à l'utilisateur de choisir la méthode de résolution qu'il souhaite utiliser 
     */
    printf("Choisir methode de resolution:\n 1-Brute force (petit echantillon)\n 2-Methode gloutonne (moyen a grand echantillon)\n 3-Algorithme genetique (tres grand echantillon) -Pas utilisable-\n");
    scanf("%d", &methode_resolution);

    switch (methode_resolution) {
        case 1: test = brute_force(C, article, commande, &prix_final);
            break;
        case 2: test = gloutonne(C, article, commande, &prix_final);
            break;
        case 3: test = genetique(C, article, commande, &prix_final);
            break;
        default: printf("Methode de résolution inexistante, veuillez entrer 1, 2 ou 3 uniquement\n");
            return 2;
    }

    /**
     * @brief Si 'test' est différent de 0, une erreur a eu lieu pendant l'execution de la methode de resolution 
     */
    if (test != 0) {
        printf("La resolution n'a pas pu s'effectuer correctement, code d'erreur : %d", test);
        return 3;
    }

    FILE* fichier_commande = fopen(sortie,"w");
    if (!fichier_commande) {
        printf("Erreur d'ouverture du fichier de sortie\n");
        return 4;
    }

    for (int j=0; j<article; j++) fprintf(fichier_commande, "%d/%d/%f/%f\n", commande[j].UID, commande[j].quantité, commande[j].prix, commande[j].poids);
    fprintf(fichier_commande, "%f", prix_final);
    
    fclose(fichier_demande);
    fclose(fichier_commande);

    return 0;
}