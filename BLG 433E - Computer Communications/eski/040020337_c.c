/* Beycan Kahraman - 040020337 - beycan@mail.com                   */
/*                               Bilgisayar Haberlesmesi - Odev II */
#ifndef unix
   #define WIN32
   #include <windows.h>
   #include <winsock.h>
   #include <io.h>
#else
   #define closesocket close
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <arpa/inet.h>
   #include <netdb.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PROTOPORT       1453            /* default protocol port number */
#define DOSYA           "gonderilen_bit_dizisi.txt"

extern  int             errno;
char    localhost[] =   "localhost";    /* default host name            */
/*------------------------------------------------------------------------
 * Program:   client
 *
 * Purpose:   allocate a socket, connect to a server, and print all output
 *
 * Syntax:    client [ host [port] ]
 *
 *               host  - name of a computer on which server is executing
 *               port  - protocol port number server is using
 *
 * Note:      Both arguments are optional.  If no host name is specified,
 *            the client uses "localhost"; if no protocol port is
 *            specified, the client uses the default given by PROTOPORT.
 *
 *------------------------------------------------------------------------
 */
main(int argc, char *argv[]){
        struct  hostent  *ptrh;  /* pointer to a host table entry       */
        struct  protoent *ptrp;  /* pointer to a protocol table entry   */
        struct  sockaddr_in sad; /* structure to hold an IP address     */
        int     sd;              /* socket descriptor                   */
        int     port;            /* protocol port number                */
        char    *host;           /* pointer to host name                */
        int     n;               /* number of characters read           */
        char    buf[1000];       /* buffer for data from the server     */

        char    buffErr[10];                /* send eslik error             */
        char    err[5];                     /* get ACK                      */
        FILE    *f;                         /* file to read DOSYA           */
        int     i;                          /* loops                        */
        int     totalOnes;                  /* used to calculate eslik bit  */
        int     fileEnd = 1;                /* is file end                  */
        int     noError = 1;                /* re-send the message          */

#ifdef WIN32
        WSADATA wsaData;
        WSAStartup(0x0101, &wsaData);
#endif
        memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure */
        sad.sin_family = AF_INET;         /* set family to Internet     */

        /* Check command-line argument for protocol port and extract    */
        /* port number if one is specified.  Otherwise, use the default */
        /* port value given by constant PROTOPORT                       */

        if (argc > 2) {                 /* if protocol port specified   */
                port = atoi(argv[2]);   /* convert to binary            */
        } else {
                port = PROTOPORT;       /* use default port number      */
        }
        if (port > 0)                   /* test for legal value         */
                sad.sin_port = htons((u_short)port);
        else {                          /* print error message and exit */
                fprintf(stderr,"bad port number %s\n",argv[2]);
                exit(1);
        }

        /* Check host argument and assign host name. */

        if (argc > 1) {
                host = argv[1];         /* if host argument specified   */
        } else {
                host = localhost;
        }

        /* Convert host name to equivalent IP address and copy to sad. */

        ptrh = gethostbyname(host);
        if ( ((char *)ptrh) == NULL ) {
                fprintf(stderr,"invalid host: %s\n", host);
                exit(1);
        }
        memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);

        /* Map TCP transport protocol name to protocol number. */

        if ( ((int)(ptrp = getprotobyname("tcp"))) == 0) {
                fprintf(stderr, "cannot map \"tcp\" to protocol number");
                exit(1);
        }

        /* Create a socket. */

        sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
        if (sd < 0) {
                fprintf(stderr, "socket creation failed\n");
                exit(1);
        }

        /* Connect the socket to the specified server. */

        if (connect(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
                fprintf(stderr,"connect failed\n");
                exit(1);
        }


        /*********************** ADDED *******************************/

        err[4] = '\0';                                       // 4 bit ACK
        srand(time(NULL));                                   // SRAND
        f = fopen(DOSYA,"r");                                // open file

        while(fileEnd)
        {
                if(noError)                                  // send again ?
                {
                        for(i=0; i<7; ++i)                   // read 7 bits
                        {
                                fscanf(f, "%c", &buf[i]);
                                if(feof(f))
                                {
                                        fileEnd = 0;
                                        buf[i+1] = '\0';
                                        break;
                                }
                        }

                        buf[i+1] = '\0';

                        totalOnes = 0;

                        for(n=0; n<i; ++n)
                                if(buf[n] == '1')
                                        ++totalOnes;            // calculate eslik bit

                        buf[i] = totalOnes%2 == 1 ? '1' : '0';  // write eslik bit
                }

                if(rand()%4002 < 0337 && i > 3)               // let's create an error
                {
                        strcpy(buffErr, buf);
                        n = rand()%(i+1);

                        buffErr[n] = buffErr[n] == '1' ? '0' : '1';
                        send(sd, buffErr, i+1, 0);
                }
                else
                        send(sd, buf, i+1, 0);                // no error

                n = recv(sd, err, 4, 0);                      // get ACK

                noError = 1;

                if(err[0] == '1' || err[3] == '1')
                        noError = 0;                          // NACK
        }

        fclose(f);                                            // close file

        /************************ END ********************************/

        /* Close the socket. */
        closesocket(sd);

        /* Terminate the client program gracefully. */
        exit(0);
}

