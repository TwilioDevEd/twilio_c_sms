/*
* Twilio C SMS Demo
* You should be able to build this in most POSIX-compliant environments.
*
* See our documentation at https://twilio.com/docs !
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "twilio.h"


/*
* Main is here to demonstrate the send_message function and take our command
* line parameters.
*/
int main(int argc, char *argv[])
{
        int cmd;
        bool verbose = false;
        char *account_sid = NULL;
        char *auth_token = NULL;
        char *message = NULL;
        char *from_number = NULL;
        char *to_number = NULL;
        char *picture_url = NULL;
        opterr = 0;

        while ((cmd = getopt(argc, argv, "a:s:m:f:t:p:vh?")) != -1) {
                switch (cmd) {
                        case '?':
                        case 'h':
                                printf("Twilio C SMS Example Help:\n");
                                printf("-a: Account\t\t"
                                       "(ex: -a \"ACXXXXX\")\n");
                                printf("-s: Auth Token\t\t"
                                       "(ex: -s \"your_token\")\n");
                                printf("-f: From Number\t\t"
                                       "(ex: -f \"+18005551212\")\n");
                                printf("-t: To Number\t\t"
                                       "(ex: -t \"+18005551212\")\n");
                                printf("-m: Message to send\t"
                                       "(ex: -m \"Hello, Twilio!\")\n");
                                printf("-p: (Opt.) URL to Image\t"
                                       "(ex: -p \"Hello, Twilio!\")\n");
                                printf("-v: Verbose Mode\n");
                                printf("-h: This help dialog\n");
                                return 0;
                        case 'a':
                                account_sid = optarg;
                                break;
                        case 's':
                                auth_token = optarg;
                                break;
                        case 'm':
                                message = optarg;
                                break;
                        case 'f':
                                from_number = optarg;
                                break;
                        case 't':
                                to_number = optarg;
                                break;
                        case 'p':
                                picture_url = optarg;
                                break;
                        case 'v':
                                verbose = true;
                                break;
                        default:
                                abort();
                }
        }

        if ( !account_sid || !auth_token || !from_number
                || !to_number || !message ) {
                fprintf(stderr,
                        "You didn't include all necessary inputs!\n"
                        "Call using -h for help.\n");
                return -1;
        }

        if (verbose) {
                printf("Sending a message with the Twilio C SMS Demo!\n"
                       "________________________________________"
                       "________________________________________\n");
        }

        if (twilio_send_message(account_sid,
                                auth_token,
                                message,
                                from_number,
                                to_number,
                                picture_url,
                                verbose
        ) == true) {
            return 0;
        } else {
            return -1;
        }


}
