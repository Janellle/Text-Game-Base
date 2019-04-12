// object.h: interface for the object class.
//
//////////////////////////////////////////////////////////////////////

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

//#include "Room.h"
#include<string>
#include<ciso646>  // http://www.cplusplus.com/reference/clibrary/ciso646/
#include<vector>
#include<iostream>
using namespace std;

class Object
{
public:
    // constructors
	Object(string name, string desc, string home_room);
	Object();

	// inspectors for other attributes
	string description() const;
	string name() const;
	string home_room() const;
	vector<Object*> Objects;

    // mutators
	void set_description(string d);
	void set_name(string n);
	void set_home_room(string hr);

	//virtual ~Object();

private:
    //  attributes
	string description_;
	string name_;
	string home_room_;

};

ostream & operator<<(ostream & out, const Object & o);

#endif // OBJECT_H_INCLUDED
