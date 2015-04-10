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
		void removeChild(int p);
		void appendChild(int p, const DOM_Tree &nvo);
		void appendChild(const DOM_Tree &nvo);
		void replaceChild(int p, const DOM_Tree &nvo);
		
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
	
	
	
	void DOM_Tree:: removeChild(int p)
	{
		int i=1;
		Node *aux;
		DOM_Tree ab;

		if(p>0 && nodeRaiz!=NULL && nodeRaiz->firstChild()!= NULL)
		{
			if (p==1)
			{
				ab.nodeRaiz=nodeRaiz->firstChild();
				nodeRaiz->setFirstChild(nodeRaiz->firstChild()->nextSibling());
				ab.nodeRaiz->setNextSibling(NULL);
				ab.vaciarDT();
			}
			else
			{
				aux=nodeRaiz->firstChild();
				while (aux!=NULL && i<p-1)
				{
					aux=aux->nextSibling();
					i++;
				}
				if (aux!=NULL && aux->nextSibling()!=NULL)
				{
					ab.nodeRaiz= aux->nextSibling();
					aux->setNextSibling(ab.nodeRaiz->nextSibling());
					ab.nodeRaiz->setNextSibling(NULL);
					ab.vaciarDT();
				}
			}
			
			ab.nodeRaiz=NULL;
		}
	}
	void DOM_Tree:: appendChild(int p, const DOM_Tree &nvo)
	{
		int i=1;
		Node *aux;
		DOM_Tree ab;

		if(p>0 && nodeRaiz!=NULL && nvo.nodeRaiz!=NULL)
		{
			ab.copiar(nvo);
			if(nodeRaiz->firstChild()==NULL && p==1)
				nodeRaiz->setFirstChild(ab.nodeRaiz);
			else if(nodeRaiz->firstChild()!=NULL)
			{
				if(p==1)
				{
					ab.nodeRaiz->setNextSibling(nodeRaiz->firstChild());
					nodeRaiz->setFirstChild(ab.nodeRaiz);
				}
				else
				{
					aux=nodeRaiz->firstChild();
					while (aux!=NULL && i<p-1)
					{
						aux=aux->nextSibling();
						i++;
					}
					if(aux!=NULL)
					{
						ab.nodeRaiz->setNextSibling(aux->nextSibling());
						aux->setNextSibling(ab.nodeRaiz);
					}
				}
			}
			ab.nodeRaiz=NULL;
		}
	}



	void DOM_Tree:: appendChild(const DOM_Tree &nvo)
	{
		Node *aux;
		DOM_Tree ab;

		if(nodeRaiz!=NULL)
		{
			ab.copiar(nvo);
			if(nodeRaiz->firstChild()==NULL)
				nodeRaiz->setFirstChild(ab.nodeRaiz);
			else
			{
				aux=nodeRaiz->firstChild();
				while (aux->nextSibling()!=NULL)
					aux=aux->nextSibling();
				aux->setNextSibling(ab.nodeRaiz);
			}
			ab.nodeRaiz=NULL;
		}
	}
	
	
	
	void DOM_Tree:: replaceChild(int p, const DOM_Tree &nvo)
	{
		int i=1;
		Node *aux, *rpc;
		DOM_Tree ab;

		if(p>0 && nodeRaiz!=NULL && nvo.nodeRaiz!=NULL && nodeRaiz->firstChild()!=NULL)
		{
			if (p==1)
			{
				rpc=nodeRaiz->firstChild();
				ab.copiar(nvo);
				ab.nodeRaiz->setNextSibling(rpc->nextSibling());
				nodeRaiz->setFirstChild(ab.nodeRaiz);
				ab.nodeRaiz=rpc;
				ab.nodeRaiz->setNextSibling(NULL);
				ab.vaciarDT();
			}
			else
			{
				aux=nodeRaiz->firstChild();
				while (aux!=NULL && i<p-1)
				{
					aux=aux->nextSibling();
					i++;
				}
				if(aux!=NULL)
				{
					rpc=aux->nextSibling();
					if (rpc!=NULL)
					{
						ab.copiar(nvo);
						ab.nodeRaiz->setNextSibling(rpc->nextSibling());
						aux->setNextSibling(ab.nodeRaiz);
						ab.nodeRaiz=rpc;
						ab.nodeRaiz->setNextSibling(NULL);
						ab.vaciarDT();
					}
				}
			}
			ab.nodeRaiz= NULL;
		}
	}
	
