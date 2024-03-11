#pragma once
#include <iostream>
#include <fstream>
#include <string>"
#include <vector>
#include <algorithm>
class Product {
public:
    std::string id;
    std::string name;
    double price;
    int quantity;

    Product() : id(""), name(""), price(0.0), quantity(0) {}

    Product(const std::string& _id, const std::string& _name, double _price, int _quantity)
        : id(_id), name(_name), price(_price), quantity(_quantity) {}

    void display() const {
        std::cout << "ID: " << id << "\nName: " << name << "\nPrice: VND " << price << "\nQuantity: " << quantity << "\n\n";
    }
};

class ProductManager {
public:
    static const std::string dataFile;
    std::vector<Product> products;

public:
    void addProduct();
    void updateProduct();
    void deleteProduct();
    void searchProduct();
    void checkProductExistence();
    void saveDataToFile();


    ProductManager() {
        loadDataFromFile();
    }

public:
    void loadDataFromFile();
    bool isIdExist(const std::string& productId);
};

const std::string ProductManager::dataFile = "C:\\Users\\admin\\source\\repos\\14012024\\products.txt";

void ProductManager::addProduct() {
    std::string id;
    std::string name;
    double price;
    int quantity;

    std::cout << "Nhập ID: ";
    std::cin >> id;

    if (isIdExist(id)) {
        std::cout << "Sản phẩm với ID " << id << " đã tồn tại.\n";
        return;
    }

    std::cout << "Nhập tên: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Nhập giá: ";
    std::cin >> price;

    std::cout << "Nhập số lượng : ";
    std::cin >> quantity;

    if (price < 30000 || price >500000 || quantity <10 ) {
        std::cout << "Thông tin không hợp lệ. Tạo sản phẩm thất bại.\n";
        return;
    }
    Product newProduct(id, name, price, quantity);
    products.push_back(newProduct);
    std::cout << "Thêm sản phẩm thành công.\n";

    saveDataToFile();
}

void ProductManager::updateProduct() {
    std::string id;
    std::cout << "Nhap ID san pham muon chinh sua: ";
    std::cin >> id;

    auto it = std::find_if(products.begin(), products.end(), [id](const Product& p) {
        return p.id == id;
        });

    if (it != products.end()) {
        it->display();

        std::cout << "Cap nhat ten san pham: ";
        std::cin.ignore();
        std::getline(std::cin, it->name);

        std::cout << "Cap nhat gia: ";
        std::cin >> it->price;

        std::cout << "Cap nhat so luong: ";
        std::cin >> it->quantity;

        std::cout << "Cap nhat san pham thanh cong.\n";

        saveDataToFile();
    }
    else {
        std::cout << "San pham khong ton tai.\n";
    }
}

void ProductManager::deleteProduct() {
    std::string id;
    std::cout << "Nhập id sản phẩm muốn xóa: ";
    std::cin >> id;

    auto it = std::find_if(products.begin(), products.end(), [id](const Product& p) {
        return p.id == id;
        });

    if (it != products.end()) {
        it->display();

        char confirm;
        std::cout << "Xác nhận xóa sản phẩm? (y/n): ";
        std::cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            products.erase(it);
            std::cout << "Xóa sản phẩm thành công.\n";

            saveDataToFile();
        }
        else {
            std::cout << "Hủy xóa.\n";
        }
    }
    else {
        std::cout << "San pham voi ID " << id << " khong tim thay.\n";
    }
}

void ProductManager::searchProduct() {
    std::string id;
    std::cout << "Nhap ID san pham tim kiem: ";
    std::cin >> id;

    auto it = std::find_if(products.begin(), products.end(), [id](const Product& p) {
        return p.id == id;
        });

    if (it != products.end()) {
        it->display();
    }
    else {
        std::cout << "San pham ID " << id << " khong ton tai.\n";
    }
}

void ProductManager::checkProductExistence() {
    std::string id;
    std::cout << "Enter product ID to check existence: ";
    std::cin >> id;

    if (isIdExist(id)) {
        std::cout << "Product with ID " << id << " exists.\n";
    }
    else {
        std::cout << "Product with ID " << id << " does not exist.\n";
    }
}

void ProductManager::loadDataFromFile() {
    std::ifstream inputFile(dataFile);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file for reading.\n";
        return;
    }

    std::string id;
    std::string name;
    double price;
    int quantity;

    while (inputFile >> id >> std::ws && std::getline(inputFile, name) && inputFile >> price >> quantity) {
        Product loadedProduct(id, name, price, quantity);
        products.push_back(loadedProduct);
    }

    inputFile.close();
}

void ProductManager::saveDataToFile() {
    std::ofstream outputFile(dataFile);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& product : products) {
        outputFile << product.id << "\n" << product.name << "\n" << product.price << " " << product.quantity << "\n";
    }

    outputFile.close();
}

bool ProductManager::isIdExist(const std::string& id) {
    return std::any_of(products.begin(), products.end(), [id](const Product& p) {
        return p.id == id;
        });
}
