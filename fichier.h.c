#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Structure pour représenter un pixel RGB */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

/* Structure pour représenter une image PPM */
typedef struct {
    char version[3];
    int largeur;
    int hauteur;
    int max_val;
    Pixel **pixels;
} ImagePPM;

/* Fonctions de gestion de base */
ImagePPM* creer_image(int largeur, int hauteur, int max_val);
void liberer_image(ImagePPM *img);
ImagePPM* charger_ppm(const char *nom_fichier);
int sauvegarder_ppm(ImagePPM *img, const char *nom_fichier);

/* Fonctions utilitaires */
void ignorer_commentaires(FILE *f);
int clamp_value(int val, int min, int max);
unsigned char calculer_mediane(unsigned char *valeurs, int n);
int comparer_uchar(const void *a, const void *b);

/* Opérations sur les images */
int operation_dominante(ImagePPM *img, char couleur, int valeur, const char *nom_fichier);
int conversion_gris(ImagePPM *img, const char *nom_fichier);
int creer_negatif(ImagePPM *img, const char *fichier_sortie);
void afficher_taille(ImagePPM *img);
int decouper_image(const char *nom_fichier, int l1, int l2, int c1, int c2, const char *fichier_sortie);
int appliquer_filtre_median(ImagePPM *img, const char *fichier_sortie);

#endif