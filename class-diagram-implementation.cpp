#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Product
{
    private:
        string id;
        string name;
        double price;
        int quantity = 1;

    public:
        Product(string pID = "", string pName = "", double pPrice = 0)
        {
            this->id = pID;
            this->name = pName;
            this->price = pPrice;
        }

        string getID() { return id; }

        string getName() { return name; }

        double getPrice() { return price; }

        void addQuantity() { quantity++; }

        int getQuantity() { return quantity; }
        
};

int numOfProducts = 5;
Product shopProducts[5] = {
    Product("1", "Banana", 5),
    Product("2", "Chips", 30),
    Product("3", "Coke 1.5", 70),
    Product("4", "Bread", 150),
    Product("5", "Milk", 100),
};

bool checkProductID(string productID)
{
    for (int i = 0; i < numOfProducts; i++)
    {
        Product product = shopProducts[i];
        if (product.getID() == productID)
            return true;
    }
    return false;
}

Product* getShopProductWithID(string productID)
{
    for (int i = 0; i < numOfProducts; i++)
    {
        Product product = shopProducts[i];
        if (product.getID() == productID)
            return &shopProducts[i];
    }
    return nullptr;
}

void displayProducts();

class Order;

class ShoppingCart
{
    private:
        vector<Product> products;
        double totalAmount = 0;

    public:
        double getTotalAmount() { return totalAmount; }
        
        void addProductToCart()
            {
                string productID;
                char choice;
                bool idValid = false;
                do
                {
                    do
                    {
                        cout << "==========>>ADD-TO-CART<<==========\n";
                        cout << "Enter the ID of the product you want to add in the shopping cart: ";
                        getline(cin, productID);
                        idValid = checkProductID(productID);
                        if (!idValid)
                        {
                            system("cls");
                            cout << "==========>>ERROR<<==========\n";
                            cout << "Product ID is not valid or in the shop!\n";
                            system("pause");
                            displayProducts();
                        }
                    } while (!idValid);
                    
                    int cartProductIndex = getCartProductIndex(productID);
                    if (cartProductIndex == -1)
                    {
                        Product newProduct = *getShopProductWithID(productID);
                        this->totalAmount += newProduct.getPrice();
                        this->products.push_back(newProduct);

                    }
                    else
                    {
                        this->totalAmount += products[cartProductIndex].getPrice();
                        this->products[cartProductIndex].addQuantity();
                    }
                    do
                    {
                        system("cls");
                        cout << "==========>>SUCCESS<<==========\n";
                        cout << "Product successfully added to cart!\n";
                        cout << "Do you want to add another product to the shopping cart? [Y/N]: ";
                        cin >> choice;
                        if (!cin || (tolower(choice) != 'n' && tolower(choice) != 'y'))
                        {
                            system("cls");
                            cout << "==========>>ERROR<<==========\n";
                            cout << "Please input either Y or N!\n";
                            system("pause");
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        else if (tolower(choice) == 'y')
                            displayProducts();
                        
                        cin.ignore();
                    } while (!cin || (tolower(choice) != 'n' && tolower(choice) != 'y'));
                } while (tolower(choice) != 'n');

                
            }

        vector<Product> getProducts() { return products; }

        bool displayCartProducts()
        {
            system("cls");
            if (products.size() <= 0)
            {
                cout << "==========>>EMPTY<<==========\n";
                cout << "You have no products in your shopping cart!\n";
                system("pause");
                return false;
            }

            cout << "==========>>YOUR-SHOPPING-CART<<==========\n";
            cout << "Total Amount: " << this->totalAmount << endl;
            cout << "|--------------------------------------------|\n";
            for (int i = 0; i < products.size(); i++)
            {
                Product product = products[i];
                
                cout << setw(15)  << left << "| ID: " << setw(30) << left << product.getID() << "|"
                << endl << setw(15)  << left << "| Name: " << setw(30) << left << product.getName() << "|"
                << endl << setw(15)  << left << "| Price: " << setw(30) << left << product.getPrice() << "|" 
                << endl << setw(15)  << left << "| Quantity: " << setw(30) << left << product.getQuantity() << "|" << endl;
                cout << "|--------------------------------------------|\n";
            }
            return true;
        }

        int getCartProductIndex(string productID)
        {
            for (int i = 0; i < products.size(); i++)
            {
                Product product = products[i];
                if (product.getID() == productID)
                    return i;
            }
            return -1;
        }

        bool checkoutCart()
        {
            char choice;
            do
            {
                cout << "Do you want to check out all the products? [Y/N]: ";
                cin >> choice;
                if (tolower(choice) != 'n' && tolower(choice) != 'y')
                {
                    system("cls");
                    cout << "==========>>ERROR<<==========\n";
                    cout << "Enter only Y or N!\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("pause");
                    cout << endl;
                }
            } while (tolower(choice) != 'n' && tolower(choice) != 'y');

            if (tolower(choice) == 'y')
            {
                system("cls");
                cout << "==========>>SUCCESS<<==========\n";
                cout << "You have successfully checked out the products!\n";
                system("pause");
                return true;
            }
            return false;
        }
};

class Order
{
    private:
        vector<Product> products;
        double totalAmount = 0;
        int id;

