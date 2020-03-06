
#include <iostream>
#include <queue>
#include <string>

enum COLOR
{
	RED,
	BLACK
};

class Person
{
public:
	COLOR Color;
    std::string m_fname;
    std::string m_lname;
    std::string m_phoneNumber;

	Person* right;
	Person* left;
	Person* parent;


	Person();
	Person* newPerson(std::string m_fname, std::string m_lname, std::string m_phoneNumber);
	Person* uncle();
	Person* sibling();
	bool  leftCheck();
	bool  redChildCheck();
	void  moveDown(Person* ptr);
	~Person();

	std::vector<std::string> Output;
};

class Book
{
private:
	Person* m_root;
	int   m_size;


	void  rotateLeft(Person* ptr);
	void  rotateRight(Person* ptr);
	void  swapColor(Person* P1, Person* P2);
	void  swapKeys(Person* u, Person* v);

    std::vector<std::string> inorder(Person* ptr);

public:
	Book();

    // ------------------------------------------------------ //
    // ------------------- Main Functions ------------------- //
    // ------------------------------------------------------ //
	void  AddPerson            (std::string fname, std::string lname, std::string phoneNumber);
    bool  DeletePhoneNumber(std::string fname, std::string lname);
		Person* FindPhoneNumber  (std::string fname, std::string lname, Person* ptr);
    Person* ChangePhoneNumber(std::string fname, std::string lname);
    void  Display          (                                    );
    void  Quit             (                                    );

	void  EmptyTree(Person* ptr);

    // ------------------------------------------------------ //
	// ------------------ Helper Functions ------------------ //
    // ------------------------------------------------------ //
    int   GetSize();
		Person* find(std::string m_fname, std::string m_lname, Person* ptr);
	std::vector<std::string> inorder_Helper(Person* ptr, std::vector<std::string> arr);

	Person* newPerson(std::string m_fname, std::string m_lname, std::string m_phoneNumber);
	Person* GetHead() { return m_root; };
	//int   GetKey(Person* ptr) { return ptr->key.value(); };

	void  fixRedRed(Person* ptr);
	void  fixBlackBlack(Person* ptr);

	~Book();
};

class UserInterface
{
public:
    int   GetSelection();
};
