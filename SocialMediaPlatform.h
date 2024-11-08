#ifndef SOCIAL_MEDIA_PLATFORM_H
#define SOCIAL_MEDIA_PLATFORM_H

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <set>
#include <windows.h>
#include <unistd.h>
using namespace std;
#define MAX_USERS 100
#define MAX_REQUESTS 10

// Basic Queue for managing friend requests
class Queue {
    int arr[MAX_REQUESTS];
    int front, rear, size;
public:
    Queue() : front(0), rear(-1), size(0) {}
    bool isEmpty() { return size == 0; }
    bool isFull() { return size == MAX_REQUESTS; }
    void enqueue(int x);
    int dequeue();
    int frontItem();
};

void Queue::enqueue(int x) {
    if (!isFull()) {
        rear = (rear + 1) % MAX_REQUESTS;
        arr[rear] = x;
        size++;
    }
}

int Queue::dequeue() {
    if (!isEmpty()) {
        int x = arr[front];
        front = (front + 1) % MAX_REQUESTS;
        size--;
        return x;
    }
    return -1;
}

int Queue::frontItem() {
    return isEmpty() ? -1 : arr[front];
}

// Node structure for linked list used in friends' list management
struct Node {
    int userID;
    Node* next;
    Node(int id) : userID(id), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}
    void insert(int userID);
    bool contains(int userID);
    void remove(int userID);
    void display();
};

void LinkedList::insert(int userID) {
    Node* newNode = new Node(userID);
    newNode->next = head;
    head = newNode;
}

bool LinkedList::contains(int userID) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->userID == userID) return true;
        temp = temp->next;
    }
    return false;
}

void LinkedList::remove(int userID) {
    Node* temp = head, *prev = nullptr;
    while (temp != nullptr && temp->userID != userID) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) return;
    if (prev == nullptr) head = head->next;
    else prev->next = temp->next;
    delete temp;
}

void LinkedList::display() {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->userID << " ";
        temp = temp->next;
    }
}

// FriendSystem class for managing friendships and requests
class FriendSystem {
    LinkedList friends[MAX_USERS]; 
    Queue friendRequests[MAX_USERS];
public:
    void sendFriendRequest(int user1, int user2);
    void acceptFriendRequestsBatch(int user);
    void displayFriends(int user);
    void suggestFriendsBFS(int user);
    void suggestFriendsDFS(int user);
    void displayPendingRequests(int user);
    void removeFriend(int user1, int user2);
    void mutualFriendsCount(int user1, int user2);
    void dfs(int user, bool visited[], int mutualCount[]);
};
// User Class
class User
{
private:
    std::string username;
    std::string password;
    std::string email;
    std::string bio;
    bool isPublic;

public:
    User(const std::string &uname, const std::string &pwd, const std::string &email, const std::string &bio, bool isPublic);

    std::string getUsername();
    std::string getEmail();
    std::string getBio();
    bool isProfilePublic();
    bool validatePassword(const std::string &pwd);

    void updateBio(const std::string &newBio);
    void updateEmail(const std::string &newEmail);
    void updatePassword(const std::string &newPassword);
    void updatePrivacy(bool newPrivacy);
    void updateUsername(const std::string &newUsername);

    friend class FriendSystem;
    friend class MessagingSystem;
};

// MessageNode Class (For Linked List)
class MessageNode
{
public:
    User *sender;   // Pointer to the sender User
    User *receiver; // Pointer to the receiver User
    std::string message;
    MessageNode *prev;
    MessageNode *next;

    MessageNode(User *sender, User *receiver, const std::string &message)
        : sender(sender), receiver(receiver), message(message), prev(nullptr), next(nullptr) {}
};

