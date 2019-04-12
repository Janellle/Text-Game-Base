// object.cpp: implementation of the object class.
//
//////////////////////////////////////////////////////////////////////

#include "object.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Object::Object()
{
	name_ = "Unknown object";
	description_ = "Unknown description";
	home_room_ = "Unknown room";
	Objects.push_back(NULL);
}

Object::Object(string name, string desc, string home_room)
{
    name_ = name;
    description_ = desc;
    home_room_ = home_room;
    Objects.push_back(NULL);
}

string Object::name() const
{
	return name_;
}

// --- inspectors ---
string Object::description() const
{
	return description_;
}

string Object::home_room() const
{
    return home_room_;
}

// --- mutators ---
void Object::set_name(string n)
{
	name_ = n;
}

void Object::set_description(string d)
{
	description_ = d;
}

void Object::set_home_room(string hr)
{
    description_ = hr;
}
