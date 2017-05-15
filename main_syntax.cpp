#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#include "list.cpp"

class etykieta;
class Etykiety;

class wierzcholek:public Element
{
    public:
       string klucz;
       long int EID;
       int color;
       int counter;
       etykieta *E;
       wierzcholek(long int ID):Element(ID){EID=0;color=-1;counter=-1;};
       void Print(string TAB);
       void SaveInFile(ofstream *plik);
	   bool ReadFromFile(ifstream *plik);
       };

class etykieta:public Element
{
    public:
       string text;
       long int wystapienia;
    Etykiety * IncydentneEtykiety;
    etykieta(long int ID);
    ~etykieta(){if (IncydentneEtykiety!=NULL) delete IncydentneEtykiety;}
    void SaveInFile(ofstream *plik);
};

void wierzcholek::Print(string TAB)
       {cout << TAB << "ID: " << ID << " klucz " << klucz << " EID "<< EID << " color " << color << endl;
       };


 void wierzcholek::SaveInFile(ofstream *plik)
    {
    	(*plik) << "vertex" << endl;
		(*plik) << "ID: "<< ID<< endl;
		(*plik) << "Key: "<< klucz<< endl;
		(*plik) << "EID: "<< EID << endl;
	}



	 bool wierzcholek::ReadFromFile(ifstream *plik)
    {
    	char text1[255];
    	long int d;
    	(*plik) >> text1;
    	if (strcmp(text1,"vertex")!=0)
    	  {
    	      cout << "?";exit(1);
		      return false;
		  }
    	(*plik) >> text1 >> ID;
    	if (strcmp(text1,"ID:")==0)
    	{}
    	else
    	{
    	    cout << "?";exit(1);
			return false;
		}
		(*plik) >> text1 >> klucz;
    	if (strcmp(text1,"key:")==0)
    	{}
    	else
    	{
    	    cout << "?";exit(1);
			return false;
		}
		(*plik) >> text1 >> EID;
    	if (strcmp(text1,"EID:")==0)
    	{}
    	else
    	{
    	    cout << "?";exit(1);
			return false;
		}

		return true;
	}



class Etykiety:public List
{ public:
    Etykiety():List("ListaEtykiet"){};
};


etykieta::etykieta(long int ID):Element(ID){wystapienia=0;IncydentneEtykiety=new Etykiety;};


class Wierzcholki:public List
{
    public:
    Wierzcholki():List("ListaWierzcholek"){};
    Element * Create(long int newID){return new wierzcholek(newID);};
};




 void etykieta::SaveInFile(ofstream *plik)
    {
    	(*plik) << "Label" << endl;
		(*plik) << "ID: "<< ID<< endl;
		(*plik) << "text: "<< text<< endl;
		(*plik) << "count: "<< wystapienia << endl;
		(*plik) << "III:" << IncydentneEtykiety->getNumber()
		       << endl;
		Element * temp = IncydentneEtykiety->getFirst();

        while (temp)
        {
            (*plik) << " " << temp->ID;
            temp = temp->getNext();
        }
        (*plik) << endl;
	}



class graf
{
  public:
    Wierzcholki *W;
    Etykiety *E;
    long int ilosc_krawedzi_etykiety;
    graf()
    {
        W=new Wierzcholki;
        E=new Etykiety;
        ilosc_krawedzi_etykiety=0;
    }
    ~graf()
    {
        delete W;
        delete E;
    }
    void ReadFromFile(char * name_plik);

