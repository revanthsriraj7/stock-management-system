#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "akshaybhawarkiti@gmail.com"
#define AUTHOR_PASSWORD "uabulpopoejyiyxk"
#define RECIPIENT_EMAIL "akshaybhawarkiti@gmail.com"
#define RECIPIENT_EMAIL_2 "akshaybhawarlego1@gamil.com"
#define RECIPIENT_EMAIL_3 "revanthsriraj007@gmail.com"

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
  message.sender.name = F("Stock Management System");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("LOW ON STOCK!!");
  message.addRecipient(F("akshaybhawarkiti@gmail.com"), RECIPIENT_EMAIL); 
  message.addRecipient(F("akshaybhawarlego1@gamil.com"), RECIPIENT_EMAIL_2);
  message.addRecipient(F("revanthsriraj007@gmail.com"), RECIPIENT_EMAIL_3);

  //email content
  String textMsg = "YOUR STOCK IS GETTING LOW BELOW <100g please refill the stock as soon as possible.";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void sendEmail()
{
if (!smtp.connect(&config))
 {
return;
 }

if (!MailClient.sendMail(&smtp, &message))
  {
 return;
 }
}

void smtpCallback(SMTP_Status status)
{
if (status.success())
{
for (size_t i = 0; i < smtp.sendingResult.size(); i++)
{
SMTP_Result result = smtp.sendingResult.getItem(i);
}
smtp.sendingResult.clear();
    }
}
