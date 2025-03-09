// SymmetricKeyDistribution.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Agent.h"


int main()
{
	cout << "---- Key1 and Key2 exchange master key with KDC\n";
	Sender* s = new Sender(); Receiver* r = new Receiver(); KDC* kdc = new KDC;
	s->recvClient = r; r->sendClient = s;
	s->id = "This is Key1";
	s->symmetricKeyFuncs.regenerateNewKey();
	//s->symmetricKeyFuncs.setKey(s->masterKey);
	s->masterKey = s->symmetricKeyFuncs.getKeyString();

	r->id = "This is Key2";
	r->symmetricKeyFuncs.regenerateNewKey();
	//r->symmetricKeyFuncs.setKey(r->masterKey);
	r->masterKey = r->symmetricKeyFuncs.getKeyString();
	//r->sendClient->id = s->id;

	//KDC kdc;
	kdc->arrId.push_back({ s->id, s->masterKey });
	kdc->arrId.push_back({ r->id, r->masterKey });

	cout << setw(20) << left << "Identifier" << setw(30) << left << "Master Key" << endl;

	for (int i = 0; i < kdc->arrId.size(); i++)
	{
		cout << setw(20) << left << kdc->arrId[i][0] << setw(30) << left << kdc->arrId[i][1] << endl;
	}
	//s->recvClient
	

	return 0;
}