#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Global Variabels
float total_price=0;
float capital=10000;
class restaurant_face
{
public:
    void restaurant()
    {
       string outputprint = "HELLO our working hours are every day except for prayer times\n";
        outputprint += "There is an additional amount to deliver the product varies from place to place\n";
        outputprint += "*-*-*-*-*-* Menu *-*-*-*-*-*\n";
        outputprint += "* Appetizers:\n";
        outputprint += "1- Spring Rolls: $ 5.99\n2- Chicken Wings: $ 8.99\n3- Bruschetta: $6.49\n";
        outputprint += "* Soups:\n";
        outputprint += "4- Tomato Soup: $ 4.99\n5-Chicken Noodle Soup: $ 5.49\n6- Lentil Soup: $4.99\n";
        outputprint += "*Salads:\n";
        outputprint += "7- Caesar Salad: $ 7.99\n8- Greek Salad: $ 8.49\n9- Caprese Salad: $ 6.99\n";
        outputprint += "*Main Courses:\n";
        outputprint += "10-Grilled Steak with Mashed Potatoes: $ 18.99\n11-Vegetable Stir-Fry with Tofu: $ 12.99\n";
        outputprint += "*Pasta:\n";
        outputprint += "12-Penne Arrabbiata: $ 9.99\n13-Spaghetti Bolognese: $ 11.99\n";
        outputprint += "*Pizza:\n";
        outputprint += "14-Margherita Pizza: $ 12.99\n15-Vegetarian Pizza: $ 11.99\n";
        outputprint += " *Sandwiches:\n";
        outputprint += "16-Philly Cheesesteak Sandwich: $ 11.49\n17-Grilled Chicken Panini: $ 10.99\n";
        outputprint += "* Beverages:\n";
        outputprint += "18-Coffee (Espresso, Cappuccino, Latte): $ 3.49\n19-Soft Drinks (Coke, Pepsi, Sprite): $ 2.49\n";
        outputprint +="*Desserts:\n";
        outputprint +="20-Chocolate Cake: $ 6.99\n21-Apple Pie: $ 5.99\n22- Tiramisu: $ 7.49\n";


         fstream file("restaurant.txt");
    file.close();


    ifstream file_read("restaurant.txt");
    if (!file_read.is_open()) {
        cout << "Unable to open file" << endl;
    }

    //in the menu there is a unique charactares like *
    //output print += "*-*-*-*-*-* Menu *-*-*-*-*-*\n";
    //when the complier find the * it converts the check menu to true
    char targetChar = '*';
    char ch;
    bool checkMenu = false;

    while (file_read.get(ch))
	      {
	        if (ch == targetChar)
			   {
	            checkMenu = true;
	            break;
	           }
          }

    file_read.close();
//check if the menu is created ,if so don't create another one.
    if (!checkMenu)
	 {
        ofstream file_write("restaurant.txt", ios::app);
        file_write << outputprint;
        file_write.close();
     }
    }
};

class Owner
{
private:
    string name;

public:
    Owner( string n) : name(n) {}

    int NumOfMeals ;
    string itemName ;
    float itemPrice ;

   void addFoodItem() {
    int t;
    cout << "Enter number of meals you want to add: ";
    cin >> t;
    ofstream file("restaurant.txt", ios::app);
    if (!file.is_open())
       {
        cout << "Error: Unable to open file!" << endl;
       return;
       }
       while (t--) {

        cout << "Enter the number of the meal in menu: ";
        cin >> NumOfMeals;

        while (NumOfMeals!=0)
            {
     ifstream file("restaurant.txt");
     string line;
     bool found2 = false;


         while (getline(file, line)) {
            if (line.find((NumOfMeals) + "-")) {
               found2 = true;
                 break;
            }
         }
              if(!found2)
          {
            cout << "The number is already in the menu."<<endl << "Please enter another number:" ;
             cin >> NumOfMeals;
          }
          else break;
        file.close();
        }
        cout << "Enter the name of the meal: ";
        cin >> itemName;
        cout << "Enter the price of the meal: ";
        cin >> itemPrice;

        ofstream outfile("restaurant.txt", ios::app);
        outfile << NumOfMeals << "-" << itemName << ": $" << itemPrice << endl;
        outfile.close();
    }

    cout << "\nDone! All meals added to the menu successfully." << endl;
   }

