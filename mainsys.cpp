#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>


using namespace std;

struct contact
{
    string nick;
    int tel_nr;
    string email;
    string description;
};

void show_main_menu_title();

bool contact_person_add(vector<contact>&);
bool contact_person_remove_byname(vector<contact>&);
bool contact_person_remove_byid(vector<contact>&);
bool contact_person_modify();

bool contact_list_load(vector<contact>&);

short int menu_control_panel(vector<contact>&);

int main()
{
    vector<contact> st;

    show_main_menu_title();
    cout << "Initialization phonebook..." << endl;
    if(!contact_list_load(st))
    {
        cout << "! failed communication with the database !" << endl << endl << endl;
        return -1;
    }

    system("CLS");
    show_main_menu_title();
    menu_control_panel(st);


    return 0;
}


////////////////////////
//                    //
//                    //
/*   VISU FUNCTIONS   */
//                    //
//                    //
////////////////////////


void show_main_menu_title()
{
    cout << "      PhoneBook By Matafovski     " << endl;
    cout << "----------------------------------" << endl;
    cout << endl;
}

short int menu_control_panel(vector<contact>& st)
{

    bool infinity_loop_breaker = true;
    do{
        system("CLS");
        short int choice = 0;
        for(size_t i = 0; i < st.size(); ++i)
        {
        cout << i << ">> " << st[i].nick << endl;
        }
        cout << st.size() << endl;
        cout << endl;
        cout << "Select option: " << endl;
        cout << "1 Add Person" << endl;
        cout << "2 Remove Person by name" << endl;
        cout << "3 Remove Person by id" << endl;
        cout << "4 Modify Person" << endl;
        cout << "5 Phonebook List" << endl;
        cout << "6 Quit" << endl;
        cout << "Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            contact_person_add(st);
            break;
        case 2:
            contact_person_remove_byname(st);
            break;
        case 3:
            contact_person_remove_byid(st);
            break;
        case 4:
            contact_person_modify();
            break;
        case 4:
            cout << "PHONEBOOK LIST" << endl;
            break;
        case 6:
            infinity_loop_breaker = false;
            break;
        default: //0 - NULL
            cout << endl << "! failed communication with essential systems !" << endl << endl << endl;
            break;
        }
    }while(infinity_loop_breaker);

    return 0;
}


////////////////////////
//                    //
//                    //
/*  PERSON FUNCTIONS  */
//                    //
//                    //
////////////////////////

bool contact_person_add(vector<contact>& st)
{
    cin.ignore();
    string name = "";
    string telnr = "";
    string email = "";
    string description = "";

    cout << "Name: " << endl;
    getline(cin, name);
    if(name.length() <= 2)
    {
        cout << "Name cannot be smaller than 2 chars" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }


    cout << "Phone number: " << endl;
    getline(cin, telnr);
    if(name.length() <= 2)
    {
        cout << "Phone number cannot be smaller than 2 chars" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }

    cout << "Email: " << endl;
    getline(cin, email);
    if(name.length() <= 5)
    {
        cout << "Email cannot be smaller than 5 chars" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }

    cout << "Description: " << endl;
    getline(cin, description);

    st.push_back(contact());
    int last_vector = st.size()-1;
    st[last_vector].nick = name;
    st[last_vector].tel_nr = stoi(telnr);
    st[last_vector].email = email;
    st[last_vector].description = description;

    return true;
}

bool contact_person_remove_byname(vector<contact> &st)
{
    string name_to_remove;
    cout << "Enter correct name to remove: ";
    cin.clear();
    cin.ignore();
    getline(cin,name_to_remove);
    if(name_to_remove.length() <= 2)
    {
        cout << "Name cannot be smaller than 2 chars" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }
    for(size_t i = 0; i<st.size(); ++i) //Read every contact
    {
        string name_from_phonebook = st[i].nick;
        int correct_letters = 0;
        if(name_from_phonebook.length() != name_to_remove.length())
        {
            continue;
        }
        string clear_name_to_remove = "";
        string clear_name_from_phonebook = "";
        for(size_t j = 0; j < name_to_remove.length(); ++j) //Read every char from key name
        {

            if(name_to_remove[j] >= 65 && name_to_remove[j] <= 90)
            {
                clear_name_to_remove += (name_to_remove[j] + 32);
            }
            else
            {
                clear_name_to_remove += name_to_remove[j];
            }

            if(name_from_phonebook[j] >= 65 && name_from_phonebook[j] <= 90)
            {
                clear_name_from_phonebook += (name_from_phonebook[j] + 32);
            }
            else
            {
                clear_name_from_phonebook += name_from_phonebook[j];
            }
        }
        if(clear_name_from_phonebook == clear_name_to_remove)
        {
            st.erase(st.begin()+i);
            return true;
        }
    }

    return false;
}

bool contact_person_remove_byid(vector<contact> &st)
{
    int id = 0;
    cout << "Enter id to remove: ";
    cin >> id;
    if(id >= st.size() || !cin.good() || id <= 0)
    {
        cin.clear();
        cout << "Specified id is outside the set" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }

    st.erase(st.begin()+id);

    return true;
}

bool contact_person_modify()
{
    int id = 0;
    cout << "Enter contact id to modify: ";
    cin >> id;
    if(id >= st.size() || !cin.good() || id <= 0)
    {
        cin.clear();
        cout << "Specified id is outside the set" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }

    system("CLS");
    cout << "FOUNDED "
    
    return false;
}



////////////////////////
//                    //
//                    //
/*   LIST FUNCTIONS   */
//                    //
//                    //
////////////////////////

/*bool contact_list_update()
{

    return false;
}
*/

bool contact_list_load(vector<contact> &st)
{
    int person_nr = 1;

    string data_nick; //nick
    string data_telnr; //tel_nr
    string data_email; //email
    string data_description; //description
    string data_spacer; //spacer in phonebook;

    fstream pb; //pb - Phonebook

    pb.open("phonebook.txt", ios::in);
    if(!pb.good())
        return false;
    st.push_back(contact());
    while(!pb.eof())
    {
        getline(pb, data_nick);
        getline(pb, data_telnr);
        getline(pb, data_email);
        getline(pb, data_description);
        getline(pb, data_spacer);

        st.push_back(contact());

        st[person_nr].tel_nr = stoi(data_telnr);
        st[person_nr].nick = data_nick;
        st[person_nr].email = data_email;
        st[person_nr].description = data_description;
        person_nr++;
    }
    pb.close();
    return true;
}

