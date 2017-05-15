#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Element
{
	private:
	  Element *previous,
	          *next;
	public:
		long int ID;
	Element * getPrevious() {
        return previous;
	};
	Element * getNext() {
        return next;
	};
	void setPrevious(Element *NewPrevious) {
        previous=NewPrevious;
	};
	void setNext(Element *NewNext) {
        next=NewNext;
	};
	void setID(long int NewID) {
        ID=NewID;
	};
	Element() {
        setPrevious(NULL);
        setNext(NULL);
        setID(0);
	};
	Element(long int newID) {
        setPrevious(NULL);
        setNext(NULL);
        setID(newID);
	};
	virtual void Print(string TAB) {
        { cout << TAB << "ID:" << ID << endl;}
	};
    virtual void SaveInFile(ofstream *plik) {
    	(*plik) << "Element" << endl;
		(*plik) << "ID: "<< ID<< endl;
    };
	virtual bool ReadFromFile(ifstream *plik) {
    	char text1[255];
    	long int d;
    	(*plik) >> text1;
    	if (strcmp(text1,"Element")!=0)
    	  {
		  return false;}
    	(*plik) >> text1 >> d;
    	if (strcmp(text1,"ID:")==0)
    	{ID = d;}
    	else
    	{
			return false;
		}
		return true;
	};
};

class List
{
	private:
		string name;
		Element * first,
	            * last;
        long int number;
	public:
	void setName(string Name) {
        name=Name;
	};
	Element * getFirst() {
        return first;
	};
	Element *getLast() {
        return last;
	};
	long int getNumber() {
        return number;
	};
	void setFirst(Element *NewFirst) {
        first=NewFirst;
	};
	void setLast(Element *NewLast) {
        last=NewLast;
	};
	string getName() {
        return name;
	};
	List() {
        setFirst(NULL);
        setLast(NULL);
        number=0;
        setName("Brak");
	};
	List(string NewName) {
        setFirst(NULL);
        setLast(NULL);
        number=0;
        setName(NewName);
	};
	~List() {
        Element *E=getFirst(),*Temp;
        while (E)
        {
          Temp=E->getNext();
          delete E;
          E=Temp;
        }
	};
	void AddCopyList(List *L) {
		Element * Temp=L->getFirst();
		while (Temp)
		{
			Add2End(Copy(Temp));
			Temp=Temp->getNext();
		}
    };
	virtual void PrintHead(string TAB) {
		cout <<TAB<< "List:" << name << endl;
	    cout <<TAB<< "number: " << number << endl;
	};
	void Print(string TAB) {
	    PrintHead(TAB);
	    Element * Temp = getFirst();
	    while (Temp)
	    {
		   Temp->Print(TAB+"  ");
	       Temp=Temp->getNext();
		};
	};
	void Add2End(Element *E) {
		if (getFirst())
		{
			getLast()->setNext(E);
			E->setPrevious(getLast());
			setLast(E);
			number++;
		}
		else
		{
			setFirst(E);
			setLast(E);
			number=1;
		};
	};
	void Add2Begin(Element *E) {
		if (getFirst())
		{
			getFirst()->setPrevious(E);
			E->setNext(getFirst());
			setFirst(E);
			number++;
		}
		else
		{
			setFirst(E);
			setLast(E);
			number=1;
		};
	};
	virtual bool Less(Element *A,Element *B) /*czy A < B */{
		if (A->ID < B->ID)
		{return true;
		}
		else
		{return false;
		}
	};

	virtual bool Equal(Element *A,Element *B) /*czy A==B */ {
		if (A->ID == B->ID)
		{
            return true;
		}
		else
		{
            return false;
		}
	};

	void AddSort(Element *E) /*dodaje sortuj¹c po Less Equal*/ {
		if (getFirst())
		{

			if (Less(getFirst(),E)==false)
			    {Add2Begin(E);}
			else
			   if (Less(E,getLast())==false)
			      {Add2End(E);}
			   else
			   {
			   	  Element *WciazMniejszy=getFirst();
			   	  while(WciazMniejszy && WciazMniejszy->getNext() &&
					     Less(WciazMniejszy->getNext(),E)//==true
						 )
			   	  {
					 WciazMniejszy=WciazMniejszy->getNext();
				  }

				  WciazMniejszy->getNext()->setPrevious(E);
				  E->setNext(WciazMniejszy->getNext());
				  E->setPrevious(WciazMniejszy);
				  WciazMniejszy->setNext(E);
				  number++;

			   }

		}
		else
		{
			setFirst(E);
			setLast(E);
			number=1;
		}

	};

	Element * Copy(Element *E) {
        return new Element(E->ID);
	};
	virtual Element * Create(long int newID) {
        return new Element(newID);
	};
	void Remove(Element *E) {
		if (Belongs(E))
		{

		if (E==getFirst())
		   {
		   	 number--;
		   	 setFirst(getFirst()->getNext());
		   	 if (getFirst()) getFirst()->setPrevious(NULL);
		   }
		else if (E==getLast())
		  {
		  	 number--;
		  	 setLast(getLast()->getPrevious());
		   	 getLast()->setNext(NULL);
		  }
		else
		{
             E->getPrevious()->setNext(E->getNext());
             E->getNext()->setPrevious(E->getPrevious());
			 number--;
		}
	    }
	    else
	    {

		   cout << "Element nie nalezy do listy";;
        }

	};
	bool Belongs(Element *E) {
		Element *Temp=getFirst();
		while(Temp)
		{
		   if (Temp==E) return true;
		   Temp=Temp->getNext();
		}
		return false;
	};
	void SaveInFile(char* name_pliku) {
	   ofstream plik;
       plik.open( name_pliku);
       if( plik.good() == false )
         {
         cout << "no access";
         }
       else
       {
         SaveInOpenFile(&plik);
       	 plik.close();
	   };
	};
    void ReadFromFile(char * name_plik) {
	 	ifstream plik;
		 plik.open( name_plik);
       if( plik.good() == false )
         {
         cout << "no access";
         }
       else
       {
       	 ReadFromOpenFile(&plik);
       	 plik.close();
	   };
    };
	virtual void SaveInOpenFile(ofstream *plik) {
	     *plik << "name: "<< name<< endl;
       	 *plik << "number: " << number<< endl;
       	 Element * Temp=getFirst();
	      while(Temp)
	      {
	   	  Temp->SaveInFile(plik);
	   	  Temp=Temp->getNext();
	      }
	};
	virtual bool ReadFromOpenFile(ifstream *plik) {
	 	char text1[255], text2[255];
       	*plik >> text1;// >> text2;
        string s;
       	getline(*plik,s);

       	if (strcmp(text1,"name:")==0)
         {
         	setName(s);
		  }
		  else
		  {
		  	  cout << "corrupted file List1:::"<< text1<<":::";
		  }
		long int number_temp;
		*plik >> text1 >> number_temp;

		if (strcmp(text1,"number:")==0)
         {
		    ///numer jest obliczany przez funkcjê Add2End
		  }
		  else
		  {
		  	cout << "corrupted file List2:::" << text1<<":::";
		  };

		for (long int i =0;i<number_temp;i++)
		{
			Element *E = Create(0);
			if (E->ReadFromFile(plik))
			   {
			      Add2End(E);
			    }
			else {
				cout << "error: read element";
			delete E;}
		}
	};

    Element * Find(long int ID) {
        Element * E=getFirst();
        while (E)
        {
            if (E->ID==ID) return E;
            E=E->getNext();
        }
        return NULL;
    };

};


