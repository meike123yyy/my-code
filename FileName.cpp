#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// 基类 Media 表示图书馆中的物品
class Media {
protected:
    string id;       // 物品ID
    string title;    // 物品标题
    string author;   // 物品作者
    bool isBorrowed;  // 物品是否被借出
public:
    Media(const string& id, const string& title, const string& author) : id(id), title(title), author(author), isBorrowed(false) {}
    virtual ~Media() {}

    string getID() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsBorrowed() const { return isBorrowed; }

    virtual void display() const = 0;
    virtual void edit(const string&, const string&, const string&) = 0;
    virtual void borrow() { isBorrowed = true; }
    virtual void returnItem() { isBorrowed = false; }
};

// 派生类 Book 表示图书
class Book : public Media {
private:
    string publisher;  // 出版社
    string isbn;       // ISBN编号
    int pages;         // 页数
public:
    Book(const string& id, const string& title, const string& author, const string& publisher, const string& isbn, int pages) :
        Media(id, title, author), publisher(publisher), isbn(isbn), pages(pages) {}

    void display() const override {
        cout << "类型: Book, ID: " << id << ", 标题: " << title << ", 作者: " << author << ", 出版商: " << publisher << ", ISBN: " << isbn << ", 页数: " << pages << ", 借出状态: " << (isBorrowed ? "已借出" : "未借出") << endl;
    }

    void edit(const string& newTitle, const string& newAuthor, const string& newPublisher) override {
        title = newTitle;
        author = newAuthor;
        publisher = newPublisher;
    }

    int getPages() const {
        return pages;
    }
    string getISBN() const {
        return isbn;
    }
    string getPublisher() const {
        return publisher;
    }
};

// 派生类 CD 表示光盘
class CD : public Media {
private:
    string producer;  // 制作人
    int year;         // 发行年份
    int duration;     // 时长（单位：分钟）
public:
    CD(const string& id, const string& title, const string& author, const string& producer, int year, int duration) :
        Media(id, title, author), producer(producer), year(year), duration(duration) {}

    void display() const override {
        cout << "类型: CD, ID: " << id << ", 标题: " << title << ", 作者: " << author << ", 出品者: " << producer << ", 出品年份: " << year << ", 时长: " << duration << ", 借出状态: " << (isBorrowed ? "已借出" : "未借出") << endl;
    }

    void edit(const string& newTitle, const string& newAuthor, const string& newProducer) override {
        title = newTitle;
        author = newAuthor;
        producer = newProducer;
    }

    int getYear() const {
        return year;
    }
    string getProducer() const {
        return producer;
    }
    int getDuration() const {
        return duration;
    }
};

// 用户类
class User {
private:
    string id;
    string name;
    string username;
    string password;
    vector<string> borrowedItems;  // 存储借出的物品ID
public:
    User(const string& id, const string& name, const string& username, const string& password)
        : id(id), name(name), username(username), password(password) {}

    string getID() const { return id; }
    string getName() const { return name; }
    string getUsername() const { return username; }
    string getPassword()const { return password; }
    bool validatePassword(const string& pwd) const { return password == pwd; }

    vector<string> getBorrowedItems() const { return borrowedItems; }

    void borrowItem(const string& itemID) {
        borrowedItems.push_back(itemID);
    }

    void returnItem(const string& itemID) {
        borrowedItems.erase(remove(borrowedItems.begin(), borrowedItems.end(), itemID), borrowedItems.end());
    }

    void display() const {
        cout << "用户ID: " << id << ", 用户名: " << name << ", 借出物品数量: " << borrowedItems.size() << endl;
    }
};

// 图书馆类，管理图书馆中的物品（书籍和光盘）
class Library {
private:
    vector<Media*> items;  // 存储物品的容器
    vector<User*> users;   // 存储用户的容器
    const int MAX_ITEMS = 100;  // 图书馆物品的最大容量
    User* currentUser;
public:
    Library() : currentUser(nullptr) {}
    ~Library() {
        for (Media* item : items) {
            delete item;
        }
        for (User* user : users) {
            delete user;
        }
    }

    void addItem(Media* item) {
        if (items.size() >= MAX_ITEMS) {
            cout << "无法添加, 容量已满." << endl;
            return;
        }
        for (Media* existingItem : items) {
            if (existingItem->getID() == item->getID()) {
                cout << "重复数据，添加取消." << endl;
                return;
            }
        }
        items.push_back(item);
    }

    void queryByTitle(const string& title) const {
        bool found = false;
        for (const Media* item : items) {
            if (item->getTitle() == title) {
                item->display();
                found = true;
            }
        }
        if (!found) {
            cout << "没有该标题的项目!" << endl;
        }
    }

