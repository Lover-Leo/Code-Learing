#pragma once
#include<string>
enum class BorrowStatus
{
    Available = 0,
    Borrowed = 1
};
class Book
{
    private:
        std::string id;
        std::string title;
        std::string author;
        BorrowStatus status;
    public:
        Book(
            const std::string& newTitle,
            const std::string& newId,
            const std::string& newAuthor,
            BorrowStatus newStatus);
        const std::string& getId() const;
        const std::string& getTitle() const;
        const std::string& getAuthor() const;
        BorrowStatus getStatus() const;
        void showInfo() const;
        bool borrow();
        bool returnBook();
};
