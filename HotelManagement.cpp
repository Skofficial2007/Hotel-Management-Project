#include <iostream> // Basic header file
#include <vector>   // To use vector
#include <conio.h>  // To use getch()
#include <unistd.h> // To use sleep function
#include <iomanip>  // To use setprecision()
#include <ctype.h>  // To use isdigit(), isaplha()
using namespace std;

// Global Variables
int CustomerChoice;
bool food = 0;

// Functions Declarations
void entry();
void clearBuffer();
int getIntegerInput();
float getFloatInput();
float calculateTip(double, int);
float calculateBill(int, float);
bool isValid(string &arr);

// Class Declaration
class Hotel;
class Resturant;

// Class Definations ->

class Resturant
{
    // Variable
    double ResturantBill;

    // To store item name and price
    struct MenuItem
    {
        string name;
        double price;
    };

    // To create a menu
    vector<MenuItem> menu = {
        {"Chicken Biryani", 10.5},
        {"Naan", 1.0},
        {"Paneer Tikka", 8.0},
        {"Dosa", 2.5}
        // add more items as you like
    };

    // To store ordered item no & it's quantity
    struct OrderItem
    {
        MenuItem menuItem;
        int quantity;
    };

    // To store ever item we ordered with it's quantity
    vector<OrderItem> order;

    // To create a copy of menu to print in table only
    vector<MenuItem> copy;

public:
    void ResturantEntry()
    {
        cout << "\n\n\t\t\t\t------------------------------------------ \n";
        cout << "\t\t\t\t\t   >>> Resturant <<< \n";
        cout << "\t\t\t\t------------------------------------------ \n\n";
    }

    void FirstTimeMenu()
    {
        string longest{};
        int LongestString;

        for (int i = 0; i < menu.size(); i++)
        {
            string temp = menu[i].name;

            if (temp.length() > longest.length())
            {
                longest = temp;
                LongestString = temp.length();
            }
        }

        for (int i = 0; i < menu.size(); i++)
        {
            bool flag = 0;
            string temp = menu[i].name;
            int space = LongestString - temp.length();

            if (space != 0)
            {
                int half = space / 2;
                string temp2{};
                for (int i = 0; i < (space); i++)
                {
                    if (i < half)
                    {
                        temp2 = temp2 + " ";
                    }
                    else
                    {
                        if (!flag)
                        {
                            temp2 = temp2 + temp;
                            flag = true;
                        }
                        temp2 = temp2 + " ";
                    }
                }

                copy.push_back({temp2, menu[i].price});
            }
            else
            {
                copy.push_back({menu[i].name, menu[i].price});
            }
        }
    }

    void showMenu()
    {
        cout << "\t --------------------------------------" << endl;
        for (int i = 0; i < copy.size(); i++)
        {
            if (copy[i].price > 9)
            {
                cout << "\t|  " << i + 1 << ".  |  "
                     << copy[i].name << "  |   " << fixed << setprecision(1) << copy[i].price << "$"
                     << "   |" << endl;
            }
            else
            {
                cout << "\t|  " << i + 1 << ".  |  "
                     << copy[i].name << "  |    " << fixed << setprecision(1) << copy[i].price << "$"
                     << "   |" << endl;
            }

            if (i == copy.size() - 1)
            {
                cout << "\t --------------------------------------" << endl;
            }
            else
            {
                cout << "\t|--------------------------------------|" << endl;
            }
        }
    }

    double showOrder()
    {
        clearBuffer();
        double total = 0;
        cout << "\n-> Your ordered items and there price are:\n";
        for (const auto &orderItem : order)
        {
            double cost = orderItem.menuItem.price * orderItem.quantity;
            total += cost;
            cout << "\n-> " << orderItem.menuItem.name << " x " << orderItem.quantity << " = $" << cost << "\n";
        }

        return total;
    }

    void addToOrder(int itemNumber, int quantity)
    {
        for (auto &orderItem : order)
        {
            if (orderItem.menuItem.name == menu[itemNumber - 1].name)
            {
                orderItem.quantity += quantity;
                return;
            }
        }
        order.push_back({menu[itemNumber - 1], quantity});
    }

