//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
#include "graph.h"

Graph::Graph(){
    //Default constructor creates an empty object and initializes member variables.
    m_numNodes = 0;
    m_head = nullptr; 
    m_dataFile = " ";
}

Graph::Graph(string dataFile){
    //Alternative constructor creates a graph using the information in dataFile. You can call the function loadData() here.
    m_dataFile = dataFile;
    clearGraph();
    loadData();
}

Graph::~Graph(){
    //Destructor deallocate all memory and reinitialize member variables.
    m_numNodes = 0;
    m_dataFile = " ";
    Node * prev = m_head;
    Node * next = m_head;
    while(next != nullptr) {
      prev = next;
      next = next->m_next;
      delete prev;
    }
    m_head = nullptr;
}

void Graph::loadData(){
    int numNodes;
    int node, n, e, s, w; 
    ifstream dataFile;
    dataFile.open(m_dataFile);
    if (dataFile.is_open()) {
        dataFile >> numNodes;
        m_numNodes = numNodes;
        for (int i = 0; i < numNodes; i++) {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open
        //please note: not all platforms are providing the same message
        cerr << "Error: " << strerror(errno) << endl;
}

void Graph::insert(int node, int n, int e, int s, int w){
    // This function creates nodes and insert them into the linked list. 
    // The node parameter presents the value for the node to be inserted. 
    // Moreover, it uses the parameters n, e, s, and w to initialize the required fields of the node. 
    // Every node we read from data file is inserted only once in the linked list. 
    // Then, if a node is already in the list, we only update its member variables using the information. Here is a sample algorithm:
    // 1. Read the line “0 -1 1 -1 -1”, the node with 0 value is not in the list.
    // 2. Allocate memory for the node, and set its value. Since the node to its north is -1, then there is no need to initialize its m_north variable to a pointer, it should be only initialized to nullPtr.
    // 3. The east pointer of node 0 points to the node 1. There is no node 1 in the list. Allocate memory and insert it into the list.
    // 4. Initialize the m_east member variable of the node 0 with the pointer for node 1. And continue processing the information for node 0.
    // 5. At next line of data file, read “1 -1 -1 2 -1”. Node 1 is already inserted into the list. Then, its information should be processed. The member variables m_north and m_east are initialized to nullPtr.
    // 6. The south pointer of node 1 should point to node 2. If the node 2 is not in the list, create it and insert it. Then, initialize the m_south member variable of node 1 to the pointer for node 2.
    // 7. Continue the insertion process through the end of information in the data file.


  //test for deplicates
    if(findNode(node) == nullptr) {
      Node * aNode = new Node(node);
      //cout << "Node " << node << " " << aNode << endl;

      //Since the value north is -1, it should be only initialized to nullPtr.
      if(n == -1) {
        aNode->m_north = nullptr;
      } else {
        //if the n has a value and the node is NOT in the listit will initialize m_north, set it as aNode's north and then set as aNode's set. 
        if(findNode(n) == nullptr) {
          aNode->m_north = new Node(n);
          aNode->setNorth(aNode->m_north);
          aNode->setNext(aNode->m_north);
          insertAtHead(aNode->m_north);
        } else {
            // if n is already in the list, just set it as aNode's north, but use findNOde to make sure its the right node
            if(n != -1) {
              aNode->setNorth(findNode(n));
            }
	        }
        }

      if(e == -1) {
	      aNode->m_east = nullptr;
      } else {
          if(findNode(e) == nullptr) {
            aNode->m_east = new Node(e);
            aNode->setEast(aNode->m_east);
            aNode->setNext(aNode->m_east);
            insertAtHead(aNode->m_east);
          } else {
              if(e != -1) {
                aNode->setEast(findNode(e));
              }
            }
        } 
      
      if(s == -1) {
	      aNode->m_south = nullptr;
      } else {
        if(findNode(s) == nullptr) {
          aNode->m_south = new Node(s);
          aNode->setSouth(aNode->m_south);
          aNode->setNext(aNode->m_south);
          insertAtHead(aNode->m_south);
	        } else {
              if(s != -1) {
                aNode->setSouth(findNode(s));
              }
        }
      }
      
      if(w == -1) {
	      aNode->m_west = nullptr;
      } else {
          if(findNode(w) == nullptr) {
            aNode->m_west = new Node(w);
            aNode->setWest(aNode->m_west);
            aNode->setNext(aNode->m_west);
            insertAtHead(aNode->m_west);
        } else {
            if(w != -1) {
              aNode->setWest(findNode(w));
            }
        }
      }
      //after everything as been gathered, insert it at the head
      insertAtHead(aNode);
    } else {

      //if north has a value and north's node is already IN the listm then just set the current node's north to the returned node of the value
      if(n != -1) {
        if(findNode(n) != nullptr) {
          findNode(node)->m_north = findNode(n);
        } else {
          //if north is NOT in the list, add it as the node's north
          findNode(node)->m_east = new Node(e); ///????
          insertAtHead(findNode(node)->m_east);
        } 
      } else {
        // if n = -1, set it to nullptr
        findNode(node)->m_north = nullptr;
      }

      if(e != -1) {
        if(findNode(e) != nullptr) {
          findNode(node)->m_east = findNode(e);
        } else {
          findNode(node)->m_east = new Node(e); 
          insertAtHead(findNode(node)->m_east);
        }
      } else {
        findNode(node)->m_east = nullptr;
      }

      if(s != -1) {
        if(findNode(s) != nullptr) {
          findNode(node)->m_south = findNode(s);
        } else {
          findNode(node)->m_south = new Node(s); 
          insertAtHead(findNode(node)->m_south);
        }
      } else {
        findNode(node)->m_south = nullptr;
      }

      if(w != -1) {
        if(findNode(w) != nullptr) {
          findNode(node)->m_west = findNode(w);
        } else {
          findNode(node)->m_west = new Node(w); 
          insertAtHead(findNode(node)->m_west);
        }
      } else {
        findNode(node)->m_west = nullptr;
      }
      
    }
}

void Graph::insertAtHead(Node * aNode){
    //This function insertes aNode at the head of linked list and updates the required pointers to maintain the linked list. 
    //This can be called by the insert function whenever there is a need to insert a new node.

  if(m_head == nullptr) {
    m_head = aNode;
    aNode->m_next = nullptr;
  } else {
    Node * temp = m_head;
    m_head = aNode;
    aNode->m_next = temp;
  }

}


Node * Graph::findNode(int nodeValue){
    //if it finds the node, if it doesnt
    //traverse linked list based of node value and try to find the node, if it finds it returns the node pointer
    //This function traverse the linked list to find the node having nodeValue. 
    //If it finds the node it returns the pointer to the node, otherwise it returns nullPtr.
    
  Node * temp = m_head;
  while(temp != nullptr) {
    if(temp->m_value == nodeValue) {
      return temp;
    } else {
      temp = temp->m_next;
    }
  }
  
  return nullptr;
}

bool Graph::findPath(int start, int end){
  //This public function is the interface to the class. 
  //The user calls this function to find a path from the start node to the end node. 
  //The path will be stored in the member variable m_path. 
  //For finding every new path the information about previous path such as visited nodes or m_path should be cleared.
  //cout << endl << "in find path with ints" << endl;
  clearVisited();
  clearResult();

  //if the start or end nodes arent in the list, return false
  if(findNode(start) == nullptr || findNode(end) == nullptr) {
    return false;
  } 

  //set a temp node to the start node, mark it as visited; if its already the end value just push it, otherwise send it into findPath(node, int)
  Node * temp = findNode(start);
  temp->m_visited = true;

  if(temp->m_value == end) {
    m_path.push(temp->m_value);
    return true;
  } else {
    if(findPath(temp, end)) {
      if(temp->m_visited == true) {
        return true;
      } else {
        findPath(temp, end);
      }
    } else {
      return false;
    }
  }

}

bool Graph::findPath(Node* aNode, int end){
    //This private function is a helper that can be used recursively to traverse the nodes. 
    //Originally it can be called on the pointer to the start node. 
    //Once in a node, it tags the node as visited, then it tries all possible connections, and so on. 
    //If it reaches a visited node, it backtracks. Backtrack means the function returns from that node with false return value. 
    //The reasons for backtracking are to avoid dead ends or loops. 
    //If the current node is newly visited, the function can record the nodes in the m_path variable and moves on. 
    //The sample algorithm provided above shows how the traversal can work.

  //mark node as visited
  aNode->m_visited = true;
  

  // //first base case: find path and return. If you've added the end node to the list
  if(aNode->m_value == end) {
    m_path.push(aNode->m_value);
    return true;
  } else {
    //if the nodes direction has a value, and it hasnt veen visited yet, check if it has a path, if it does, push the value and return true
    if(aNode->m_north != nullptr && aNode->m_north->m_visited == false) {
      if(findPath(aNode->m_north, end)) {
        m_path.push(aNode->m_value);
        return true;
      }
    }

    if(aNode->m_east != nullptr && aNode->m_east->m_visited == false) {
      if(findPath(aNode->m_east, end)) {
        m_path.push(aNode->m_value);
        return true;
      }
    }

    if(aNode->m_south != nullptr && aNode->m_south->m_visited == false) {
      if(findPath(aNode->m_south, end)) {
        m_path.push(aNode->m_value);
        return true;
      }
    }

    if(aNode->m_west != nullptr && aNode->m_west->m_visited == false) {
      if(findPath(aNode->m_west, end)) {
        m_path.push(aNode->m_value);
        return true;
      }
    } return false;
  }

}

void Graph::dump(){
    //This function prints out the path to the output in a specific format. The format of the output is presented in the sample output.
 
  int n = 0;
  while(!m_path.empty()) {
    //while the path stack isnt empty, make n its top, print n and then pop the number so that it moves on
      n = m_path.top();
      cout << n << " => ";
      m_path.pop();
  }
  cout << "END" << endl;
    
}

void Graph::clearResult(){
    //This function clears the path found.
    while(!m_path.empty()) {
        m_path.pop();
    }
}

void Graph::clearVisited(){
    //This function resets the visited flag for all Node objects. It sets m_visited to false;
    // maybe traverse through he list and see all the node m_visted to false
  Node * temp = m_head;
  while(temp != nullptr) {
      temp->m_visited = false;
      temp = temp->m_next;
  }
}

void Graph::buildGraph(string file){
    //This function builds a new graph using the information in file.
  if(file == " ") {
    throw std::out_of_range("EMPTY FILE");
  } else {
    Graph aGraph(file);
  }
}

void Graph::clearGraph(){
    //This function deallocates all memory and reinitializes all member variables. It makes the object an empty one.
  m_numNodes = 0;
  m_head = nullptr;
}

const Graph & Graph::operator=(const Graph & rhs) {
    //The assignment operator, creates a deep copy of rhs. 
    //Reminder: a deep copy means the current object has the same information as rhs object, however, it has its own memory allocated. 
    //Moreover, an assignment operator needs protection against self-assignment.
    
  if(this != &rhs) {
      delete m_head;
      Node * temp = m_head;
      Node * rhsTemp = rhs.m_head;
      while(temp != nullptr) {
        if(temp->m_north != nullptr) {
          temp->m_north = rhsTemp->m_north;
        }
      
        if(temp->m_east != nullptr) {
          temp->m_east = rhsTemp->m_east;
        }
        
        if(temp->m_south != nullptr) {
          temp->m_south = rhsTemp->m_south;
        }
        
        if(temp->m_west != nullptr) {
          temp->m_west = rhsTemp->m_west;
        }
      }
      m_path = rhs.m_path;
  }
  m_numNodes = rhs.m_numNodes;
  return *this;
}

bool Graph::empty() const		// is the list empty?
    { return m_head == nullptr; }
