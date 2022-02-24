#include <bits/stdc++.h>
#include <windows.h>
#define int long long
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
vector<string> productName;
map<string, pair<int, int>> products; // price is in rupees, duration is in minutes
map<string, int> productCount; // stores no.of units of that product ordered
map<string, int> profitMargin;
int x = 0, numberOfOrders = 0;

int convert(string s) {
    int ans = 0, x = 1;
    for(int i = (int)s.size() - 1; i > -1; i--) {
        if (s[i] >= '0' & s[i] <= '9') {
            ans += ((int)(s[i]) - (int)('0')) * x;
        } 
        else {
            ans += ((int)(s[i]) - (int)('A') + 10) * x;
        }
        x *= 16;
    }
    return ans;
}

void colour(){
    SetConsoleTextAttribute(hConsole, 7);
}
 
void colour(int k){
    SetConsoleTextAttribute(hConsole, k);
    // green is 10
    //light blue is 9
    //red is 4
    //purple is 5
}
 
string generateSpaces(int x){
    // x sized spacing
    string s="";
    while (x--)
    {
        s+=" ";
    }
    return s;
}

int generateSpacing(int x){
    // number .length basically
    int ans = 0;
    while (x > 0) {
        x /= 10;
        ans++;
    }
    return ans;
}

class bill
{
    public:
        int customerId;
        string customerName;
        string customerContact;
        vector<pair<string, int>> order; // product name, quantity
        int duration;
 
        bill(int id, string name, string contact, vector<pair<string, int>> &iorder, int d) {//&order already string , quantity
            customerId = id;
            customerName = name;
            customerContact = contact;
            order = iorder;
            duration = d;
        }
 
        void onScreen(int inst) { // BILL ID, CUSTOMER NAME, DURATION
           cout << "Bill ID: " << customerId << "     Customer Name: " << customerName << "   Estimated Duration: " << inst << endl;
        }
 
        void offScreen() { // BILL ID AND ORDER
            
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
            cout << "Customer ID: " << customerId << endl;
            cout << "Product Name                                                                     Quantity" << endl;
            for (auto x : order){
                cout << x.first << generateSpaces(85-x.first.length()-generateSpacing(x.second)) << x.second << endl;
            }
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
        }
        
        void generateBill(){
            colour(10);
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
            cout << "Bill ID:- " << customerId << endl;
            cout << "Customer name:- " << generateSpaces(84-16-customerName.length())<<customerName << endl;
            cout << "Customer contact:- " << generateSpaces(85-20-customerContact.length())<< customerContact << endl;
            int totalPrice = 0;
            cout << "Delicacy          " << "Quantity         " << "Price" << endl;
            for(int i = 0; i < (int)order.size(); i++){
                cout << order[i].first << "         " << order[i].second << "        " << order[i].second * products[order[i].first].first << endl;
                totalPrice += order[i].second * products[order[i].first].first;
            }
 
            cout << "Your total amount will be: " << totalPrice << endl;
            cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
            colour();
            //system("default")
        }
};
 
queue<bill> q;
 
void productInititalize() // default in menu available
{
    products["paneer burger"] = {65, 3}; // price, duration
    profitMargin["paneer burger"]=10;
    productName.push_back("paneer burger");
    productCount["paneer burger"] = 0;
    products["chicken burger"] = {85, 4};
    productName.push_back("chicken burger"); // to be added
    productCount["chicken burger"] = 0;
    profitMargin["chicken burger"]=15;
}
 
void addProduct() // To give feature to add products
{
    string name;
    int price, duration, profit;
    colour(3);
    cout << "Enter product name" << endl;
    colour();
    getline(cin >> ws, name);
    
    for (int i = 0; i < name.size(); i++)
    {
        name[i] = tolower(name[i]);
    }
    colour(12);
    cout << "Enter price, duration, profit Margin " << endl;
    colour();
    cin >> price >> duration >> profit;
    products[name] = {price, duration};
    productCount[name] = 0;
    productName.push_back(name);
    profitMargin[name] = profit;
    colour(10);
    cout << "Product Successfully Added" << endl << endl;
    colour();
}
 
