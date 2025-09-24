#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

// Fonction utilitaire pour afficher une matrice
void afficherMatrice(int mat[][MAX_SIZE], int lignes, int colonnes) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("\n");
    }
}

// Fonction utilitaire pour afficher un tableau
void afficherTableau(int tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

// 1. Somme de matrices
void sommeMatrices(int mat1[][MAX_SIZE], int mat2[][MAX_SIZE], int resultat[][MAX_SIZE], int lignes, int colonnes) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            resultat[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

// 2. Produit de matrices
bool produitMatrices(int mat1[][MAX_SIZE], int mat2[][MAX_SIZE], int resultat[][MAX_SIZE], 
                     int l1, int c1, int l2, int c2) {
    if (c1 != l2) {
        printf("Erreur : Impossible de multiplier les matrices (dimensions incompatibles)\n");
        return false;
    }
    
    // Initialisation du résultat à 0
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < c2; j++) {
            resultat[i][j] = 0;
        }
    }
    
    // Calcul du produit
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                resultat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return true;
}

// 3. Recherche séquentielle dans un tableau
int rechercheSequentielle(int tab[], int taille, int element) {
    for (int i = 0; i < taille; i++) {
        if (tab[i] == element) {
            return i; // Retourne l'index de l'élément
        }
    }
    return -1; // Élément non trouvé
}

// 4. Multiplication a × b en utilisant uniquement + 1 (pour a,b > 0)
int multiplication(int a, int b) {
    if (a <= 0 || b <= 0) {
        printf("Erreur : a et b doivent être positifs\n");
        return -1;
    }
    
    int resultat = 0;
    int compteur = 0;
    
    // Ajouter 'a' exactement 'b' fois
    while (compteur < b) {
        resultat = resultat + a;
        compteur = compteur + 1;
    }
    
    return resultat;
}

// 5. Tester si un tableau est trié
bool estTrie(int tab[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        if (tab[i] > tab[i + 1]) {
            return false;
        }
    }
    return true;
}

// 6. Trouver la médiane dans un tableau (suppose le tableau trié)
double mediane(int tab[], int taille) {
    if (taille % 2 == 1) {
        // Nombre impair d'éléments
        return tab[taille / 2];
    } else {
        // Nombre pair d'éléments
        return (tab[taille / 2 - 1] + tab[taille / 2]) / 2.0;
    }
}

