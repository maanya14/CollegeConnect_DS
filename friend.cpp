#include <iostream>
#define MAX_USERS 100
#define MAX_REQUESTS 10

using namespace std;

// Queue class for managing friend requests
class Queue {
    int arr[MAX_REQUESTS];
    int front, rear, size;
public:
    Queue(){
        front=0;
        rear=-1;
        size=0;
    }
    
    bool isEmpty() { 
        return size == 0;
     }
    bool isFull() {
        return size == MAX_REQUESTS;
     }

    void enqueue(int x) {
        if (!isFull()) {
            rear = (rear + 1) % MAX_REQUESTS;
            arr[rear] = x;
            size++;
        }
        else return;
    }

    int dequeue() {
        if (!isEmpty()) {
            int x = arr[front];
            front = (front + 1) % MAX_REQUESTS;
            size--;
            return x;
        }
        return -1;
    }

    int frontItem() { 
        return isEmpty() ? -1 : arr[front]; }
};

// Node structure for Linked List
struct Node {
    int userID;
    Node* next;
    Node(int id) : userID(id), next(nullptr) {}
};

// Linked List for managing friend lists and suggestions
class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void insert(int userID) {
        if (head==nullptr){
            head = new Node(userID);
        }
        Node* newNode = new Node(userID);
        newNode->next = head;
        head = newNode;
    }

    bool contains(int userID) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->userID == userID) return true;
            temp = temp->next;
        }
        return false;
    }

    void remove(int userID) {
        Node* temp = head, *prev = nullptr;
        while (temp != nullptr && temp->userID != userID) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) return; // User not found
        if (prev == nullptr) head = head->next;
        else prev->next = temp->next;
        delete temp;
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->userID << " ";
            temp = temp->next;
        }
    }
};

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

// Send friend request
void FriendSystem::sendFriendRequest(int user1, int user2) {
    friendRequests[user2].enqueue(user1);
    cout << "Friend request sent from User " << user1 << " to User " << user2 << ".\n";
}

// Accept all friend requests in batch
void FriendSystem::acceptFriendRequestsBatch(int user) {
    while (!friendRequests[user].isEmpty()) {
        int requester = friendRequests[user].dequeue();
        friends[user].insert(requester);
        friends[requester].insert(user);
        cout << "User " << user << " accepted friend request from User " << requester << ".\n";
    }
}

// Display a user's friend list
void FriendSystem::displayFriends(int user) {
    std::cout << "Friends of User " << user << ": ";
    friends[user].display();
    cout << "\n";
}

// Display pending friend requests for a user
void FriendSystem::displayPendingRequests(int user) {
    std::cout << "Pending friend requests for User " << user << ": ";
    Queue temp = friendRequests[user];
    while (!temp.isEmpty()) {
        cout << temp.dequeue() << " ";
    }
    cout << "\n";
}

// Suggest friends using BFS
void FriendSystem::suggestFriendsBFS(int user) {
    int mutualCount[MAX_USERS] = {0};
    bool visited[MAX_USERS] = {false};
    int queue[MAX_USERS];
    int front = 0, rear = 0;

    visited[user] = true;
    queue[rear++] = user;

    while (front < rear) {
        int currentUser = queue[front++];
        Node* friendNode = friends[currentUser].head;

        while (friendNode != nullptr) {
            int friendID = friendNode->userID;
            if (!visited[friendID]) {
                mutualCount[friendID]++;
                visited[friendID] = true;
                queue[rear++] = friendID;
            }
            friendNode = friendNode->next;
        }
    }

    std::cout << "Suggested friends for User " << user << " using BFS: ";
    for (int i = 0; i < MAX_USERS; i++) {
        if (mutualCount[i] > 1 && !friends[user].contains(i)) {
            cout << i << " (mutual friends: " << mutualCount[i] << ") ";
        }
    }
    cout << "\n";
}

// Helper function for DFS suggestion
void FriendSystem::dfs(int user, bool visited[], int mutualCount[]) {
    visited[user] = true;

    Node* friendNode = friends[user].head;
    while (friendNode != nullptr) {
        int friendID = friendNode->userID;
        if (!visited[friendID]) {
            mutualCount[friendID]++;
            dfs(friendID, visited, mutualCount);
        }
        friendNode = friendNode->next;
    }
}

// Suggest friends using DFS
void FriendSystem::suggestFriendsDFS(int user) {
    int mutualCount[MAX_USERS] = {0};
    bool visited[MAX_USERS] = {false};

    dfs(user, visited, mutualCount);

    cout << "Suggested friends for User " << user << " using DFS: ";
    for (int i = 0; i < MAX_USERS; i++) {
        if (mutualCount[i] > 1 && !friends[user].contains(i)) {
            cout << i << " (mutual friends: " << mutualCount[i] << ") ";
        }
    }
    std::cout << "\n";
}

// Remove a friend
void FriendSystem::removeFriend(int user1, int user2) {
    friends[user1].remove(user2);
    friends[user2].remove(user1);
    cout << "User " << user1 << " and User " << user2 << " are no longer friends.\n";
}

// Display mutual friends count between two users
void FriendSystem::mutualFriendsCount(int user1, int user2) {
    int count = 0;
    Node* friendNode1 = friends[user1].head;

    while (friendNode1 != nullptr) {
        if (friends[user2].contains(friendNode1->userID)) {
            count++;
        }
        friendNode1 = friendNode1->next;
    }

    cout << "Mutual friends between User " << user1 << " and User " << user2 << ": " << count << "\n";
}

int main() {
    FriendSystem fs;

    fs.sendFriendRequest(1, 2);
    fs.sendFriendRequest(2, 3);
    fs.sendFriendRequest(1, 3);

    fs.acceptFriendRequestsBatch(2);
    fs.acceptFriendRequestsBatch(3);

    fs.displayFriends(1);
    fs.displayFriends(2);
    fs.displayPendingRequests(3);

    fs.suggestFriendsBFS(1); // Suggest friends for User 1 using BFS
    fs.suggestFriendsDFS(1); // Suggest friends for User 1 using DFS

    fs.removeFriend(1, 2);
    fs.displayFriends(1);
    fs.displayFriends(2);

    fs.mutualFriendsCount(1, 3);

    return 0;
}

