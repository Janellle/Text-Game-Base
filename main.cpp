#include "Room.h"
#include "object.h"
#include <iostream>

using namespace std;

void menu();
void look(Room* current_room);
void exits(Room* current_room);
void add(Room* current, vector<Room*>& allRooms);
void connect(Room* current, vector<Room*> allRooms);
void rename(Room* current);
void description(Room* current);
Direction char2Direction(char c); // convert a char value ('N','S','E','W')
                                  // to an enum value NORTH, SOUTH, etc

void jump(Room* current_room, vector<Room*> allRooms);
void credits();
void inspect(Object* current_object);
void addObj(Object* selected, vector<Object*>& Objects);
void itemList(Object* current_object, vector<Object*> Objects);

int main()
{
    // initialize
    Room* current_room = new Room();
    vector<Room*> allRooms;
    allRooms.push_back(current_room);

    Object* current_object = new Object();
    vector<Object*> Objects;
    Objects.push_back(current_object);

    char choice;
    int menuChoice;

    do
    {
    cout << "                         Adventure Game Builder                          " << endl;

    cout << "Type the following number to: " << endl;
    cout << "1. Start" << endl;
    cout << "2. Credits" << endl;
    cout << "3. Exit program" << endl;
    cin >> menuChoice;

    if (menuChoice == 1)
    {

        look(current_room);

        exits(current_room);
    // menu loop
    do
    {
        cout<<"Enter a command (? to list): "<<endl;
        cin>>choice;
        switch(choice)
        {
            case 'n':
                if (current_room->north()!= NULL)
                    current_room = current_room->north();
                else
                    cout<<"You cannot go that way"<<endl;
                break;
            case 'e':
                if (current_room->east()!= NULL)
                    current_room = current_room->east();
                else
                    cout<<"You cannot go that way"<<endl;
                break;
            case 's':
                if (current_room->south()!= NULL)
                    current_room = current_room->south();
                else
                    cout<<"You cannot go that way"<<endl;
                break;
            case 'w':
                if (current_room->west()!= NULL)
                    current_room = current_room->west();
                else
                    cout<<"You cannot go that way"<<endl;
                break;
            case 'i':
                inspect(current_object); break;
            case 'j':
                jump(current_room, allRooms); break;
            case 'l':
                look(current_room); break;
            case 'o':
                itemList(current_object,Objects); break;
            case 'x':
                exits(current_room);break;
            case 'c':
                connect(current_room, allRooms); break;
            case 'r':
                rename(current_room); break;
            case 'd':
                description(current_room); break;
            case 'a':
                add(current_room, allRooms); break;
            case '?':
                menu(); break;
            default:
                cout<<"invalid command"<<endl;
        }
    }while(choice != 'q');

    }

    if (menuChoice == 2)
        credits();

    // cleanup before quitting

    //return 0;
    }while (menuChoice != 3);
        return 0;
}

// Show the name and description of a room */
void look(Room* r)
{
    cout << r->name() << endl;
    cout << r->description() << endl;
}

// add a new room, connected to the current room
//  Parameters
//     current -- the current room we are in
//     allRooms-- a vector of pointers to (addresses of) all the rooms in the game
//  Precondition
//     current refers to an existing room
//  Postcondition
//    if possible (current must have a free exit)
//     a) a new room has been added off one of the exits of current
//     b) the address of the new room has also been added to the allRooms vector

void add(Room* current, vector<Room*>& allRooms)
{
    char toLoc, exitLoc;

    Room* temp = new Room("New room"," Loading...");

    allRooms.push_back(temp);

    cout << "Connect new room in which direction? (North 'N',South 'S', East 'E', West 'W')" << endl;
    cin >> exitLoc;

    cout << "Which exit of the new room leads to this room? ('N', 'S', 'E', 'W')"<<endl;
    cin >> toLoc;

    bool connected = current->connect(char2Direction(exitLoc), temp, char2Direction(toLoc)); //connect function within the Room class.

    if (connected)
        cout<<"Room connected."<<endl;
    else
        cout<<"Connection error."<<endl;

}