    etykieta * FindEtykieta(string text)
      {
	     etykieta * e=(etykieta*)E->getFirst();
	    while (e)
	{
		if (e->text==text) return e;
		e=(etykieta*)e->getNext();
	}
	return NULL;
    }

void oblicz_krawedzie_etykietowe()
{
    etykieta * temp = (etykieta*)W->getFirst();
    ilosc_krawedzi_etykiety=0;
    while (temp)
    {
        if (temp->IncydentneEtykiety) ilosc_krawedzi_etykiety+=temp->IncydentneEtykiety->getNumber();
        temp=(etykieta*)temp->getNext();
    }
}

wierzcholek * FindWierzcholek(string text)
      {
	     wierzcholek * w=(wierzcholek*)W->getFirst();
	    while (w)
	{
		if (w->klucz==text) return w;
		w=(wierzcholek*)w->getNext();
	}
	return NULL;
    }

void zapisz_M(char * name_pliku)
  {
      ofstream plik;
       plik.open( name_pliku);
       if( plik.good() == false )
         {
         cout << "No access";
         }
       else
       {
         oblicz_krawedzie_etykietowe();
         plik << E->getNumber() << " " << (long int)(ilosc_krawedzi_etykiety/2)<<endl;
         Element * e= E->getFirst();
         while (e)
         {
             etykieta * ee=(etykieta *)e;
             Element * temp = ee->IncydentneEtykiety->getFirst();
            // if (ee->ID==26) {cout << "LLLL"<< ee->ID<<"LLLL";}
            // plik << "...";
            // plik << ee->ID;
            // plik << " ";
            // plik <<  ee->IncydentneEtykiety->getNumber()<< "::";
             while (temp)
             {
                 plik << temp->ID;
                 temp = temp->getNext();
                 if (temp) plik << " ";
             }
             plik << endl;
             e = e->getNext();
         }

       	 plik.close();
	   };
  }
};

void graf::ReadFromFile(char * name_plik)
{
    ifstream plik;
		 plik.open( name_plik);
       if( plik.good() == false )
         {
         cout << "No access"  << "name_plik";
         exit(1);
         }
    string Temp;
    while (!plik.eof( ))
     {
        string s;
       	getline(plik,s);
       	if (!plik.eof( ))
       	{

       	if (s!="(") {cout << "Error 1::"<< s;exit(1);};
       	string klucz1;
       	getline(plik,klucz1);
       	getline(plik,s);
       	if (s=="{")
            {
                if (W->getNumber()%10000==0) cout << W->getNumber()<<endl;
       	        string etykieta1;
                getline(plik,s);
       	        if (s!="v:") {cout << "Error 3::"<< s;exit(1);};
       	        //getline(*plik,s);
       	        //if (s!=":") {cout << "Error 4::"<< s;exit(1);};

                getline(plik,etykieta1);

                getline(plik,s);
       	        if (s!="}") {cout << "Error 5::"<< s;exit(1);};
       	        getline(plik,s);
       	        if (s!=")") {cout << "Error 6::"<< s;exit(1);};

       	        wierzcholek *w = NULL;


                w = FindWierzcholek(klucz1);
                if (w!=NULL)
                {
                    if (w->E==NULL) {cout << "????";exit(1);}
                    if (w->E!=NULL && w->E->text != etykieta1)
                    {
                        cout << "Error key" << klucz1 << "has two labels" << etykieta1 << " " << w->E->text;
                        exit(1);
                    }

                }
            else
                {

       	        w=new wierzcholek(W->getNumber()+1);
                etykieta *e=NULL;
       	        w->klucz=klucz1;
       	        e = FindEtykieta(etykieta1);
       	        if (e==NULL)
                    {
                        e = new etykieta(E->getNumber()+1);
                        e->text=etykieta1;
                        E->Add2End(e);
                    };
                w->E=e;
                w->EID=e->ID;
                e->wystapienia++;
                W->Add2End(w);
                }
       	        //cout << "OK" << endl;
            }
        else if (s==")")
        {
          getline(plik,s);
          if (s!="-[") {cout << "Error 7::"<< s;exit(1);};
          string etykieta1;
          getline(plik,etykieta1);
          getline(plik,s);
          if (s!="]->") {cout << "Error 8::"<< s;exit(1);};
          getline(plik,s);
          if (s!="(") {cout << "Error 9::"<< s;exit(1);};
       	  string klucz2;
       	  getline(plik,klucz2);
       	  getline(plik,s);
          if (s!=")") {cout << "Error 10::"<< s;exit(1);};
        }
        else {cout << "Error 2::"<< s;exit(1);};
       	}
     }
}


