#include <iostream>
#include <string>
#include "curl/curl.h"
#include "helperFunctions.hpp"

/*
Build Command:
  g++ client.cpp -o client -lcurl

*/

using namespace std;
 
 
 bool addUser();
 bool sendMsg();
 bool printUsers();
 bool readMsgs();
 
 
int main()
{

  curl_global_init(CURL_GLOBAL_ALL);
  
  string command;
  
  cout<<"Type 'help' to see command options."<<endl;
  
  //Used to get the return status of each endpoint
  bool OK;
  
  while(command != "exit")
  {
  
    cout<<"What do you want to do?"<<endl;
    
    cin>>command;
    
    if(command == "help")
    {
      cout<<"Command options are:"<<endl;
      cout<<"    addUser"<<endl;
      cout<<"    send"<<endl;
      cout<<"    read"<<endl;
      cout<<"    printUsers"<<endl;
    }
    else if(command == "addUser")
    {
       OK = addUser();
      
      if(!OK)
      {
        cout<<"Problem running command addUser."<<endl;
      }
      
    }
    else if(command == "send")
    {
      OK = sendMsg();
      
      if(!OK)
      {
        cout<<"Problem running command send."<<endl;
      }
    }
    else if(command == "printUsers")
    {
      OK = printUsers();
      
      if(!OK)
      {
        cout<<"Problem running command printUsers."<<endl;
      }
    }
    else if(command == "read")
    {
      OK = readMsgs();
      
      if(!OK)
      {
        cout<<"Problem running command read."<<endl;
      }
    }
    
    
    //Including this fixes the problem where after multiple cin statments
    //all the newline characters suddenly input after the fact and cause 
    //several empyt "commands" to be entered.
    //cin.ignore();
    //SORT OF FIXES IT
    
  
  }
  
  
  curl_global_cleanup();
  
  
}



//This function adds a new user to the email server
bool addUser()
{
  
  string userName, password, data;
  
  cout<<"Enter a new username: "<<endl;
  cin>>userName;
  cout<<"Enter your password: "<<endl;
  cin>>password;
  
  data = userName + "\n" + password;
  
  CURL *curl;
  CURLcode res;
  
  curl = curl_easy_init();
  
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "https://email-server-damay.c9users.io/addUser.cgi");
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());    
    
    res = curl_easy_perform(curl);
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
  
  
}



//This function sends a message to a particular user on the email server
bool sendMsg()
{
  string userName, password, message, receiveUser, data;
  
  //Get all needed data from the user
  cout<<"Enter your username: "<<endl;
  cin>>userName;
  cout<<"Enter your password: "<<endl;
  cin>>password;
  cout<<"Enter who you want to send to: "<<endl;
  cin>>receiveUser;
  cout<<"Enter you message: "<<endl;
  
  //This is needed to get rid of the newline after the the cin that is still in the buffer
  //If you don't do this getline will end immediatly without letting you type anything.
  cin.ignore();
  getline(cin, message);
  
  /*
  
            ADD THE ENCODING FOR THE MESSAGE
  
  */
  
  cout<<"STILL NEED TO ADD ENCRYPTING"<<endl;
  
  data = userName + '\n' + password + '\n' + receiveUser + '\n' + message;
  
  CURL *curl;
  CURLcode res;
  
  curl = curl_easy_init();
  
  //If curl was setup correctly send the POST request and wait for a response
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "https://email-server-damay.c9users.io/receiveMessage.cgi");
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());    
    
    res = curl_easy_perform(curl);
    
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
}




bool printUsers()
{
  CURL *curl;
  CURLcode res;
  
  curl = curl_easy_init();
  
  //If curl was setup correctly send the POST request and wait for a response
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "https://email-server-damay.c9users.io/printUsers.cgi");
    
    res = curl_easy_perform(curl);
    
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
}




bool readMsgs()
{
  string userName, password;
  
  //Get all needed data from the user
  cout<<"Enter your username: "<<endl;
  cin>>userName;
  cout<<"Enter your password: "<<endl;
  cin>>password;
  
  /*
  
            ADD THE ENCODING FOR THE MESSAGE
  
  */
  
  cout<<"STILL NEED TO ADD ENCRYPTING"<<endl;
  
  data = userName + '\n' + password + '\n';
  
  CURL *curl;
  CURLcode res;
  
  curl = curl_easy_init();
  
  //If curl was setup correctly send the POST request and wait for a response
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "https://email-server-damay.c9users.io/getMessages.cgi");
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());    
    
    res = curl_easy_perform(curl);
    
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
  
  
  
  
}