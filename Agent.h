#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <cstdlib> 
#include "cryptlib.h"
#include "modes.h"
#include "files.h"
#include "rsa.h"
#include "AESClass.h"

using namespace std;
using namespace CryptoPP;


//A struct represents the structure of a possible message in a key distribution scheme
struct Message{
	string IDA, IDB; //Identifiers of sender and receiver 
	string nonce; //A random number
	string sessionKey;
	string info; //Main message to be exchanged
	Message* msg = NULL;
};

class Sender;
class Receiver;

//Interface class representing each agent in the communication
class IClient {
public:
	string id;
	AESClass symmetricKeyFuncs; //This is used to encrypt and decrypt message using the secret key
	string masterKey;
	string sessionKey;
	string nonce;
public:

	IClient() { }
	virtual void response(Message m, int step) = 0;
	//virtual void responseWithAuthentication(Message m, int step) = 0; //
};

//Sender means the one request distribution of symmetric key, or A
class Sender : public IClient {
public:
	Receiver *recvClient;
	void response(Message m, int step);
	//void responseWithAuthentication(Message m, int step);
};

//Receiver means the one which will distribute symmetric keys to sender, or B
class Receiver : public IClient {
public:
	Sender *sendClient;
	void response(Message m, int step);
	//void responseWithAuthentication(Message m, int step);
};

class KDC{
public:
	vector<vector<string>> arrId;
	AESClass symmetricKeyFuncs;
	//string sessionKey;
public:
	Receiver* recvClient;
	void response(Message m, int step, Message*& res);
};


//Represent the actor which intercept the communication and tries to eardrop
//class MaliciousActor : virtual public Sender, virtual public Receiver {
//public:
//	AESClass symmetricKeyFuncs;
//	string secretKey;
//	void response(Message m, int step);
//	void responseWithAuthentication(Message m, int step) {} 
//};
