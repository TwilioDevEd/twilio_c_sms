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