    void queryByType(const string& type) const {
        bool found = false;
        for (const Media* item : items) {
            if (type == "Book" && dynamic_cast<const Book*>(item) != nullptr) {
                item->display();
                found = true;
            }
            else if (type == "CD" && dynamic_cast<const CD*>(item) != nullptr) {
                item->display();
                found = true;
            }
        }
        if (!found) {
            cout << "该类别中没有项目!" << endl;
        }
    }

    void displayAllItems() const {
        for (const Media* item : items) {
            item->display();
        }
    }

    void editItem(const string& id, const string& newTitle, const string& newAuthor, const string& additionalInfo) {
        for (Media* item : items) {
            if (item->getID() == id) {
                item->edit(newTitle, newAuthor, additionalInfo);
                return;
            }
        }
        cout << "这个ID不存在." << endl;
    }

    void deleteItem(const string& id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getID() == id) {
                delete* it;
                items.erase(it);
                return;
            }
        }
        cout << "这个ID不存在." << endl;
    }

    void queryByAuthor(const string& author) const {
        bool found = false;
        for (const Media* item : items) {
            if (item->getAuthor() == author) {
                item->display();
                found = true;
            }
        }
        if (!found) {
            cout << "没有该作者的项目!" << endl;
        }
    }

    void queryCDByYearRange(int startYear, int endYear) const {
        bool found = false;
        for (const Media* item : items) {
            const CD* cd = dynamic_cast<const CD*>(item);
            if (cd && cd->getYear() >= startYear && cd->getYear() <= endYear) {
                cd->display();
                found = true;
            }
        }
        if (!found) {
            cout << "该年份范围内没有光盘项目!" << endl;
        }
    }

    void queryBookByPageRange(int startPage, int endPage) const {
        bool found = false;
        for (const Media* item : items) {
            const Book* book = dynamic_cast<const Book*>(item);
            if (book && book->getPages() >= startPage && book->getPages() <= endPage) {
                book->display();
                found = true;
            }
        }
        if (!found) {
            cout << "该页数范围内没有书籍项目!" << endl;
        }
    }

    void lendItem(const string& userID, const string& itemID) {
        Media* item = nullptr;
        User* user = nullptr;
        for (Media* mediaItem : items) {
            if (mediaItem->getID() == itemID) {
                item = mediaItem;
                break;
            }
        }
        for (User* libraryUser : users) {
            if (libraryUser->getID() == userID) {
                user = libraryUser;
                break;
            }
        }
        if (item && user) {
            if (!item->getIsBorrowed()) {
                item->borrow();
                user->borrowItem(itemID);
                cout << "物品已借出: ";
                item->display();
            }
            else {
                cout << "物品已被借出." << endl;
            }
        }
        else {
            cout << "用户或物品ID不存在." << endl;
        }
    }

    void returnItem(const string& userID, const string& itemID) {
        Media* item = nullptr;
        User* user = nullptr;
        for (Media* mediaItem : items) {
            if (mediaItem->getID() == itemID) {
                item = mediaItem;
                break;
            }
        }
        for (User* libraryUser : users) {
            if (libraryUser->getID() == userID) {
                user = libraryUser;
                break;
            }
        }
        if (item && user) {
            if (item->getIsBorrowed()) {
                item->returnItem();
                user->returnItem(itemID);
                cout << "物品已归还: ";
                item->display();
            }
            else {
                cout << "物品未被借出." << endl;
            }
        }
        else {
            cout << "用户或物品ID不存在." << endl;
        }
    }

    void countItems() const {
        int bookCount = 0, cdCount = 0;
        for (const Media* item : items) {
            if (dynamic_cast<const Book*>(item) != nullptr) {
                bookCount++;
            }
            else if (dynamic_cast<const CD*>(item) != nullptr) {
                cdCount++;
            }
        }
        cout << "书籍数量: " << bookCount << ", 光盘数量: " << cdCount << endl;
    }

    string generateRandomID() const {
        srand(static_cast<unsigned int>(time(nullptr)));
        stringstream ss;
        ss << "ID" << setw(4) << setfill('0') << rand() % 10000;
        return ss.str();
    }

    void registerUser(const string& id, const string& name, const string& username, const string& password) {
        for (User* user : users) {
            if (user->getUsername() == username) {
                cout << "用户名已存在." << endl;
                return;
            }
        }
        users.push_back(new User(id, name, username, password));
        cout << "用户已注册: 用户名 = " << username << ", 名称 = " << name << endl;
    }

    bool loginUser(const string& username, const string& password) {
        for (User* user : users) {
            if (user->getUsername() == username && user->validatePassword(password)) {
                currentUser = user;
                cout << "登录成功, 欢迎 " << user->getName() << "!" << endl;
                return true;
            }
        }
        cout << "用户名或密码错误." << endl;
        return false;
    }

    void logoutUser() {
        currentUser = nullptr;
        cout << "已注销." << endl;
    }

    User* getCurrentUser() const {
        return currentUser;
    }

    vector<Media*> getItems() const
    {
        return items;
    }

    vector<User*> getUsers() const {
        return users;
    }
};

