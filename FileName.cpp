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

// ���� Media ��ʾͼ����е���Ʒ
class Media {
protected:
    string id;       // ��ƷID
    string title;    // ��Ʒ����
    string author;   // ��Ʒ����
    bool isBorrowed;  // ��Ʒ�Ƿ񱻽��
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

// ������ Book ��ʾͼ��
class Book : public Media {
private:
    string publisher;  // ������
    string isbn;       // ISBN���
    int pages;         // ҳ��
public:
    Book(const string& id, const string& title, const string& author, const string& publisher, const string& isbn, int pages) :
        Media(id, title, author), publisher(publisher), isbn(isbn), pages(pages) {}

    void display() const override {
        cout << "����: Book, ID: " << id << ", ����: " << title << ", ����: " << author << ", ������: " << publisher << ", ISBN: " << isbn << ", ҳ��: " << pages << ", ���״̬: " << (isBorrowed ? "�ѽ��" : "δ���") << endl;
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

// ������ CD ��ʾ����
class CD : public Media {
private:
    string producer;  // ������
    int year;         // �������
    int duration;     // ʱ������λ�����ӣ�
public:
    CD(const string& id, const string& title, const string& author, const string& producer, int year, int duration) :
        Media(id, title, author), producer(producer), year(year), duration(duration) {}

    void display() const override {
        cout << "����: CD, ID: " << id << ", ����: " << title << ", ����: " << author << ", ��Ʒ��: " << producer << ", ��Ʒ���: " << year << ", ʱ��: " << duration << ", ���״̬: " << (isBorrowed ? "�ѽ��" : "δ���") << endl;
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

// �û���
class User {
private:
    string id;
    string name;
    string username;
    string password;
    vector<string> borrowedItems;  // �洢�������ƷID
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
        cout << "�û�ID: " << id << ", �û���: " << name << ", �����Ʒ����: " << borrowedItems.size() << endl;
    }
};

// ͼ����࣬����ͼ����е���Ʒ���鼮�͹��̣�
class Library {
private:
    vector<Media*> items;  // �洢��Ʒ������
    vector<User*> users;   // �洢�û�������
    const int MAX_ITEMS = 100;  // ͼ�����Ʒ���������
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
            cout << "�޷����, ��������." << endl;
            return;
        }
        for (Media* existingItem : items) {
            if (existingItem->getID() == item->getID()) {
                cout << "�ظ����ݣ����ȡ��." << endl;
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
            cout << "û�иñ������Ŀ!" << endl;
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
            cout << "�������û����Ŀ!" << endl;
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
        cout << "���ID������." << endl;
    }

    void deleteItem(const string& id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getID() == id) {
                delete* it;
                items.erase(it);
                return;
            }
        }
        cout << "���ID������." << endl;
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
            cout << "û�и����ߵ���Ŀ!" << endl;
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
            cout << "����ݷ�Χ��û�й�����Ŀ!" << endl;
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
            cout << "��ҳ����Χ��û���鼮��Ŀ!" << endl;
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
                cout << "��Ʒ�ѽ��: ";
                item->display();
            }
            else {
                cout << "��Ʒ�ѱ����." << endl;
            }
        }
        else {
            cout << "�û�����ƷID������." << endl;
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
                cout << "��Ʒ�ѹ黹: ";
                item->display();
            }
            else {
                cout << "��Ʒδ�����." << endl;
            }
        }
        else {
            cout << "�û�����ƷID������." << endl;
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
        cout << "�鼮����: " << bookCount << ", ��������: " << cdCount << endl;
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
                cout << "�û����Ѵ���." << endl;
                return;
            }
        }
        users.push_back(new User(id, name, username, password));
        cout << "�û���ע��: �û��� = " << username << ", ���� = " << name << endl;
    }

    bool loginUser(const string& username, const string& password) {
        for (User* user : users) {
            if (user->getUsername() == username && user->validatePassword(password)) {
                currentUser = user;
                cout << "��¼�ɹ�, ��ӭ " << user->getName() << "!" << endl;
                return true;
            }
        }
        cout << "�û������������." << endl;
        return false;
    }

    void logoutUser() {
        currentUser = nullptr;
        cout << "��ע��." << endl;
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
        cerr << "�޷����ļ�����д��: " << filename << endl;
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
        cerr << "�޷����ļ����ж�ȡ: " << filename << endl;
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
        cout << "1. �û�ע��" << endl;
        cout << "2. �û���¼" << endl;
        if (loggedIn) {
            cout << "3. �����Ŀ" << endl;
            cout << "4. �������ѯ" << endl;
            cout << "5. �����Ͳ�ѯ" << endl;
            cout << "6. չʾ������Ŀ" << endl;
            cout << "7. �༭��Ŀ" << endl;
            cout << "8. ɾ����Ŀ" << endl;
            cout << "9. �����߲�ѯ" << endl;
            cout << "10. �����̳�Ʒ��ݷ�Χ��ѯ" << endl;
            cout << "11. ���鼮ҳ����Χ��ѯ" << endl;
            cout << "12. �����Ʒ" << endl;
            cout << "13. �黹��Ʒ" << endl;
            cout << "14. ͳ����Ʒ����" << endl;
            cout << "15. ���������ƷID" << endl;
            cout << "16. ע��" << endl;
            cout << "17. �˳�" << endl;
        }
        else {
            cout << "3. �˳�" << endl;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "�������ѡ��: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "��Ч����.������һ������." << endl;
            continue;
        }

        if (!loggedIn) {
            switch (choice) {
            case 1: {
                string userID, username, userName, password;
                cout << "�����û�ID: ";
                cin.ignore();
                getline(cin, userID);
                cout << "�����û���: ";
                getline(cin, username);
                cout << "��������: ";
                getline(cin, userName);
                cout << "��������: ";
                getline(cin, password);
                library.registerUser(userID, userName, username, password);
                saveLibraryToFile(library, filename);
                break;
            }
            case 2: {
                string username, password;
                cout << "�����û���: ";
                cin.ignore();
                getline(cin, username);
                cout << "��������: ";
                getline(cin, password);
                loggedIn = library.loginUser(username, password);
                break;
            }
            case 3:
                return 0;
            default:
                cout << "��Чѡ��. ����һ��." << endl;
            }
        }
        else {
            switch (choice) {
            case 3: {
                string id, title, author, publisherOrProducer, isbn;
                int pages, year, duration;
                cout << "����ID (�������������ID): ";
                cin.ignore();
                getline(cin, id);
                if (id.empty()) {
                    id = library.generateRandomID();
                }
                cout << "�������: ";
                getline(cin, title);
                cout << "��������: ";
                getline(cin, author);
                cout << "������(B)����CD(C)? ";
                char type;
                cin >> type;
                if (type == 'B') {
                    cout << "���������: ";
                    cin.ignore();
                    getline(cin, publisherOrProducer);
                    cout << "����ISBN: ";
                    cin >> isbn;
                    cout << "����ҳ��: ";
                    cin >> pages;
                    library.addItem(new Book(id, title, author, publisherOrProducer, isbn, pages));
                }
                else if (type == 'C') {
                    cout << "�����Ʒ��: ";
                    cin.ignore();
                    getline(cin, publisherOrProducer);
                    cout << "�����Ʒ���: ";
                    cin >> year;
                    cout << "����ʱ��: ";
                    cin >> duration;
                    library.addItem(new CD(id, title, author, publisherOrProducer, year, duration));
                }
                else {
                    cout << "��Ч����." << endl;
                }
                saveLibraryToFile(library, filename);
                break;
            }
            case 4: {
                string title;
                cout << "�������: ";
                cin.ignore();
                getline(cin, title);
                library.queryByTitle(title);
                break;
            }
            case 5: {
                string type;
                cout << "��������: ";
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
                cout << "����ID: ";
                cin >> id;
                cout << "�����±���: ";
                cin.ignore();
                getline(cin, newTitle);
                cout << "����������: ";
                getline(cin, newAuthor);
                cout << "����������Ϣ��ͼ������̡�CD��Ʒ�ߣ�: ";
                getline(cin, additionalInfo);
                library.editItem(id, newTitle, newAuthor, additionalInfo);
                saveLibraryToFile(library, filename);
                break;
            }
            case 8: {
                string id;
                cout << "����ID: ";
                cin >> id;
                library.deleteItem(id);
                saveLibraryToFile(library, filename);
                break;
            }
            case 9: {
                string author;
                cout << "��������: ";
                cin.ignore();
                getline(cin, author);
                library.queryByAuthor(author);
                break;
            }
            case 10: {
                int startYear, endYear;
                cout << "������ʼ���: ";
                cin >> startYear;
                cout << "����������: ";
                cin >> endYear;
                library.queryCDByYearRange(startYear, endYear);
                break;
            }
            case 11: {
                int startPage, endPage;
                cout << "������ʼҳ��: ";
                cin >> startPage;
                cout << "�������ҳ��: ";
                cin >> endPage;
                library.queryBookByPageRange(startPage, endPage);
                break;
            }
            case 12: {
                string userID, itemID;
                cout << "�����û�ID: ";
                cin >> userID;
                cout << "������ƷID: ";
                cin >> itemID;
                library.lendItem(userID, itemID);
                saveLibraryToFile(library, filename);
                break;
            }
            case 13: {
                string userID, itemID;
                cout << "�����û�ID: ";
                cin >> userID;
                cout << "������ƷID: ";
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
                cout << "���ɵ����ID: " << library.generateRandomID() << endl;
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
                cout << "��Чѡ��. ����һ��." << endl;
            }
        }
    }
    return 0;
}