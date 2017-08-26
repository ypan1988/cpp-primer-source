#include "Folder.h"

#include<iostream>
using std::endl; using std::cerr;

void swap(Message &lhs, Message &rhs)
{
    using std::swap;              // not strictly needed in this case, but good habit
    // remove pointers to each Message from their (original) respective Folders
    for (auto f: lhs.folders)
        f->remMsg(&lhs);
    for (auto f: rhs.folders)
        f->remMsg(&rhs);
    // swap the contents and Folder pointer sets
    swap(lhs.folders, rhs.folders);    // use swap(set& set&)
    swap(lhs.contents, rhs.contents);  // swap(string&, string&)
    // add pointers to each Message to their (new) respective Folders
    for (auto f: lhs.folders)
        f->addMsg(&lhs);
    for (auto f: rhs.folders)
        f->addMsg(&rhs);
}

Message::Message(const Message &m):
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);            // add this Message to the Folders that point to m
}

Message& Message::operator=(const Message &rhs)
{
    // handle self-assignment by removing pointer before inserting them
    remove_from_Folders();        // update existing Folders
    contents = rhs.contents;      // copy message contents from rhs
    folders = rhs.folders;        // copy Folder pointers from rhs
    add_to_Folders(rhs);          // add this Message to those Folders
    return *this;
}

Message::Message(Message &&m):
    contents(std::move(contents))
{
    move_Folders(&m);
}

Message& Message::operator=(Message &&rhs)
{
    if (this != &rhs) {  // direct check for self-assignment
        remove_from_Folders();
        contents = std::move(rhs.contents);  // move assignment
        move_Folders(&rhs);  // reset the Folders to point to this Message
    }
    return *this;
}

Message::~Message()
{
    remove_from_Folders();
}

void Message::save(Folder &f)
{
    folders.insert(&f);           // add the given Folder to our list of Folders
    f.addMsg(this);               // add this Message to f's set of Messages
}

void Message::remove(Folder &f)
{
    folders.erase(&f);            // tale the given Folder out of our list of Folders
    f.remMsg(this);               // remove this Message to f's set of Messages
}

void Message::debug_print()
{
    cerr << "Message:\t" << contents << endl;
    cerr << "Appears in " << folders.size() << " Folders" << endl;
    cerr << endl;
}

// add this Message to Folders that point to m
void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)      // for each Folder that holds m
        f->addMsg(this);            // add a pointer to this Message to that Folder
}

void Message::remove_from_Folders()
{
    for (auto f : folders)        // for each pointer in folders
        f->remMsg(this);            // remove this Message
}

void Message::move_Folders(Message *m)
{
    folders = std::move(m->folders);  // uses set move assignment
    for (auto f : folders) {  // for each Folder
        f->remMsg(m);     // remove the old Message from the Folder
        f->addMsg(this);  // add this Message to that Folder
    }
    m->folders.clear();   // ensure that destroying m is harmless
}

Folder::Folder(const Folder &f)
    : msgs(f.msgs)
{
    add_to_Messages(f);
}

Folder& Folder::operator =(const Folder &rhs)
{
    remove_from_Messages();
    msgs = rhs.msgs;
    add_to_Messages(rhs);
    return *this;
}

Folder::Folder(Folder &&f)
{
    move_Messages(&f);
}

Folder& Folder::operator =(Folder &&rhs)
{
    if (this != &rhs) {
        remove_from_Messages();
        move_Messages(&rhs);
    }
    return *this;
}

Folder::~Folder() { remove_from_Messages(); }

void Folder::save(Message &m)
{
    msgs.insert(&m);
    m.addFldr(this);
}

void Folder::remove(Message &m)
{
    msgs.erase(&m);
    m.remFldr(this);
}

void Folder::debug_print()
{
    cerr << "Folder contains " << msgs.size() << " messages" << endl;
    int ctr = 0;
    for (auto m : msgs) {
        cerr << "Message " << ++ctr << ":\t" << m->contents << endl;
    }
    cerr << endl;
}

void Folder::add_to_Messages(const Folder &f)
{
    for (auto m : f.msgs) {
        m->addFldr(this);
    }
}

void Folder::remove_from_Messages()
{
    for (auto m : msgs) {
        m->remFldr(this);
    }
}

void Folder::move_Messages(Folder *f)
{
    msgs = std::move(f->msgs);
    for (auto m : msgs) {
        m->remFldr(f);
        m->addFldr(this);
    }
    f->msgs.clear();
}
