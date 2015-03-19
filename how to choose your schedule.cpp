/*this short program is trying to help people from making decisions of course selecting 
and timetable arrangement. i think true human dicision-making can be traced, but factors
that human considers when they make dicisions is way too much to be programmed, aside
from how the courses and teachers are, they might also consider the classmates and
even the classroom. i believe, that decision making could be complete with huge database
and a series of prior rankings of each factor. 

EXAMPLE INPUT FILE
MA103 math1 WY@

number name teacher@            @is used to identify the end of a line;

                                                                Evan Yang
*/
#include <fstream>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
using namespace std;
ifstream scheduleR;
ofstream resultoutput;
struct course{                                                                                                          //perpose of setting up a node structure is it could help restoring        
    string number;                                                                                                      //different categories of information of a course
    string name;
    string teacher;                                                                 
    float measure;                                                                                                      //a number from 1-10 measuring how do you like a teacher and a class, teacher and class each for 5 points
    course *next;
    course *pre;
};

int main()
{
 float coursefactor, teacherfactor; 
 scheduleR.open("schedule.txt");
 course *one = new course;  
 one -> pre = NULL;                                                                                                     //meaning the first course being input
 course *end = NULL;
 course *temp= one;
 string compulsory;
 int totalnum = 0;
 int coursecount = 0;
 int loopfactor;
 string Cclass[9];
 while(!scheduleR.eof())
    {
        char inputline[100];
        int i = 0;
        scheduleR.getline(inputline,100);
        for(;; i++)                                                                                                     //input every element one by one into the node link
         {
            if(inputline[i] != ' ')                                                                                     //if it scans a space, which is the sign of another element, break
                {
                    temp -> number = temp -> number + inputline[i];
                    continue;
                }
            else
                break;
        }
        
        i++;
        
        for(;; i++)
         {
            if(inputline[i] != ' ')
            {
                temp -> name = temp -> name + inputline[i];
                continue;
            }
            else
                break;
        }        
        
        i++;
        for(;; i++)
         {
            if(inputline[i] != '@')                                                                                     // @ means end of a line, as an identifier. i hope nobody's
            {                                                                                                           //name ends with @;        
                temp -> teacher = temp -> teacher + inputline[i];
                continue;
            }
            else
                break;
        }
        i++;
                                                                                                                        //in different system, the "newline" is different, some is
                                                                                                                        ///n, some is /r/n. here the time table could use a character
        course *transfer = temp;                                                                                        //instead of long name, for example, A for monday 9:00
        temp = new course;
        transfer -> next = temp;
        temp -> pre = transfer;                             
    }
    temp->pre->next = NULL;
    temp = one;               
    scheduleR.close();
                                                                                                                        //following is to determind a factor for teacher & course
    cout<<"how much do you weight your course and teacher in your dicision?"<<endl;
    cout<<"type in a number after prompt, sum of the two numbers must be ten"<<endl;
    recin:
    cout<<"course?"<<endl;
    cin>>coursefactor;
    cout<<"teacher?"<<endl;
    cin>>teacherfactor;
    if(coursefactor + teacherfactor != 10)
    {
        cout<<"sum must be ten!"<<endl;
        goto recin;
    } 
 
 while(1)                                                                                                               //note******* future add load and save to end of this section    
    {                                                                                                                   //so people could save their valuation of course and only need    
        cout << "From 0 to 10, how much do you like this course?" << endl;                                              //to change or add those they want to change instead of typing 
                                                                                                                        //again.
        temp -> measure = 0;
        int i;
        retypeC:
        cout << temp -> name << endl;
        cin >> i;
    
        if (i <= 10 && i >= 0)
            temp -> measure = i * coursefactor/10;
        else
        {
            cout << "From 0 to 10, please!" << endl;
            goto retypeC;   
        }
        if(temp -> next == NULL)
            break;
        else
            temp = temp -> next;   
    }
    temp = one;
                                                                                                                        //end of first correctiction   date 15.2.5
                                                                                                                        //input teacher's number, to avoid creating more complicated code
 string teacherstorage[50];                                                                                             //here i choose 50 as a top number, which could be changed
 float teachernumber[50];
 int Tstoragenum=0; 
 while(1)
    {
        teacherstorage[Tstoragenum] = temp -> teacher;
        Tstoragenum += 1;
        for(int loopfactor = 0; loopfactor < Tstoragenum-1; loopfactor++ )
        if (teacherstorage[loopfactor] == temp -> teacher)
        {
            temp -> measure += teachernumber[loopfactor];
            goto Nex;
        }
        cout << "From 0 to 10, how much do you like this teacher?"<<endl;
        retypeT:
        cout << temp -> teacher <<endl;
        cin >> teachernumber[Tstoragenum-1];
        if(teachernumber[Tstoragenum-1] > 10 || teachernumber[Tstoragenum-1] <0 )
        {
            cout << "From 0 to 10, please!" << endl;
            goto retypeT;            
        }
        else
            teachernumber[Tstoragenum-1] = teachernumber[Tstoragenum-1] * teacherfactor /10;
        temp -> measure += teachernumber[Tstoragenum-1];       
    Nex:1
        if(temp -> next == NULL)
            break;
        else
            temp - temp -> next;           
    }

 cout << "how many course would you like to attend in this semester?" << endl;
 cin >> totalnum;

 cout << "what are you compulsory courses? type in their NO." <<endl;                                                   //in my school courses are labeled as these abbreviations as 
 cout << "Math -> MA, Physics -> PH, Chemistry -> CM" <<endl;                                                           //prefix.
 cout << "Biology -> BI, History -> HL,Geography -> GE" <<endl;
 cout << "Politics -> PO, Chinese -> CH, English -> EN" <<endl;
 cout << "please put them in one line:)" <<endl; 
 getline(cin, compulsory);                                                                                              //to avoid being skipped by the last /n typed in when input
 getline(cin, compulsory);                                                                                              //teacher number
 
 int temporary = 0;
 
 resultoutput.open("recommended choices.txt");
 for ( loopfactor = 0; loopfactor < compulsory.size(); loopfactor++)
 {
    if (compulsory[loopfactor] != ' ')
    {
        Cclass[temporary][0] = compulsory[loopfactor];
        Cclass[temporary][1] = compulsory[loopfactor+1];
        loopfactor+=2;
        temporary++;
    }  
 }
 
 for ( loopfactor = 0; loopfactor < temporary; loopfactor++)                                                            //compulsory course choose
 {
    course *transfer;
    temp = one;      
    char name1, name2;
    string courseN;
    courseN[0] = temp -> number[0];
    courseN[0] = temp -> number[1];
    int ifthecourseexist=0;
    if (courseN == Cclass[loopfactor]) 
    transfer = one;
    while(temp != NULL)
    {
        courseN[0] = temp -> number[0];
        courseN[0] = temp -> number[1];    
        if (courseN == Cclass[loopfactor]) 
        {
            transfer = temp;   
            ifthecourseexist++;
            break;
        }
        temp = temp -> next;
    }
    while(temp != NULL && temp -> next != NULL)
    {
        temp = temp -> next;
        courseN[0] = temp -> number[0];
        courseN[0] = temp -> number[1];
        if (courseN == Cclass[loopfactor] && temp -> measure > transfer -> measure) 
        {
            ifthecourseexist++;
            transfer = temp;   
        } 
    }
    if(ifthecourseexist!=0)
    {
        resultoutput << transfer -> number << " " << transfer -> name << " " << transfer -> teacher << endl;
        if(transfer == one)
        {   
            if (transfer -> next == NULL)
            goto END;
            transfer -> next -> pre = NULL;
            one = one -> next;
        }
        else
        {
            transfer -> pre -> next = transfer -> next;
            transfer -> next -> pre = transfer -> pre;
        }

        delete transfer;
        coursecount++;  
    }
    else
        resultoutput << "there is no course under the subject " << Cclass[loopfactor] <<endl;
 }
 
 temp = one;
 if (temp == NULL)
    goto END;
 if (temp -> next != NULL)                                                                                              //other course choose
    if (temp -> measure > one -> measure)
    {
        one -> next = temp -> next;
        temp -> next = one;
        one -> pre = temp;
        temp -> pre = NULL;
        one = temp;
        temp = one -> next;
    }
 if(temp -> next == NULL)
    goto output;
 
 course *transfer1, *transfer2;
 loopfactor = 0;
 while(loopfactor > -1 )            
    {    
        transfer1 = temp;
        temp = temp -> next;
        if (temp == NULL)
            loopfactor = -2;
        transfer2 = one;
        while (transfer2 -> next != temp && transfer1 != NULL && transfer2 != NULL )
        {
            if(transfer1 -> measure > transfer2 -> measure)
            {
                transfer1 -> pre -> next = temp;
                temp -> pre = transfer1 -> pre; 
                transfer1 -> pre = transfer2 -> pre;
                transfer2 -> pre = transfer1;
                transfer1 -> next = transfer2;
                break;   
            }      
            transfer2 = transfer2 -> next;
        }     
    }   
 output:
 temp = one;
 for (loopfactor = 1; loopfactor < (totalnum - coursecount); loopfactor++)                                              //output other course result
 {
    resultoutput << temp -> number << " " << temp -> name << " " << temp -> teacher << endl;     
    temp = temp -> next;
    if (temp == NULL)
    {
        cout << "course is not enough!" <<endl;
        break;     
    }
 }       
 resultoutput.close();
        
 END:
 cout << "recommend choice had been output to recommended choices.txt " <<endl; 
 system("pause");
 return 0;
}
