Sure, here's a README for your library management system:

# Library Management System

This is a simple library management system implemented in C++. It allows users to manage books and CDs, perform various queries, and manage user accounts. The system supports functionalities such as adding, editing, deleting items, borrowing, and returning items.

## Features

- **User Registration and Login**: Users can register and log in to the system.
- **Add Items**: Add new books or CDs to the library.
- **Query Items**: Query items by title, type, author, year range (for CDs), and page range (for books).
- **Display All Items**: Display all items in the library.
- **Edit Items**: Edit the details of existing items.
- **Delete Items**: Delete items from the library.
- **Borrow/Return Items**: Borrow and return items.
- **Count Items**: Count the number of books and CDs in the library.
- **Generate Random ID**: Generate a random ID for new items.
- **Save/Load Library Data**: Save the library data to a file and load it from the file.

## Classes

### Media
- **Attributes**: `id`, `title`, `author`, `isBorrowed`
- **Methods**: `display()`, `edit()`, `borrow()`, `returnItem()`

### Book (Inherits from Media)
- **Attributes**: `publisher`, `isbn`, `pages`
- **Methods**: `display()`, `edit()`

### CD (Inherits from Media)
- **Attributes**: `producer`, `year`, `duration`
- **Methods**: `display()`, `edit()`

### User
- **Attributes**: `id`, `name`, `username`, `password`, `borrowedItems`
- **Methods**: `borrowItem()`, `returnItem()`, `display()`

### Library
- **Attributes**: `items`, `users`, `MAX_ITEMS`, `currentUser`
- **Methods**: `addItem()`, `queryByTitle()`, `queryByType()`, `displayAllItems()`, `editItem()`, `deleteItem()`, `queryByAuthor()`, `queryCDByYearRange()`, `queryBookByPageRange()`, `lendItem()`, `returnItem()`, `countItems()`, `generateRandomID()`, `registerUser()`, `loginUser()`, `logoutUser()`, `getCurrentUser()`, `getItems()`, `getUsers()`

### File Operations
- **saveLibraryToFile()**: Save the library data to a file.
- **loadLibraryFromFile()**: Load the library data from a file.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- Standard C++ libraries

### Compilation

To compile the program, use the following command:
```sh
g++ -o library_management_system main.cpp
```

### Running the Program

To run the program, use the following command:
```sh
./library_management_system
```

## Usage

1. **Register a User**: Register a new user by providing a user ID, username, name, and password.
2. **Login**: Login with a registered username and password.
3. **Add Items**: Add new books or CDs by providing the necessary details.
4. **Query Items**: Query items by title, type, author, year range, or page range.
5. **Display All Items**: Display all items in the library.
6. **Edit Items**: Edit the details of existing items by providing the item ID and new details.
7. **Delete Items**: Delete items by providing the item ID.
8. **Borrow/Return Items**: Borrow or return items by providing the user ID and item ID.
9. **Count Items**: Count the number of books and CDs in the library.
10. **Generate Random ID**: Generate a random ID for new items.
11. **Save/Load Library Data**: Save the library data to a file and load it from the file.

## Example Usage

```sh
1. 用户注册
2. 用户登录
3. 退出
```

After logging in:

```sh
3. 添加项目
4. 按标题查询
5. 按类型查询
6. 展示所有项目
7. 编辑项目
8. 删除项目
9. 按作者查询
10. 按光盘出品年份范围查询
11. 按书籍页数范围查询
12. 借出物品
13. 归还物品
14. 统计物品数量
15. 生成随机物品ID
16. 注销
17. 退出
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This project was developed as a simple example of a library management system in C++.
- Feel free to contribute, report issues, or suggest features!

---

Feel free to modify this README as needed for your specific use case or additional features you may add in the future.
