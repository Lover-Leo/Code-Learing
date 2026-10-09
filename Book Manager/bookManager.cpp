#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "book.h"
#define NOMINMAX
#include <windows.h>
#include<fstream>
#include<algorithm>
#include <cstddef>
void addBook(std::vector<Book>& books)
{
    std::string newId;
    std::string newTitle;
    std::string newAuthor;
    BorrowStatus newStatus = BorrowStatus::Available;
    std::cout << "编号:";
    std::getline(std::cin,newId);
    if(newId.empty())
    {
        std::cout << "图书编号不能为空";
        return;
    }
    for(const auto& bo:books)
    {
        if(newId == bo.getId())
        {
            std::cout << "您的图书编号与其他图书编号重复\n";
            return;
        }
    }
    std::cout << "书名:";
    std::getline(std::cin,newTitle);
    if(newTitle.empty())
    {
        std::cout << "书名不能为空";
        return;
    }
    std::cout << "作者:";
    std::getline(std::cin,newAuthor);
    if(newAuthor.empty())
    {
        std::cout << "作者不能为空";
        return;
    }
    books.emplace_back(newTitle,newId,newAuthor,newStatus);
}
void showBooks(const std::vector<Book>& books)
{
    if(books.empty())
    {
        std::cout << "系统内没有添加图书\n";
        return;
    }
    for(const auto& bo: books)
    {
        bo.showInfo();
    }
}
Book* findBook(
    std::vector<Book>& books,
    const std::string& targetId
)
{
    auto result = std::find_if(
        books.begin(),
        books.end(),
        [&targetId](const Book& bo)
        {
            return bo.getId() == targetId;
        }
    );
    if(result == books.end())
    {
        return nullptr;
    }
    return &(*result);
}
void searchBook(std::vector<Book>& books)
{
    if(books.empty())
    {
        std::cout << "您的系统内没有图书\n";
        return;
    }
    std::string targetId;
    std::cout << "请输入您要查找的图书编号:";
    std::getline(std::cin,targetId);
    const Book* result = findBook(books,targetId);
    if(result == nullptr)
    {
        std::cout << "图书系统内没有该图书\n";
        return;
    }
    else
    {
        result -> showInfo();
    }
}

void borrowBook(std::vector<Book>& books)
{
    if(books.empty())
    {
        std::cout << "系统内没有图书\n";
        return;
    }
    std::string targetId;
    std::cout << "请输入图书编号:";
    std::getline(std::cin,targetId);
    Book* result;
    result = findBook(books,targetId);
    if(result == nullptr)
    {
        std::cout << "没有找到该图书\n";
        return;
    }
    else
    {
        result -> borrow();
        return;
    }

}
void returnBook(std::vector<Book>& books)
{
    if(books.empty())
    {
        std::cout << "系统内没有图书\n";
        return;
    }
    std::string targetId;
    std::cout << "请输入图书编号:";
    std::getline(std::cin,targetId);
    Book* result = findBook(books,targetId);
    if(result == nullptr)
    {
        std::cout << "未能找到该图书\n";
        return;
    }
    else
    {
        result -> returnBook();
        return;
    }
}
void saveBooks(const std::vector<Book>& books)
{
    std::ofstream output("book.txt");
    if(!output)
    {
        std::cout << "文件未正常打开";
        return;
    }
    for(const auto& bo:books)
    {
        output << bo.getId() << '\n';
        output << bo.getTitle() << '\n';
        output << bo.getAuthor() <<'\n';
        output << static_cast<int>(bo.getStatus()) << '\n';
    }
}
void loadBooks(std::vector<Book>& books)
{
    std::ifstream input("book.txt");
    std::string id;
    std::string title;
    std::string author;
    std::string statusText;
    BorrowStatus status;
    while(getline(input,id))
    {
        if(
            !getline(input,title)||
            !getline(input,author)||
            !getline(input,statusText)
        )
        {
            std::cout << "图书信息不完整\n";
            return;
        }
        if(statusText == "0")
        {
            status = BorrowStatus::Available;
        }
        else if(statusText == "1")
        {
            status = BorrowStatus::Borrowed;
        }
        else
        {
            std::cout << "借阅状态无效\n";
            continue;
        }
        books.emplace_back(title,id,author,status);
    }
}
void sortBooksByTitle(std::vector<Book>& books)
{
    if(books.empty())
    {
        std::cout << "系统内没有图书\n";
        return;
    }
    std::sort(
        books.begin(),
        books.end(),
        [](const Book& left,const Book& right)
        {
            return left.getTitle() < right.getTitle();
        }
    );
    std::cout << "已按照书名排序\n";
}
void sortBooksById(std::vector<Book>& books)
{
    if(books.empty())
    {
        std::cout << "系统内没有图书\n";
        return;
    }
    std::sort(
        books.begin(),
        books.end(),
        [](const Book& left,const Book& right)
        {
            return left.getId() < right.getId();
        }
    );
    std::cout << "已按照图书编号排序\n";
}
void countBooks(const std::vector<Book>& books)
{
    std::size_t allCount = books.size();
    auto borrowedCount = std::count_if(
        books.begin(),
        books.end(),
        [](const Book& bo)
        {
            return bo.getStatus() == BorrowStatus::Borrowed;
        }
    );
    std::size_t availableCount = allCount - borrowedCount;
    std::cout << "图书总量:" << allCount << '\n';
    std::cout << "已借出:" << borrowedCount << '\n';
    std::cout << "未借出:" << availableCount << '\n';
}
void deleteBook(std::vector<Book>& books)
{
    if(books.empty())
    {
        std::cout << "系统内没有图书\n";
        return;
    }
    std::string deleteId;
    std::cout << "请输入要删除的图书编号:";
    std::getline(std::cin,deleteId);
    auto newEnd = std::remove_if(
        books.begin(),
        books.end(),
        [deleteId](const Book& bo)
        {
           return bo.getId() == deleteId;
        }
    );
    if(newEnd == books.end())
    {
        std::cout << "没有找到该图书\n";
        return;
    }
    books.erase(newEnd,books.end());
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::vector<Book> books;
    loadBooks(books);
    int choice = -1;
    do
    {
        std::cout << "====图书馆管理系统====\n";
        std::cout << "1.添加图书\n";
        std::cout << "2.显示全部图书\n";
        std::cout << "3.根据编号查找图书\n";
        std::cout << "4.根据编号借出图书\n";
        std::cout << "5.根据编号归还图书\n";
        std::cout << "6.根据书名排序\n";
        std::cout << "7.根据图书编号排序\n";
        std::cout << "8.统计所有图书\n";
        std::cout << "9.删除图书\n";
        std::cout << "0.退出系统\n";
        if(!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
            std::cout << "请输入正确的选择\n";
            choice = -1;
            continue;
        }
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
        switch(choice)
        {
            case 1:
                addBook(books);
                break;
            case 2:
                showBooks(books);
                break;
            case 3:
                searchBook(books);
                break;
            case 4:
                borrowBook(books);
                break;
            case 5:
                returnBook(books);
                break;
            case 6:
                sortBooksByTitle(books);
                break;
            case 7:
                sortBooksById(books);
                break;
            case 8:
                countBooks(books);
                break;
            case 9:
                deleteBook(books);
                break;
            case 0:
                std::cout << "您已成功退出系统\n";
                saveBooks(books);
                break;
            default:
                std::cout << "无效输入\n";
                break;
        }
    }while(choice != 0);
    return 0;
}
