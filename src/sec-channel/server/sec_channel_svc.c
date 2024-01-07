/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "sec_channel.h"
#include <stdio.h>
#include <stdlib.h>
#include <tirpc/rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>



#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

void writePidFile(char * pidfile, int pid)
{
	if (pidfile == NULL) return;
	int f;
	char outbuf[128];
	f = open(pidfile,O_CREAT | O_WRONLY);
	if (f <= 0) return;
	sprintf(outbuf,"%d",pid);
	outbuf[sizeof(outbuf)-1] = '\0';
	write(f,outbuf,strlen(outbuf));
	close(f);
}
static void
sec_channel_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		int sec_channel_ping_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case SEC_CHANNEL_PING:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) sec_channel_ping_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;
	char c;
	char * pidfile = NULL;
	pid_t pid;

	int debug = 0;
	
	while ((c=getopt(argc,argv,"dp:")) != -1)
	{
		switch(c)
		{
			case 'd': debug = 1;
				  break;
			case 'p': pidfile = optarg;
				  // fprintf(stderr,"pidfile is %s\n", pidfile);
				  break;
			default:  break;
		}
	}

	openlog(SERVICE_NAME, LOG_PID, LOG_LOCAL0);
	syslog(LOG_INFO, "starting service");

	pmap_unset (SEC_CHANNEL, SEC_CHANNEL_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		syslog (LOG_ERR, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, SEC_CHANNEL, SEC_CHANNEL_VERS, sec_channel_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (SEC_CHANNEL, SEC_CHANNEL_VERS, udp).");
		syslog (LOG_ERR, "%s",
			"unable to register (SEC_CHANNEL, SEC_CHANNEL_VERS, udp)");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		syslog (LOG_ERR, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, SEC_CHANNEL, SEC_CHANNEL_VERS, sec_channel_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (SEC_CHANNEL, SEC_CHANNEL_VERS, tcp).");
		syslog(LOG_ERR, "%s",
		       "unable to register (SEC_CHANNEL, SEC_CHANNEL_VERS, tcp)");

		exit(1);
	}

	if(!debug){
	switch(pid = fork()){
		case -1:		//Fork failed
			perror("Fork Failed\n");
			exit(1);
		case 0:			// Child
			break;
		default:		// Parent
			// fprintf(stderr,"Parent writes pidfile %s %d\n",pidfile,pid);
			writePidFile(pidfile,pid);
			exit(0);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	// Don't wait for child processes to complete.
	// This makes sure that the child does not turn
	// into a zombie on exit.

	struct sigaction sa;
	sigaction(SIGCHLD, NULL, &sa);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGCHLD, &sa, NULL);

	}
	setsid();
	fprintf(stdout, "Starting SVC_RUN loop\n");
	svc_run();
	fprintf (stderr, "%s", "svc_run returned");
	syslog (LOG_ERR, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
	
	
