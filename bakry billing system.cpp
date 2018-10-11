#include<iostream>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<conio.h>

using namespace std;
ifstream fin;
ofstream fout;
fstream inoutfile;

class INVENTORY{
 public:
 int itemCode,itemPrice;
 char itemName[15];
 
 void putdata();
 void getdata();
 void update();
 void addItem();
 void showList();
  
}item;
 

void INVENTORY::getdata()
 {
  cout<<"\n\t\tItem code:";
  cin>>itemCode;
  cout<<"\n\t\tItem Name:";
  cin>>itemName;
  cout<<"\n\t\tItem Price:";
  cin>>itemPrice;
 }

void INVENTORY::putdata()
{
  cout<<"\t\t"<<itemCode<<"\t\t"<<itemPrice<<"\t\t"<<itemName<<endl;  
}

void INVENTORY::update()
{
 int code,flag=0;
 cout<<"\n\n\t\t<<<<<<<<<<<<<<<<<<<<UPDATE ITEM DETAIL>>>>>>>>>>>>>>>>>>>\n\n";
 cout<<"\n\t\tEnter itemCode to be Update: ";
 cin>>code;
 inoutfile.open("ITEM_MENU.dat");
 while(inoutfile.read((char*)&item,sizeof(item)))
 {  
  if(code==item.itemCode);
  {
   item.getdata();
   flag=1;
   break;
  }  
 }
 if(flag==1)
 {
  inoutfile.write((char*)&item,sizeof(item)); 
  cout<<"\n\n\t\tItem Updated Successfully...";
 }
 else
  cout<<"\n\n\t\tEntered itemCode is not available..."<<endl;
 inoutfile.close();
}  
void INVENTORY::addItem()
{
 fout.open("ITEM_MENU.dat",ios::app);
 item.getdata();        
 fout.write((char*)&item,sizeof(item));
 fout.close();
}
void INVENTORY::showList()
{
 cout<<"\n\n\t\t<<<<<<<<<<<<<<<<<<<<ITEM MENU>>>>>>>>>>>>>>>>>>>\n\n";     
    fin.open("ITEM_MENU.dat");    
    cout<<"\t\t-------------------------------------------------";
    cout<<"\n\t\titemCode"<<"\titemPrice"<<"\titemName"<<endl;
    cout<<"\t\t-------------------------------------------------"<<endl;        
 while(fin.read((char*)&item,sizeof(item)))
    {
     cout<<"";
     item.putdata();
 } 
 cout<<"\t\t-------------------------------------------------";
    fin.close();
}







class CUSTOMER
{
  int itemCode,itemPrice,itemQty,totalPrice; 
  char itemName[15];
 public:
  int flag;   
  void enter();
  void display();
  void addItem();
  void itemBill();
  void itemRemove();
  
}customer;
void CUSTOMER::enter()
{
 system("cls");
 cout<<"\n\n\t\t<<<<<<<<<<<<<<<<<<<<ADD AN ITEM IN BILL>>>>>>>>>>>>>>>>>>>>\n\n";
 cout<<"\n\t\tEnter itemcode: ";
 cin>>itemCode;
 cout<<"\n\t\tEnter Quantity: ";
 cin>>itemQty;
 
 flag=0;
 fin.open("ITEM_MENU.dat");
 while(fin.read((char*)&item,sizeof(item)))
 {
  if(itemCode==item.itemCode)
  {
      strcpy(itemName,item.itemName);
   itemPrice=item.itemPrice;
   totalPrice=itemPrice*itemQty;
   flag=1;
   break;
  }
  
 }
 if(flag==0)
  cout<<"\n\n\t\tYou Entered wrong itemCode...";
 fin.close();
}

void CUSTOMER::display()
{
 
 cout<<"  "<<itemCode<<"\t\t"<<itemName<<"\t\t"<<itemPrice<<"\t\t"<<itemQty<<"\t\t"<<totalPrice<<endl;
}
void CUSTOMER::addItem()
{
 cout<<"<<<<<<<<<<<<<ADD AN ITEM>>>>>>>>>>>"<<endl;
 fout.open("LIST.dat",ios::app);
 customer.enter();   
 if(customer.flag==1)
 
 {
  fout.write((char*)&customer,sizeof(customer));
  cout<<"\n\n\t\tItem added successfully...";
    }
 fout.close();
}
void CUSTOMER::itemBill()
{
 int totalItems,totalPrice=0;
 float vat,tax,grandTotal;
 totalItems=0;
 
 
 
 
 cout<<"\n\n\t\t<<<<<<<<<<<<<<<<<<<<ORDER BILL>>>>>>>>>>>>>>>>>>>\n\n"; 
 cout<<"  ------------------------------------------------------------------------"<<endl;       
 cout<<"  itemCode"<<"\titemName"<<"\titemPrice"<<"\titemQty"<<"\t\tTotalPrice\n";
 cout<<"  ------------------------------------------------------------------------"<<endl; 
 fin.open("LIST.dat");    
 while(fin.read((char*)&customer,sizeof(customer)))
 {
  cout<<""; 
  customer.display();
  totalItems++;
  totalPrice+=customer.itemPrice*itemQty;
  
 }        
 cout<<"  ------------------------------------------------------------------------"<<endl;       
  fin.close();
   
  vat=.05*totalPrice;
  tax=(13.125/100)*totalPrice;
  grandTotal=vat+tax+totalPrice;
     
 cout<<"\n\t\tTotal Amount : "<<totalPrice<<endl;
 cout<<"\t\tTax          : "<<tax<<endl;
 cout<<"\t\tVat          : "<<vat<<endl;
 cout<<"\t\tGrand Total  : "<<grandTotal<<endl<<endl;
 cout<<"  ------------------------------------------------------------------------"; 
}

