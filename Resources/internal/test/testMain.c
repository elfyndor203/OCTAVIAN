#include "image/image.h"
#include <stdio.h>

int main() {
	OCT_image image = OCT_image_loadPNG("C:/Users/haex4/MyDocuments/Projects/OCTAVIAN/Resources/internal/test/grey.png");
	for (int i = 0; i < 1000; i++) {
		printf("%d ", image.pixels[i]);
	}
	return 0;
}