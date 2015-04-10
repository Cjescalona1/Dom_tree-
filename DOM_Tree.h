#ifndef DOMTREE_H
#define DOMTREE_H

#include <iostream>
#include <string>
#include <list>
#include "Element.h"
#include "Node.h"

using namespace std;

class DOM_Tree
{
	private:
		Node *nodeRaiz, *Seed;
		
		///estaticos
		static Node* copiarNode(Node *ptr);
		static Node* buscarByID(string ID, Node *ptr);
					
	public:
		///constructores
		DOM_Tree(): nodeRaiz(NULL), Seed(NULL){}
		DOM_Tree(const Element &e1){nodeRaiz= new Node(e1); Seed=NULL}
		DOM_Tree(const Element &raiz, list<DOM_Tree> &l1);
		///consultores
		Element getRaizDT()const{return(nodeRaiz->element());}
		DOM_Tree childNode(int p)const;
		DOM_Tree getElementByID(string ID)const;
		///modificadores
		void copiar(const DOM_Tree &aDT);
		
		///sobreCargas
		void operator=(const DOM_Tree &a2){this->copiar(a2);}
		///Destructores
	
};		
	///constructores
	DOM_Tree:: DOM_Tree(const Element &raiz, list<DOM_Tree> &lst)
	{
		Node *aux;
		DOM_Tree arbAux;

		nodeRaiz= new Node (raiz, NULL, NULL) ;
		if (!lst.empty())
		{
			arbAux.copiar(lst.front());
			
			nodeRaiz->setFirstChild(arbAux.nodeRaiz);
			aux= nodeRaiz->firstChild();
			lst.pop_front();
			while (!lst.empty())
			{
				arbAux.nodeRaiz= NULL;
				
				arbAux.copiar(lst.front());
				lst.pop_front();
				aux->setNextSibling(arbAux.nodeRaiz);
				aux= aux->nextSibling();
			}
		}
		arbAux.nodeRaiz= NULL;
	}

	///static
	Node* DOM_Tree:: copiarNode(Node *ptr)
	{
		Node *nvo;

		if(ptr== NULL)
			return NULL;
		else
		{
			nvo= new Node (ptr->element(), copiarNode(ptr->firstChild()), copiarNode(ptr->nextSibling()) ) ;
			return nvo;
		}
	}
	
	Node* DOM_Tree:: buscarByID(string ID, Node *ptr)
	{
	Node *sol=NULL;	
		if (ptr!=NULL)
		{
			if (!(ptr->element().attributeList().empty()))//si la lista de atributos del elemento NO ES VACIA
			{
				list<string>::iterator it;
				list<string> l;
				l= ptr->element().attributeList();
				it= l.begin();
				///( (((*it)[0]=='i')||((*it)[0]=='I')) && (((*it)[1]=='d')||((*it)[1]=='D')) );
				while (it!=l.end() && !( (((*it)[0]=='i')||((*it)[0]=='I')) && (((*it)[1]=='d')||((*it)[1]=='D')) ))
					++it;
				if(it!= l.end() && ((it->substr(4,it->length()-5))==ID) )
					sol=ptr;
				else
				{
					sol= buscarByID(ID,ptr->nextSibling());
					if(sol==NULL)
						sol= buscarByID(ID,ptr->firstChild());
				}
			}
			else
			{
				sol= buscarByID(ID,ptr->nextSibling());
				if(sol==NULL)
					sol= buscarByID(ID,ptr->firstChild());
			}
		}
		return (sol);
	}
	///consultores
	DOM_Tree DOM_Tree:: childNode(int p)const
	{
		int i=1;
		Node *aux;
		DOM_Tree ab;
		
		if(p>0 && nodeRaiz!=NULL)
		{
			aux=nodeRaiz->firstChild();
			while (aux!=NULL && i<p)
			{
				aux=aux->nextSibling();
				i++;
			}
			ab.nodeRaiz= copiarNode(aux);
			if(ab.nodeRaiz!=NULL)
				ab.nodeRaiz->setNextSibling(NULL);
		}
		return(ab);
	}
	
	DOM_Tree DOM_Tree:: getElementByID(string ID)const
	{
		DOM_Tree ab;

		if(nodeRaiz!=NULL)
		{
			ab.nodeRaiz= copiarNode(buscarByID(ID, nodeRaiz));
			if(ab.nodeRaiz!=NULL)
				ab.nodeRaiz->setNextSibling(NULL);
		}
		return(ab);
	}
	
	///modificadores
	void DOM_Tree:: copiar(const DOM_Tree &aDT)
	{
		if(aDT.nodeRaiz!= NULL)
			nodeRaiz= new Node(aDT.nodeRaiz->element(),copiarNode(aDT.nodeRaiz->firstChild()), NULL);
		else
			nodeRaiz=NULL;
	}
