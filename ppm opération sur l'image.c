#include "ppm.h"

// Fonction pour limiter une valeur entre min et max
int clamp(int val, int min, int max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

// Fonction pour calculer la médiane
int comparer(const void *a, const void *b) {
    return (*(unsigned char*)a - *(unsigned char*)b);
}

unsigned char mediane(unsigned char *valeurs, int n) {
    qsort(valeurs, n, sizeof(unsigned char), comparer);
    return valeurs[n / 2];
}

// Afficher la taille d'une image
void afficher_taille(ImagePPM *img) {
    if (img) {
        printf("%d x %d\n", img->largeur, img->hauteur);
    }
}

// Opération dominante : foncer ou éclaircir les pixels avec dominante
int dominante(ImagePPM *img, char couleur, int valeur, const char *nom_fichier) {
    if (!img) return 0;
    
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel *p = &img->pixels[i][j];
            int dominant = 0;
            
            // Déterminer la couleur dominante
            if (couleur == 'R' && p->r >= p->g && p->r >= p->b) {
                dominant = 1;
            } else if (couleur == 'G' && p->g >= p->r && p->g >= p->b) {
                dominant = 1;
            } else if (couleur == 'B' && p->b >= p->r && p->b >= p->g) {
                dominant = 1;
            }
            
            // Appliquer la modification si le pixel a la dominante
            if (dominant) {
                p->r = clamp(p->r + valeur, 0, img->max_val);
                p->g = clamp(p->g + valeur, 0, img->max_val);
                p->b = clamp(p->b + valeur, 0, img->max_val);
            }
        }
    }
    
    // Générer le nom du fichier de sortie
    char fichier_sortie[512];
    char *point = strrchr(nom_fichier, '.');
    if (point) {
        int len = point - nom_fichier;
        strncpy(fichier_sortie, nom_fichier, len);
        fichier_sortie[len] = '\0';
        strcat(fichier_sortie, "_dom.ppm");
    } else {
        sprintf(fichier_sortie, "%s_dom.ppm", nom_fichier);
    }
    
    if (sauvegarder_ppm(img, fichier_sortie)) {
        printf("opération effectuée ; %s créé\n", fichier_sortie);
        return 1;
    }
    return 0;
}

// Convertir en niveaux de gris
int gris(ImagePPM *img, const char *nom_fichier) {
    if (!img) return 0;
    
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel *p = &img->pixels[i][j];
            unsigned char moyenne = (p->r + p->g + p->b) / 3;
            p->r = p->g = p->b = moyenne;
        }
    }
    
    // Générer le nom du fichier de sortie
    char fichier_sortie[512];
    char *point = strrchr(nom_fichier, '.');
    if (point) {
        int len = point - nom_fichier;
        strncpy(fichier_sortie, nom_fichier, len);
        fichier_sortie[len] = '\0';
        strcat(fichier_sortie, "_gris.ppm");
    } else {
        sprintf(fichier_sortie, "%s_gris.ppm", nom_fichier);
    }
    
    if (sauvegarder_ppm(img, fichier_sortie)) {
        printf("opération effectuée ; %s créé\n", fichier_sortie);
        return 1;
    }
    return 0;
}

// Créer le négatif d'une image
int negatif(ImagePPM *img, const char *fichier_sortie) {
    if (!img) return 0;
    
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel *p = &img->pixels[i][j];
            p->r = img->max_val - p->r;
            p->g = img->max_val - p->g;
            p->b = img->max_val - p->b;
        }
    }
    
    if (sauvegarder_ppm(img, fichier_sortie)) {
        printf("opération effectuée\n");
        return 1;
    }
    return 0;
}

// Découper une partie de l'image
int decouper(const char *nom_fichier, int l1, int l2, int c1, int c2, const char *fichier_sortie) {
    ImagePPM *img = charger_ppm(nom_fichier);
    if (!img) return 0;
    
    // Vérifier les paramètres
    if (l1 < 0 || l2 > img->hauteur || l1 >= l2 || 
        c1 < 0 || c2 > img->largeur || c1 >= c2) {
        printf("Paramètres de découpe invalides\n");
        liberer_image(img);
        return 0;
    }
    
    // Créer la nouvelle image
    int nouvelle_hauteur = l2 - l1;
    int nouvelle_largeur = c2 - c1;
    ImagePPM *img_decoupee = creer_image(nouvelle_largeur, nouvelle_hauteur, img->max_val);
    
    if (!img_decoupee) {
        liberer_image(img);
        return 0;
    }
    
    // Copier les pixels
    for (int i = 0; i < nouvelle_hauteur; i++) {
        for (int j = 0; j < nouvelle_largeur; j++) {
            img_decoupee->pixels[i][j] = img->pixels[l1 + i][c1 + j];
        }
    }
    
    int resultat = sauvegarder_ppm(img_decoupee, fichier_sortie);
    
    liberer_image(img);
    liberer_image(img_decoupee);
    
    if (resultat) {
        printf("opération effectuée\n");
        return 1;
    }
    return 0;
}

// Appliquer le filtre médian
int filtre_median(ImagePPM *img, const char *fichier_sortie) {
    if (!img) return 0;
    
    ImagePPM *img_filtree = creer_image(img->largeur, img->hauteur, img->max_val);
    if (!img_filtree) return 0;
    
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            unsigned char valeurs_r[9], valeurs_g[9], valeurs_b[9];
            int count = 0;
            
            // Parcourir le voisinage 3x3
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    
                    // Vérifier les limites
                    if (ni >= 0 && ni < img->hauteur && nj >= 0 && nj < img->largeur) {
                        valeurs_r[count] = img->pixels[ni][nj].r;
                        valeurs_g[count] = img->pixels[ni][nj].g;
                        valeurs_b[count] = img->pixels[ni][nj].b;
                        count++;
                    }
                }
            }
            
            // Appliquer la médiane
            img_filtree->pixels[i][j].r = mediane(valeurs_r, count);
            img_filtree->pixels[i][j].g = mediane(valeurs_g, count);
            img_filtree->pixels[i][j].b = mediane(valeurs_b, count);
        }
    }
    
    int resultat = sauvegarder_ppm(img_filtree, fichier_sortie);
    liberer_image(img_filtree);
    
    if (resultat) {
        printf("opération effectuée\n");
        return 1;
    }
    return 0;
}