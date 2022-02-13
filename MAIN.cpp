#include <bits/stdc++.h>
#define int long long

using namespace std;
vector<string> productName;
map<string, pair<int, int>> products; // price is in rupees, duration is in minutes
int x = 0;

class bill
{
    public:
        int customerId;
        string customerName;
        string customerContact;
        vector<pair<string, int>> order;//product name,quantity
        int duration;
        
        bill(int id, string name, string contact, vector<pair<string, int>> &iorder, int d) {//&order already string , quantity 
            customerId = id;
            customerName = name;
            customerContact = contact;
            order = iorder;
            duration = d;
        }
        
        void onScreen() { // BILL ID, CUSTOMER NAME, DURATION
           // Tikki Tikki Tambo No Saribo Hari Kari Bushki Peri Pem Po Hai Kai Nikki No Meeno Dom Barako//90
           cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl; 
           cout << "Bill ID: " << customerId << " Customer Name: " << customerName << " Estimated Duration: " << duration << endl;
           cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl; 
        }
        
        void offScreen() { // BILL ID AND ORDER
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl; 
            cout << "Customer ID: " << customerId << endl;
            cout << "Product Name         Quantity" << endl;
            for (auto x : order){
                cout << x.first << " " << x.second << endl;
            }
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl; 
        }
        
        void generateBill(){
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl; 
            cout << "Bill ID:- " << customerId << endl;
            cout << "Customer name:- " << customerName << endl;
            cout << "Customer contact:- " << customerContact << endl;
            int totalPrice = 0;
            cout << "Delicacy          " << "Quantity         " << "Price" << endl;
            for(int i = 0; i < (int)order.size(); i++){
                cout << order[i].first << "         " << order[i].second << "          " << order[i].second * products[order[i].first].first << endl;
                totalPrice += order[i].second * products[order[i].first].first;
            }
            cout << "Your total amount will be: " << totalPrice << endl;
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl; 
        }
};
queue<bill> q;
// 1 class bill --- 11th 5-7 --- {Bill id, customer name, customer contact, product list(product name, product quantity), total price.}
// 2 list product --- minor
// 3 print menu --- minor
// 4 place order --- major
// 5 queue --- major
// 6 histogram(prefed time)
// 7 generate and print bill

void productInititalize() // default in menu available
{
    products["Paneer Burger"] = {65, 3};//price, duration
    productName.push_back("Paneer Burger");
    products["Chicken Burger"] = {85, 4};
    productName.push_back("Chicken Burger"); // to be added
}

void addProduct() // To give feature to add products
{   string name;
    int price, duration;
    cin >> name >> price >> duration;
    products[name] = {price, duration};
    productName.push_back(name);
}

void printMenu()
{
    cout << "Delicacy          " << "Price            " << "Duration" << endl;
    for (auto x : productName){
        cout << x << " " << products[x].first << " " << products[x].second << endl;
    }
}

void reflect() { //sequencially display onScreen boxes and then offscreen boxes
    vector<bill>printer;
    int n=q.size();
    if(n<=0){
        return;
    }
    while(n--){
        bill p=q.front();
        q.pop();
        q.push(p);
        printer.push_back(p);
    }
    cout << "This is the customer screen display" << endl;
    for(auto x:printer){
        x.onScreen();
    }
    cout << "This is the worker screen display" << endl;
    q.front().offScreen();
}

void placeOrder(){ //bill obj(12, "Arki", "12345678890", test//vector<name and quantity);
    cout << "Enter customer name:" << endl;
    string custname;
    cin >> custname;

    cout << "Enter phone number:" << endl;
    int number;
    cin >> number;
    string phone_no = to_string(number);

    vector<pair<string, int>> test; // name + quantity
    int instDuration = 0;
    while(1) {
        cout << "Enter product name and quantity or press 1" << endl;
        string pro_name;
        int quantity;
        getline(cin >> ws, pro_name);
        if (pro_name == "1") {
            break;
        }
        else if (products.count(pro_name)==0) {
            cout << "Invalid Input" << endl; 
            continue;
        }
        else
        {   
            cout << "Enter Quantity" << endl;
            cin >> quantity;
            if(quantity <= 0) {
                continue;  
            }
            test.push_back({pro_name, quantity});
            instDuration = max(instDuration, products[pro_name].second*quantity);
        }
    }
    if(test.size()==0) {
        return;
    }
    cout << "Your order is placed! " << endl;
    bill obj(x++, custname, phone_no, test, instDuration);
    q.push(obj);
    reflect();
}

void generateHistogram(){
    cout << "Histogram" << endl;
}
// A ---3 - 3 mins d * q max----A's duration 
// A ---2 - 4 mins d * q
// B ---2 - 3 mins
// B ---1 - 5 mins
// A --- 4 // a --- 17     a --- 9
// B --- 9 // b --- 17+11  b --- 9 + 6 
// C --- 
// kitchen component --- ye package me ye ye order ready karna hai --- 
int32_t main()
{
    productInititalize();
    while(1)
    {   // reflect
        int option = 0;
        cout << "----------------------------------------------------------------------------------------" << endl;
        cout << "Enter 1 for seeing the menu" << endl; 
        cout << "Enter 2 to place order" << endl;
        cout << "Enter 3 to generate bill of completed order and pop from the queue" << endl; 
        cout << "Enter 4 to view the histogram of ----" << endl;
        cout << "Enter 5 to add a product" << endl;
        cout << "Enter 6 to close the counter" << endl;
        cout << "----------------------------------------------------------------------------------------" << endl;
        cin >> option;
        switch (option) {
            case 1:
                printMenu();
                break;
            case 2:
                placeOrder();
                break;
            case 3:
                //generate bill of topmost member of queue
                if (q.size() > 0) {
                    q.front().generateBill();
                    q.pop();
                    reflect();
                }
                else {
                    cout << "No customers in the queue!" << endl;
                }
                break;
            case 4:
                generateHistogram();
                break;
            case 5:
                cout << "Enter product name , price , duration" << endl;
                addProduct();
                cout << "Product Successfully Added" << endl;
                break;
            case 6:
                cout << "Counter Closed" << endl;
                break;
            default:
                cout << "invalid Input" << endl;
        }
        if (option == 6) {
            break;
        }
    }
    return 0;
}