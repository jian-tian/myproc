#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define BUFFERSIZE 16

#undef DEBUG

#ifdef DEBUG
#define PRINT_DEBUG(format, ...)	printf("[File:"__FILE__",line:%05d] "format, __LINE__, ##__VA_ARGS__)
#else
#define PRINT_DEBUG(format, ...)
#endif
int is_fileexist(char *comm, char *buffer);
int pipel(char *input, int li_inputlen);
int redirect(char *input, int li_inputlen);

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
	is_bj = 0;
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
	
	PRINT_DEBUG("buffer is %s, input is %s, li_inputlen is %d\n", buffer, input, li_inputlen);	
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
		    PRINT_DEBUG("i=%d, k=%d\n", i,k);
		    arg[k] = (char *)malloc(sizeof(char) * j);
		    PRINT_DEBUG("buffer is %s\n", buffer);
		    strcpy(arg[k], buffer);
		    PRINT_DEBUG("i=%d, k=%d, arg[k]=%s\n", i, k, arg[k]);
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
	if (0 == is_bj) {
	    if (0 == strcmp(arg[0], "leave")) {
		printf("Bye-bye\n");
		break;
	    }

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

int is_fileexist(char *comm, char *buffer)
{
    char *path,*p;
    int i = 0;

    path = getenv("PATH");
    p = path;
    while (*p != '\0') {
	if(*p != ':')
	    buffer[i++] = *p;
	else {
	    buffer[i++] = '/';
	    buffer[i] = '\0';
	    strcat(buffer,comm);
	    if (access(buffer, F_OK) == 0)
		return 0;
	    else
		i = 0;
	}
	p++;
    }
    return -1;
}

/*重定向*/
int redirect(char *input, int len)
{
    char *argv[30],*filename[2];
    char buffer[BUFFERSIZE] = {'\0'};
    char dirpath[256] = {'\0'};
    pid_t pid;
    int i,j,k,fd_in,fd_out;
    int is_in = -1;
    int is_out = -1;
    int num = -1;
    int is_back = 0;
    int status = 0;

    PRINT_DEBUG("input is %s\n", input);
    for (i=0,j=0,k=0; i<= len; i++) {
	if (input[i] == ' ' || input[i] == '\t' || input[i] == '\0' || \
	    input[i] == '>' || input[i] == '<') {/*特殊字符*/
	    if (input[i] == '>' || input[i] == '<') {/*重定向字符处理*/
		if (num < 3) {
		    num++;
		    if (input[i] == '<')
			is_in++;
		    else
			is_out++;
		    PRINT_DEBUG("j =%d,is_in is %d, is_out is %d, num is %d\n", j,is_in,is_out,num);
		    if(j > 0 && num == -1) {/*二次重定向*/
			buffer[j++] = '\0';
			argv[k] = (char *)malloc(sizeof(char) * j);
			strcpy(argv[k], buffer);
			PRINT_DEBUG("--arv[%d] is %s\n", k, argv[k]);
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
		PRINT_DEBUG("num is %d, buffer is %s\n", num, buffer);
		if (num == -1) {/*重定向前的命令*/
		    argv[k] = (char *)malloc(sizeof(char) * j);
		    strcpy(argv[k], buffer);
		    PRINT_DEBUG("arv[%d] is %s\n", k, argv[k]);
		    k++;
		} else {/*获取重定向文件*/
		    filename[status] = (char *)malloc(sizeof(char) * j);
		    strcpy(filename[status++], buffer);
		    PRINT_DEBUG("filename[%d] is %s\n", status-1,filename[status-1]);
		}
		j = 0;/*每次copy结束后j置零，表示清空buffer*/
	    }
	} else if(input[i] == '&' && input[i+1] == '\0') {
	    is_back = 1;
	    continue;
	} else {
	    buffer[j++] = input[i];
	}
    }
   
    /*参数末尾赋值为NULL*/ 
    argv[k] = (char *)0;

    /*判断命令是否存在*/
    if (is_fileexist(argv[0], dirpath) == -1) {
	printf("This command:%s is not founded\n", argv[0]);
	for (i=0; i<k; i++)
	    free(argv[i]);
	return 0;
    }

    /*创建子进程*/
    if ((pid = fork()) == 0) {/*子进程*/
	/*打开重定向文件*/
	if (is_out != -1) {
	    if ((fd_out = open(filename[is_out],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) == -1) {
		printf("Open out %s Error\n", filename[is_out]);
		return -1;
	    }
	}
	if (is_in != -1) {
	    if ((fd_in = open(filename[is_in],O_RDONLY,S_IRUSR|S_IWUSR)) == -1) {
		printf("Open in %s Error\n", filename[is_out]);
		return -1;
	    }
	}
	/**/
	if (is_out != -1) {
	    if (dup2(fd_out, STDOUT_FILENO) == -1) {
		printf("Redirect Standard Out Error\n");
                exit(1); 
	    }
	}
	if (is_in != -1) {
	    if (dup2(fd_in, STDIN_FILENO) == -1) {
		printf("Redirect Standard Out Error\n");
		exit(1);
	     }
	}
	execv(dirpath, argv);
    } else if (is_back == 0) {/*父进程,如果后台运行，父进程等待子进程结束*/
	waitpid(pid, &status, 0);
    }

    /*释放资源*/
    for (i=0; i<k; i++) {
	free(argv[i]);
    }
    if (is_in != -1) {
	free(filename[is_in]);
	close(fd_in);
    }
    if(is_out != -1) {
	free(filename[is_out]);
	close(fd_out);
    }

    return 0;
}

int  pipel(char *input, int li_inputlen)
{
    char *argv[2][30];/*两个命令组，一个存储管道前命令，一个存储管道后命令*/
    int i,j,k,count;
    char buffer[BUFFERSIZE] = {'\0'};
    int is_back=0;
    int li_comm = 0;
    int fd[2],fpip[2];
    char dirpath[256] = {'\0'};
    char lc_char,lc_end[1];
    pid_t child1,child2;

    for (i=0,j=0,k=0; i<=li_inputlen; i++) {
	if (input[i] == ' ' || input[i] == '\t' || input[i] == '|' || input[i] == '\0') {
	    if (input[i] == '|') {
		if(j > 0) {
		    buffer[j++] = '\0';
		    argv[li_comm][k] = (char *)malloc(sizeof(char) * j);
		    strcpy(argv[li_comm][k++], buffer);
		}
		argv[li_comm][k++] = (char *)0;
		li_comm++;
		count = k;
		k=0;
		j=0;
	    }
	    if(j == 0)
		continue;
	    else {
		buffer[j++] = '\0';
		argv[li_comm][k] = (char *)malloc(sizeof(char) * j);
		strcpy(argv[li_comm][k], buffer);
		k++;
	    }
	    j = 0;
	}
	else {
	    if (input[i] == '&' && input[i+1] == '\0') {
		is_back = 1;
		continue;
	    }
	    buffer[j++] = input[i];
	}
    }
    argv[li_comm][k++] = (char *)0;

    if (is_fileexist(argv[0][0],dirpath) == -1) {
	printf("This first command is not found\n");
	for (i=0; i<count; i++)
	    free(argv[0][i]);
	return 0;
    }
	/*建立管道*/
	if (pipe(fd) == -1) {
	    printf("open pipe error\n");
	    return -1;
	}

	if ((child1 = fork()) == 0) {/*第一个子进程，标准输出到管道*/
	    close(fd[0]);
	    if (fd[1] != STDOUT_FILENO) {
		if (dup2(fd[1], STDOUT_FILENO) == -1) {
		    printf("Redirect Standard Out Error\n");
		    return -1;
		}
		close(fd[1]);
	    }
	    execv(dirpath, argv[0]);
	}
	else {/*父进程*/
	    waitpid(child1, &li_comm, 0);
	    lc_end[0] = 0x1a;
	    write(fd[1], lc_end, 1);
	    close(fd[1]);
	    
	    if (is_fileexist(argv[1][0], dirpath) == -1) {
		printf("This command is not founded\n");
		for (i=0; i<k; i++)
		    free(argv[1][i]);
		return 0;
	    }

	    if ((child2 = fork()) == 0) {/*第二个子进程，标准输入为管道*/
		if (fd[0] != STDIN_FILENO) {
		    if (dup2(fd[0], STDIN_FILENO) == -1) {
			printf("Redirect Standard In Error\n");
			return -1;
		    }
		    close(fd[0]);
		}
		execv(dirpath, argv[1]);
	    }
	    else {/*父进程*/
		if (is_back == 0)
		    waitpid(child2, NULL, 0);
	    }
	}
	/*释放资源*/
	for (i=0; i<count; i++) { 
	    free(argv[0][i]);
	}
	for (i=0; i<k; i++) {
	    free(argv[1][i]);
	}
	
	return 0;
}