// Fonction de tri à bulles pour trier avant de calculer la médiane
void triBulles(int tab[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

// 7. Inverser un tableau
void inverserTableau(int tab[], int taille) {
    for (int i = 0; i < taille / 2; i++) {
        int temp = tab[i];
        tab[i] = tab[taille - 1 - i];
        tab[taille - 1 - i] = temp;
    }
}

// 8. Produit vectoriel (pour vecteurs 3D)
void produitVectoriel(int v1[], int v2[], int resultat[]) {
    resultat[0] = v1[1] * v2[2] - v1[2] * v2[1];
    resultat[1] = v1[2] * v2[0] - v1[0] * v2[2];
    resultat[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

// 9. Produit vecteur × matrice
void produitVecteurMatrice(int vecteur[], int matrice[][MAX_SIZE], int resultat[], int tailleVecteur, int colonnes) {
    for (int j = 0; j < colonnes; j++) {
        resultat[j] = 0;
        for (int i = 0; i < tailleVecteur; i++) {
            resultat[j] += vecteur[i] * matrice[i][j];
        }
    }
}

// Fonction principale avec menu interactif
int main() {
    int choix;
    
    do {
        printf("\n STRUCTURES DE DONNEES  \n");
        printf("1. Somme de matrices\n");
        printf("2. Produit de matrices\n");
        printf("3. Recherche séquentielle\n");
        printf("4. Multiplication a × b (avec + et 1)\n");
        printf("5. Tester si tableau trié\n");
        printf("6. Médiane d'un tableau\n");
        printf("7. Inverser un tableau\n");
        printf("8. Produit vectoriel\n");
        printf("9. Produit vecteur × matrice\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        
        switch(choix) {
            case 1: {
                printf("\n--- Somme de matrices ---\n");
                int mat1[MAX_SIZE][MAX_SIZE] = {{1, 2}, {3, 4}};
                int mat2[MAX_SIZE][MAX_SIZE] = {{5, 6}, {7, 8}};
                int resultat[MAX_SIZE][MAX_SIZE];
                
                printf("Matrice 1:\n");
                afficherMatrice(mat1, 2, 2);
                printf("Matrice 2:\n");
                afficherMatrice(mat2, 2, 2);
                
                sommeMatrices(mat1, mat2, resultat, 2, 2);
                printf("Somme:\n");
                afficherMatrice(resultat, 2, 2);
                break;
            }
            
            case 2: {
                printf("\n--- Produit de matrices ---\n");
                int mat1[MAX_SIZE][MAX_SIZE] = {{1, 2, 3}, {4, 5, 6}};
                int mat2[MAX_SIZE][MAX_SIZE] = {{7, 8}, {9, 10}, {11, 12}};
                int resultat[MAX_SIZE][MAX_SIZE];
                
                printf("Matrice 1 (2x3):\n");
                afficherMatrice(mat1, 2, 3);
                printf("Matrice 2 (3x2):\n");
                afficherMatrice(mat2, 3, 2);
                
                if (produitMatrices(mat1, mat2, resultat, 2, 3, 3, 2)) {
                    printf("Produit (2x2):\n");
                    afficherMatrice(resultat, 2, 2);
                }
                break;
            }
            
            case 3: {
                printf("\n--- Recherche séquentielle ---\n");
                int tab[] = {10, 25, 3, 8, 15, 7, 20};
                int taille = 7;
                int element;
                
                printf("Tableau: ");
                afficherTableau(tab, taille);
                printf("Élément à rechercher: ");
                scanf("%d", &element);
                
                int index = rechercheSequentielle(tab, taille, element);
                if (index != -1) {
                    printf("Élément trouvé à l'index %d\n", index);
                } else {
                    printf("Élément non trouvé\n");
                }
                break;
            }
            
            case 4: {
                printf("\n--- Multiplication a × b ---\n");
                int a, b;
                printf("Entrez a (> 0): ");
                scanf("%d", &a);
                printf("Entrez b (> 0): ");
                scanf("%d", &b);
                
                int resultat = multiplication(a, b);
                if (resultat != -1) {
                    printf("%d × %d = %d\n", a, b, resultat);
                }
                break;
            }
            
            case 5: {
                printf("\n--- Test si tableau trié ---\n");
                int tab1[] = {1, 3, 5, 7, 9};
                int tab2[] = {5, 2, 8, 1, 9};
                
                printf("Tableau 1: ");
                afficherTableau(tab1, 5);
                printf("Est trié: %s\n", estTrie(tab1, 5) ? "Oui" : "Non");
                
                printf("Tableau 2: ");
                afficherTableau(tab2, 5);
                printf("Est trié: %s\n", estTrie(tab2, 5) ? "Oui" : "Non");
                break;
            }
            
            case 6: {
                printf("\n--- Médiane d'un tableau ---\n");
                int tab[] = {7, 3, 1, 9, 5, 2, 8};
                int taille = 7;
                
                printf("Tableau original: ");
                afficherTableau(tab, taille);
                
                triBulles(tab, taille);
                printf("Tableau trié: ");
                afficherTableau(tab, taille);
                
                double med = mediane(tab, taille);
                printf("Médiane: %.1f\n", med);
                break;
            }
            
            case 7: {
                printf("\n--- Inverser un tableau ---\n");
                int tab[] = {1, 2, 3, 4, 5, 6};
                int taille = 6;
                
                printf("Tableau original: ");
                afficherTableau(tab, taille);
                
                inverserTableau(tab, taille);
                printf("Tableau inversé: ");
                afficherTableau(tab, taille);
                break;
            }
            
            case 8: {
                printf("\n--- Produit vectoriel ---\n");
                int v1[] = {2, 3, 4};
                int v2[] = {5, 6, 7};
                int resultat[3];
                
                printf("Vecteur 1: [%d, %d, %d]\n", v1[0], v1[1], v1[2]);
                printf("Vecteur 2: [%d, %d, %d]\n", v2[0], v2[1], v2[2]);
                
                produitVectoriel(v1, v2, resultat);
                printf("Produit vectoriel: [%d, %d, %d]\n", resultat[0], resultat[1], resultat[2]);
                break;
            }
            
            case 9: {
                printf("\n--- Produit vecteur × matrice ---\n");
                int vecteur[] = {2, 3};
                int matrice[MAX_SIZE][MAX_SIZE] = {{1, 4, 7}, {2, 5, 8}};
                int resultat[MAX_SIZE];
                
                printf("Vecteur: [%d, %d]\n", vecteur[0], vecteur[1]);
                printf("Matrice (2x3):\n");
                afficherMatrice(matrice, 2, 3);
                
                produitVecteurMatrice(vecteur, matrice, resultat, 2, 3);
                printf("Résultat: [%d, %d, %d]\n", resultat[0], resultat[1], resultat[2]);
                break;
            }
            
            case 0:
                printf("Au revoir!\n");
                break;
                
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);
    
    return 0;
}