    void gen_Res_Bill() // Generate Resturant Bill
    {
        double tipPer;
        double tip;
        cout << "\n-> Enter the percentage of tip you want to give: ";
        cin >> tipPer;
        tip = calculateTip(ResturantBill, tipPer);
        cout << "\n-> Tip Given by you is: $" << tip << endl;
        cout << "\n-> Total: $" << ResturantBill + tip << endl;
    }

    // To add food bill in check out
    double roomServiceBill()
    {
        cout << "\n-> Total bill for Food only is: $" << ResturantBill << endl;
        cout << "\n-> This will be added with your total at check out....." << endl;

        return (ResturantBill);
    }

    void choices(bool food = 0)
    {
        int option;
        char check;
        bool flag = 0;

        FirstTimeMenu();
        do
        {
            clearBuffer();
            showMenu();
            cout << "\n\n-> What do you wanna do?" << endl;
            cout << "\n-> Options:\n";
            cout << "\n1. Add to order\n";
            cout << "\n2. Show order\n";
            cout << "\n3. Checkout\n";

            flag = 0;
            do
            {
                if (flag)
                {
                    cout << "\n-> Wrong Input" << endl
                         << "\n-> Try again...." << endl;
                }
                fflush(stdin);
                cout << "\n-> Enter your choice: ";
                cin >> check;
                flag = 1;
            } while ((int)check < 49 || (int)check > 51);

            if (check == '1')
            {
                option = 1;
            }
            else if (check == '2')
            {
                option = 2;
            }
            else
            {
                option = 3;
            }

            if (option == 1)
            {
                bool error = 0;
                int itemNumber = 0;
                string checkItem{};
                int quantity = 0;
                do
                {
                    if (error)
                    {
                        cout << "\n-> Wrong input try again...." << endl;
                    }
                    cout << "\n-> Enter menu item number: ";
                    cin >> checkItem;
                    if (isValid(checkItem))
                    {
                        if (!(checkItem.length() > 1))
                        {
                            itemNumber = (int)checkItem[0] - 48;
                        }
                    }
                    error = 1;
                } while (itemNumber < 1 || itemNumber > menu.size());

                checkItem = {};
                error = 0;

                do
                {
                    if (error)
                    {
                        cout << "\n-> Wrong input try again...." << endl;
                    }
                    cout << "\n-> Enter quantity: ";
                    cin >> checkItem;
                    if (isValid(checkItem))
                    {
                        for (int i = 0; i < checkItem.length(); i++)
                        {
                            int temp = (int)checkItem[i] - 48;
                            quantity = (quantity * 10) + temp;
                        }
                        break;
                    }
                    error = 1;
                } while (1);

                addToOrder(itemNumber, quantity);
            }
            else if (option == 2)
            {
                showOrder();
                cout << "\n\n-> Press any key to continue : ";
                getch();
                clearBuffer();
            }
        } while (option != 3);
        clearBuffer();

        if (!food)
        {
            ResturantBill = showOrder();
            gen_Res_Bill();
            cout << "\n\n\n-> Press any key to exit : ";
            getch();
            clearBuffer();
        }
        else
        {
            ResturantBill = showOrder();
            roomServiceBill();
            cout << "\n\n\n-> Press any key to continue : ";
            getch();
            clearBuffer();
        }
    }
};

class Hotel
{
    // Variables
    int days, roomNo;
    float roomCharge, tipPer;
    bool Is_Room_Service = 0;

    // To access resturant class
    Resturant roomService;

public:
    void HotelCheckIn()
    {
        clearBuffer();
        cout << "\n\t\t\t\t------------------------------------------ \n";
        cout << "\t\t\t\t            >>> Reception <<< \n";
        cout << "\t\t\t\t------------------------------------------ \n\n";
        cout << "\n-> Welcome Sir To Our Hotel" << endl;
        cout << "\n-> How many days do you want to stay here: " << endl;
        cout << "\n-> Days: ";
        days = getIntegerInput();

        clearBuffer();
        SelectRoom();
        cout << "\n-> Thanks you for your time" << endl
             << "\n-> Enjoy your Stay...." << endl;
    }

