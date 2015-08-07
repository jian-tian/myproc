#include <stdio.h>
#include <stdlib.h>
#define BUFFERSIZE 16

void pipel(char *input, int li_inputlen){};
void redirect(char *input, int li_inputlen){};
int main(int argc, char *argv[])
{
    char *path;
    char lc_char;
    int li_inputlen = 0; 
    char buffer[BUFFERSIZE] = {'\0'};
    char *input;
    char **arg;
    int is_bj = 0;
    int is_back = 0;
    int i,j,k;

    while (1) {
	/*input instructior*/
	path = get_current_dir_name();
	printf("%s>$", path);

	lc_char = getchar();
	while (lc_char != '\n' && li_inputlen < BUFFERSIZE) {
	    buffer[li_inputlen++] = lc_char;
	    lc_char = getchar();
	}

	if (li_inputlen >= BUFFERSIZE) {
	    printf("command too long! Re-enter!\n");
	    li_inputlen = 0;
	    continue;
	}
	input = (char *)malloc(sizeof(char) * (li_inputlen + 1));
	strcpy(input, buffer);
	
	/*profile instruction*/
	for (i = 0,j = 0,k = 0; i <= li_inputlen; i++) {
	    if (input[i] == '<' || input[i] == '>' || input[i] == '|') {
		if (input[i] == '|')
		    pipel(input, li_inputlen);
		else
		    redirect(input, li_inputlen);
		is_bj = 1;
		break;
	    }
	    if (input[i] == ' ' || input[i] == '\t' || input[i] == '\0') {
		if( j == 0)
		    continue;
		else {
		    buffer[j++] = '\0';
		    arg[k] = (char *)malloc(sizeof(char) * j);
		    strcpy(arg[k], buffer);
		    j = 0;
		    k++;
		}
	    }
	    else {
		if (input[i] == '&' && input[i+1] == '\0') {
		    is_back = 1;
		    continue;
		}
		buffer[j++] = input[i];
	    }
	}
	for(i=0;i < j; i++)
	    printf("arg[%d] is %s\n", i, arg[j]);
	free(input);
    }
}