void printMenu()
{
    colour(convert("9F"));
    cout << "Delicacy                               " << "Price                             " << "Duration" << endl;
    string s = "Delicacy                               ";
    string t = "Price                             ";
    string dur = "Duration";
    int first = s.size(), second = t.size(), third = dur.size();
    for (auto x : productName) {
        colour(convert("9F"));
        cout << x << generateSpaces(first - x.size()) << products[x].first << generateSpaces(second - generateSpacing(products[x].first) + third - generateSpacing(products[x].second)) << products[x].second; // << generateSpaces(third - generateSpacing(products[x].second));
        colour();
        cout << endl;
    }
    colour();
}
 
void reflect() { //sequencially display onScreen boxes and then offscreen boxes
    vector<bill> printer;
    int n = q.size();
    if (n <= 0) {
        return;
    }
    while (n--) {
        bill p = q.front();
        q.pop();
        q.push(p);
        printer.push_back(p);
    }
    cout << "This is the customer screen display" << endl;
    int cumulated = 0;
    cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
    //system("orange code")
    //system("red code")
    colour(4);
    for(auto x : printer){
        cumulated += x.duration;
        x.onScreen(cumulated);
        colour(3);
    }
    colour();
    //system("default")
    cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
    cout << "This is the worker screen display" << endl;
    q.front().offScreen();
    cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
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
    while (1) {
        cout << "Enter product name and quantity or type exit" << endl;
        string pro_name;
        int quantity;
        getline(cin >> ws, pro_name);
        for (int i = 0; i < pro_name.size(); i++)
        {
            pro_name[i] = tolower(pro_name[i]);
        }
        if (pro_name == "exit") {
            break;
        }
        else if (products.count(pro_name) == 0) {
            cout << "Invalid Input" << endl;
            continue;
        }
        else
        {
            cout << "Enter Quantity" << endl;
            cin >> quantity;
            if (quantity <= 0) {
                continue;
            }
            test.push_back({pro_name, quantity});
            productCount[pro_name] += quantity;
            instDuration = max(instDuration, products[pro_name].second * quantity);
        }
    }
    if(test.size() == 0) {
        return;
    }
    cout << "Your order is placed! " << endl;
    numberOfOrders++;
    bill obj(x++, custname, phone_no, test, instDuration);
    q.push(obj);
    reflect();
}
 
void printHistogram(map<string, int> &a)
{   
    int maxFreq = -1;
    for(auto x : a){
        maxFreq = max(x.second, maxFreq);
    }
    maxFreq += 2;
	for (int i = maxFreq; i > 0; i--) {
		cout.width(2);
        int maxSpace = log10(maxFreq) + 1;
        int space = log10(i);
        string spaces = "";
        for(int i = 0; i <= maxSpace - space; i++){
            spaces += " ";
        }
        colour(convert("0A"));
		cout << spaces << i << " > ";
        colour();

		for (auto j : a) {
 
			if (j.second >= i){
				colour(convert("05"));
                cout << "     O          ";
                colour();
            }
			// else print blank spaces
			else
				cout << "                ";
		}
		cout << "\n";
	}
 
	// for (int i = 0; i < a.size() + 3; i++)
	// 	cout << "---";
 
	cout << "\n";
	cout << "	 ";
    colour(convert("0A"));
	for (auto i : a) {
		cout.width(2); 
		cout << right << i.first << " ";
	}
    cout << endl;
    colour();
}

void profitHistogram(map<string, int> &delta, map<string, int> &productCount)
{
    int maxFreq = -1, cost;
    for (auto x : delta)
    {
        cost = x.second * productCount[x.first];
        maxFreq = max(cost, maxFreq);
    }
    maxFreq += 2;
    for (int i = maxFreq; i > 0; i--)
    {
        cout.width(2);
        int maxSpace = log10(maxFreq) + 1;
        int space = log10(i);
        string spaces = "";
        for (int i = 0; i <= maxSpace - space; i++)
        {
            spaces += " ";
        }
        colour(convert("0A"));
        cout << spaces << i << " > ";
        colour();
        for (auto j : delta)
        {
            cost = j.second * productCount[j.first];
            if (cost >= i){
                colour(convert("05"));
                cout << "     O          ";
                colour();
            }
            // else print blank spaces
            else
                cout << "                ";
        }
        cout << "\n";
    }

    // for (int i = 0; i < delta.size() + 3; i++)
    //     cout << "---";

    cout << "\n";
    cout << "	 ";
    colour(convert("02"));
    for (auto i : delta)
    {
        cout.width(2);
        cout << right << i.first << " ";
    }
    cout << endl;
    colour();
}

