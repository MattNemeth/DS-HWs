//
// EECE 4040 - Data Structures and Algorithms [Kenneth Berman]
// Developed by: Joshua Musch, Matt Nemeth and Michael Hallbrin
//
// Functions implemented in this phone book:
// Implementing an elctronic phone book with a red-black tree
//    * Add():     Adds a persons name (first and last) and
//                 there phone number to the phone book
//    * Delete():  Deletes a given person's phone number
//                   - Given only the persons name
//    * Find():    Locates a person's phone number
//                   - Given the person's Name
//    * Change():  Changes a person's phone number
//                   - Given the person's phone number
//                     & new phone number
//    * Display(): Displays entire phone book in alpha order
//    * Quit():    Save the phone book to a text file and
//                 quit the application.
//

#include "Hw3.h"
#include <vector>

// ------------------ Person Class ------------------ //
Person::Person()
{
    // Constructor
    Color = RED;
}
Person* Person::newPerson(std::string fname, std::string lname, std::string phonenumber)
{
    // Create Pointer
    Person * n = new Person;
    n->m_fname = fname;
    n->m_lname = lname;
    n->m_phoneNumber = phonenumber;
    n->left  = NULL;
    n->right = NULL;
    return n;
}
Person* Person::uncle()
{
    // Returns the Uncle Node Pointer
    if (parent == NULL || parent->parent == NULL)
        return NULL;
    if (parent->leftCheck())
        return parent->parent->right;
    else
        return parent->parent->left;
}
Person* Person::sibling()
{
    // Returns the Siblings Node Pointer
    if (parent == NULL)
        return NULL;
    else if (leftCheck())
        return parent->right;
    else
        return parent->left;
}
bool  Person::leftCheck()
{
    return this == parent->left;
}
bool  Person::redChildCheck()
{
    // Checks the color of the children of the node
    if (left != NULL && left->Color == RED)
        return true;
    else if (right != NULL && right->Color == RED)
        return true;
    else
        return false;
}
void  Person::moveDown(Person* ptr)
{
    // Move the Node downwards
    if (parent != NULL)
    {
        if (leftCheck())
            parent->left = ptr;
        else
            parent->right = ptr;

        ptr->parent = parent;
        parent = ptr;
    }
}
Person::~Person()
{
    // Destructor
    delete left;
    delete right;
    delete parent;
}

// ------------------ Book Class ------------------ //
Book::Book()
{
    m_root = NULL;
    m_size = 0;
}

void  Book::AddPerson(std::string m_fname, std::string m_lname, std::string m_phoneNumber)
{
    Person* newperson = newPerson(m_fname, m_lname, m_phoneNumber);
    std::string fullName = m_fname + ' ' + m_lname;
    if (m_size == 0)
    {
        newperson->Color = BLACK;
        m_root = newperson;
        m_size++;
        return;
    }
    else
    {
        //Person *temp = FindPhoneNumber(newperson->m_fname, newperson->m_lname, m_root);
        Person* currPerson = m_root;
        std::string fullName = newperson->m_fname + ' ' + newperson->m_lname;

        while (currPerson != nullptr)
        {
            if (currPerson->left == nullptr && fullName.compare(currPerson->m_lname + " " + currPerson->m_fname) < 0)
            {
                currPerson->left = newperson;
                return;
            }
            else if (currPerson->right == nullptr && fullName.compare(currPerson->m_lname + " " + currPerson->m_fname) > 0)
            {
                currPerson->right = newperson;
                return;
            }
            else if (fullName.compare(currPerson->m_lname + " " + currPerson->m_fname) > 0)
            {
                return;
            }
            else if (fullName.compare(currPerson->m_fname + ' ' + currPerson->m_lname) < 0)
            {
                currPerson = currPerson->left;
            }
            else
            {
                currPerson = currPerson->right;
            }
        }
      /*  if ((newperson->m_fname + ' ' + newperson->m_lname).compare(fullName) == 0)
        {
            return;
        }

        newperson->parent = temp;

        if ((newperson->m_fname + ' ' + newperson->m_lname).compare(temp->m_fname + ' ' + temp->m_lname) < 0)
        {
            temp->left  = newperson;
            m_size++;
        }
        else
        {
            temp->right = newperson;
            m_size++;
        }*/

        fixRedRed(newperson);
    }
    return;
}

