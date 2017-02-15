#include <stdio.h>

void printUsage() {
	printf("Usage: bth <file>\n");
}

void printFileError() {
	printf("The specified file does not exist\n");
}

void printFileSizeError() {
	printf("The specified file is empty\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printUsage();
		return 1;
	}

	char* fileName = argv[1];
	FILE* fileHandle;
	fopen_s(&fileHandle, fileName, "rb");

	if (fileHandle == 0) {
		printFileError();
		printUsage();
		return 1;
	}

	unsigned int fileSize = 0;
	unsigned long counter = 0;
	unsigned char currentCharacter = 0;

	fseek(fileHandle, 0L, SEEK_END);
	fileSize = ftell(fileHandle);
	fseek(fileHandle, 0L, SEEK_SET);

	if (fileSize == 0) {
		printFileSizeError();
		printUsage();
		return 1;
	}

	printf("static unsigned char %s[%i] = {", fileName, fileSize);

	while (!feof(fileHandle)) {
		if (fread(&currentCharacter, 1, 1, fileHandle) == 0) {
			break;
		}

		printf("0x%.2X", (int)currentCharacter);

		++counter;

		if (counter < fileSize) {
			printf(",");
		}
	}

	fclose(fileHandle);
	printf("};\n");

	return 0;
}