void saveLibraryToFile(const Library& library, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "无法打开文件进行写入: " << filename << endl;
        return;
    }
    for (const Media* item : library.getItems()) {
        if (dynamic_cast<const Book*>(item)) {
            outFile << "Book" << endl;
        }
        else if (dynamic_cast<const CD*>(item)) {
            outFile << "CD" << endl;
        }
        outFile << item->getID() << endl;
        outFile << item->getTitle() << endl;
        outFile << item->getAuthor() << endl;
        outFile << item->getIsBorrowed() << endl;
        if (const Book* book = dynamic_cast<const Book*>(item)) {
            outFile << book->getPublisher() << endl;
            outFile << book->getISBN() << endl;
            outFile << book->getPages() << endl;
        }
        else if (const CD* cd = dynamic_cast<const CD*>(item)) {
            outFile << cd->getProducer() << endl;
            outFile << cd->getYear() << endl;
            outFile << cd->getDuration() << endl;
        }
    }
    for (const User* user : library.getUsers()) {
        outFile << "User" << endl;
        outFile << user->getID() << endl;
        outFile << user->getName() << endl;
        outFile << user->getUsername() << endl;
        outFile << user->getPassword() << endl;
        for (const string& itemID : user->getBorrowedItems()) {
            outFile << itemID << endl;
        }
        outFile << "END" << endl;
    }
    outFile.close();
}

void loadLibraryFromFile(Library& library, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "无法打开文件进行读取: " << filename << endl;
        return;
    }
    string type, id, title, author, publisherOrProducer, isbn, userID, userName, username, userpassword, itemID;
    bool isBorrowed;
    int pages, year, duration;
    while (getline(inFile, type)) {
        if (type == "Book" || type == "CD") {
            getline(inFile, id);
            getline(inFile, title);
            getline(inFile, author);
            inFile >> isBorrowed;
            inFile.ignore();
            if (type == "Book") {
                getline(inFile, publisherOrProducer);
                getline(inFile, isbn);
                inFile >> pages;
                inFile.ignore();
                library.addItem(new Book(id, title, author, publisherOrProducer, isbn, pages));
            }
            else if (type == "CD") {
                getline(inFile, publisherOrProducer);
                inFile >> year >> duration;
                inFile.ignore();
                library.addItem(new CD(id, title, author, publisherOrProducer, year, duration));
            }
            if (isBorrowed) {
                library.lendItem("unknown", id);
            }
        }
        else if (type == "User") {
            getline(inFile, userID);
            getline(inFile, userName);
            getline(inFile, username);
            getline(inFile, userpassword);
            User* user = new User(userID, userName, username, userpassword);
            while (getline(inFile, itemID) && itemID != "END") {
                user->borrowItem(itemID);
            }
            library.registerUser(userID, userName, username, userpassword);
        }
    }
    inFile.close();
}