    public:
        Order(ShoppingCart pCart, int pID)
        {
            this->products = pCart.getProducts();
            this->totalAmount = pCart.getTotalAmount();
            this->id = pID;
        }

        void displayOrder()
        {
            cout << "Order ID: " << id << endl;
            cout << "Total Amount: " << totalAmount << endl;
            cout << setw(25)  << left << "| Product ID "
            << setw(25)  << left << "Name: " 
            << setw(25)  << left << "Price: " 
            << setw(25)  << left << "Quantity: " << "|" << endl;
            for (int i = 0; i < products.size(); i++)
            {
                Product product = products[i];

                cout << "| " << setw(23)  << left << product.getID()
                << setw(25)  << left << product.getName()
                << setw(25)  << left << product.getPrice()
                << setw(25)  << left << product.getQuantity() << "|" << endl;
            }
            cout << endl;
        }
};

int displayMenu()
{
    system("cls");
    int value;
    cout << "==========>>MENU<<==========\n";
    cout << "1. View Products\n";
    cout << "2. View Shopping Cart\n";
    cout << "3. View Orders\n";
    cout << "4. Exit\n";
    cin >> value;
    return value;
}

void displayProducts()
{
    system("cls");
    cout << "|===============>>SHOP<<================|\n";
    for (int i = 0; i < numOfProducts; i++)
    {
        Product product = shopProducts[i];
        cout << setw(10)  << left << "| ID: " << setw(30) << left << product.getID() << "|"
        << endl << setw(10)  << left << "| Name: " << setw(30) << left << product.getName() << "|"
        << endl << setw(10)  << left << "| Price: " << setw(30) << left << product.getPrice() << "|" << endl;
        cout << "|---------------------------------------|\n";
    }
}

void displayOrders(vector<Order> orders)
{
    system("cls");
    if (orders.size() <= 0)
    {
        cout << "==========>>EMPTY<<==========\n";
        cout << "You have no orders!\n";
        system("pause");
        return;
    }

    for(int i = 0; i < orders.size(); i++)
    {
        Order order = orders[i];
        order.displayOrder();
    }
    system("pause");
}

int main()
{
    ShoppingCart cart;
    vector<Order> orders;
    int choice = 0;
    do
    {
        if (!cin)
        {
            cout << "==========>>ERROR<<==========\n";
            cout << "Incorrect Input!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            system("pause");
        }
        choice = displayMenu();
        cin.ignore();
        switch(choice)
        {
            case 1:
                displayProducts();
                cart.addProductToCart();
                break;
            case 2:
                if (cart.displayCartProducts())
                {
                    if (cart.checkoutCart())
                    {
                        Order newOrder(cart, orders.size() + 1);
                        orders.push_back(newOrder);
                        cart = ShoppingCart();
                    }
                }
                break;
            case 3:
                displayOrders(orders);
                break;
            case 4:
                return 0;
        }
        
    } while (choice != 4);
    
    return 0;
}