    void SelectRoom()
    {
        cout << "\n\t\t\t\t------------------------------------------ \n";
        cout << "\t\t\t\t            >>> Select Menu <<< \n";
        cout << "\t\t\t\t------------------------------------------ \n\n";
        cout << "\n-> Select your room please: " << endl;
        cout << "\n1. Single Bed Room -> 250$ per night" << endl;
        cout << "\n2. Double Bed Room -> 450$ per night" << endl;
        cout << "\n3. Shared Room -> 150$ per night" << endl;
        cout << "\n4. Vip Single Bed Room -> 700$ per night" << endl;
        cout << "\n5. Vip Double Bed Room -> 1000$ per night" << endl;

        int choice;
        int flag = 0;
        do
        {
            if (flag)
            {
                cout << "\n-> Wrong input...." << endl
                     << "\n-> Try Again!" << endl;
            }
            cout << "\n-> Enter your choice: ";
            cin >> choice;
            flag = 1;
        } while (choice > 5 || choice < 1);

        switch (choice)
        {
        case 1:
        {
            roomCharge = 250.00;
            break;
        }
        case 2:
        {
            roomCharge = 450.00;
            break;
        }
        case 3:
        {
            roomCharge = 150.00;
            break;
        }
        case 4:
        {
            roomCharge = 700.00;
            break;
        }
        case 5:
        {
            roomCharge = 1000.00;
            break;
        }
        default:
        {
            cout << "\n-> Something is wrong....Let's try again" << endl;
            cout << "\n-> Press any key to reset : ";
            getch();
            clearBuffer();
            SelectRoom();
            break;
        }
        }

        roomNo = choice;
    }

    string RoomName(int choice)
    {
        string roomName;

        switch (choice)
        {
        case 1:
        {
            roomName = "Single Bed Room";
            break;
        }
        case 2:
        {
            roomName = "Double Bed Room";
            break;
        }
        case 3:
        {
            roomName = "Shared Room";
            break;
        }
        case 4:
        {
            roomName = "Vip Single Bed Room";
            break;
        }
        case 5:
        {
            roomName = "Vip Double Bed Room";
            break;
        }
        default:
        {
            roomName = "ERROR";
            break;
        }
        }

        return roomName;
    }

    void RoomService()
    {
        clearBuffer();

        cout << "\n\n\t\t\t\t------------------------------------------ \n";
        cout << "\t\t\t\t\t   >>> Room Service <<< \n";
        cout << "\t\t\t\t------------------------------------------ \n\n";

        cout << "\n-> Do you also wanna try our Resturant service? (Y/N || y/n) " << endl;
        while (1)
        {
            cout << "\n-> Enter your choice: ";
            char ch;
            cin >> ch;

            if (ch == 'Y' || ch == 'y')
            {
                food = 1;
                roomService.choices(food);
                food = 0;
                Is_Room_Service = 1;
                break;
            }
            else if (ch == 'N' || ch == 'n')
            {
                food = 0;
                cout << "\n-> Alright! Hope you enjoy your stay...." << endl;
                Is_Room_Service = 0;
                break;
            }
            else
            {
                cout << "\n-> Wrong Input" << endl
                     << "\n-> Try again...." << endl;
            }
        }
    }

    void generateBill(int days, float roomCharge, float tip, string roomName, double foodBill, bool Is_Room_Service)
    {
        cout << "\n-> Your room was: " << roomName << endl;
        cout << "\n-> Which is charged " << roomCharge << "$ per night" << endl;
        float totalBill = calculateBill(days, roomCharge);
        cout << "\n-> The total bill amount is Rs." << totalBill << endl;
        if (Is_Room_Service)
        {
            cout << "\n-> The total bill amount for food is " << foodBill << "$" << endl;
            cout << "\n-> The tip amount is Rs." << tip << endl;
            cout << "\n-> The net amount payable is Rs." << (totalBill + tip + foodBill) << endl;
        }
        else
        {
            cout << "\n-> The total bill amount for food is 0$" << endl;
            cout << "\n-> The tip amount is Rs." << tip << endl;
            cout << "\n-> The net amount payable is Rs." << (totalBill + tip) << endl;
        }
    }

