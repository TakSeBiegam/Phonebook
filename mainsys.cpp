#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
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
bool contact_person_modify(vector<contact>&);

bool contact_person_list(vector<contact>&);

//Load from file
bool contact_list_load(vector<contact>&);
//Update to file
bool contact_list_update(vector<contact>&);

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
        /*for(size_t i = 0; i < st.size(); ++i)
        {
        cout << i << ">> " << st[i].nick << endl;
        }*/
        cout << endl;
        st.size();
        show_main_menu_title();
        cout << "Select option: " << endl;
        cout << "1 Add Person" << endl;
        cout << "2 Remove Person by name" << endl;
        cout << "3 Remove Person by id" << endl;
        //cout << "4 Modify Person" << endl;
        cout << "4 Phonebook List" << endl;
        cout << "5 Quit" << endl;
        cout << "Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            contact_person_add(st);
            contact_list_update(st);
            break;
        case 2:
            contact_person_remove_byname(st);
            contact_list_update(st);
            break;
        case 3:
            contact_person_remove_byid(st);
            contact_list_update(st);
            break;
        /*case 4:
            contact_person_modify(st);
            contact_list_update(st);
            break;*/
        case 4:
            contact_person_list(st);
            break;
        case 5:
            infinity_loop_breaker = false;
            break;
        default: //0 - NULL
            cout << endl << "! failed communication with essential systems !" << endl;
            cout << "! ERROR - Reopening system" << endl << endl << endl;
            Sleep(2000);
            choice = 999;
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
    if(telnr.length() <= 2)
    {
        cout << "Phone number cannot be smaller than 2 chars" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }

    cout << "Email: " << endl;
    getline(cin, email);
    if(email.length() <= 5)
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

bool contact_person_modify(vector<contact> &st)
{

    int id = 0;
    cout << endl << "Enter contact id: ";
    cin >> id;
    string name = "";
    string email = "";
    string tel_nr = "";
    string description = "";
    if(id >= st.size() || !cin.good() || id <= 0)
    {
        cin.clear();
        cout << "Specified id is outside the set" << endl;
        cout << "Returning to the menu" << endl;
        Sleep(2000);
        return false;
    }
    bool is_editing = false;
    char edit_data_char;
    system("CLS");
    cout << "  ORIGNAL DATA  " << endl;
    cout << "----------------" << endl;
    cout << st[id].nick << endl;
    cout << st[id].tel_nr << endl;
    cout << st[id].email << endl;
    cout << st[id].description << endl;
    cout << "----------------" << endl;
    cout << "Do you wanna edit data ? " << endl;
    cout << "Type Y/n: " << endl;
    cin >> edit_data_char;
    switch(edit_data_char)
    {
    case 'Y':
    case 'y':
        is_editing = true;
        break;
    default:
        is_editing = false;
        break;
    }
    if(is_editing)
    {
        cout << "----------------" << endl;
        cout << "  DATA TO EDIT  " << endl;
        cout << "(if keep old data, press enter)" << endl;
        cout << "----------------" << endl;
        cout << "Name:" << endl;
        cin.clear();
        cin.ignore();
        getline(cin, name);
        if(name.length() <= 2)
        {
            if(name.length() != 0)
            {
                cout << "Name cannot be smaller than 2 chars" << endl;
                cout << "Returning to the menu" << endl;
                Sleep(2000);
                return false;
            }
        }
        if(name.length() != 0)
        {
            st[id].nick = name;
        }

        cout << "Phone number: " << endl;
        getline(cin, tel_nr);
        if(tel_nr.length() <= 2)
        {
            if(tel_nr.length() != 0)
            {
                cout << "Phone number cannot be smaller than 2 chars" << endl;
                cout << "Returning to the menu" << endl;
                Sleep(2000);
                return false;
            }
        }
        if(tel_nr.length() != 0)
        {
            st[id].tel_nr = stoi(tel_nr);
        }

        cout << "Email: " << endl;
        getline(cin, email);
        if(email.length() <= 5)
        {
            if(email.length() != 0)
            {
                cout << "Email cannot be smaller than 5 chars" << endl;
                cout << "Returning to the menu" << endl;
                Sleep(2000);
                return false;
            }
        }
        if(email.length() != 0)
        {
            st[id].email = email;
        }

        cout << "Description: " << endl;
        getline(cin, description);
        if(email.length() != 0)
        {
            st[id].description = description;
        }
    }
    return true;
}



////////////////////////
//                    //
//                    //
/*   LIST FUNCTIONS   */
//                    //
//                    //
////////////////////////

string crypt(string text_to_crypt)
{
    string crypted = "";
    for(size_t i = 1; i <= text_to_crypt.length(); ++i)
    {
        if(i%2 == 0)
        {
            crypted += (text_to_crypt[i-1] - 2);
        }
        else{
           crypted += (text_to_crypt[i-1] + 3);
        }
        if(i % 5 == 0)
            crypted += rand() % 24 + 97;
    }

    return crypted;
}