Person* Book::FindPhoneNumber(std::string m_fname, std::string m_lname, Person* ptr)
{
    std::string fullName = m_fname + ' ' + m_lname;

    if(ptr == nullptr)
    {
        return nullptr;
    }
    else if((ptr->m_fname + ' ' + ptr->m_lname).compare(fullName) == 0)
    {
        return ptr;
    }
    else if((ptr->m_fname + ' ' + ptr->m_lname).compare(fullName) < 0)
    {
        return FindPhoneNumber(m_fname, m_lname, ptr->right);
    }
    else if((ptr->m_fname + ' ' + ptr->m_lname).compare(fullName) > 0)
    {
        return FindPhoneNumber(m_fname, m_lname, ptr->left);
    }
}

int   Book::GetSize()
{
    return m_size;
}
std::vector<std::string> Book::inorder(Person* ptr)
{
    std::vector<std::string> arr;
    return inorder_Helper(ptr, arr);
}
std::vector<std::string> Book::inorder_Helper(Person* ptr, std::vector<std::string> arr)
{
    std::string str;
    if (m_root != NULL)
    {
        if (ptr->left != NULL)
        {
            return inorder_Helper(ptr->left, arr);
        }
        str = ptr->m_fname + " " + ptr->m_lname + "\t" + ptr->m_phoneNumber;
        arr.push_back(str);
        if (ptr->right != NULL)
        {
            return inorder_Helper(ptr->right, arr);
        }
        return arr;
    }
    else
    {
        arr.push_back("NULL");
        std::cout << "The tree is Empty." << std::endl;
        return arr;
    }
}

bool  Book::DeletePhoneNumber(std::string fname, std::string lname)
{
    Person* del = FindPhoneNumber(fname, lname, m_root);
    if (del == nullptr)
    {
        return false;
    }
    else
    {
        del->m_phoneNumber = "NULL";
        return true;
    }
}

Person* Book::newPerson(std::string fname, std::string lname, std::string phonenumber)
{
    // Create Pointer
    Person * n = new Person;
    n->m_fname = fname;
    n->m_lname = lname;
    n->m_phoneNumber = phonenumber;
    n->left  = NULL;
    n->right = NULL;
    return n;
}

void  Book::rotateLeft(Person* ptr)
{
    Person* newParent = ptr->right;

    if (ptr == m_root)
        m_root = newParent;

    ptr->moveDown(newParent);
    ptr->right = newParent->left;

    if (newParent->left != NULL)
        newParent->left->parent = ptr;

    newParent->left = ptr;
}
void  Book::rotateRight(Person* ptr)
{
    Person *newParent = ptr->left;

    if (ptr == m_root)
        m_root = newParent;

    ptr->moveDown(newParent);
    ptr->left = newParent->right;

    if (newParent->right != NULL)
        newParent->right->parent = ptr;

    newParent->right = ptr;
}
void  Book::swapColor(Person* S1_ptr, Person* S2_ptr)
{
    COLOR temp = S1_ptr->Color;
    // S1_ptr->Color = NULL;
    S1_ptr->Color = S2_ptr->Color;
    S2_ptr->Color = temp;
}
void  Book::swapKeys(Person* S1_ptr, Person* S2_ptr)
{
    std::string tempfname1 = S1_ptr->m_fname;
    std::string templname1 = S1_ptr->m_lname;
    std::string tempphone1 = S1_ptr->m_phoneNumber;
    std::string tempfname2 = S2_ptr->m_fname;
    std::string templname2 = S2_ptr->m_lname;
    std::string tempphone2 = S2_ptr->m_phoneNumber;
    S1_ptr->m_fname = tempfname2;
    S1_ptr->m_lname = templname2;
    S1_ptr->m_phoneNumber = tempphone2;
    S2_ptr->m_fname = tempfname1;
    S2_ptr->m_lname = templname1;
    S2_ptr->m_phoneNumber = tempphone1;
}