// Doubly Linked List Class (Chat History)
class DoublyLinkedList
{
private:
    MessageNode *head;
    MessageNode *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList()
    {
        MessageNode *current = head;
        while (current)
        {
            MessageNode *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void append(User *sender, User *receiver, const std::string &message)
    {
        MessageNode *newNode = new MessageNode(sender, receiver, message);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display(User *user1, User *user2) const
    {
        MessageNode *current = head;
        bool foundMessages = false;

        while (current)
        {
            if (current->sender == user1 && current->receiver == user2)
            {
                std::cout << "To " << user2->getUsername() << ": " << current->message << std::endl;
                foundMessages = true;
            }
            else if (current->sender == user2 && current->receiver == user1)
            {
                std::cout << "From " << user2->getUsername() << ": " << current->message << std::endl;
                foundMessages = true;
            }
            current = current->next;
        }

        if (!foundMessages)
        {
            std::cout << "No messages found between " << user1->getUsername() << " and " << user2->getUsername() << "!" << std::endl;
        }
    }

    void display2() const
    {
        MessageNode *current = head;
        if (!current)
        {
            std::cout << "No messages in this group." << std::endl;
            return;
        }

        while (current)
        {
            std::cout << "From " << current->sender->getUsername() << ": " << current->message << std::endl;
            current = current->next;
        }
    }
    MessageNode *getHead() const
    {
        return head;
    }
};

// Group Class for Group Messaging
class Group
{
public:
    std::string groupId;             // Unique identifier for the group
    std::string groupName;           // Name of the group
    std::set<User *> participants;   // Users in the group
    DoublyLinkedList messageHistory; // Group chat history

    // Default constructor
    Group() : groupId(""), groupName("") {}

    // Parameterized constructor
    Group(const std::string &groupId, const std::string &groupName)
        : groupId(groupId), groupName(groupName) {}

    void addUser(User *user)
    {
        participants.insert(user);
    }

    void removeUser(User *user)
    {
        participants.erase(user);
    }

    bool isUserInGroup(User *user) const
    {
        return participants.find(user) != participants.end();
    }

    // Add a message to the group's message history
    void addMessage(User *sender, const std::string &message)
    {
        messageHistory.append(sender, nullptr, message);
    }
};

// User Management Class
class UserManagement
{
private:
    std::unordered_map<std::string, std::pair<std::string, User *>> userCredentials; // Hashmap for user credentials and pointers to profiles
    std::list<User *> userProfiles;                                                  // Linked list for storing user profile information

public:
    User *signUp();
    User *logIn(const std::string &username, const std::string &password);
    void updateUserProfile(User *user, const std::string &newBio, const std::string &newEmail);
    void displayProfile(User *user);
    User *findUserByUsername(const std::string &username);
    void displayAllUsers();
    void editProfile(User *user);
    User *validateUsername(const string &username);
    bool isValidEmail(const string &email);

    friend class FriendSystem;
    friend class MessagingSystem;
};

// Post Management Class
class PostManagement
{
public:
    std::map<User *, std::list<std::string>> userPosts; // User object as key, list of posts as value
    void createPost(User *user, const std::string &content);
    void viewUserPosts(User *user);
    void viewFriendsPosts(User *user, const std::map<User *, std::list<User *>> &friends);
    void viewPublicPosts(const std::map<User *, std::list<std::string>> &userPosts, User *currentUser);
    std::vector<std::string> getAllPosts(); // Return all posts as strings
};

// Messaging System Class (One-on-One and Group Messaging)
class MessagingSystem
{
private:
    std::map<User *, std::queue<std::pair<User *, std::string>>> userMessages;
    std::map<User *, DoublyLinkedList> chatHistory; // One-on-one chat history
    std::map<std::string, Group> groups;            // Group messaging system

public:
    void sendMessage(User *fromUser, User *toUser, const std::string &message);
    void viewNewMessages(User *user);
    void viewChatHistory(User *recipient, User *friendUser);

    // Group-related functions
    void createGroup(User *currentUser, UserManagement &userManagement, FriendSystem &friendSystem, MessagingSystem &messagingSystem);
    // void createGroup(const std::string &groupId, const std::string &groupName, const std::set<User *> &initialParticipants);
    bool sendMessageToGroup(User *fromUser, const std::string &groupId, const std::string &message);
    void viewGroupChatHistory(const std::string &groupName, User *currentUser);
    bool addUserToGroup(const std::string &groupName, User *user);
    bool removeUserFromGroup(const std::string &groupId, User *user);
    bool isUserInGroup(const std::string &groupName, User *user);
    const std::map<std::string, Group> &getGroups() const
    {
        return groups;
    }
};

#endif // SOCIAL_MEDIA_PLATFORM_H
