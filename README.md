# College Connect - A C++ Social Media Platform

**[Repository Link](https://github.com/SwayamGupta12345/CollegeConnect_in_cpp)**

"College Connect" is a robust and interactive social media platform designed for college students, implemented in **C++**. This project demonstrates advanced applications of **data structures** like graphs, hash tables, linked lists, and priority queues. Developed as a **third-semester Data Structures project**, it highlights functionalities such as **user management, community interactions, friend systems, messaging**, and **group management**.

---

## Features

### 1. User Management
- **Registration & Authentication**: Secure login system using **hash tables** for efficient user verification.
- **Profile Management**: Editable profiles stored in a **linked list**, enabling quick updates without performance trade-offs.

### 2. Community Interaction
- **Post Management**: 
  - Create, edit, and view text-based posts stored in **linked lists** or **dynamic arrays**.
  - Threaded discussions with voting mechanisms for replies and posts.
- **Trending Topics**: Tracks and highlights popular posts based on user engagement using a **priority queue**.
- **Threaded Discussions**: Users can engage in meaningful conversations by commenting and replying to posts.

### 3. Friend System
- **Friendship Management**: Represented as a **graph** with users as nodes and friendships as edges.
- **Friend Suggestions**: Utilizes **BFS/DFS algorithms** to suggest connections based on mutual friends.
- **Mutual Friends Count**: Displays shared connections for better networking.
- **Pending Requests**: Manage and view pending friend requests in a **queue**.

### 4. Messaging System
- **Direct Messaging**: Queue-based structure for private message handling.
- **Group Messaging**:
  - Groups created among friends for shared interactions.
  - Dictionary-like structures to manage groups and their members.
- **Chat History**: Doubly linked lists for browsing past conversations.

### 5. Group Management
- **Create and Join Groups**: Users can create and join groups for collaboration and discussions.
- **Group Conversations**: Interactive messaging systems extend to group chats, ensuring a seamless experience.

---

## Advanced Data Structures Used
- **Graphs**: Representing relationships and performing traversal algorithms for suggestions and insights.
- **Hash Tables**: Efficiently storing and retrieving user data for authentication.
- **Queues**: Managing friend requests and messaging in order.
- **Linked Lists**: Handling dynamic data such as posts and message histories.
- **Priority Queues**: Highlighting trending topics based on engagement metrics.

---

## Getting Started

### Prerequisites
- A C++ compiler (e.g., GCC, Clang)
- Basic knowledge of graph traversal and file handling

### Installation
1. **Clone the Repository**  
   ```bash
   git clone https://github.com/SwayamGupta12345/CollegeConnect_in_cpp.git
   cd CollegeConnect_in_cpp
   ```

2. **Compile the Program**  
   ```bash
   g++ -o college_connect SocialMediaPlatform.cpp
   ```

3. **Run the Platform**  
   ```bash
   ./college_connect
   ```

---

## Usage

### Initial Setup
- Use the provided `sample-data.txt` file to pre-load the system with default users, posts, and relationships.
- Customize or prepare your own data file as per the format for personalized testing.

### Interaction Workflow
1. **Login Credentials**:  
   - **Username**: `student01`  
   - **Password**: `connect123`
2. **Explore Modules**:  
   - Register, login, and manage your profile.  
   - Create, interact with, and explore posts.  
   - Send friend requests, view suggestions, and manage connections.  
   - Participate in private or group messaging.

---

## File Structure
- **SocialMediaPlatform.cpp**: Core program logic and entry point.
- **SocialMediaPlatformHeader.h**: Modular header files defining classes and functionalities.
- **sample-data.txt**: Example data for testing the platform.
- **README.md**: Documentation for understanding and navigating the project.

---

## Customization
- Modify `sample-data.txt` to include new users, posts, and relationships for testing purposes.
- Extend or tweak algorithms in the provided `.cpp` files to enhance platform functionality.

---

## Troubleshooting
- **Login Issues**: Ensure the credentials are correct and case-sensitive.
- **Data Loading Errors**: Validate the structure of your custom data file.
- **Group Management Errors**: Ensure the user creating a group is a registered and authenticated user.

---

## Contact
For queries, suggestions, or contributions, reach out at **[swayamsam2005@gmail.com](mailto:swayamsam2005@gmail.com)**.