    void displayOwnerInfo() {
        cout << "\nOwner Name: " << name << endl;
        cout << "Capital: $" << capital << endl;

        cout<<"\nDone "<<itemName << ": $" << itemPrice << " Added to menu Succesfully" <<endl;
    }
};

class customer {
private:
    string customername;

    // These static variables are used to track the writing state for customer names in text files.
    static bool namewritten;
    static bool namewrittenagain;
    static bool firstcustomer;
    static bool firstcustomeragain;
public:
    customer()
        {
        //we used trunc method to delete lastcustomer txt file and update it every time
        //to not conflict
        fstream customerorder_clear("lastcustomer.txt", ios::out | ios::trunc);
        customerorder_clear.close();
        }

    //setter and getter for customer name
    void setCustomerName(const string& name){customername = name;}
    string getCustomerName(){return customername;}

    //Function to search in menu for a product by id and get it back
    // and making a file database for customers and their orders
    void searchByNumber(string numberserach)
     {
        ifstream file("restaurant.txt");
        string lineafternuumber;
        int found = 0;
        while (getline(file, lineafternuumber))
        {
            if (lineafternuumber.find((numberserach) + "-") == 0)
                {
                cout << lineafternuumber << endl;
                found = 1;
                break;
                }
        }
        file.close();

             if (!found){cout << "No item found with that number." << endl;}
                 else
                {
                    int quantity;
                    cout << "How many of this product would you like to buy?" << endl;
                    cin >> quantity;
                    if(quantity<=0 || quantity> 50)
                    {
                        cout<<"Please quantity can't be zero and can't be more than 100\nEnter Valid Number\n";
                    }
                    else{  cout << "You have selected " << quantity << " of " << lineafternuumber << "." << endl;}


                   //FILE TO DATABASE FOR ALL CUSTOMERS
                    ofstream customerdataset("customerorder.txt", ios::app);

                     if (customerdataset.is_open())
                        {
                            if(!namewritten)
                              {
                                if(!firstcustomer){customerdataset<<"#############\n";}
                                customerdataset << "Customer Name: "<< getCustomerName()<<"\n"<<"Items purchased: \n" ;namewritten=true;
                              }
                            customerdataset << lineafternuumber << ", Quantity: " << quantity <<"\n";
                            customerdataset.close();
                        }
                        else cout << "Unable to open the file" << endl;
                    //PASTE HERE ABDO PAYMENT MEHTOD
                    string numbersmenu[22] =
                    {
                        "1","2","3","4","5","6","7","8","9","10",
                        "11","12","13","14","15","16","17","18","19","20","21","22"
                    };

                    ifstream file("lastcustomer.txt");
                    if (!file)
                       {
                        cout << "Error opening file." << endl;
                      }

                    string linestringarray;
                    int Q=quantity;
                    string x;
                    while (getline(file, linestringarray))
                     {
                        for(int i=0;i<21;i++)
                        {
                         size_t idPos = linestringarray.find(numbersmenu[i]);
                        if (idPos != string::npos && idPos < linestringarray.size() - 1 && linestringarray[idPos + 2] == '-')
                           {
                               x=numbersmenu[i];
                            if (x == "1")  total_price += (Q * 5.99);
                            if (x == "2")  total_price += (Q * 8.99);
                            if (x == "3")  total_price += (Q * 6.49);
                            if (x == "4")  total_price += (Q * 4.99);
                            if (x == "5")  total_price += (Q * 5.49);
                            if (x == "6")  total_price += (Q * 4.99);
                            if (x == "7")  total_price += (Q * 7.99);
                            if (x == "8")  total_price += (Q * 8.49);
                            if (x == "9")  total_price += (Q * 6.99);
                            if (x == "10") total_price += (Q * 18.99);
                            if (x == "11") total_price += (Q * 12.99);
                            if (x == "12") total_price += (Q * 9.99);
                            if (x == "13") total_price += (Q * 11.99);
                            if (x == "14") total_price += (Q * 12.99);
                            if (x == "15") total_price += (Q * 11.99);
                            if (x == "16") total_price += (Q * 11.49);
                            if (x == "17") total_price += (Q * 10.99);
                            if (x == "18") total_price += (Q * 3.49);
                            if (x == "19") total_price += (Q * 2.49);
                            if (x == "20") total_price += (Q * 6.99);
                            if (x == "21") total_price += (Q * 5.99);
                            if (x == "22") total_price += (Q * 7.49);
                           }
                        }

                    }


                                fstream customerorder("lastcustomer.txt", ios::out | ios::app);

                                if (customerorder.is_open()) {
                                    // Check if this is the first time writing to the file
                                    if (!namewrittenagain) {
                                        // Add separator if not the first customer
                                        if (!firstcustomeragain) {
                                            customerorder << "#############\n";
                                        }

                                        customerorder << "Customer Name: " << getCustomerName() << "\nItems purchased:\n";
                                        // Set  flag  true
                                        namewrittenagain = true;
                                    }

                                    customerorder << lineafternuumber << ", Quantity#" << quantity << "\n";

                                    customerorder.close();
                                } else {
                                    cout << "Unable to open the file" << endl;
                                }

                }
    }
};
//initialize boolean out of customer class as they are static variabels
bool customer::namewritten=false;
bool customer::namewrittenagain=false;
bool customer::firstcustomer=false;
bool customer::firstcustomeragain=false;

