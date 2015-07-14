#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int oc; /* option character */
	char *b_opt_arg;
	while ((oc = getopt(argc, argv, ":ab:")) != -1) {
 		switch (oc) {
		case 'a':
			/* handle -a, set a flag, whatever */
 			break;
		case 'b':
			/* handle -b, get arg value from optarg */
 			b_opt_arg = optarg;
 			break;
 		case ':':
			 /* missing option argument */
 			fprintf(stderr, "%s: option `-%c' requires an argument\n",
             argv[0], optopt);
             break;
        case '?':
        default:
            /* invalid option */
            fprintf(stderr, "%s: option `-%c' is invalid: ignored\n", argv[0], optopt);
        break;
        }
    }
}
