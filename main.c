#include <stdio.h>
#include <zbar.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
zbar_image_scanner_t *scanner = NULL;

int main(int argc, char const *argv[])
{
	if(argc < 2) 
		{
			printf("usage: %s imageName\n", argv[0]);
			return(1);
		}
	const char *inputFile = argv[1];

	int w, h, n;
	unsigned char *data = stbi_load(inputFile, &w, &h, &n, 0);
	printf("%d, %d, %d\n", w, h, n);


	/* create a reader */
    scanner = zbar_image_scanner_create();

    /* configure the reader */
    zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);


    // /* wrap image data */
    zbar_image_t *image = zbar_image_create();
    // zbar_image_set_format(image, *(int*)"GREY");
    zbar_image_set_format(image, *(int*)"Y800");
    zbar_image_set_size(image, w, h);
    zbar_image_set_data(image, data, w * h, zbar_image_free_data);


    // /* scan the image for barcodes */
    int num = zbar_scan_image(scanner, image);

    // /* extract results */
    const zbar_symbol_t *symbol = zbar_image_first_symbol(image);
    for(; symbol; symbol = zbar_symbol_next(symbol)) {
        /* do something useful with results */
        zbar_symbol_type_t typ = zbar_symbol_get_type(symbol);
        const char *results = zbar_symbol_get_data(symbol);
        printf("decoded %s symbol \"%s\"\n",
               zbar_get_symbol_name(typ), results);
    }

    /* clean up */
    // zbar_image_destroy(image);
    zbar_image_scanner_destroy(scanner);


	// for(int j = 0; j < h; j++){
	// 	for(int i = 0; i < w; i++)
	// 	{	
	// 		printf("%d \n", data[j*w + i]);
	// 		if(j > h/2 && i > w/2)
	// 		{
	// 			data[j*w + i] = 255;
	// 		}
	// 	}
	// 	printf("\n");
	// }

	// stbi_write_png("write.png", w, h, n, data, w * 1);
	stbi_image_free(data);
	return 0;
}