class create_order
{
	private:
	int Mno;
	string Mname;
	//string response;

	public:
	void show_Info()
	{
	  ifstream reader("lastcustomer.txt");
	  if(reader.is_open())
	  {
	  	while(getline(reader,Mname))
	  	{
	  		cout<<Mname<<endl;
		}
	  }
	  /*
	cout<<"\nDo you want to continue? (yes::No)";
	cin>>response;

	if(response=="yes" ||response=="YES" || response=="Yes")
	cout<<"you can complete "<<endl;
	else if(response=="No" ||response=="NO" ||response=="no")
	cout<<"operation canceled"<<endl;
	*/
	}
	/*
	void saveToFile()
	{
		fstream file("restaurant.txt",ios::out|ios::app);
		file<<Mno<<" "<<Mname<<" "<<endl;

		file.close();
	}
	*/
};
//inheritance from customer class to payment class to share total price and other functions
class Payment : public customer
{
public:
 int pay;
 int id;
 int pass;

   void paymentcalculator()
   {
       cout<<"\nHow do you want to pay the amount (Card)=> 1 or (Cash)=> 2 :\n";
       cin>>pay;
       if(pay==1)
        {
        cout<<"Please enter your Id Card :\n";
        cin>>id;

        //id must be 15
        cout<<"Enter your Password :\n";
        cin>>pass;
         if(1000 <=pass && pass<= 9999)
         {
        cout<<"\nThe amount "<<total_price<<" has been successfully debited from your credit card";
         }
        //pass must be 4
        //capital+=total_price;
        }
       else if(pay==2) cout<<"Thanks, You have to pay "<< total_price <<" When the order Reaches you";
       else cout<<"Invalid Choice,Not found ..";

   }
};

class Delivery
{

public:
    int Deliv_Price;
    int num;

    void choose()
    {
        cout << "\nChoose Delivery Area:  " << endl;
        cout << "1_ Share3 ElGlaa \n2_ Share3 ElStad \n3_ Share3 Paris \n4_ Share3 ElMasn3 \n5_ Elbatanon \n";
    }

