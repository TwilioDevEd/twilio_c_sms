/*
* Twilio C SMS Demo
* You should be able to build this in most POSIX-compliant environments.
*
* See our documentation at https://twilio.com/docs !
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

/* Defaults - 10K max memory for our strings, and a definition of boolean. */
#define MAX_SIZE 10000
typedef enum { false, true } bool;


int send_message(char *, char *, char *, char *, char *, bool);

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
        opterr = 0;

        while ((cmd = getopt(argc, argv, "a:s:m:f:t:vh?")) != -1) {
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
                       "libCurl version: %s\n"
                       "________________________________________"
                       "________________________________________\n",
                       curl_version());
        }

        return send_message(account_sid,
                            auth_token,
                            message,
                            from_number,
                            to_number,
                            verbose);
}


/*
* send_message should be portable if you have libcurl linked.
*/
int send_message(char *account_sid,
                 char *auth_token,
                 char *message,
                 char *from_number,
                 char *to_number,
                 bool verbose)
{

        CURL *curl;
        CURLcode res;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        char url[MAX_SIZE];
        snprintf(url,
                 sizeof(url),
                 "%s%s%s",
                 "https://api.twilio.com/2010-04-01/Accounts/",
                 account_sid,
                 "/Messages");

        char parameters[MAX_SIZE];
        snprintf(parameters,
                 sizeof(parameters),
                 "%s%s%s%s%s%s",
                 "To=",
                 to_number,
                 "&From=",
                 from_number,
                 "&Body=",
                 message);


        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters);
        curl_easy_setopt(curl, CURLOPT_USERNAME, account_sid);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, auth_token);

        if (!verbose) {
                curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
        }

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        long http_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (res != CURLE_OK) {
                if (verbose) {
                        fprintf(stderr,
                                "SMS send failed: %s.\n",
                                curl_easy_strerror(res));
                }
                return -1;
        } else if (http_code != 200 && http_code != 201) {
                if (verbose) {
                        fprintf(stderr,
                                "SMS send failed, HTTP Status Code: %ld.\n",
                                http_code);
                }
                return -1;
        } else {
                if (verbose) {
                        fprintf(stderr,
                                "SMS sent successfully!\n");
                }
                return 0;
        }

}
