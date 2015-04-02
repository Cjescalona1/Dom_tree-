#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Element
{
	private:
		string Tag, Inner;
		list<string> Listattr;
	public:
		///constructores
		Element():Tag(""), Inner(""), Listattr(){};
		Element(string tag): Tag(tag), Inner(""), Listattr(){};
		Element(string tag, const list<string> &l1): Tag(tag), Listattr(l1){} 
	  	Element(string tag, string inner): Tag(tag), Inner(inner), Listattr(){}
		Element(string tag, string inner, const list<string> &l1): Tag(tag), Inner(inner), Listattr(l1){};

		///consultores
		string tagName() const{return(Tag);}
		list<string> attributeList() const{return(Listattr);}
		string innerHTML() const {return(Inner);}

		///modificadores
		void setTagName(const string &tag){this->Tag=tag;}
		void setAttributeList(const list<string> &l1){this->Listattr= l1;}
		void setInnerHTML(const string &inner){this->Inner= inner;}

		///sobreCargas
		bool operator==(const Element& e2) const{return((Tag==e2.Tag) && (Inner==e2.Inner)&& (Listattr==e2.Listattr));}
		bool operator!=(const Element& e2) const{return(!((*this)==e2));}
		void operator=(const Element& e2){Tag=e2.Tag;Inner=e2.Inner;Listattr=e2.Listattr;}
		friend istream& operator>> (istream& is, Element& ex){is>> ex.Tag;return is;}
		friend ostream& operator<< (ostream& os, const Element& ex){os<<ex.Tag;return os;}
};
#endif
