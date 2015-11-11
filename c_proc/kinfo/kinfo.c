#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

const char *program_name;

void print_usage(FILE *stream, int exit_code)
{
    fprintf(stream, "Usage:%s options\n", program_name);
    fprintf(stream, "-h --help Display this usage information.\n" \
                    "-l int dur --load int dur Set interval and duration of average load.\n");
    exit(exit_code);
}

int main(int argc, char *argv[])
{   
    int next_option;
    const char *const short_options = "hl";
    const struct option long_options[] = {
	{"help", 0, NULL, 'h'},
	{"load", 1, NULL, 'l'},
	{NULL, 0, NULL, 0}
    };

    program_name = argv[0];
    do{
	next_option = getopt_long(argc, argv, short_options, long_options, NULL);
	switch(next_option){
	    case 'h':
		print_usage(stdout, 0);
	    case 'l':
		break;
	    case -1:
		break;
	    case '?':
		print_usage(stderr, 1);
	    default:
		abort();
	}
    }while(next_option != -1);

    return 0;
}
