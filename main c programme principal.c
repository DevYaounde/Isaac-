#include "ppm.h"

void afficher_aide() {
    printf("\nCommandes disponibles :\n");
    printf("  size fichier.ppm                              - Afficher la taille\n");
    printf("  dom C val fichier.ppm                         - Modifier dominante (C=R/G/B)\n");
    printf("  gris fichier.ppm                              - Convertir en gris\n");
    printf("  neg fichier.ppm fichier_sortie.ppm            - Créer le négatif\n");
    printf("  cut fichier.ppm l1 l2 c1 c2 fichier_sortie.ppm - Découper l'image\n");
    printf("  fil fichier.ppm fichier_sortie.ppm            - Filtre médian\n");
    printf("  help                                          - Afficher cette aide\n");
    printf("  quit                                          - Quitter\n\n");
}

int main() {
    char commande[1024];
    char cmd[50];
    
    printf("Application de traitement d'images PPM réalisée par [Votre Nom].\n");
    
    while (1) {
        printf("ppmviewer > ");
        fflush(stdout);
        
        if (!fgets(commande, sizeof(commande), stdin)) {
            break;
        }
        
        // Supprimer le saut de ligne
        commande[strcspn(commande, "\n")] = 0;
        
        // Ignorer les lignes vides
        if (strlen(commande) == 0) {
            continue;
        }
        
        // Extraire la première commande
        sscanf(commande, "%s", cmd);
        
        // Commande quit
        if (strcmp(cmd, "quit") == 0) {
            break;
        }
        
        // Commande help
        else if (strcmp(cmd, "help") == 0) {
            afficher_aide();
        }
        
        // Commande size
        else if (strcmp(cmd, "size") == 0) {
            char fichier[512];
            if (sscanf(commande, "%s %s", cmd, fichier) == 2) {
                ImagePPM *img = charger_ppm(fichier);
                if (img) {
                    afficher_taille(img);
                    liberer_image(img);
                }
            } else {
                printf("Usage: size fichier.ppm\n");
            }
        }
        
        // Commande dom
        else if (strcmp(cmd, "dom") == 0) {
            char couleur;
            int valeur;
            char fichier[512];
            
            if (sscanf(commande, "%s %c %d %s", cmd, &couleur, &valeur, fichier) == 4) {
                if (couleur != 'R' && couleur != 'G' && couleur != 'B') {
                    printf("Couleur invalide. Utilisez R, G ou B.\n");
                    continue;
                }
                
                ImagePPM *img = charger_ppm(fichier);
                if (img) {
                    dominante(img, couleur, valeur, fichier);
                    liberer_image(img);
                }
            } else {
                printf("Usage: dom C val fichier.ppm (C=R/G/B, val=entier)\n");
            }
        }
        
        // Commande gris
        else if (strcmp(cmd, "gris") == 0) {
            char fichier[512];
            if (sscanf(commande, "%s %s", cmd, fichier) == 2) {
                ImagePPM *img = charger_ppm(fichier);
                if (img) {
                    gris(img, fichier);
                    liberer_image(img);
                }
            } else {
                printf("Usage: gris fichier.ppm\n");
            }
        }
        
        // Commande neg
        else if (strcmp(cmd, "neg") == 0) {
            char fichier[512], fichier_sortie[512];
            if (sscanf(commande, "%s %s %s", cmd, fichier, fichier_sortie) == 3) {
                ImagePPM *img = charger_ppm(fichier);
                if (img) {
                    negatif(img, fichier_sortie);
                    liberer_image(img);
                }
            } else {
                printf("Usage: neg fichier.ppm fichier_sortie.ppm\n");
            }
        }
        
        // Commande cut
        else if (strcmp(cmd, "cut") == 0) {
            char fichier[512], fichier_sortie[512];
            int l1, l2, c1, c2;
            
            if (sscanf(commande, "%s %s %d %d %d %d %s", 
                      cmd, fichier, &l1, &l2, &c1, &c2, fichier_sortie) == 7) {
                decouper(fichier, l1, l2, c1, c2, fichier_sortie);
            } else {
                printf("Usage: cut fichier.ppm l1 l2 c1 c2 fichier_sortie.ppm\n");
            }
        }
        
        // Commande fil
        else if (strcmp(cmd, "fil") == 0) {
            char fichier[512], fichier_sortie[512];
            if (sscanf(commande, "%s %s %s", cmd, fichier, fichier_sortie) == 3) {
                ImagePPM *img = charger_ppm(fichier);
                if (img) {
                    filtre_median(img, fichier_sortie);
                    liberer_image(img);
                }
            } else {
                printf("Usage: fil fichier.ppm fichier_sortie.ppm\n");
            }
        }
        
        // Commande inconnue
        else {
            printf("Commande inconnue. Tapez 'help' pour l'aide.\n");
        }
    }
    
    return 0;
}