void generateHistogram() {
    cout << "Enter 1 to generate histogram of popularity of products \nEnter 2 to generate histogram of profit margin" << endl;
    int histoChoice = 0;
    cin >> histoChoice;
    switch(histoChoice){
        case 1 : 
            printHistogram(productCount); 
            break;
        case 2 : 
            profitHistogram(profitMargin, productCount); 
            break;
        default : 
            cout << "Invalid Input" <<endl;
    }
}
 
void editOrDelete() {
    for(int i = 0; i < productName.size(); i++) {
        cout << i + 1 << " - " << productName[i] << endl;
    }
    cout << "Enter the number corresponding to the product you want to update " << endl;
    int choice1 = 0;
    cin >> choice1;//index
    if (choice1 <= 0 && choice1 > productName.size()) {
        cout << " No such product " << endl;
        return;
    }
    else {
        cout << "Enter 1 to edit 2 to delete " << endl;
        int choice = 0;
        cin >> choice;
        if (choice == 1) {
            cout << "Enter 1 to edit price only \nEnter 2 to edit duration only \nEnter 3 to edit both " << endl;
            int nr = 0;
            cin >> nr;
            int newprice = products[productName[choice1 - 1]].first, newduration = products[productName[choice1 - 1]].second;
            if (nr == 1) {
                cout << "Enter the new price " << endl;
                cin >> newprice ;
            }
            else if (nr == 2) {
                cout << "Enter the new duration " << endl;
                cin >> newduration;
            }
            else if (nr == 3) {
                cout << "Enter the new price and new duration" << endl;
                cin >> newprice >> newduration;
            }
            else {
                cout << "Invalid choice" << endl;
                return;
            }
            products[productName[choice1 - 1]].first = newprice;
            products[productName[choice1 - 1]].second = newduration;
            
        }
        else if (choice == 2) { // delete
            products.erase(productName[choice1 - 1]);
            productName.erase(productName.begin() + choice1 - 1);
        }
        else {
            cout << "Invalid input" << endl;
            return;
        }
        cout << "The updated menu" << endl;
            printMenu();
    }
}

void averages() {
    long double orderTime = 0, itemTime = 0;
    int noOfProducts = 0;
    for (int i = 0; i < productName.size(); i++)
    {
        orderTime += productCount[productName[i]] * products[productName[i]].second;
        itemTime = orderTime;
        noOfProducts += productCount[productName[i]];
    }
    orderTime /= (long double)numberOfOrders;
    itemTime /= (long double)noOfProducts;
    cout << fixed << setprecision(3) << "Average time taken to process an order = " << orderTime << endl;
    cout << fixed << setprecision(3) << "Average time taken to prepare an item = " << itemTime << endl;
}

void editProfit() {
     for(int i = 0; i < productName.size(); i++) {
        cout << i + 1 << " - " << productName[i] << endl;
    }
    cout << "Enter the number corresponding to the product you want to update " << endl;
    int choice1 = 0;
    cin >> choice1;//index
    if (choice1 <= 0 && choice1 > productName.size()) {
        cout << " No such product " << endl;
        return;
    }
    else {
        cout << "Enter new profit" << endl;
        int profit = 0;
        cin >> profit;
        profitMargin[productName[choice1-1]] = profit;
    }
}

int32_t main()
{
    productInititalize();
    colour(convert("03"));
    cout << "Welcome to SwiftEats!" << endl;
    colour();
    while(1)
    {   
        // reflect
        int option = 0;
        cout << "----------------------------------------------------------------------------------------" << endl;
        cout << "Enter 1 for seeing the menu" << endl;
        cout << "Enter 2 to place order" << endl;
        cout << "Enter 3 to generate bill of completed order and pop from the queue" << endl;
        cout << "Enter 4 to print histograms" << endl;
        cout << "Enter 5 to add a product" << endl;
        cout << "Enter 6 to edit/delete a product" << endl;
        cout << "Enter 7 to edit profit margin" << endl;
        cout << "Enter 8 to print average time to prepare orders and items" << endl;
        cout << "Enter 9 to close the counter" << endl;
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
                addProduct();
                break;
            case 6:
                editOrDelete();
                break;
            case 7:
                editProfit();
                break;
            case 8:
                averages();
                break;
            case 9:
                cout << "Counter Closed" << endl;
                break;
            default:
                cout << "invalid Input" << endl;
        }
        if (option == 9) {
            break;
        }
    }
    return 0;
}