string decrypt(string text_to_decrypt)
{
    string decrypted = "";
    bool is_change_polarity = true;

    for(size_t i = 1; i <= text_to_decrypt.length(); i++)
    {
        if(i % 6 == 0){
            if(is_change_polarity)
            {
                is_change_polarity = false;
                continue;
            }
            else{
                is_change_polarity = true;
                continue;
            }
        }
        if(is_change_polarity)
            if(i%2 == 0)
            {
                decrypted += (text_to_decrypt[i-1] + 2);
            }
            else{
                decrypted += (text_to_decrypt[i-1] - 3);
            }
        else{
            if(i%2 == 0)
            {
                decrypted += (text_to_decrypt[i-1] - 3);
            }
            else{
                decrypted += (text_to_decrypt[i-1] + 2);
            }
        }
    }

    return decrypted;
}

bool contact_list_update(vector<contact> &st)
{
    fstream pb;
    pb.open("phonebook.txt", ios::out);
    if(!pb.good())
        return false;
    for(size_t i = 1; i < st.size(); ++i)
    {
        string nick = st[i].nick;
        string crypto_nick = "";

        string tel_nr = to_string(st[i].tel_nr);
        string crypto_telnr = "";

        string email = st[i].email;
        string crypto_email = "";

        string descrption = st[i].description;
        string crypto_desc = "";

        crypto_nick = crypt(nick);
        crypto_email = crypt(email);
        crypto_telnr = crypt(tel_nr);
        crypto_desc = crypt(descrption);



        pb << crypto_nick << endl;
        pb << crypto_telnr << endl;
        pb << crypto_email << endl;
        pb << crypto_desc << endl;
        string spacer = "";
        int long_char_in_empty_line = rand()%20+7;
        for(size_t j = 0; j < long_char_in_empty_line; j++)
        {
            spacer += rand() % 24 + 97;
        }
        pb << spacer << endl;
    }

    pb.close();

    return true;
}


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
        string data_nick_decrypted = decrypt(data_nick);
        string data_telnr_decrypted = decrypt(data_telnr);
        string data_email_decrypted = decrypt(data_email);
        string data_description_decrypted = decrypt(data_description);

        cout << data_nick_decrypted << endl;
        cout << data_telnr_decrypted << endl;
        cout << data_email_decrypted << endl;
        cout << data_description_decrypted << endl;
        st[person_nr].nick = data_nick_decrypted;
        st[person_nr].tel_nr = stoi(data_telnr_decrypted);
        st[person_nr].email = data_email_decrypted;
        st[person_nr].description = data_description_decrypted;

        /*st[person_nr].nick = data_nick;
        st[person_nr].tel_nr = stoi(data_telnr);
        st[person_nr].email = data_email;
        st[person_nr].description = data_description;*/

        person_nr++;
    }
    pb.close();
    return true;
}

int show_page(int pointer_in_phonebook, vector<contact> &st, char direction)
{
    if(direction == 'u')
    {
        for(size_t i = pointer_in_phonebook; i < (pointer_in_phonebook + 15); i++)
        {
            if(i == (st.size()-1))
                return pointer_in_phonebook;
            cout << i << ">> " << st[i].nick << endl;
        }
        pointer_in_phonebook += 15;
    }
    else{
            if(pointer_in_phonebook - 15 < 1)
            {
                show_page(pointer_in_phonebook, st, 'u');
                return pointer_in_phonebook;
            }
        for(size_t i = pointer_in_phonebook - 15; i < pointer_in_phonebook; i++)
        {
            if(i < 1)
                return pointer_in_phonebook;
            cout << i << ">> " << st[i].nick << endl;
        }
        pointer_in_phonebook -= 15;
    }

    return pointer_in_phonebook;
}

bool contact_person_list(vector<contact> &st)
{
    int choice = 0;
    int pointer_on_place_in_phonebook = 1;

    system("CLS");
    show_main_menu_title();
    bool infinity_loop_breaker = true;
    bool is_last_was_prev_page = false;
    pointer_on_place_in_phonebook = show_page(pointer_on_place_in_phonebook, st, 'u');

    do{
        cout << endl;
        cout << "Select option: " << endl;
        cout << "1 Prev Page" << endl;
        cout << "2 Next Page" << endl;
        cout << "3 Select Person" << endl;
        cout << "4 Quit" << endl;
        cout << "pointer: " << pointer_on_place_in_phonebook << endl;
        cout << "Your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("CLS");
            show_main_menu_title();
            pointer_on_place_in_phonebook = show_page(pointer_on_place_in_phonebook, st, 'd');
            is_last_was_prev_page = true;
            break;
        case 2:
            system("CLS");
            show_main_menu_title();
            if(is_last_was_prev_page)
            {
                is_last_was_prev_page = false;
                pointer_on_place_in_phonebook += 15;
            }
            pointer_on_place_in_phonebook = show_page(pointer_on_place_in_phonebook, st, 'u');
            break;
        case 3:
            contact_person_modify(st);
            contact_list_update(st);
            system("CLS");
            show_main_menu_title();
            show_page(pointer_on_place_in_phonebook, st, 'u');
            break;
        case 4:
            return true;
            break;
        default:
            system("CLS");
            show_main_menu_title();
            show_page(pointer_on_place_in_phonebook, st, 'u');
            choice = 999;
            break;
        }
    }while(infinity_loop_breaker);

    return false;
}
