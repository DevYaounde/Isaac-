#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int width;
    int height;
    int maxval;
    unsigned char *data; // RGB data
} PPMImage;

// Prototypes
PPMImage* load_ppm(const char *filename);
int save_ppm(const char *filename, PPMImage *img);
void free_ppm(PPMImage *img);
void cmd_size(const char *filename);
void cmd_cut(const char *input, int x1, int x2, int y1, int y2, const char *output);
void cmd_dom(char channel, int level, const char *input);
void cmd_neg(const char *input, const char *output);
void cmd_gris(const char *input);
void cmd_fil(const char *input, const char *output);

// Charge une image PPM (format P6)
PPMImage* load_ppm(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("fichier non trouvé\n");
        return NULL;
    }

    PPMImage *img = (PPMImage*)malloc(sizeof(PPMImage));
    char format[3];
    
    fscanf(fp, "%s", format);
    if (strcmp(format, "P6") != 0) {
        printf("Format non supporté (seulement P6)\n");
        fclose(fp);
        free(img);
        return NULL;
    }

    // Ignorer les commentaires
    char c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n');
        c = getc(fp);
    }
    ungetc(c, fp);

    fscanf(fp, "%d %d", &img->width, &img->height);
    fscanf(fp, "%d", &img->maxval);
    getc(fp); // Lire le dernier '\n'

    int size = img->width * img->height * 3;
    img->data = (unsigned char*)malloc(size);
    fread(img->data, 1, size, fp);

    fclose(fp);
    return img;
}

// Sauvegarde une image PPM
int save_ppm(const char *filename, PPMImage *img) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Erreur d'écriture\n");
        return 0;
    }

    fprintf(fp, "P6\n%d %d\n%d\n", img->width, img->height, img->maxval);
    fwrite(img->data, 1, img->width * img->height * 3, fp);
    fclose(fp);
    return 1;
}

void free_ppm(PPMImage *img) {
    if (img) {
        if (img->data) free(img->data);
        free(img);
    }
}

// Commande: size
void cmd_size(const char *filename) {
    PPMImage *img = load_ppm(filename);
    if (img) {
        printf("%d x %d\n", img->width, img->height);
        free_ppm(img);
    }
}

// Commande: cut (découpe une région)
void cmd_cut(const char *input, int x1, int x2, int y1, int y2, const char *output) {
    PPMImage *img = load_ppm(input);
    if (!img) return;

    int new_width = x2 - x1 + 1;
    int new_height = y2 - y1 + 1;

    PPMImage *new_img = (PPMImage*)malloc(sizeof(PPMImage));
    new_img->width = new_width;
    new_img->height = new_height;
    new_img->maxval = img->maxval;
    new_img->data = (unsigned char*)malloc(new_width * new_height * 3);

    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int src_idx = ((y + y1 - 1) * img->width + (x + x1 - 1)) * 3;
            int dst_idx = (y * new_width + x) * 3;
            new_img->data[dst_idx] = img->data[src_idx];
            new_img->data[dst_idx + 1] = img->data[src_idx + 1];
            new_img->data[dst_idx + 2] = img->data[src_idx + 2];
        }
    }

    if (save_ppm(output, new_img)) {
        printf("opération effectuée\n");
    }

    free_ppm(img);
    free_ppm(new_img);
}

// Commande: dom (couleur dominante)
void cmd_dom(char channel, int level, const char *input) {
    PPMImage *img = load_ppm(input);
    if (!img) return;

    int channel_idx = (channel == 'R' || channel == 'r') ? 0 : 
                      (channel == 'G' || channel == 'g') ? 1 : 2;

    int step = 256 / level;

    for (int i = 0; i < img->width * img->height * 3; i += 3) {
        int val = img->data[i + channel_idx];
        img->data[i + channel_idx] = (val / step) * step;
    }

    // Créer le nom de fichier de sortie
    char output[256];
    strcpy(output, input);
    char *ext = strrchr(output, '.');
    if (ext) {
        strcpy(ext, "_dom.ppm");
    } else {
        strcat(output, "_dom.ppm");
    }

    if (save_ppm(output, img)) {
        printf("opération effectuée ; %s créé\n", output);
    }

    free_ppm(img);
}

