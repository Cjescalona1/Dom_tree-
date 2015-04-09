#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <list>
#include "Element.h"

using namespace std;

class Node
{
	private:
		Element e;
		Node *Child,*Broth;
	public:
		///constructores
		Node(): Child(NULL), Broth(NULL){}
		Node(const Element &e1): e(e1), Child(NULL), Broth(NULL){}
		Node(const Element &e1, Node *fchild, Node* fbroth): e(e1), Child(fchild), Broth(fbroth){}
		
		///consultores
		Element element()const{return e;}
		Node* firstChild() const{return Child;}
		Node* nextSibling() const{return Broth;}
		Element* getPTRelement(){return (&e);}

		///modificadores
		void setElement(const Element &e1){this->e=e1;}
		void setFirstChild(Node *c){this->Child=c;}
		void setNextSibling(Node *b){this->Broth=b;}

};
#endif
