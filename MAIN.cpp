#include <bits/stdc++.h>
#define int long long

using namespace std;
vector<string> productName;
map<string, pair<int, int>> products; // price is in rupees, duration is in minutes

class bill
{
    public:
        int customerId;
        string customerName;
        string customerContact;
        vector<pair<string, int>> order;//product name,quantity

        bill(int id, string name, string contact, vector<pair<string, int>> &iorder) {//&order already string , quantity 
            customerId = id;
            customerName = name;
            customerContact = contact;
            order = iorder;
        }

        void generateBill(){
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

        }
};
// 1 class bill --- 11th 5-7 --- {Bill id, customer name, customer contact, product list(product name, product quantity), total price.}
// 2 list product --- minor
// 3 print menu --- minor
// 4 place order --- major
// 5 queue --- major
// 6 histogram(prefed time)
// 7 generate and print bill


void productInititalize() // default in menu available
{
    products["Paneer Burger"] = {65, 10};//price, duration
    productName.push_back("Paneer Burger");
    products["Chicken Burger"] = {85, 10};
    productName.push_back("Chicken Burger"); // to be added
}

void addProduct(string product, int price, int duration) // To give feature to add products
{
    products[product] = {price, duration};
    productName.push_back(product);
}

void printMenu()
{
    cout << "Delicacy          " << "Price            " << "Duration" << endl;
    for (auto x : productName){
        cout << x << " " << products[x].first << " " << products[x].second << endl;
    }
}

int32_t main()
{
    productInititalize();
    addProduct("Milkshake",50,10);
    printMenu();
    vector<pair<string, int>> test = {{"Paneer Burger", 5}, {"Chicken Burger", 2}};//
    bill obj(12, "Arki", "12345678890", test);
    obj.generateBill();
    
    
    return 0;
}