// Commande: neg (négatif)
void cmd_neg(const char *input, const char *output) {
    PPMImage *img = load_ppm(input);
    if (!img) return;

    for (int i = 0; i < img->width * img->height * 3; i++) {
        img->data[i] = img->maxval - img->data[i];
    }

    if (save_ppm(output, img)) {
        printf("opération effectuée\n");
    }

    free_ppm(img);
}

// Commande: gris (conversion en niveaux de gris)
void cmd_gris(const char *input) {
    PPMImage *img = load_ppm(input);
    if (!img) return;

    for (int i = 0; i < img->width * img->height * 3; i += 3) {
        int gray = (img->data[i] + img->data[i + 1] + img->data[i + 2]) / 3;
        img->data[i] = img->data[i + 1] = img->data[i + 2] = gray;
    }

    // Créer le nom de fichier de sortie
    char output[256];
    strcpy(output, input);
    char *ext = strrchr(output, '.');
    if (ext) {
        strcpy(ext, "_gris.ppm");
    } else {
        strcat(output, "_gris.ppm");
    }

    if (save_ppm(output, img)) {
        printf("opération effectuée ; %s créé\n", output);
    }

    free_ppm(img);
}

// Commande: fil (filtre de flou)
void cmd_fil(const char *input, const char *output) {
    PPMImage *img = load_ppm(input);
    if (!img) return;

    PPMImage *new_img = (PPMImage*)malloc(sizeof(PPMImage));
    new_img->width = img->width;
    new_img->height = img->height;
    new_img->maxval = img->maxval;
    new_img->data = (unsigned char*)malloc(img->width * img->height * 3);

    // Filtre moyenneur 3x3
    for (int y = 1; y < img->height - 1; y++) {
        for (int x = 1; x < img->width - 1; x++) {
            for (int c = 0; c < 3; c++) {
                int sum = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int idx = ((y + dy) * img->width + (x + dx)) * 3 + c;
                        sum += img->data[idx];
                    }
                }
                int idx = (y * img->width + x) * 3 + c;
                new_img->data[idx] = sum / 9;
            }
        }
    }

    // Copier les bords
    for (int x = 0; x < img->width; x++) {
        for (int c = 0; c < 3; c++) {
            new_img->data[x * 3 + c] = img->data[x * 3 + c];
            new_img->data[((img->height - 1) * img->width + x) * 3 + c] = 
                img->data[((img->height - 1) * img->width + x) * 3 + c];
        }
    }
    for (int y = 0; y < img->height; y++) {
        for (int c = 0; c < 3; c++) {
            new_img->data[(y * img->width) * 3 + c] = img->data[(y * img->width) * 3 + c];
            new_img->data[(y * img->width + img->width - 1) * 3 + c] = 
                img->data[(y * img->width + img->width - 1) * 3 + c];
        }
    }

    if (save_ppm(output, new_img)) {
        printf("opération effectuée\n");
    }

    free_ppm(img);
    free_ppm(new_img);
}

int main() {
    printf("PPM Viewer - Test des commandes\n\n");

    // Test 1: size
    printf("ppmviewer > size image1.ppm\n");
    cmd_size("image1.ppm");

    // Test 2: cut
    printf("ppmviewer > cut image1.ppm 1 50 1 100 ..\\mesimages\\image2.ppm\n");
    cmd_cut("image1.ppm", 1, 50, 1, 100, "../mesimages/image2.ppm");

    // Test 3: dom (échec attendu)
    printf("ppmviewer > dom R 4 image2.ppm\n");
    cmd_dom('R', 4, "image2.ppm");

    // Test 4: dom (succès)
    printf("ppmviewer > dom R 4 ..\\mesimages\\image2.ppm\n");
    cmd_dom('R', 4, "../mesimages/image2.ppm");

    // Test 5: neg
    printf("ppmviewer > neg image1.ppm image3.ppm\n");
    cmd_neg("image1.ppm", "image3.ppm");

    // Test 6: gris
    printf("ppmviewer > gris image3.ppm\n");
    cmd_gris("image3.ppm");

    // Test 7: fil
    printf("ppmviewer > fil image3_gris.ppm image4.ppm\n");
    cmd_fil("image3_gris.ppm", "image4.ppm");

    printf("ppmviewer > quit\n");
    return 0;
}