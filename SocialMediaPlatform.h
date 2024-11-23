#ifndef SOCIAL_MEDIA_PLATFORM_H
#define SOCIAL_MEDIA_PLATFORM_H
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <unistd.h>
#include <windows.h>
#include <algorithm>

using namespace std;

class User; // Forward declaration

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

    // Methods to update profile details
    void updateBio(const std::string &newBio);
    void updateEmail(const std::string &newEmail);
    void updatePassword(const std::string &newPassword);
    void updatePrivacy(bool newPrivacy);
    void updateUsername(const std::string &newUsername);
};

class Comment
{
public:
    string content;
    User *author;
    list<Comment> replies; // List of replies to this comment

public:
    Comment(User *author, const string &content) : author(author), content(content) {}

    string getContent() { return content; }
    string getAuthor() { return author->getUsername(); }

    list<Comment> &getReplies() { return replies; }
    void addReply(User *replier, const string &replyContent);
    void displayComment(int level = 0);
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
};

// Post Management Class
class PostManagement
{
public:
    // Use unordered_map or map as per your requirement, here's using unordered_map
    std::map<User *, std::list<std::string>> userPosts;
    std::map<std::string, std::vector<Comment *>> postComments; // Assuming Comment is defined somewhere

    void createPost(User *user, const std::string &content);
    void viewUserPosts(User *user);
    void viewFriendsPosts(User *user, const std::map<User *, std::list<User *>> &friends);
    void viewPublicPosts(const std::map<User *, std::list<std::string>> &userPosts, User *currentUser); // Change parameter to match internal structure
    void addComment(User *user, const std::string &postContent, const std::string &commentContent);
    void addReplyToComment(User *user, const string &postContent, Comment *parentComment, const string &replyContent);
    void displayPostWithComments(const std::string &postContent);
    std::vector<std::string> getAllPosts();
    void viewPostComments(const string &postContent);
    void addCommentOrReply(Comment &parentComment, User *currentUser);
    void interactiveCommentSection(User *currentUser);
};

// Friend System Class
class FriendSystem
{
private:
    std::map<User *, list<User *>> friends; // Map storing each user and their list of friends
    std::map<User *, list<User *>> pendingRequests; // To store pending friend requests

public:
// Get the entire friends list (for internal use or testing)
    const std::map<User *, std::list<User *>> &getFriendsList() { 
        return friends; 
    }
void addFriend(User *user, User *friendUser);
bool viewFriends(User *user);
void suggestFriendsBFS(User *user);
void suggestFriendsDFS(User *user);
void dfs(User *user, std::map<User *, bool> &visited, std::map<User *, int> &mutualCount);
void displayPendingRequests(User *user);
void removeFriend(User *user1, User *user2);
void mutualFriendsCount(User *user1, User *user2);
};

// Messaging System Class
class MessagingSystem
{
private:
    std::map<User *, std::queue<std::string>> userMessages; // User object as key, queue of messages as value

public:
    void sendMessage(User *fromUser, User *toUser, const std::string &message);
    void viewMessages(User *user);
};

// // User Class
// class User
// {
// private:
//     std::string username;
//     std::string password;
//     std::string email;
//     std::string bio;
//     bool isPublic;

// public:
//     User(const std::string &uname, const std::string &pwd, const std::string &email, const std::string &bio, bool isPublic);
//     std::string getUsername();
//     std::string getEmail();
//     std::string getBio();
//     bool isProfilePublic();
//     bool validatePassword(const std::string &pwd);

//     // FriendSystem and MessagingSystem may need access to private data
//     friend class FriendSystem;
//     friend class MessagingSystem;
// };

#endif // SOCIAL_MEDIA_PLATFORM_H