int main() {
    Library library;
    const string filename = "library.txt";
    loadLibraryFromFile(library, filename);
    int choice;
    bool loggedIn = false;

    while (true) {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "1. 用户注册" << endl;
        cout << "2. 用户登录" << endl;
        if (loggedIn) {
            cout << "3. 添加项目" << endl;
            cout << "4. 按标题查询" << endl;
            cout << "5. 按类型查询" << endl;
            cout << "6. 展示所有项目" << endl;
            cout << "7. 编辑项目" << endl;
            cout << "8. 删除项目" << endl;
            cout << "9. 按作者查询" << endl;
            cout << "10. 按光盘出品年份范围查询" << endl;
            cout << "11. 按书籍页数范围查询" << endl;
            cout << "12. 借出物品" << endl;
            cout << "13. 归还物品" << endl;
            cout << "14. 统计物品数量" << endl;
            cout << "15. 生成随机物品ID" << endl;
            cout << "16. 注销" << endl;
            cout << "17. 退出" << endl;
        }
        else {
            cout << "3. 退出" << endl;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "输入你的选择: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "无效输入.请输入一个数字." << endl;
            continue;
        }

        if (!loggedIn) {
            switch (choice) {
            case 1: {
                string userID, username, userName, password;
                cout << "输入用户ID: ";
                cin.ignore();
                getline(cin, userID);
                cout << "输入用户名: ";
                getline(cin, username);
                cout << "输入名称: ";
                getline(cin, userName);
                cout << "输入密码: ";
                getline(cin, password);
                library.registerUser(userID, userName, username, password);
                saveLibraryToFile(library, filename);
                break;
            }
            case 2: {
                string username, password;
                cout << "输入用户名: ";
                cin.ignore();
                getline(cin, username);
                cout << "输入密码: ";
                getline(cin, password);
                loggedIn = library.loginUser(username, password);
                break;
            }
            case 3:
                return 0;
            default:
                cout << "无效选择. 再试一次." << endl;
            }
        }
        else {
            switch (choice) {
            case 3: {
                string id, title, author, publisherOrProducer, isbn;
                int pages, year, duration;
                cout << "输入ID (留空以生成随机ID): ";
                cin.ignore();
                getline(cin, id);
                if (id.empty()) {
                    id = library.generateRandomID();
                }
                cout << "输入标题: ";
                getline(cin, title);
                cout << "输入作者: ";
                getline(cin, author);
                cout << "这是书(B)或者CD(C)? ";
                char type;
                cin >> type;
                if (type == 'B') {
                    cout << "输入出版社: ";
                    cin.ignore();
                    getline(cin, publisherOrProducer);
                    cout << "输入ISBN: ";
                    cin >> isbn;
                    cout << "输入页数: ";
                    cin >> pages;
                    library.addItem(new Book(id, title, author, publisherOrProducer, isbn, pages));
                }
                else if (type == 'C') {
                    cout << "输入出品者: ";
                    cin.ignore();
                    getline(cin, publisherOrProducer);
                    cout << "输入出品年份: ";
                    cin >> year;
                    cout << "输入时长: ";
                    cin >> duration;
                    library.addItem(new CD(id, title, author, publisherOrProducer, year, duration));
                }
                else {
                    cout << "无效类型." << endl;
                }
                saveLibraryToFile(library, filename);
                break;
            }
            case 4: {
                string title;
                cout << "输入标题: ";
                cin.ignore();
                getline(cin, title);
                library.queryByTitle(title);
                break;
            }
            case 5: {
                string type;
                cout << "输入类型: ";
                cin.ignore();
                getline(cin, type);
                library.queryByType(type);
                break;
            }
            case 6: {
                library.displayAllItems();
                break;
            }
            case 7: {
                string id, newTitle, newAuthor, additionalInfo;
                cout << "输入ID: ";
                cin >> id;
                cout << "输入新标题: ";
                cin.ignore();
                getline(cin, newTitle);
                cout << "输入新作者: ";
                getline(cin, newAuthor);
                cout << "输入其他信息（图书出版商、CD出品者）: ";
                getline(cin, additionalInfo);
                library.editItem(id, newTitle, newAuthor, additionalInfo);
                saveLibraryToFile(library, filename);
                break;
            }
            case 8: {
                string id;
                cout << "输入ID: ";
                cin >> id;
                library.deleteItem(id);
                saveLibraryToFile(library, filename);
                break;
            }
            case 9: {
                string author;
                cout << "输入作者: ";
                cin.ignore();
                getline(cin, author);
                library.queryByAuthor(author);
                break;
            }
            case 10: {
                int startYear, endYear;
                cout << "输入起始年份: ";
                cin >> startYear;
                cout << "输入结束年份: ";
                cin >> endYear;
                library.queryCDByYearRange(startYear, endYear);
                break;
            }
            case 11: {
                int startPage, endPage;
                cout << "输入起始页数: ";
                cin >> startPage;
                cout << "输入结束页数: ";
                cin >> endPage;
                library.queryBookByPageRange(startPage, endPage);
                break;
            }
            case 12: {
                string userID, itemID;
                cout << "输入用户ID: ";
                cin >> userID;
                cout << "输入物品ID: ";
                cin >> itemID;
                library.lendItem(userID, itemID);
                saveLibraryToFile(library, filename);
                break;
            }
            case 13: {
                string userID, itemID;
                cout << "输入用户ID: ";
                cin >> userID;
                cout << "输入物品ID: ";
                cin >> itemID;
                library.returnItem(userID, itemID);
                saveLibraryToFile(library, filename);
                break;
            }
            case 14: {
                library.countItems();
                break;
            }
            case 15: {
                cout << "生成的随机ID: " << library.generateRandomID() << endl;
                break;
            }
            case 16: {
                library.logoutUser();
                loggedIn = false;
                break;
            }
            case 17:
                saveLibraryToFile(library, filename);
                return 0;
            default:
                cout << "无效选择. 再试一次." << endl;
            }
        }
    }
    return 0;
}