    int Title()
    {
   while(true)
   {
        cin >> num;

        if (1 == num)
        {
            cout << "Delivery Price to Share3 ElGlaa = $3." << endl;
             Deliv_Price = 3; break;
        }
        else if (2 == num)
        {
            cout << "Delivery Price to Share3 ElStad = $4." << endl;
            Deliv_Price = 4;break;
        }
        else if (3 == num)
        {
            cout << "Delivery Price to Share3 Paris = $5." << endl;
            Deliv_Price = 5;break;
        }
        else if (4 == num)
        {
            cout << "Delivery Price to Share3 ElMasn3 = $5." << endl;
            Deliv_Price = 5;break;
        }
        else if (5 == num)
        {
            cout << "Delivery Price to Elbatanon = $8." << endl;
            Deliv_Price = 8;break;
        }
    else
     {
        cout << "Invalid, Try Again, Choose Your Delivery Area From These Options:  " << endl;
        cout << "1_ Share3 ElGlaa \n2_ Share3 ElStad \n3_ Share3 Paris \n4_ Share3 ElMasn3 \n5_ Elbatanon \n";
    }
   }
        //return Deliv_Price;
    }
};

class feedback
{
public:
    int evalua_ques; //Evaluation Question
   // feedback(){ };
void rate_us()
{
    cout << "Would you like to rate us? That's will Help us improve.\n" << "1-Rate Us Now \n2-No, Maybe Later\n" << endl;
    cin >> evalua_ques;

   while(true)
 {
         if(1 == evalua_ques)
         {
              int i;
              string r[6]= {"error","*","* *","* * *","* * * *","* * * * *"}; //rating
              cout << "To rate us please Enter a number from 1 to 5: ";
              cin >> i;
              cout << r[i] << endl;

             if(0 == i)
             {
                 cout << "Error, Please try Again\n" << "1-Rate Us Now \n2-No, Maybe Later" << endl;
              cin >> evalua_ques;
              cout << "To rate us please choose from 1 to 5: ";
                 cin>>i;
                 cout<<r[i];break;
             }
             break;
         }

         else if (2 == evalua_ques)
          break;

          else {
            cout << "Error,Please try Again\n" << "1-Rate Us Now \n2-No, Maybe Later" << endl;
            cin >> evalua_ques;
             }
    }
     cout<<"\nThanks for your feedback!..\n";
     return;
}
};

