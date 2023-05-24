#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <assert.h>

#include "transfer.h"

#include "utils.h"
#include "numList.h"

#include <glob.h>

int keepRunning = 1;

#include "snack.h"


void usage(int defaultthreads, size_t defaultlen) {
  printf("usage: snack [server mode] or [client mode]\n");
  printf("\n");
  printf("   snack -s [-t n]       # runs a server with <n> threads/ports, default %d\n", defaultthreads);
  printf("\n");
  printf("   snack -c IPaddress    # connects to a server, IP only\n");
  printf("\n");
  printf("options:\n");
  printf("   -c IP                 # client (sending) mode. IP only to avoid interface woes\n");
  printf("   -l size               # specifies the packet length <size>, default %zd\n", defaultlen);
  printf("   -s                    # server (listening) mode\n");
  printf("   -t n                  # specifies the number of threads/ports\n");
}
  

int main(int argc, char *argv[]) {
    int threads = 32;
    int opt;
    int servermode = 0;
    char *client = NULL;
    size_t len = 1024*1024;
    
    const char *getoptstring = "hsc:t:l:";

    while ((opt = getopt(argc, argv, getoptstring)) != -1) {
        switch (opt) {
            case 'h':
	        usage(threads, len);
		exit(1);
		break;
	    case 's':
	      servermode = 1;
	      break;
	    case 'c':
	      client = strdup(optarg);
	      break;
	    case 't':
	      threads = MAX(1, atoi(optarg));
	      break;
	    case 'l':
	      len = MAX(1, atoi(optarg));
	      break;
	    default:
	      usage(threads, len);
	      exit(1);
	}
    }


    if (servermode) {
      fprintf(stderr, "*info* starting receiver -- using %d ports/threads\n", threads);
      //      dumpEthernet();
      // start servers
      snackServer(threads);
    } else if (client) {
      snackClient(client, len);
    } else {
      usage(threads, len);
    }

    free(client);

    return 0;
}
