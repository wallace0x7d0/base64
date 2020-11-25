#include <stdio.h>
#include <string.h>
#include <stdint.h>

char base64table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64encode(char text[], int size);
void base64decode(char text[], int size);

int main(int argc, char **argv){

	printf("=========================================================\n");
	printf("=                                                       =\n");
	printf("=                 BASE64 ENCODE/DECODE                  =\n");
	printf("=                                                       =\n");
	printf("=========================================================\n\n");

	while(1){
		printf("1 - ENCODE\n");
		printf("2 - DECODE\n\n");

		int  option;
		char buffer[1000];
		scanf("%i", &option);
        while (getchar() != '\n');

		switch(option){
			case 1:
				printf("Type the text to be encoded: ");
				fgets(buffer, sizeof(buffer), stdin);

				base64encode(buffer, strlen(buffer) - 1);
				break;
			case 2:
				printf("Type the text to be decoded: ");
				fgets(buffer, sizeof(buffer), stdin);

				base64decode(buffer, strlen(buffer) - 1);
				break;
		}
	}
	
	return 0;
}


void base64encode(char text[], int size){
	for (int i = 0; i < size; i+=3){
		uint8_t a = text[i];
		uint8_t b = text[i+1];
		uint8_t c = text[i+2];

		char b64[4];
		b64[0] = base64table[((a & 0xFC) >> 2)];
		b64[1] = base64table[((a & 0x03) << 4 | (b & 0xF0) >> 4)];
		b64[2] = base64table[((b & 0x0F) << 2 | (c & 0xC0) >> 6)];
		b64[3] = base64table[((c & 0x3F))];

		printf("%c%c", b64[0], b64[1]);

		if(size - i == 1){
			printf("==");

		}else if(size - i == 2){
			printf("%c%c", b64[2]);
			printf("=");

		}else {
			printf("%c%c", b64[2], b64[3]);

		}

	}

    printf("\n\n");
}

void base64decode(char text[], int size){
    for (int i = 0; i < size; i+=4){
        uint8_t a = strchr(base64table, text[i]) - base64table;
        uint8_t b = strchr(base64table, text[i+1]) - base64table;
        uint8_t c = strchr(base64table, text[i+2]) - base64table;
        uint8_t d = strchr(base64table, text[i+3]) - base64table;

        if(text[i+2] == '='){
            c = 0;

        }

        if(text[i+3] == '='){
            d = 0;

        }

        char b64[3];
        b64[0] = (a << 2) | (b >> 4);
        b64[1] = (b << 4) | (c >> 2);
        b64[2] = (c << 6) | (d >> 0);


        printf("%c%c%c", b64[0], b64[1], b64[2]);

    }

    printf("\n\n");
}