main(long int argc, char** argv) {

if (argc>1)
{
 graf *G=new graf();

  {
     string TEMP = string(argv[1])+string(".yars");
     //string TEMP = string(argv[1])+string(".klucz");
				char *cstr = new char[TEMP.length() + 1];
				strcpy(cstr, TEMP.c_str());
     G->ReadFromFile(cstr);
     delete cstr;
   }

       ifstream plik;
       {
           string TEMP = string(argv[1])+string(".txt");
           char *cstr = new char[TEMP.length() + 1];
           strcpy(cstr, TEMP.c_str());

       plik.open( cstr);
       if( plik.good() == false )
         {
         cout << "No access"  << cstr;
         exit(1);
         }
         delete cstr;
       }
       long int n,c;
       string s1,s2,s3;
       plik >> s1 >> s2 >> n >> s3 >> c;
       if (s1!="Seed" && s2!= "matrix" && s3!= "x")
       {
           cout << "Error w pliku";
           exit(1);
       }
       getline(plik,s1);
       getline(plik,s1);

    while (!plik.eof( ))
          {
              char c1,c2;
              long int i,k,C=0;
              plik >> c1 >> i >> c2;
              for (int j=0;j<c;j++)
              {
                  plik >> k;
                  if (k==1) C = j;
              }
              getline(plik,s1);

              wierzcholek *temp=(wierzcholek *)G->W->getFirst();
              while (temp!=NULL)
              {
                  if (temp->EID == i+1 ) {temp->color =  C;}
                  temp=(wierzcholek *)temp->getNext();
              }
          }
        plik.close();
 /*wierzcholek *temp=(wierzcholek *)G->W->getFirst();
 while (temp!=NULL)
              {
                  if (temp->color==-1 ) {temp->Print(" "); cout <<endl;}
                  temp=(wierzcholek *)temp->getNext();
              }
*/

ifstream INput;
{
string TEMP = string(argv[1])+string(".yars");
				char *cstr = new char[TEMP.length() + 1];
				strcpy(cstr, TEMP.c_str());
     INput.open( cstr);
       if( INput.good() == false )
         {
         cout << "No access" << cstr;
         }
}
ofstream OUTput;
{
    string TEMP = string(argv[1])+string(".yarsP");
				char *cstr = new char[TEMP.length() + 1];
				strcpy(cstr, TEMP.c_str());
     OUTput.open( cstr);
       if( OUTput.good() == false )
         {
         cout << "No access" << cstr;
         }
    delete cstr;
}

ofstream OUTput2;
{
    string TEMP = string(argv[1])+string(".yarsC");
				char *cstr = new char[TEMP.length() + 1];
				strcpy(cstr, TEMP.c_str());
     OUTput2.open( cstr);
       if( OUTput2.good() == false )
         {
         cout << "No access" << cstr;
         }
    delete cstr;
}



ofstream OUTputXML;
{
    string TEMP = string(argv[1])+string(".xml");
				char *cstr = new char[TEMP.length() + 1];
				strcpy(cstr, TEMP.c_str());
     OUTputXML.open( cstr);
       if( OUTputXML.good() == false )
         {
         cout << "No access" << cstr;
         }
    delete cstr;
}

//---------------------------------
string Temp;


OUTputXML<< "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\">"<<endl;
OUTputXML<< "<graph>"<<endl;


for (int CC=0;CC<c;CC++)
{
    int Nr =0;

    OUTput2 << "("<< endl;
    OUTput2 << "c"<<CC<< endl;
    OUTput2 << "{"<< endl;
    OUTput2 << "v:"<< endl;
    OUTput2 << "[";

    OUTputXML << "<node id=\"c"<<CC<<"\" label=\"c"<<CC<<"\">"<<endl;
    wierzcholek *temp=(wierzcholek *)G->W->getFirst();
              while (temp!=NULL)
              {
                  if (temp->color == CC )
                    {
                        if (Nr >0) OUTput2 << ",";
                        Nr++;
                        OUTput2 << temp->E->text;
                        temp->counter=Nr;
                        OUTputXML << "\<data key=\"v"<<Nr<<"\">"<< temp->E->text <<"</data>"<<endl;
                    }
                  temp=(wierzcholek *)temp->getNext();
              }
    OUTput2 << "]"<<endl;
    //OUTput2 << "Counter:"<<endl;///Bonus
    //OUTput2 << Nr<<endl;///Bonus
    OUTput2 << "}"<<endl;
    OUTput2 << ")"<<endl;
    OUTputXML << "</node>"<<endl;


    /*
    <node id="c1" label="c1">
<data key="v1">bla</data>
<data key="v2">bla</data>
</node>
*/

}

    while (!INput.eof( ))
     {
        string s;
       	getline(INput,s);
       	if (!INput.eof( ))
       	{
       	if (s!="(") {cout << "Error 1::"<< s;exit(1);};
       	string klucz1;
       	getline(INput,klucz1);
       	getline(INput,s);
       	if (s=="{")
            {
       	        string etykieta1;
                getline(INput,s);
       	        if (s!="v:") {cout << "Error 3::"<< s;exit(1);};
                getline(INput,etykieta1);

                getline(INput,s);
       	        if (s!="}") {cout << "Error 5::"<< s;exit(1);};
       	        getline(INput,s);
       	        if (s!=")") {cout << "Error 6::"<< s;exit(1);};

       	        wierzcholek *w = NULL;
                w = (wierzcholek *)G->FindWierzcholek(klucz1);
                if (w==NULL){cout << "????";exit(1);}
                else
                {
                    OUTput << "("<< endl;
                    OUTput << klucz1<< endl;
                    OUTput << "{"<< endl;
                    OUTput << "v:"<< endl;
                    OUTput << etykieta1<< endl;
                    OUTput << "ID:"<< endl; // bonus
                    OUTput << w->ID<< endl;  // bonus
                    OUTput << "Color:"<< endl;  // bonus
                    OUTput << w->color<< endl;  // bonus
                    OUTput << "}"<< endl;
                    OUTput << ")"<< endl;


                }


                //cout << "OK" << endl;
            }
        else if (s==")")
        {
          getline(INput,s);
          if (s!="-[") {cout << "Error 7::"<< s;exit(1);};
          string etykieta1;
          getline(INput,etykieta1);
          getline(INput,s);
          if (s!="]->") {cout << "Error 8::"<< s;exit(1);};
          getline(INput,s);
          if (s!="(") {cout << "Error 9::"<< s;exit(1);};
       	  string klucz2;
       	  getline(INput,klucz2);
       	  getline(INput,s);
          if (s!=")") {cout << "Error 10::"<< s;exit(1);};
          wierzcholek *w1=G->FindWierzcholek(klucz1);
          wierzcholek *w2=G->FindWierzcholek(klucz2);
          if (w1==NULL||w2==NULL){cout << "Error 11::"<< s;exit(1);};
              OUTput << "("<< endl;
              OUTput << klucz1<< endl;
              OUTput << "Color:"<< endl;  // bonus
              OUTput << w1->color<< endl;  // bonus
              OUTput << ")"<< endl;
              OUTput << "-["<< endl;
              OUTput << etykieta1<< endl;
              OUTput << "]->"<< endl;
              OUTput << "("<< endl;
              OUTput << klucz2<< endl;
              OUTput << "Color:"<< endl;  // bonus
              OUTput << w2->color<< endl;  // bonus
              OUTput << ")"<< endl;




              OUTput2 << "("<< endl;
              OUTput2 << "c" << w1->color<< endl;
              OUTput2 << ")"<< endl;
              OUTput2 << "-[";//<< endl;
              OUTput2 << etykieta1;//<< endl;
              OUTput2 << "{kl:"<<w1->counter<<",kr:"<<w2->counter<<"}";
              OUTput2 << "]->"<< endl;
              OUTput2 << "("<< endl;
              OUTput2 << "c"<<w2->color<< endl;  // bonus
              OUTput2 << ")"<< endl;


              OUTputXML << "<edge source=\"c"<<w1->color<<"\" target=\"c"<<w2->color<<"\" label=\""<<etykieta1<<"\">"<<endl;
              OUTputXML <<"<data key=\"kl\">"<< w1->counter << "</data>"<<endl;
              OUTputXML <<"<data key=\"kr\">"<< w2->counter << "</data>"<<endl;
              OUTputXML <<"</edge>"<<endl;

        }
       	}
     }
//-----------------------


OUTputXML<< "</graph>"<< endl;
OUTputXML<< "</graphml>"<<endl;





INput.close();
OUTput.close();
OUTput2.close();
OUTputXML.close();


//G->W->Print(" ");

   delete G;
}
else{cout << "brak parametrow";}

}