// add a new connection between current room and an already existing room.
//  Parameters
//     current -- the current room we are in
//     allRooms-- a vector of pointers to (addresses of) all the rooms in the game
//  Precondition
//     current refers to an existing room
//  Postcondition
//    if possible (both rooms must have a spare exit to link them together)
//     current is now linked to another room in the game
//
void connect(Room* current, vector<Room*> allRooms)
{
    int num;
    char toLoc, exitLoc;

    cout << "Connect new room in which direction? (North 'N',South 'S', East 'E', West 'W')" << endl;
    cin >> exitLoc;

    cout << "Connect room to which room #?" << endl;

    for (int i = 0; i < allRooms.size(); i++)
        cout << i << ": " << allRooms[i]->name() << endl; // display all room numbers
    cin >> num;

    cout << "Which exit of the new room leads to this room? ('N', 'S', 'E', 'W')"<<endl;
    cin >> toLoc;

    bool connected = current->connect(char2Direction(exitLoc), allRooms[num], char2Direction(toLoc));

    if (connected)
        cout<<"Room connected."<<endl;
    else
        cout<<"Connection error."<<endl;
}

// change the name of a room
void rename(Room* current)
{
    string renamed;
    cout << "What would you like to rename this room to?" << endl;
    cin.ignore(1,'\n');
    getline(cin,renamed);
    current->set_name(renamed);

}

// change the description of a room
void description(Room* current)
{
    string text;
    cout<<"Enter a new description for this room and hit <enter>"<<endl;
    cin.ignore(1,'\n');
    getline(cin,text);
    current->set_description(text);
}

// for each exit from room r,
//   show the name of the room it connects to
//   or say "Nothing" if the link is null
void exits(Room* r)
{
    cout << "  North --- ";
    if (r->north() != NULL)
        cout << r->north()->name() << endl;
    else
        cout << "Nothing." << endl;

    cout << "  South --- ";
    if (r->south() != NULL)
        cout << r->south()->name() << endl;
    else
        cout << "Nothing." << endl;

    cout << "  East  --- ";
    if (r->east() != NULL)
        cout << r->east()->name() << endl;
    else
        cout << "Nothing." << endl;

    cout << "  West  --- ";
    if (r->west() != NULL)
        cout << r->west()->name() << endl;
    else
        cout << "Nothing." << endl;
}

void jump(Room* current_room, vector<Room*> allRooms)
{
    int num;

    cout << "Jump to which room #?" << endl;

    for (int i = 0; i < allRooms.size(); i++)
        cout << i << ": " << allRooms[i]->name() << endl; // display all room numbers
    cin >> num;

    if (allRooms[num]!= NULL)
        current_room = allRooms[num];
}

void itemList(Object* current_object, vector<Object*> Objects)
{
    for (int i = 0; i < Objects.size(); i++)
        cout << i << ": " << Objects[i]->name() << endl;
}

void menu()
{
    cout<<"Please choose from the following: "<<endl;
    cout<<"     n or north --- move north (if possible)"<<endl;
    cout<<"      e or east --- move east (if possible)"<<endl;
    cout<<"     s or south --- move south (if possible)"<<endl;
    cout<<"      w or west --- move at west (if possible)"<<endl;
    //cout<<"   i or inspect --- inspect room for objects"<< endl;
    //cout<<"      j or jump --- jump to a room (if possible)"<<endl;
    //cout<<"      l or look --- look at room"<<endl;
    //cout<<"   o or objects --- object list"<<endl;
    cout<<"     x or exits --- show room exits"<<endl;
    cout<<"   c or connect --- connect this room to another (already made) room"<<endl;
    cout<<"    r or rename --- rename this room"<<endl;
    cout<<"      d or desc --- change description for this room"<<endl;
    cout<<"       a or add --- add new room"<<endl;
    cout<<"      q or quit --- exit program"<<endl;
    cout<<"              ? --- show commands (DUH)"<<endl;
}

void credits()
{
    cout << "                          Credits                           " << endl;

    cout << "Written by Janelle Uganiza " << endl;
    cout << "Software used:" << endl;
    cout << "Code::Blocks 17.12" << endl;
    cout << "Programmed in C++" << endl;
    cout << "CSIS 10C Fall 2018" << endl;
    cout << "Final Project" << endl;
}

void inspect(Object* current_object)
{
    cout << current_object->name() << endl;
    cout << current_object->description() << endl;
    cout << current_object->home_room() << endl;
}

// convert a char direction: 'N','S','E','W'
// into a Direction enum: NORTH, SOUTH, EAST, WEST
Direction char2Direction(char c)
{
    switch(c)
    {
        case 'N': return NORTH;
        case 'S': return SOUTH;
        case 'E': return EAST;
        case 'W': return WEST;
        default: return NORTH;
    }
}