int main()
{
    restaurant_face mf;
    mf.restaurant();
    cout<<"*-*-*-*-*-*-Welcome to Our Online food order system-*-*-*-*-*-*"<<endl<<"*-*-*-*-*-*-Press 1 for Owner and 2 for customer-*-*-*-*-*-*\n";

    int numberchoice_ownercustomer,numberchoice_loginsignin,accpassword,chooseinowner;
    string numberincustomer="0",accname,response,customerorderstringprint,cutomeraccountsstringprint;
    string name1="mohamed2024",name2="anas2024",name3="abdo2024",name4="ali2024",name5="eman2024";

    while(true)
    {
        cin>>numberchoice_ownercustomer;
        if(numberchoice_ownercustomer==1)
          {

          	Owner restaurantOwner("aklani shokran");

            cout << "Akalani shokran-Online_Order\n"<<"\nOur Capital :"<<capital<< "\n \n16th May 2024, 9:30 AM\n \n";
            cout << "+------+---------------------------+\n";
            cout << "|  1.  | View Customers Accounts   |\n";
            cout << "|  2.  | View a Report of Lastorder|\n";
            cout << "|  3.  | Add meals to The Menu     |\n";
            cout << "|  4.  | Exit                      |\n";
            cout << "+------+---------------------------+\n";
            cin>>chooseinowner;

            if(chooseinowner==1)
            {
            	cout<<"Here is a list of customer_accouunts in our system\n";
            	ifstream readcustomeraccounts("customeraccounts.txt");
				  if(readcustomeraccounts.is_open())
				  {
				  	while(getline(readcustomeraccounts,cutomeraccountsstringprint))
				  	{
				  		cout<<cutomeraccountsstringprint<<endl;
					}
				  }

			}
			else if(chooseinowner==2)
			{
				  cout<<"Here is a Report of Orders in our system\n";
				  ifstream readcustomerorder("customerorder.txt");
				  if(readcustomerorder.is_open())
				  {
				  	while(getline(readcustomerorder,customerorderstringprint))
				  	{
				  		cout<<customerorderstringprint<<endl;
					}
				  }
			}
			else if(chooseinowner==3)
			{
			 restaurantOwner.addFoodItem();
			}
			else if(chooseinowner==4)
			{
				cout<<"Have a Goodday,Boss ! <3\n";


			}else cout<<"Invalid number";break;


            break;
          }
        else if(numberchoice_ownercustomer==2)
               {
                 cout<<"Do you want to signin or signup"<<endl<<"Press 1 for signin and 2 for signup\n";
                 cin>>numberchoice_loginsignin;
                                   if(numberchoice_loginsignin==1 )
                                    {
                                        customer  buy;
                                        cout<<"Enter Your Username\n";cin>>accname;
                                        if(accname == name1 || accname==name2|| accname==name3|| accname==name4||accname==name5 )
                                        {
                                            cout<<"Enter Your password\n"; cin>>accpassword;
                                            cout<<endl;
                                            if(accpassword == 1234)
                                            {
                                                    buy.setCustomerName(accname);
                                                    cout<<"Welcome "<<accname<<" our working hours are every day except for prayer times\n";

                                                    cout << "There is an additional amount to deliver the product varies from place to place\n";cout<<endl;
                                                    cout << "Please Choose a Number from The Menu and Enter -1 to End order\n";
                                                    cout<<endl;
                                                    cout << "                 | *-*-*-*-*-*-*-*-* Menu *-*-*-*-*-*-*-*|\n";
                                                    cout<<endl;
                                                    cout << "| Category       | Item                                  | Price      |\n";
                                                    cout << "|----------------|---------------------------------------|------------|\n";
                                                    cout << "| Appetizers     | 1- Spring Rolls                       | $5.99      |\n";
                                                    cout << "|                | 2- Chicken Wings                      | $8.99      |\n";
                                                    cout << "|                | 3- Bruschetta                         | $6.49      |\n";
                                                    cout << "| Soups          | 4- Tomato Soup                        | $4.99      |\n";
                                                    cout << "|                | 5- Chicken Noodle Soup                | $5.49      |\n";
                                                    cout << "|                | 6- Lentil Soup                        | $4.99      |\n";
                                                    cout << "| Salads         | 7- Caesar Salad                       | $7.99      |\n";
                                                    cout << "|                | 8- Greek Salad                        | $8.49      |\n";
                                                    cout << "|                | 9- Caprese Salad                      | $6.99      |\n";
                                                    cout << "| Main Courses   | 10-Grilled Steak with Mashed Potatoes | $18.99     |\n";
                                                    cout << "|                | 11-Vegetable Stir-Fry with Tofu       | $12.99     |\n";
                                                    cout << "| Pasta          | 12-Penne Arrabbiata                   | $9.99      |\n";
                                                    cout << "|                | 13-Spaghetti Bolognese                | $11.99     |\n";
                                                    cout << "| Pizza          | 14-Margherita Pizza                   | $12.99     |\n";
                                                    cout << "|                | 15-Vegetarian Pizza                   | $11.99     |\n";
                                                    cout << "| Sandwiches     | 16-Philly Cheesesteak Sandwich        | $11.49     |\n";
                                                    cout << "|                | 17-Grilled Chicken Panini             | $10.99     |\n";
                                                    cout << "| Beverages      | 18-Coffee (Espresso, Cappuccino,Latte)| $3.49      |\n";
                                                    cout << "|                | 19-Soft Drinks (Coke, Pepsi, Sprite)  | $2.49      |\n";
                                                    cout << "| Desserts       | 20-Chocolate Cake                     | $6.99      |\n";
                                                    cout << "|                | 21-Apple Pie                          | $5.99      |\n";
                                                    cout << "|                | 22-Tiramisu                           | $7.49      |\n";
                                                    //read from file which owner have added to menu then print them here
                                                while(numberincustomer!="-1")
                                                {
                                                    cin>>numberincustomer;
                                                    if(numberincustomer=="-1")
                                                   {
                                                    cout<<endl;
                                                    create_order customerorderobject;
                                                    customerorderobject.show_Info();
                                                    Payment completeorder;
                                                    cout<<"\nYour total price is "<< total_price<<endl;
                                                    completeorder.paymentcalculator();cout<<endl;

                                                    Delivery deliveryprice;
                                                    deliveryprice.choose();
                                                    deliveryprice.Title();cout<<endl;
                                                    feedback();
                                                    feedback rating;
                                                    rating.rate_us();
                                                    //THIS IF CONDITION IS FROM CREATE ORDER CLASS(EMAN)
                                                    cout<<"\nDo you want to continue? (yes::No)";
                                                    cin>>response;cout<<endl;
                                                    if(response=="yes" ||response=="YES" || response=="Yes")
                                                    {
                                                        Delivery test2;
                                                        cout << "-----------------------------\n";
                                                        cout << "akalni shukran For Online Order\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Order Details\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Order ID:       730555994\n";
                                                        cout << "Customer Name:  " << accname << endl;
                                                        cout << "Total Price:    " << total_price << endl; //total + delivery
                                                        cout << "-----------------------------\n";
                                                        cout << "\nDate of Delivery\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Date:           2024-05-16\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "\nOrder Status\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Status:         " << "Confirmed" << endl;
                                                        cout << "-----------------------------\n";
                                                        cout << "\nThank you for your order! We appreciate your business.\n";
                                                    }
                                                    else if(response=="No" ||response=="NO" ||response=="no")
                                                    cout<<"\nThe order has been canceled \nall your payments have been successfully returned to you\n"<<endl;break;
                                                            //when he pay with visa
                                                   //cout<<"DONE FROM HERE PASS TO ORDER CLASS";break;
                                                   }

                                                buy.searchByNumber(numberincustomer);
                                                }
                                            }else cout<<"\nPassword is not correct,Please Try Again\n";

                                        }else cout<<"\nUsername not found,Please Try Again\n";

                                    }
                                    else if(numberchoice_loginsignin==2)
                                    {
                                                customer  buy;
                                                cout<<"Enter Your Username\n";cin>>accname;
                                                cout<<"Enter Your password\n"; cin>>accpassword;
                                                cout<<endl;
                                            if(1000 <=accpassword &&accpassword <= 9999)
                                            {
                                                buy.setCustomerName(accname);
                                                cout<<"Welcome "<<accname<<" our working hours are every day except for prayer times\n";


                                                    cout << "There is an additional amount to deliver the product varies from place to place\n";cout<<endl;
                                                    cout << "Please Choose a Number from The Menu and Enter -1 to End order\n";
                                                    cout<<endl;
                                                    cout << "                 | *-*-*-*-*-*-*-*-* Menu *-*-*-*-*-*-*-*|\n";
                                                    cout<<endl;
                                                    cout << "| Category       | Item                                  | Price      |\n";
                                                    cout << "|----------------|---------------------------------------|------------|\n";
                                                    cout << "| Appetizers     | 1- Spring Rolls                       | $5.99      |\n";
                                                    cout << "|                | 2- Chicken Wings                      | $8.99      |\n";
                                                    cout << "|                | 3- Bruschetta                         | $6.49      |\n";
                                                    cout << "| Soups          | 4- Tomato Soup                        | $4.99      |\n";
                                                    cout << "|                | 5- Chicken Noodle Soup                | $5.49      |\n";
                                                    cout << "|                | 6- Lentil Soup                        | $4.99      |\n";
                                                    cout << "| Salads         | 7- Caesar Salad                       | $7.99      |\n";
                                                    cout << "|                | 8- Greek Salad                        | $8.49      |\n";
                                                    cout << "|                | 9- Caprese Salad                      | $6.99      |\n";
                                                    cout << "| Main Courses   | 10-Grilled Steak with Mashed Potatoes | $18.99     |\n";
                                                    cout << "|                | 11-Vegetable Stir-Fry with Tofu       | $12.99     |\n";
                                                    cout << "| Pasta          | 12-Penne Arrabbiata                   | $9.99      |\n";
                                                    cout << "|                | 13-Spaghetti Bolognese                | $11.99     |\n";
                                                    cout << "| Pizza          | 14-Margherita Pizza                   | $12.99     |\n";
                                                    cout << "|                | 15-Vegetarian Pizza                   | $11.99     |\n";
                                                    cout << "| Sandwiches     | 16-Philly Cheesesteak Sandwich        | $11.49     |\n";
                                                    cout << "|                | 17-Grilled Chicken Panini             | $10.99     |\n";
                                                    cout << "| Beverages      | 18-Coffee (Espresso, Cappuccino,Latte)| $3.49      |\n";
                                                    cout << "|                | 19-Soft Drinks (Coke, Pepsi, Sprite)  | $2.49      |\n";
                                                    cout << "| Desserts       | 20-Chocolate Cake                     | $6.99      |\n";
                                                    cout << "|                | 21-Apple Pie                          | $5.99      |\n";
                                                    cout << "|                | 22-Tiramisu                           | $7.49      |\n";

                                                while(numberincustomer!="-1")
                                                {
                                                cin>>numberincustomer;
                                                if(numberincustomer=="-1")
                                                   {
                                                    cout<<endl;
                                                    create_order customerorderobject;
                                                    customerorderobject.show_Info();//break;
                                                    Payment completeorder;
                                                    cout<<"\nYour total price is "<< total_price<<endl;
                                                    completeorder.paymentcalculator();cout<<endl;

                                                    Delivery deliveryprice;
                                                    deliveryprice.choose();
                                                    deliveryprice.Title();cout<<endl;
                                                    feedback();
                                                    feedback rating;
                                                    rating.rate_us();
                                                    //THIS IF CONDITION IS FROM CREATE ORDER CLASS(EMAN)
                                                    cout<<"\nDo you want to continue? (yes::No)";
                                                    cin>>response;cout<<endl;
                                                    if(response=="yes" ||response=="YES" || response=="Yes")
                                                    {
                                                        Delivery test2;
                                                        cout << "-----------------------------\n";
                                                        cout << "akalni shukran For Online Order\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Order Details\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Order ID:       730555994\n";
                                                        cout << "Customer Name:  " << accname << endl;
                                                        cout << "Total Price:    " << total_price << endl;
                                                        cout << "-----------------------------\n";
                                                        cout << "\nDate of Delivery\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Date:           2024-05-05\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "\nOrder Status\n";
                                                        cout << "-----------------------------\n";
                                                        cout << "Status:         " << "Confirmed" << endl;
                                                        cout << "-----------------------------\n";
                                                        cout << "\nThank you for your order! We appreciate your business.\n";
                                                    }
                                                    else if(response=="No" ||response=="NO" ||response=="no")
                                                    cout<<"\nThe order has been canceled \nall your payments have been successfully returned to you"<<endl;break;

                                                   //cout<<"DONE FROM HERE PASS TO ORDER CLASS";break;
                                                   }

                                                buy.searchByNumber(numberincustomer);
                                                }
                                            } else cout<<"Password Must be 4 digits,Please Try Again\n";



                                    }
                                    else{cout<<"In valid Number,PLease Press 1 for login and 2 for signin\n"; break;}

                 break;
              }
              else{cout<<"In valid Number,PLease Press 1 for Owner and 2 for customer\n";}
    }

return 0;

}