void  Book::fixRedRed(Person* ptr)
{
    if (ptr == m_root) {
        ptr->Color = BLACK;
        return;
    }

    // initialize parent, grandparent, uncle
    Person *parent = ptr->parent;
    Person* grandparent = parent->parent;
    Person* uncle = ptr->uncle();

    if (parent->Color != BLACK) {
        if (uncle != NULL && uncle->Color == RED)
        {
            parent->Color = BLACK;
            uncle->Color = BLACK;
            grandparent->Color = RED;
            fixRedRed(grandparent);
        }
        else
        {
            if (parent->leftCheck())
            {
                if (ptr->leftCheck())
                    swapColor(parent, grandparent);
                else
                {
                    rotateLeft(parent);
                    swapColor(ptr, grandparent);
                }
                rotateRight(grandparent);
            }
            else
            {
                if (ptr->leftCheck())
                {
                    rotateRight(parent);
                    swapColor(ptr, grandparent);
                }
                else
                    swapColor(parent, grandparent);

                rotateLeft(grandparent);
            }
        }
    }
}
void  Book::fixBlackBlack(Person* ptr)
{
    if (ptr == m_root)
        return;

    Person* brother = ptr->sibling();
    Person* dad     = ptr->parent;

    if (brother == NULL) {
        // No sibiling, double black pushed up
        fixBlackBlack(dad);
    }
    else
    {
        if (brother->Color == RED)
        {
            // Sibling red
            dad->Color = RED;
            brother->Color = BLACK;

            if (brother->leftCheck())
                rotateRight(dad); // left case
            else
                rotateLeft(dad);  // right case

            fixBlackBlack(ptr);

        }
        else if (brother->Color == BLACK)
        {
            // Sibling black
            if (brother->redChildCheck())
            {
                // 1+ red children
                if (brother->left != NULL && brother->left->Color == RED)
                {
                    if (brother->leftCheck())
                    {
                        // left left
                        brother->left->Color = brother->Color;
                        brother->Color = dad->Color;
                        rotateRight(dad);
                    }
                    else
                    {
                        // right left
                        brother->left->Color = dad->Color;
                        rotateRight(brother);
                        rotateLeft(dad);
                    }
                }
                else
                {
                    if (brother->leftCheck())
                    {
                        // left right
                        brother->right->Color = dad->Color;
                        rotateLeft(brother);
                        rotateRight(dad);
                    }
                    else
                    {
                        // right right
                        brother->right->Color = brother->Color;
                        brother->Color = dad->Color;
                        rotateLeft(dad);
                    }
                }
                dad->Color = BLACK;
            }
            else
            {
                // 2 black children
                brother->Color = RED;
                if (dad->Color == BLACK)
                    fixBlackBlack(dad);
                else
                    dad->Color = BLACK;
            }
        }
    }
}

void  Book::EmptyTree(Person* ptr)
{
    if (ptr->left != nullptr)
    {
        EmptyTree(ptr->left);
    }

    if (ptr->right != nullptr)
    {
        EmptyTree(ptr->right);
    }

    ptr->left = nullptr;
    ptr->right = nullptr;

    m_size--;

    delete ptr;
}

Book::~Book()
{
    EmptyTree(m_root);
    m_root = NULL;
}


// ------------------ UserInterface Class ------------------ //
int   UserInterface::GetSelection()
{
    std::cout << "Please select what you want to do with the Phone Book" << std::endl <<
        "1 : (Add)     Add a persons name(first and last) and phone number to the phone book.       " << std::endl <<
        "2 : (Delete)  Deletes a given person’s phone number, given only the name.                  " << std::endl <<
        "3 : (Find)    Locates a person’s phone number, given only the person’s name.               " << std::endl <<
        "4 : (Change)  Changes a person’s phone number given the person’s name and new phone number." << std::endl <<
        "5 : (Display) Displays (dumps) entire phone book in alphabetical order.                    " << std::endl <<
        "6 : (Quit)    : Quits the application, after first saving the phone book in a text file.   " << std::endl;

    int sel;
    std::cin >> sel;
    return sel;
}


int main()
{
  int value = 0;
  std::string fname;
  std::string lname;
  std::string phoneNumber;

  UserInterface* UI = new UserInterface();
  Book* Book;

  while(value != 6)
  {
    value = UI->GetSelection();

    if(value == 1)
    {
      std::cout << "Adding a person to the phone book" << std::endl <<
      "First Name: ";
      std::cin >> fname;

      std::cout << "Last Name: ";
      std::cin >> lname;

      std::cout << "Phone Number: ";
      std::cin >> phoneNumber;

      Book->AddPerson(fname, lname, phoneNumber);

    }
    else if(value == 2)
    {
      std::cout << "Deleting a person's phone number from the phone book" << std::endl <<
      "First Name: ";
      std::cin >> fname;

      std::cout << "Last Name: ";
      std::cin >> lname;

      Book->DeletePhoneNumber(fname, lname);

    }
    else if(value == 3)
    {

    }
    else if(value == 4)
    {

    }
    else if(value == 5)
    {

    }


  }



  return 0;
}
