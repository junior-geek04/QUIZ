/****************************\
Header files required
\****************************/


#include<string.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<process.h>


char A[80] ;
char B[80] ;


/*****************************************\
Class ques
\*****************************************/

class ques
{
 public:
 int compno ;

 char str[80] ;
 char A[20],B[20],C[20],D[20] ;

 char ans ;

/*********************************\
Member Function for entering the details
\*********************************/
  void enter()
  {
   cout<<"\nEnter the question\n" ;
   gets(str);
   cout<<"\n Enter the options" ;
   cout<<"\nA:" ; gets(A) ;
   cout<<"\nB:" ; gets(B) ;
   cout<<"\nC:" ; gets(C) ;
   cout<<"\nD:" ; gets(D) ;
   cout<<"\nEnter answer " ;
   cin>>ans ;
	;
   ;
 }

 /**********************************\
 Member function for displaying the
 details
 \**********************************/

 void display()
 {
   cout<<"\n"<<compno<<"."<<str<<"\n"<<"A)"<<A<<"\tB)"<<B<<"\nC)"<<C<<"\tD)"<<D ;

 }

} ;

/***************************\
Function for entering a
question in the file
\***************************/

void enterques(char fnm[80])
{ ques Q ; ques Q1   ;

 ifstream fin ;
 fin.open(fnm,ios::binary) ;
 if(!fin)
	Q.compno =1;
 else
 {

 fin.seekg(0) ;
 while(fin.read((char*)&Q1,sizeof(Q1)))
 {
	Q.compno = Q1.compno + 1 ;
 }
 }
 fin.close();
 ofstream fout ;
 fout.open(fnm ,ios::app|ios::binary) ;
 if (!fout)
	   cout<<"Error";
 else
 {
 cout<<"\nQuestion No. : "<<Q.compno<<"\n" ;
 Q.enter() ;
 fout.write((char*)&Q,sizeof(Q)) ;
 }
 fout.close();
}

/************************\
Function for displaying
the details
\************************/

void displall(char fn[])
{
ques Q;
ifstream fin;
fin.open(fn,ios::binary);
if (!fin)
  cout<<"Error";
else
{
fin.seekg(0);
while(fin.read((char *)&Q,sizeof(Q)))
  {	Q.display();
	cout<<"\n" ;
  }

}
fin.close();
}

/******************************\
Function for deleting a question
\******************************/

void deleteques(char fnm[80])
{ ofstream fout ;
  ifstream fin ;
  ques Q ;
  int q ;
  cout<<"\nEnter ques no\n ";
  cin>>q ;
  fin.open(fnm,ios::binary )  ;
  fout.open("temp",ios::binary) ;
  fin.seekg(0) ;
  int flag =0;
  while(fin.read((char*)&Q,sizeof(Q)))
  {
  if(Q.compno<q)
	  fout.write((char*)&Q,sizeof(Q)) ;

  else
	if(Q.compno==q)
	  {
	   flag=1;
	   break;
	   }
  }
  if (flag==1)
  {
	while(fin.read((char*)&Q,sizeof(Q)))
	 {
	   Q.compno-=1;
	   fout.write((char*)&Q,sizeof(Q)) ;
	 }
  }
  else
   if(flag==0)
	cout<<"\nQues Not found\n" ;

  fout.close() ;
  fin.close();
  remove(fnm) ;
  rename("temp",fnm) ;

  if(flag==1)cout<<"\nQues Deleted Successfully\n" ;


}
/**********************************\
Function for modifying a question
\**********************************/



void modifyques(char fnm[80])
{ fstream finout ;
  int ch ;  int flag=0 ;
  ques Q ,Q1 ;
  cout<<"\nEnter the desired question no. \n " ;

  cin>>Q1.compno ;
  Q1.enter() ;
  finout.open(fnm,ios::in|ios::out|ios::binary)  ;
  if(!finout)cout<<"\nError" ;
 else
 {
  finout.seekg(0) ; long int P ;
  while(!finout.eof()&& flag==0)
  {
	P = finout.tellg() ;
	finout.read((char*)&Q,sizeof(Q)) ;

	if(Q.compno==Q1.compno)
	{
	  flag=1 ;


	   finout.seekp(P)  ;
	   finout.write((char*)&Q1,sizeof(Q1)) ;

	   break ;
	}

  }
	 if(finout.eof() || flag==0)
	   cout<<"\nNot Found\n" ;



	  finout.close();
	  cout<<"\nModified successfully\n" ;

 }
}

