CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = ppmviewer
OBJS = main.o ppm_io.o ppm_operations.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c ppm.h
	$(CC) $(CFLAGS) -c main.c

ppm_io.o: ppm_io.c ppm.h
	$(CC) $(CFLAGS) -c ppm_io.c

ppm_operations.o: ppm_operations.c ppm.h
	$(CC) $(CFLAGS) -c ppm_operations.c

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe *.o

test: $(TARGET)
	@echo "Création d'une image de test..."
	@echo "P3" > test.ppm
	@echo "# Image de test" >> test.ppm
	@echo "4 4" >> test.ppm
	@echo "255" >> test.ppm
	@echo "255 0 0  0 255 0  0 0 255  255 255 0" >> test.ppm
	@echo "255 0 255  0 255 255  128 128 128  255 255 255" >> test.ppm
	@echo "100 50 25  200 150 100  50 100 150  75 75 200" >> test.ppm
	@echo "0 0 0  64 64 64  128 128 128  192 192 192" >> test.ppm
	@echo "Image de test créée : test.ppm"

.PHONY: all clean test