#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "akshaybhawarkiti@gmail.com"
#define AUTHOR_PASSWORD "uabulpopoejyiyxk"
#define RECIPIENT_EMAIL "akshaybhawarkiti@gmail.com"

SMTPSession smtp;  //declare smtp 
Session_Config config; //initialising smtp configration
SMTP_Message message; // Declare message as a global variable

void setup() {
  //email time configuration

  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 3;
  config.time.day_light_offset = 0;

  //server connection

  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;

  //email sending test
  message.sender.name = F("test email");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("HI I'M REVANTH");
  message.addRecipient(F("akshaybhawarkiti@gmail.com"), RECIPIENT_EMAIL);

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
