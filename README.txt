============================ SocialNet Simulator ==========================================================
Author → Saurabh Pandey
Entry No. → 2024EE30043
Course → COL106

1. Project Overview:
    * This project implements a simplified command-line Social Network Simulator called SocialNet.
    * It allows users to create accounts, add friends, post updates, and explore their network — all through a set of textual commands.
    * The program is built entirely from scratch using Graphs and AVL Trees, without relying on any C++ STL implementations of these data structures.
    * It demonstrates how efficient search, traversal, and relationship modeling can be achieved using fundamental data structures.
2. Features:
    * User Management: Add users and connect them as friends (bidirectional).
    * Post Management: Create and retrieve posts efficiently using AVL Trees.
    * Friendship Graph: Represent and navigate social connections using adjacency lists.
    * Analytics:
        * Suggest friends based on mutual connections.
        * Calculate degrees of separation between users.
        * Retrieve recent posts in reverse chronological order.
    * Case Insensitivity: All usernames and content are treated case-insensitively.
3. Project Structure:
    * main.cpp               # Contains the entry point (main function)
    * social_network.hpp     # Implements all logic (AVL Tree, Graph, Command Processor)
    * compile.sh             # Shell script to compile and run the program (Linux/macOS)
    * run.bat                # Batch script to compile and run the program (Windows)
    * ReadMe.txt             # Documentation (this file)
4. Compilation Instructions:
    4.1. Windows:
        * Open Command Prompt or PowerShell.
        * Navigate to the project directory:
            cd path\to\project
        * Run the provided batch script:
            .\run.bat
    4.2. Linux/macOS:
        * Open Terminal.
        * Navigate to the project directory:
            cd path/to/project
        * Make the shell script executable (only once):
            chmod +x compile.sh
        * Run the script:
            ./compile.sh
* If compilation is successful, an executable named socialnet will be created and launched automatically.
* If it fails, an appropriate error message will be displayed.
5. Running the Program:
    * When executed, the program initializes the simulator and waits for user input.
    * Example startup message:
        ****** SocialNet Simulator ******
        Enter commands: (Type EXIT to quit.)
        >

    * Type commands directly into the terminal.
    * The program runs interactively until you type:
        EXIT
6. Command Reference:
    6.1. Core Social Network Operations:
                Command	                            	                Description
        * ADD_USER <username>	                        |    Adds a new user to the network.
        * ADD_FRIEND <username1> <username2>	        |    Creates a bidirectional friendship between two users.
        * LIST_FRIENDS <username>             	        |    Lists all friends of the user in alphabetical order.
        * SUGGEST_FRIENDS <username> <N>	            |    Suggests up to N new friends based on mutual friends.
        * DEGREES_OF_SEPARATION <username1> <username2> |	 Calculates the minimum number of friendship links separating two users.
    6.2. User Content Operations:
                Command	 	                                            Description
        * ADD_POST <username> "<post content>"	        |    Adds a new post for the specified user.
     	* OUTPUT_POSTS <username> <N>	                |    Prints the N most recent posts (or all if N = -1).
    * NOTE:
        * All usernames and content are case-insensitive.
        * If N is -1, the system displays all posts by the user.
        * If N is greater than available posts, all existing posts are displayed.
7. Error Handling:
            Condition	                                                Output
    * Adding an existing user	                  |     User '<username>' already added.
    * Adding friend for a non-existent user	      |     User '<username>' does not exist added.
    * Listing friends for a non-existent user	  |     User '<username>' does not exist.
    * Adding post for a non-existent user	      |     User '<username>' does not exist added.
    * Requesting posts for a non-existent user	  |     User '<username>' does not exist added.
    * Suggesting friends for non-existent user	  |     User '<username>' doesnot exist.
    * No mutual friends found	                  |     No suggested friends
    * Missing command arguments	                  |     Prints usage help (e.g., "Usage: ADD_USER <user_name>")
    * Unknown command	                          |     Displays available command list
    * Self-friendships                            |     Can not add self as friend
    * Adding friends if they are already friends  |     '<username1>' and '<username1>' are already friends.
8. Example Interaction:
    > ADD_USER Alice
    User 'alice' added successfully.
    > ADD_USER Bob
    User 'bob' added successfully.
    > ADD_FRIEND Alice Bob
    'alice' and 'bob' are added as friends
    > LIST_FRIENDS Alice
    Friends of 'alice' :
    bob
    > ADD_POST Alice "Hello world!"
    Post added successfully
    > OUTPUT_POSTS Alice 1
    Recent Posts of User 'alice'  :-
    hello world!
    > DEGREES_OF_SEPERATION Alice Bob
    1
    > SUGGEST_FRIENDS Alice 3
    No suggested friends
    > EXIT
9. Data Structures Used:
        Data Structure	                                Purpose
    * AVL Tree (AvlTree)	       |    Stores posts of each user sorted by timestamp. Provides efficient insertion and retrieval (O(log n)).
    * Graph (Adjacency List)	   |    Represents users and friendships. Supports BFS for degree calculations.
    * Hash Maps (unordered_map)	   |    Maps usernames to friend lists and AVL trees.
    * Queues and Sets	           |    Used for BFS traversal and visited node tracking.
10. Future Improvements:
    * Support user deletion and unfriend operations.
    * Extend posts to include timestamps and IDs for richer analytics.
    * Introduce “News Feed” combining friends’ posts.
    * Improve command parser for multi-word usernames and content with quotes.
11. Conclusion:
    * The SocialNet Simulator demonstrates how fundamental data structures — AVL Trees and Graphs — can be combined to simulate the backend of a real-world social network.
    * It handles users, friendships, and posts efficiently, while providing analytical features such as friend suggestions and degree-of-separation queries.
    * This project highlights the practical application of data structures and algorithms in building scalable, real-world systems from scratch.