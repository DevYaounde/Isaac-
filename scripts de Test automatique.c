#!/bin/bash

# Script de test pour le projet PPM Viewer
# Ce script teste toutes les fonctionnalités du programme

echo "====================================="
echo "Tests du projet PPM Viewer"
echo "====================================="
echo ""

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Compteurs
TESTS_PASSED=0
TESTS_FAILED=0

# Fonction pour afficher le résultat d'un test
check_result() {
    if [ $1 -eq 0 ] && [ -f "$2" ]; then
        echo -e "${GREEN}✓ PASS${NC} - $3"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC} - $3"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
}

# Vérifier que le programme existe
if [ ! -f "./ppmviewer" ]; then
    echo "Erreur : ppmviewer n'existe pas. Compilez d'abord avec 'make'."
    exit 1
fi

# Créer une image de test
echo "Création de l'image de test..."
cat > test_auto.ppm << EOF
P3
# Image de test automatique
4 4
255
255 0 0  0 255 0  0 0 255  255 255 0
255 0 255  0 255 255  128 128 128  255 255 255
100 50 25  200 150 100  50 100 150  75 75 200
0 0 0  64 64 64  128 128 128  192 192 192
EOF

echo "Image de test créée : test_auto.ppm"
echo ""

# Test 1 : Afficher la taille
echo "Test 1 : Affichage de la taille"
echo "size test_auto.ppm" | ./ppmviewer > /dev/null 2>&1
check_result $? "test_auto.ppm" "Affichage de la taille"
echo ""

# Test 2 : Dominante rouge (foncer)
echo "Test 2 : Dominante rouge (foncer +50)"
echo "dom R 50 test_auto.ppm
quit" | ./ppmviewer > /dev/null 2>&1
check_result $? "test_auto_dom.ppm" "Dominante rouge +50"
echo ""

# Test 3 : Dominante bleue (éclaircir)
echo "Test 3 : Dominante bleue (éclaircir -30)"
echo "dom B -30 test_auto.ppm
quit" | ./ppmviewer > /dev/null 2>&1
check_result $? "test_auto_dom.ppm" "Dominante bleue -30"
echo ""

# Test 4 : Conversion en gris
echo "Test 4 : Conversion en niveaux de gris"
echo "gris test_auto.ppm
quit" | ./ppmviewer > /dev/null 2>&1
check_result