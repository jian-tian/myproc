#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define BUFFERSIZE 16

int is_fileexist(char *comm, char *buffer);
void pipel(char *input, int li_inputlen);
void redirect(char *input, int li_inputlen);

int main(int argc, char *argv[])
{
    char *path;
    char lc_char;
    int li_inputlen = 0; 
    char buffer[BUFFERSIZE] = {'\0'};
    char dirpath[256] = {'\0'};
    char *input = NULL;
    char *arg[5];
    int is_bj = 0;
    int is_back = 0;
    int pid;
    int status;
    int i,j,k;

    while (1) {
	/*input instructior*/
	memset(buffer, 0, sizeof(buffer));
	li_inputlen = 0;
	path = (char *)get_current_dir_name();
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
	} else if (0 == li_inputlen) {
	    continue;
	} else {
	    buffer[li_inputlen] = '\0';
	}
	input = (char *)malloc(sizeof(char) * (li_inputlen + 1));
	strcpy(input, buffer);
	
	printf("buffer is %s, input is %s, li_inputlen is %d\n", buffer, input, li_inputlen);	
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
		    printf("i=%d, k=%d\n", i,k);
		    arg[k] = (char *)malloc(sizeof(char) * j);
		    printf("buffer is %s\n", buffer);
		    strcpy(arg[k], buffer);
		    printf("i=%d, k=%d, arg[k]=%s\n", i, k, arg[k]);
		    j = 0;
		    k++;
		}
	    } else if (input[i] == '&' && input[i+1] == '\0') {
		    is_back = 1;
		    continue;
	    } else {
		buffer[j++] = input[i];
	    }
	}
	free(input);
	/*search instruction*/
	if (0 == strcmp(arg[0], "leave")) {
	    printf("Bye-bye\n");
	    break;
	}
	if (0 == is_bj) {
	    arg[k] = (char *)0;
	    if (-1 == is_fileexist(arg[0], dirpath)) {
		printf("this command is not found!\n");
		for(i=0; i<k; i++)
		    free(arg[i]);
		continue;	
	    }
	 /*exec command*/   
	    if (0 == (pid = fork())) {
		/*child to execv command*/
		execv(dirpath, arg);
	    }
	    else {
		/*father to wait command*/
		if(is_back == 0)
		    waitpid(pid, &status,0);
	    }
	    
	    for(i=0; i<k; i++)
		free(arg[i]);
	}
    }
}

void pipel(char *input, int li_inputlen)
{
    printf("pipel\n");
}

void redirect(char *input, int li_inputlen)
{
    printf("redirect\n");
}

int is_fileexist(char *comm, char *buffer)
{
    char *path,*p;
    int i = 0;

    path = getenv("PATH");
    //printf("path is %s\n", path);
    p = path;
    while (*p != '\0') {
	if(*p != ':')
	    buffer[i++] = *p;
	else {
	    buffer[i++] = '/';
	    buffer[i] = '\0';
	    strcat(buffer,comm);
	   // printf("buffer is %s\n", buffer);
	    if (access(buffer, F_OK) == 0)
		return 0;
	    else
		i = 0;
	}
	p++;
    }
    return -1;
}


void redirect(char *input, int len)
{
    char *argv[30],*filename[2];
    pid_t pid;
    int i,j,k,fd_in,fd_out;
    int is_in = -1;
    int is_out = -1;
    int num = -1;
    int is_back = 0;
    int status = 0;

    for (i=0,j=0,k=0; i<= len; i++) {
	if (input[i] == ' ' || input[i] == '\t' || input[i] == '\0' || \
	    input[i] == '>' || input[i] == '<') {
	    if (input[i] == '>' || input[i] == '<') {
		if (num < 3) {
		    num++;
		    if (input == '<')
			is_in = num - 1;
		    else
			is_out = num -1;

		    if(j > 0 && num == 1) {
			buffer[j++] = '\0';
			argv[k] = (char *)malloc(sizeof(char) * j);
			strcpy(argv[k], buffer);
			k++;
			j = 0;
		    }
		} else {
		    printf("The format is error!\n");
		    return -1;
		}
	    }
	    
	    if (j == 0)
		continue;
	    else {
		buffer[j++] = '\0';
		if (num == 0) {
		    argv[k] = (char *)malloc(sizeof(char) * j);
		    strcpy(argv[k], buffer);
		    k++;
		} else {
		    filename[status] = (char *)malloc(sizeof(char) * j);
		    strcpy(filename[status++], buffer);
		}
		j = 0;
	    }
	} else if(input[i] == '&' && input[i+1] == '\0') {
	    is_back = 1;
	    continue;
	} else {
	    buffer[j++] = input[i];
	}
    }
    
    argv[k] = (char *)0;

    if (is_fileexist(argv[0]) == -1) {
    }
}
