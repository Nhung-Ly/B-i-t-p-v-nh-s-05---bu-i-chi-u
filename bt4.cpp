#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Borrowable {
public:
    virtual void borrow() = 0;
    virtual void returnItem() = 0;
    virtual bool isAvailable() const = 0;
    virtual std::string getTitle() const = 0;
    virtual ~Borrowable() = default;
};

class Book : public Borrowable {
private:
    std::string title;
    std::string author;
    std::string ISBN;
    bool available;
public:
    Book(std::string t, std::string a, std::string i)
        : title(std::move(t)), author(std::move(a)), ISBN(std::move(i)),
          available(true) {}

    void borrow() override {
        if (available) {
            available = false;
            std::cout << "Sách '" << title << "' đã được mượn." << std::endl;
        } else {
            std::cout << "Sách '" << title << "' không có sẵn để mượn." << std::endl;
        }
    }

    void returnItem() override {
        available = true;
        std::cout << "Sách '" << title << "' đã được trả lại." << std::endl;
    }

    bool isAvailable() const override {
        return available;
    }

    std::string getTitle() const override {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    std::string getISBN() const {
        return ISBN;
    }
};

class DVD : public Borrowable {
private:
    std::string title;
    std::string director;
    int duration;  
    bool available;
public:
    DVD(std::string t, std::string d, int dur)
        : title(std::move(t)), director(std::move(d)), duration(dur),
          available(true) {}

    void borrow() override {
        if (available) {
            available = false;
            std::cout << "DVD '" << title << "' đã được mượn." << std::endl;
        } else {
            std::cout << "DVD '" << title << "' không có sẵn để mượn." << std::endl;
        }
    }

    void returnItem() override {
        available = true;
        std::cout << "DVD '" << title << "' đã được trả lại." << std::endl;
    }

    bool isAvailable() const override {
        return available;
    }

    std::string getTitle() const override {
        return title;
    }

    std::string getDirector() const {
        return director;
    }

    int getDuration() const {
        return duration;
    }
};

class Library {
private:
    std::vector<std::unique_ptr<Borrowable>> items; 
public:
    void addItem(std::unique_ptr<Borrowable> item) {
        items.push_back(std::move(item));
    }

    void borrowItem(const std::string& title) {
        auto it = std::find_if(items.begin(), items.end(), [&title](const auto& item) {
            return item->getTitle() == title;
        });

        if (it != items.end()) {
            if ((*it)->isAvailable()) {
                (*it)->borrow();
            } else {
                std::cout << "Mục '" << title << "' hiện không có sẵn." << std::endl;
            }
        } else {
            std::cout << "Không tìm thấy mục '" << title << "' trong thư viện." << std::endl;
        }
    }

    void returnItem(const std::string& title) {
        auto it = std::find_if(items.begin(), items.end(), [&title](const auto& item) {
            return item->getTitle() == title;
        });

        if (it != items.end()) {
            if (!(*it)->isAvailable()) {
                (*it)->returnItem();
            } else {
                std::cout << "Mục '" << title << "' đã có sẵn trong thư viện." << std::endl;
            }
        } else {
            std::cout << "Không tìm thấy mục '" << title << "' trong thư viện." << std::endl;
        }
    }
};

int main() {
    Library library;

    library.addItem(std::make_unique<Book>("Lập Trình C++", "Nguyễn Văn A", "123456789"));
    library.addItem(std::make_unique<DVD>("Phim Khoa Học", "Đạo Diễn B", 120));

    library.borrowItem("Lập Trình C++");
    library.borrowItem("Phim Khoa Học");

    library.borrowItem("Lập Trình C++");

    library.returnItem("Lập Trình C++");
    library.returnItem("Phim Khoa Học");

    
    library.returnItem("Phim Khoa Học");

    return 0;
}