/************************************\
Function for managing the quiz
\************************************/

void check(char fnm[80])
{
  int  choice ; int p ; int n ; float score = 0;
  ifstream fin ; ques Q ;
  int i ; int c = 0 ;
  clrscr() ;

  cout<<"\nInstructions\n" ;
  cout<<"1. Each question has ONLY one correct answer \n"  ;
  cout<<"2. Giving a correct answer earns you +4 marks \n" ;
  cout<<"3. Giving an incorrect response or not attempting a question do not change your score\n";
  cout<<"4. Please answer by entering only valid options and not more than one character \n";
  cout<<"5. There is no choice \n" ;
  cout<<"6. If you want to skip the question, enter 0 as your answer\n" ;
  cout<<"7. Answers cannot be changed. Skipped questions cannnot be answered again \n";
  cout<<"8. Your score will be displayed once you complete your quiz \n";

  for(int j =0 ; j<=5000; j++) ;

  cout<<"\nWant to play a quiz of \n"  ;
  cout<<"1. 10 ques \n2. 20 ques \n 3. 30 ques  \n4. exit \ " ;

  cin>>choice ;

  switch(choice)
  {
	case 1 : p = 10 ; break ;
	case 2 : p = 20 ; break ;
	case 3 : p = 30 ; break ;
	case 4 : exit(0) ; break ;
	default : cout<<"\nInvalid choice\n" ;
  }
   cout<<"\n"<<p ;

  fin.open(fnm , ios::binary) ;
  fin.seekg(0) ;
  c = 0 ;

  while(!fin.eof())
  {fin.read((char*)&Q,sizeof(Q)) ;
  }

  n = Q.compno ;

  fin.seekg(0) ;
  randomize() ;

  while(c<p)
  {

	i = random(n) +1  ;
	int pp =sizeof(Q) * (i-1) ;
	fin.seekg(pp , ios::beg) ;
	fin.clear() ;

	 if(fin.bad())
	   cout<<"\nBAD\n" ;

	fin.read((char*)&Q,sizeof(Q)) ;
	B[c] = Q.ans  ;

	clrscr() ;
	cout<<'\n' ;

	Q.display() ;

	cout<<"\n" ;
	cout<<"\n Enter answer\n" ;
	cin>>A[c] ;

	c++ ;
  }

  fin.close() ;

  for(i =0 ; i<p ; i++)
  {
	if(A[i]==B[i])
	 score+=4 ;
  }

  clrscr() ;
  cout<<"\n   Thank you for taking the quiz \n " ;
  cout<<"\n   Your total score = "<<score ;
  cout<<"\n   Your realtive percentage ="<< (float)((score /40)*100) ;
  cout<<"\n ";

}

/*****************************\
Execution of the program
\*****************************/

void main()
{ clrscr() ;
  int ch; char cho; char fnm[25] ;
  strcpy(fnm,"DIVPRA") ;
  int freq ;

do
{
  clrscr() ;
  cout<<"\n 1.Play \n 2.Settings\n 3.exit ";
  cin>>freq ;

  if((freq!=1)&&(freq!=2)&&(freq!=3))
   cout<<"\nError\n";
  else
 {  if(freq==3)
	 exit(0) ;

   else
 { if(freq==1)
   check(fnm) ;

  else
   if(freq==2)
  {


 clrscr() ;
 cout<<"\MAIN MENU\n1.Add question \n2.Delete question \n3.Display all questions\n4.Modify question\n";
 cin>>ch;

 if (ch==1)
 enterques(fnm) ;
 else
 if (ch==2)
	   deleteques(fnm);
 else
 if(ch==3)
	   displall(fnm);
 else
 if(ch==4)
	   modifyques(fnm) ;

  }

 }

 }

 cout<<"\ncontinue?\n";
 cin>>cho;

}while(cho=='y');

}