void CUSTOMER::itemRemove()
{
 int code,flag=0;
 cout<<"\n\n\t\t<<<<<<<<<<<<<<<<<<<<REMOVE ITEM>>>>>>>>>>>>>>>>>>>>\n\n";
 cout<<"\n\t\tEnter itemCode to be remove: ";
 cin>>code;
 inoutfile.open("LIST.dat");
 if(!inoutfile)
    {
     cout<<"\n\nFile Not Found...";
    }
    inoutfile.seekg(0);
 while(inoutfile.read((char*)&customer,sizeof(customer)))
 {  
  if(code==customer.itemCode);
  {
   //customer=NULL;
   flag=1;
   break;
  }  
 }
 if(flag==1)
 {
  inoutfile.write((char*)&customer,sizeof(customer)); 
  cout<<"\n\n\t\tRemoved Successfully...";
 }
 else
  cout<<"\n\n\t\tEntered itemCode is not available...";
 inoutfile.close();
}
//-----------------------------------------------------------------------end of CUSTOMER class




int main()
{ 
 //variable declarations
 int chooseMain;
 int choiceOwner,choiceCustomer;
 int location;
 char ch,yn;
 
 
 
 do{ 
mmain:
   
   cout<<"\n\n"<<setw(50)<<"Bakery Billing System\n"; 
     cout<<setw(54)<<"===========================\n\n";
  cout<<"\n\t\t1.Admin\n\n";
  cout<<"\t\t2.Customer\n\n";
  cout<<"\t\t3.Exit\n\n";
  cout<<"\t\tPlease Enter Required Option: ";
  cin>>chooseMain;
  system("cls");
  
  
  switch(chooseMain)
  {

  case 1: 
          system("cls");
          opmain:
    cout<<"\n\n"<<setw(50)<<"Admin Access Window\n"; 
                cout<<setw(54)<<"===========================\n\n";
                int currentpass,oldpass,newpass;
                cout<<"\n\t\tIf you are first time user then enter any number!\n";
       cout<<"\n\t\tEnter password: ";
       cin>>oldpass;
       fin.open("Pass.dat");
    if(!fin)
             {
              system("cls");
              setpass:
              cout<<"\n\n"<<setw(50)<<"Admin Access Window\n"; 
                  cout<<setw(54)<<"===========================\n\n";
              cout<<"\n\t\tIn order to use the program...\n\n";
                cout<<"\n\t\tPlease create new password: ";
                 cin>>oldpass;
                cout<<"\n\t\tRe-enter password: ";
                cin>>newpass;
                if(oldpass==newpass)
                {
                 system("cls");
                 cout<<"\n\n\nBy creating new password you're agree to our terms and conditions.(Y/N)?:";
                 cin>>yn;
                     if((yn=='Y')||(yn=='y'))
                     {
                      system("cls");
                  fout.open("Pass.dat");
                      fout<<oldpass;
                      fout.close();
                     cout<<endl<<"\n\n\tCongratulation! You've successfully created new password...";
               }
               else if((yn=='N')||(yn=='n'))
                    {
                   system("cls");
                     goto mmain;
                  }
      }
      else
      {
         cout<<"\n\n\t\tPassword not match. Please try again...";
         getch();
         system("cls");
       goto setpass; 
      }
              getch();
              system("cls");
              goto opmain;
             }
             fin>>newpass;
             fin.close();
             system("cls");
  if(oldpass==newpass)
  {
   omain:
        cout<<"\n\n"<<setw(50)<<"Admin Access Window\n"; 
                    cout<<setw(54)<<"===========================\n\n";
     cout<<"\n\t\t1.Show item menu\n\n";
     cout<<"\t\t2.Add item in menu\n\n";
     cout<<"\t\t3.Modify item in menu\n\n";
     cout<<"\t\t4.Change password\n\n";
     cout<<"\t\t5.Back to previous menu\n\n";
     cout<<"\t\t6.Exit\n\n";
     cout<<"\t\tPlease Enter Required Option: ";
     do{ 
         
      cin>>choiceOwner;        
      switch(choiceOwner)
      {
       
       
    
       case 1:
           system("cls");
        item.showList();
        getch();
        system("cls");
              goto omain;
              break;
     
        
       
      case 2: 
        system("cls");
        cout<<"\n\n\t\t<<<<<<<<<<<<<<<<<<<<ADD AN ITEM>>>>>>>>>>>>>>>>>>>>\n\n";
        item.addItem();
        cout<<"\n\n\t\tItem added successfully...";
        getch();
        system("cls");
        goto omain;        
        break;       
           
       case 3: 
        system("cls");
        item.update();
        getch();
        system("cls");         
        goto omain;
        break;
      case 4:
           system("cls");
           changepass:
        cout<<"\n\n"<<setw(50)<<"Change Password\n"; 
                             cout<<setw(54)<<"===========================\n\n";
        cout<<"\n\t\tEnter current password: ";
        cin>>currentpass;
        fin.open("Pass.dat");
                     if(!fin)
                             {
                              cout<<endl<<"File not found...";
                               exit(1);
                                }
                             fin>>oldpass;
                             fin.close();
                             if(oldpass==currentpass)
                             {
                                 fout.open("Pass.dat");
                           cout<<"\n\t\tEnter new password: ";
                              cin>>newpass;
                              cout<<"\n\t\tRe-enter new password: ";
                              cin>>oldpass;
                              if(newpass==oldpass)
                              {
                            fout<<newpass;
                            fout.close();
                            cout<<"\n\n\t\tPassword successfully changed...";
                            getch();
                            system("cls");
                            goto opmain;
                         }
                         else
                         {
                          cout<<"\n\t\tNew password not match. Please try again...";
                          getch();
                        system("cls");
                      goto changepass;
           }
              }
        else
        {
         cout<<"\n\t\tPassword not match. Please try again...";
         getch();
         system("cls");
         goto changepass;
        }
        break;
       
            
      case 5: 
        system("cls");
        goto mmain;
        break;
         
           
      case 6:
           system("cls");
              cout<<"\n\n\t\tARE YOU SURE, YOU WANT TO EXIT (Y/N)?:";
                                cin>>yn;
                                 if((yn=='Y')||(yn=='y'))
                                 {
                                 system("cls");
                           cout<<"\n\n\n"<<setw(60)<<"Thank you to visit our bakery store.\n\n\n\n";
                           exit(0);
                        }
                           else if((yn=='N')||(yn=='n'))
                        {
                         system("cls");
                            goto omain;
                        }  
        break;
       default:
        system("cls");
        goto omain;
       break;
      }
     }while(choiceOwner!=5);}
     else
                  {
                  cout<<"\n\n\t\tWrong password entered. Please try again...";
                  getch();
                  system("cls");
                  goto opmain;
                     }
      break;

   case 2: system("cls");
     fout.open("LIST.dat",ios::trunc);
     fout.close();
     cmain:  
     cout<<"\n\n"<<setw(50)<<"Customer Order Window\n"; 
                    cout<<setw(54)<<"===========================\n\n";    
     cout<<"\n\t\t1.Show item Menu\n\n";
     cout<<"\t\t2.Add item and Quanitity in bill\n\n";
     cout<<"\t\t3.Remove item from bill\n\n";
     cout<<"\t\t4.Show Bill detail\n\n";     
     cout<<"\t\t5.Back to previous Menu\n\n";
     cout<<"\t\t6.Exit\n\n";
     cout<<"\t\tPlease Enter Required Option: ";
     do{
      cin>>choiceCustomer;
      switch(choiceCustomer)
      {
       
        
        case 1: system("cls");         
         item.showList();
         getch();
         system("cls");
               goto cmain;
         break;
               
        case 2:
         customer.addItem();
         getch();
         system("cls");
         goto cmain;
         break;
        
                      
        case 3:system("cls");
         customer.itemRemove();
         getch();
         system("cls");      
         goto cmain;
         break;
        
      
        case 4:system("cls");
         customer.itemBill();
         getch();
         system("cls");     
         goto cmain;            
         break;
        
       
        case 5:
        system("cls");
        goto mmain;
         break;
        
        
        case 6:system("cls");
         cout<<"\n\n\t\tARE YOU SURE, YOU WANT TO EXIT (Y/N)?:";
                                cin>>yn;
                                 if((yn=='Y')||(yn=='y'))
                                 {
                                 system("cls");
                           cout<<"\n\n\n"<<setw(60)<<"Thank you to visit our bakery store.\n\n\n\n";
                           exit(0);
                        }
                           else if((yn=='N')||(yn=='n'))
                        {
                         system("cls");
                            goto cmain;
                        }  
         break;
         
        default:
         system("cls");
        goto cmain;
         break;
      }
     }while(choiceCustomer!=6);

     break;
   case 3:
    cout<<"\n\n\t\tARE YOU SURE, YOU WANT TO EXIT (Y/N)?:";
                cin>>yn;
                if((yn=='Y')||(yn=='y'))
                {
                 system("cls");
           cout<<"\n\n\n"<<setw(60)<<"Thank you to visit our bakery store.\n\n\n\n";
           exit(0);
       }
       else if((yn=='N')||(yn=='n'))
    {
     system("cls");
        goto mmain;
    }
    break;
   default:
           goto mmain;
    
   break;
  }

 }while(chooseMain!=3);

 return 0;
}

