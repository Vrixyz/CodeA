//
// myContactListener.hpp for  in /home/berger_t//gameDevBerlin
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Aug 23 09:43:15 2012 thierry berger
// Last update Fri Feb 22 12:45:09 2013 mathieu leurquin
//

#ifndef MY_CONTACT_LISTENER
# define MY_CONTACT_LISTENER

#include <iostream>
#include "Object.hpp"

class MyContactListener : public b2ContactListener
{
  void BeginContact(b2Contact* contact) {
    
    void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
    
    if (bodyUserData1 && bodyUserData2)
      {
	Server::Object *o1 = static_cast<Server::Object*>(bodyUserData1);
	Server::Object *o2 = static_cast<Server::Object*>(bodyUserData2); 
	
	o1->collision(o2);
      }  
  }
};

#endif
