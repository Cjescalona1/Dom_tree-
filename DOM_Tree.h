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
		///consultores
		Element getRaizDT()const{return(nodeRaiz->element());}
		DOM_Tree childNode(int p)const;
		DOM_Tree getElementByID(string ID)const;
		///modificadores
		void copiar(const DOM_Tree &aDT);
		
		///Destructores
	
};		


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
				it= ptr->element().attributeList().begin();
				while (it!=ptr->element().attributeList().end() && !(it->find("ID")==0))
					++it;
				if(it!= ptr->element().attributeList().end())
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
		}
		return(ab);
	}
	
	DOM_Tree DOM_Tree:: getElementByID(string ID)const
	{
		DOM_Tree ab;

		if(nodeRaiz!=NULL)
			ab.nodeRaiz= copiarNode(buscarByID(ID, nodeRaiz));

		return(ab);
	}
	
