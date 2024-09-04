#include<iostream>
#include<vector>

int book_id = 1;

class Book{
    private:
        std::string book_name;
        std::string author_name;
        int id;
    public:
        Book() = default;
        Book(const std::string& name, const std::string& author){
            book_name = name;
            author_name = author;
            id = book_id++;
        }
        std::string get_book_name(){
            return book_name;           
        }
        void set_book_name(const std::string& title){
            book_name = title;
        }
        std::string get_author_name(){
            return author_name;
        }
        void set_author_name(const std::string& author){
            author_name = author;
        }
        int get_id(){
            return id;
        }
        void set_id(int n_id){
            id = n_id;
        }
};

class Library_manager{
    private:
        std::vector<Book> books;
    public:
        void delete_book(){
            list_books();

            int id;
            std::cout << "These are all the books that are currently available in the library.\n Please specify the appropriate id to delete the book:"<<std::endl;

            do{
                std::cin >> id;

            }while(id > 0 && id < books.size());

            books.erase(books.begin() + id);
        }

        void add_book(const Book book){
            books.push_back(book);
        }

        void list_books(){
            std::cout << "-----------------------------------------" << std::endl;

            std::cout<<"Now the following books are available in the library"<<std::endl;
            std::cout << "-----------------------------------------" << std::endl<<std::endl;
            for(int i = 0; i < books.size(); i++){
                std::cout << "Book by id " << books[i].get_id()<< std::endl <<"Book title: "<<books[i].get_book_name()<<std::endl<<"Author Name: "<<books[i].get_author_name()<<std::endl<<std::endl;
            }
        }

        Book* find_book_by_title(const std::string& title){
            for(int i = 0; i < books.size(); i++){
                if(title == books[i].get_book_name()){
                    return &(books[i]);
                }
            }
            return nullptr;
        }

        Book* find_book_by_id(int book_id){
            for(int i = 0; i < books.size(); i++){
                if(book_id == books[i].get_id();i++){
                    return &(books[i]);
                }
            }
            return nullptr;
        }

        Book* find_book_by_name(const std::string name){
            for(int i = 0; i < books.size(); i++){
                if(name == (books[i].get_author_name());i++){
                    return &(books[i]);
                }
            }
            return nullptr;
        }

};


void add_book(Library_manager& lib){  
    Book book;

    std::string tmp;
    std::cout<<"Please enter a book title: ";
    std::getline(std::cin, tmp);
    book.set_book_name(tmp);
    std::cout << "Please enter author name: ";
    std::getline(std::cin, tmp);

    book.set_author_name(tmp);
    book.set_id(book_id++);
    lib.add_book(book);

    std::cout << "-----------------------------------------"<< std::endl;

}


void active(Library_manager& lib, int action_num){
    std::string tmp;
    int n = 0;
    switch(action_num){
        case 1:
            add_book(lib);
            break;
        case 2:
            lib.list_books();
            break;
        case 3:
            std::cout << "Finde by "<<std::endl<< "1: Name" <<std::endl << "2: Author"<<std::endl<<"3: Id"<<std::endl;
            std::cin >> n;
            if(n == 1){ 
                std::cout << "Enter book title: ";
                std::getline(std::cin, tmp);
                lib.find_book_by_title(tmp);
            }
            else if(n == 2){
                std::cout << "Enter author name: ";
                std::getline(std::cin, tmp);
                lib.find_book_by_name(tmp);
            }else if(n == 3){
                int n = 0;
                std::cout << "Enter book id: ";
                std::cin >> n;
                lib.find_book_by_id(n);
            }
            break;
        case 4:
            lib.delete_book();
            break;
    }
}

void actions(Library_manager& lib){
    int actions_id;
    do{
        std::cout << "Here are the features you can use" << std::endl;
        std::cout << "1: Add Book"<< std::endl << "2։ Print all books" << std::endl << "3։ Find a book" <<std::endl<<"4։ Delete book"<<std::endl<<"-1: Exit"<<std::endl;
        std::cout << "Please enter the appropriate action id" << std::endl;
        std::cin >> actions_id;

        if(actions_id > 0 && actions_id < 5){
            active(lib,actions_id);
        }
        std::cout << "-----------------------------------------"<< std::endl;

    }while(actions_id != -1);

}

int main(){
    Library_manager library;

    std::cout << "Welcome to the Half-Blood Prince, the great library"<<std::endl;
    std::cout<<"Only add book is available in the library now, please add which book to continue"<<std::endl;
    std::cout << "-----------------------------------------"<< std::endl; 

    add_book(library);

    std::cout << "Thank you"<<std::endl;
    std::cout << "-----------------------------------------"<< std::endl; 
    actions(library);
}
