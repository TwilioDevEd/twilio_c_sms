# Twilio SMS Example (C)

An example application that demonstrates how to send SMS text messages using C and libCurl.  Requires a POSIX compliant system.

## Build example:

<pre>
git clone https://github.com/pkamp3/twilio_c_sms.git
cd twilio_c_sms
make
</pre>

## Run example:

(You must have a [Twilio account](https://twilio.com) to run this example.)

Account SID and the Auth Token can be found in your Twilio console.  Change the from number to a number in your [Twilio Account](https://twilio.com/console), and change the to number to someone you'd like to get a message!

<pre>
account_sid=ACXXXXXXXXXXXXXXXXXXXXXX
auth_token=your_auth_token
./c_sms -a $account_sid -s $auth_token -t "+18005551212" -f "+18005551213" -m "Hello, World!"
</pre>

## Motivations

Hopefully you can use this as a base for a larger project.  The send_message function should be relatively portable as long as you link libcurl.

## Meta & Licensing

* [MIT License](http://www.opensource.org/licenses/mit-license.html)
* Lovingly crafted by Twilio Developer Education.
