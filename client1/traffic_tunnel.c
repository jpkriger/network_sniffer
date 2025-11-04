#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include "tunnel.h"

#define ARG_SERVER_MODE "-s"
#define ARG_CLIENT_MODE "-c"

void usage()
{
	fprintf(stdout, "usage:\n");
	fprintf(stdout, "server: # ./traffic_tunnel [interface] -s\n");
	fprintf(stdout, "client: # ./traffic_tunnel [interface] -c [clientscript.sh]\n");
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		usage();
		exit(EXIT_FAILURE);
	}

	if (strncmp(argv[2], ARG_SERVER_MODE, strlen(argv[2])) == 0) {
		run_tunnel(1, argc, argv);
	} else {
		if (strncmp(argv[2], ARG_CLIENT_MODE, strlen(argv[2])) == 0) {
			if (argc < 4) {
				usage();
				exit(EXIT_FAILURE);
			}
				
			run_tunnel(0, argc, argv);
		} else {
			usage();
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
