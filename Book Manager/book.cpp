#include <iostream>
#include "book.h"
Book::Book(
    const std::string& newTitle,
    const std::string& newId,
    const std::string& newAuthor,
    BorrowStatus newStatus
):
title(newTitle),id(newId),author(newAuthor),status(newStatus)
{

}
const std::string& Book::getId() const
{
    return id;
}
const std::string& Book::getTitle() const
{
    return title;
}
BorrowStatus Book::getStatus() const
{
    return status;
}
bool Book::borrow()
{
    if(status == BorrowStatus::Borrowed)
    {
        std::cout << "未能成功借阅该图书\n";
        return false;
    }
    else
    {
        std::cout << "已成功借阅该图书\n";
        status = BorrowStatus::Borrowed;
        return true;
    }
}
void Book::showInfo() const
{
    std::cout << "书名:" << title << "\n";
    std::cout << "编号:" << id << "\n";
    std::cout << "作者:" << author << "\n";
    std::cout << "是否借出:" ;
    if(status == BorrowStatus::Borrowed)
    {
        std::cout << "已借出\n";
    }
    else
    {
        std::cout << "未借出\n";
    }
    std::cout << "====================\n";
}
const std::string& Book::getAuthor() const
{
    return author;
}
bool Book::returnBook()
{
    if(status == BorrowStatus::Available)
    {
        std::cout << "该图书未借出\n";
        return false;
    }
    else
    {
        std::cout << "已成功归还该图书\n";
        status = BorrowStatus::Available;
        return true;
    }
}
