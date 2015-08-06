#include <stdio.h>
#include <stdlib.h>
#define BUFFERSIZE 16

int main(int argc, char *argv[])
{
    char *path;
    char lc_char;
    int li_inputlen = 0; 
    char buffer[BUFFERSIZE] = {'\0'};
    char *input;

    while (1) {
    /*input instructior*/
	path = get_current_dir_name();
	printf("%s>$", path);

	lc_char = getchar();
	while (lc_char != '\n' && li_inputlen < BUFFERSIZE) {
	    buffer[li_inputlen++] = lc_char;
	    lc_char = getchar();
	}

	if (li_inputlen > BUFFERSIZE) {
	    printf("command too long! Re-enter!");
	    li_inputlen = 0;
	    continue;
	}
	input = (char *)malloc(sizeof(char) * (li_inputlen + 1));
	strcpy(input, buffer);
    }
}
