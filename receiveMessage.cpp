#include <iostream>
#include <string>
#include <fstream>
#include "helperFunctions.hpp"
#include <ctime>
using namespace std;


bool findUser(string userName);

int main() {
   
    cout << "Content-type: application/json" << endl;
    cout << endl;
    
    //Get the username and password from the post request
    //User name => the user name of the person sending the message
    //password => the password of the person sending the message
    //receiveUser => the user name of the person who will receive the message
    //message => the actual text of the message that is being sent
    string userName, password, receiveUser, message;
    getline(cin, userName);
    getline(cin, password);
    getline(cin, receiveUser);
    getline(cin, message);
    
    //Detect newline charactes
    if(userName.find('\n') != string::npos || 
        password.find('\n') != string::npos ||
        receiveUser.find('\n') != string::npos ||
        message.find('\n') != string::npos)
    {
        cout<<"Username and password cannot contian return character."<<endl;
    }


    //Make sure the user is who they say they are
    bool authOK = authUser(userName, password);
    
    
    if(authOK)
    {
        cout<<"Login OK."<<endl;
        
        bool foundUser = findUser(receiveUser);
        
        
        //If the user being sent the message was found
        if(foundUser)
        {
            ofstream outFile;
            outFile.open("./dat/msg/" + receiveUser, ios::app);
            
            outFile << "From " << userName<<endl;
            outFile << "At Unix Time index "<<time(NULL)<<endl;
            outFile << message <<endl;
            cout<<"Message sent."<<endl;
        }
        else
        {
            cout<<"User name being sent to not found."<<endl;
        }
        
    }
    else
    {
        cout<<"Error loging in."<<endl;
    }
    
    
    blankOutPassword(&password);
    

    return 0;
   
   

}




bool findUser(string userName)
{
    //Check to make sure the user the message is being sent to exists in it
    //Open the file
    fstream file;
    
    file.open("./dat/Users");
    
    if(!file.is_open())
    {
        cout<<"Error"<<endl;
        return -1;
    }
    
    //This loop run until either the receiveUser user name is found or the
    //end of the file is reached
    while(!file.eof())
    {
        //Username file is formated that one line userName next line password
        string userNameLine;
        getline(file, userNameLine);
        string passwordLine;
        getline(file, passwordLine);
        
        
        if(userName == userNameLine)
        {
            file.close();
            
            return true;
        }
        
    }
    
    file.close();
    
    return false;
}