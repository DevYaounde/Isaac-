#include <stdio.h>
#include <stdlib.h>

// ============= STRUCTURES =============

// Liste simplement chaînée
typedef struct NodeSimple {
    int data;
    struct NodeSimple* next;
} NodeSimple;

// Liste doublement chaînée
typedef struct NodeDouble {
    int data;
    struct NodeDouble* next;
    struct NodeDouble* prev;
} NodeDouble;

// ============= EXERCICE 1 =============
// Supprimer toutes les occurrences d'un élément

void supprimerOccurrences(NodeSimple** head, int valeur) {
    NodeSimple* current = *head;
    NodeSimple* prev = NULL;
    
    // Parcourir la liste
    while (current != NULL) {
        if (current->data == valeur) {
            // Cas: suppression en tête
            if (prev == NULL) {
                *head = current->next;
                free(current);
                current = *head;
            }
            // Cas: suppression au milieu ou en fin
            else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// ============= EXERCICE 2 =============
// Insertion dans liste simplement chaînée triée (ordre croissant)

void insererTrieSimple(NodeSimple** head, int valeur) {
    NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
    nouveau->data = valeur;
    nouveau->next = NULL;
    
    // Cas: liste vide ou insertion en tête
    if (*head == NULL || (*head)->data >= valeur) {
        nouveau->next = *head;
        *head = nouveau;
        return;
    }
    
    // Trouver la position d'insertion
    NodeSimple* current = *head;
    while (current->next != NULL && current->next->data < valeur) {
        current = current->next;
    }
    
    // Insertion
    nouveau->next = current->next;
    current->next = nouveau;
}

// ============= EXERCICE 3 =============
// Insertion dans liste doublement chaînée triée (ordre croissant)

void insererTrieDouble(NodeDouble** head, int valeur) {
    NodeDouble* nouveau = (NodeDouble*)malloc(sizeof(NodeDouble));
    if (nouveau == NULL) {
        printf("Erreur allocation mémoire\n");
        return;
    }
    nouveau->data = valeur;
    nouveau->next = NULL;
    nouveau->prev = NULL;
    
    // Cas: liste vide
    if (*head == NULL) {
        *head = nouveau;
        return;
    }
    
    // Cas: insertion en tête
    if ((*head)->data >= valeur) {
        nouveau->next = *head;
        (*head)->prev = nouveau;
        *head = nouveau;
        return;
    }
    
    // Trouver la position d'insertion
    NodeDouble* current = *head;
    while (current->next != NULL && current->next->data < valeur) {
        current = current->next;
    }
    
    // Insertion
    nouveau->next = current->next;
    nouveau->prev = current;
    
    if (current->next != NULL) {
        current->next->prev = nouveau;
    }
    current->next = nouveau;
}

// ============= EXERCICE 4 =============
// Insertion en tête et en queue dans liste circulaire simple

void insererTeteCirculaireSimple(NodeSimple** head, int valeur) {
    NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
    nouveau->data = valeur;
    
    // Cas: liste vide
    if (*head == NULL) {
        nouveau->next = nouveau; // Pointe vers lui-même
        *head = nouveau;
        return;
    }
    
    // Trouver le dernier nœud
    NodeSimple* dernier = *head;
    while (dernier->next != *head) {
        dernier = dernier->next;
    }
    
    // Insertion en tête
    nouveau->next = *head;
    dernier->next = nouveau;
    *head = nouveau;
}

void insererQueueCirculaireSimple(NodeSimple** head, int valeur) {
    NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
    nouveau->data = valeur;
    
    // Cas: liste vide
    if (*head == NULL) {
        nouveau->next = nouveau;
        *head = nouveau;
        return;
    }
    
    // Trouver le dernier nœud
    NodeSimple* dernier = *head;
    while (dernier->next != *head) {
        dernier = dernier->next;
    }
    
    // Insertion en queue
    nouveau->next = *head;
    dernier->next = nouveau;
}

// ============= EXERCICE 5 =============
// Insertion en tête et en queue dans liste circulaire double

void insererTeteCirculaireDouble(NodeDouble** head, int valeur) {
    NodeDouble* nouveau = (NodeDouble*)malloc(sizeof(NodeDouble));
    nouveau->data = valeur;
    
    // Cas: liste vide
    if (*head == NULL) {
        nouveau->next = nouveau;
        nouveau->prev = nouveau;
        *head = nouveau;
        return;
    }
    
    // Trouver le dernier nœud
    NodeDouble* dernier = (*head)->prev;
    
    // Insertion en tête
    nouveau->next = *head;
    nouveau->prev = dernier;
    dernier->next = nouveau;
    (*head)->prev = nouveau;
    *head = nouveau;
}

void insererQueueCirculaireDouble(NodeDouble** head, int valeur) {
    NodeDouble* nouveau = (NodeDouble*)malloc(sizeof(NodeDouble));
    nouveau->data = valeur;
    
    // Cas: liste vide
    if (*head == NULL) {
        nouveau->next = nouveau;
        nouveau->prev = nouveau;
        *head = nouveau;
        return;
    }
    
    // Trouver le dernier nœud
    NodeDouble* dernier = (*head)->prev;
    
    // Insertion en queue
    nouveau->next = *head;
    nouveau->prev = dernier;
    dernier->next = nouveau;
    (*head)->prev = nouveau;
}

// ============= FONCTIONS AUXILIAIRES =============

// Affichage liste simple
void afficherSimple(NodeSimple* head) {
    NodeSimple* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Affichage liste simple circulaire
void afficherCirculaireSimple(NodeSimple* head) {
    if (head == NULL) {
        printf("Liste vide\n");
        return;
    }
    NodeSimple* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(retour à %d)\n", head->data);
}

// Affichage liste double
void afficherDouble(NodeDouble* head) {
    NodeDouble* temp = head;
    printf("NULL <- ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" <-> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

// Affichage liste double circulaire
void afficherCirculaireDouble(NodeDouble* head) {
    if (head == NULL) {
        printf("Liste vide\n");
        return;
    }
    NodeDouble* temp = head;
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(retour à %d)\n", head->data);
}

// ============= MAIN (TESTS) =============

int main() {
    printf("1: Suppression d'occurrences \n");
    NodeSimple* liste1 = NULL;
    insererTrieSimple(&liste1, 5);
    insererTrieSimple(&liste1, 3);
    insererTrieSimple(&liste1, 5);
    insererTrieSimple(&liste1, 7);
    insererTrieSimple(&liste1, 5);
    printf("Liste avant: ");
    afficherSimple(liste1);
    supprimerOccurrences(&liste1, 5);
    printf("Liste après suppression de 5: ");
    afficherSimple(liste1);
    
    printf("\n 2: Insertion triée (simple) \n");
    NodeSimple* liste2 = NULL;
    insererTrieSimple(&liste2, 5);
    insererTrieSimple(&liste2, 2);
    insererTrieSimple(&liste2, 8);
    insererTrieSimple(&liste2, 1);
    insererTrieSimple(&liste2, 9);
    printf("Liste triée: ");
    afficherSimple(liste2);
    
    printf("\n 3: Insertion triée (double) \n");
    NodeDouble* liste3 = NULL;
    insererTrieDouble(&liste3, 5);
    insererTrieDouble(&liste3, 2);
    insererTrieDouble(&liste3, 8);
    insererTrieDouble(&liste3, 1);
    insererTrieDouble(&liste3, 9);
    printf("Liste doublement chaînée triée: ");
    afficherDouble(liste3);
    
    printf("\n 4: Liste circulaire simple \n");
    NodeSimple* listeCirc = NULL;
    insererTeteCirculaireSimple(&listeCirc, 3);
    insererQueueCirculaireSimple(&listeCirc, 5);
    insererTeteCirculaireSimple(&listeCirc, 1);
    insererQueueCirculaireSimple(&listeCirc, 7);
    printf("Liste circulaire simple: ");
    afficherCirculaireSimple(listeCirc);
    
    printf("\n 5: Liste circulaire double \n");
    NodeDouble* listeCircDouble = NULL;
    insererTeteCirculaireDouble(&listeCircDouble, 3);
    insererQueueCirculaireDouble(&listeCircDouble, 5);
    insererTeteCirculaireDouble(&listeCircDouble, 1);
    insererQueueCirculaireDouble(&listeCircDouble, 7);
    printf("Liste circulaire double: ");
    afficherCirculaireDouble(listeCircDouble);
    
    return 0;
}