    void HotelCheckOut()
    {
        double foodBill;

        cout << "\n\n\t\t\t\t------------------------------------------- \n";
        cout << "\t\t\t\t     >>> After Completing Your Stay <<< \n";
        cout << "\t\t\t\t------------------------------------------- \n\n";
        cout << "\n-> So you want to check-out..." << endl;
        cout << "\n-> You stayed for " << days << " Days" << endl;
        cout << "\n-> In room no. " << roomNo << " : " << RoomName(roomNo) << endl;
        cout << "\n-> Per Day price for that room: " << roomCharge << endl;
        if (Is_Room_Service)
        {
            foodBill = roomService.roomServiceBill();
            cout << "\n-> Bill for Food you ordered through Room Service: " << foodBill << "$" << endl;
        }
        else
        {
            cout << "\n-> Bill for Food you ordered through Room Service: 0$" << endl;
        }

        cout << "\n-> Tip: " << endl;
        cout << "\n-> Enter the percentage of tip you want to give for our services: ";
        tipPer = getIntegerInput();
        clearBuffer();

        double billAmount = calculateBill(days, roomCharge) + foodBill;
        cout << "\n-> Calculating Your Bill Amount";
        sleep(1);
        cout << "..";
        sleep(1);
        cout << "..";
        sleep(1);
        cout << ".." << endl;
        sleep(2);

        double tip = calculateTip(billAmount, tipPer);
        cout << "\n-> Calculating Your Tip Amount";
        sleep(1);
        cout << "..";
        sleep(1);
        cout << "..";
        sleep(1);
        cout << ".." << endl;
        sleep(2);

        cout << "\n-> Thanks for your patience and understanding" << endl;
        cout << "\n-> Here's Your Bill -> " << endl;
        sleep(2);
        clearBuffer();
        generateBill(days, roomCharge, tip, RoomName(roomNo), foodBill, Is_Room_Service);
        cout << endl
             << endl;
        cout << "\n-> Press any key to exit : ";
        getch();
    }
};

// Function Definations ->

void clearBuffer()
{
    system("cls"); // clears the output screen
    fflush(stdin); // clears the input buffers like '\n'
}

int getIntegerInput()
{
    int input;
    cin >> input;
    return input;
}

float getFloatInput()
{
    float input;
    cin >> input;
    return input;
}

float calculateTip(double billAmount, int tipPercentage)
{
    if (tipPercentage == 0)
    {
        cout << "\n-> No tip is given....." << endl;
        return 0;
    }
    else
    {
        float tipAmount = billAmount * (tipPercentage / 100.0);
        return tipAmount;
    }
}

float calculateBill(int days, float roomCharge)
{
    float totalBill = roomCharge * days;
    return totalBill;
}

bool isValid(string &arr)
{
    for (char x : arr)
    {
        if (isdigit(x) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void entry()
{
    bool flag = 0;
    char choice;

    clearBuffer();
    system("title Hotel Management System");
    system("color F5");
    cout << "\n\t\t\t\t------------------------------------------ \n";
    cout << "\t\t\t\t     >>> Hotel Management System  <<< \n";
    cout << "\t\t\t\t------------------------------------------ \n\n";

    cout << "-> Welcome!" << endl;
    cout << "\n-> How can we serve you?" << endl;
    cout << "\n-> Choices: " << endl;
    cout << "\n1. You want a room to stay here for couple of nights" << endl;
    cout << "\n2. You only want to eat at our Resturant" << endl;

    do
    {
        if (flag)
        {
            cout << "\n-> Wrong Input" << endl
                 << "\n-> Try again...." << endl;
        }
        fflush(stdin);
        cout << "\n-> Enter your choice: ";
        cin >> choice;
        flag = 1;
    } while ((int)choice < 49 || (int)choice > 50);

    if (choice == '1')
    {
        CustomerChoice = 1;
    }
    else
    {
        CustomerChoice = 2;
    }

    if (CustomerChoice == 1)
    {
        Hotel stay;
        stay.HotelCheckIn();
        stay.RoomService();
        stay.HotelCheckOut();
    }
    else
    {
        Resturant foodie;
        foodie.ResturantEntry();
        foodie.choices();
    }
}

// ------------------------- Main Function --------------------------

int main()
{
    entry();

    return 0;
}

// ------------------------------------------------------------------