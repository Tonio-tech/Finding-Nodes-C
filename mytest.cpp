//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
#include "graph.h"

class Tester{ // Tester class to implement test functions
    public:
    void testBuildGraph();
    void testEmptyGraph();
    bool testFindPath1();
    bool testFindPath2();
    bool testFindPath3();
    bool testFindPath4();
    bool testFindPath5();
    void testAssignOp(); 
    
};

int main(){

    Graph aGraph("testdata.txt");    
    aGraph.findPath(0,5);
    cout << "Finding the path from node 0 to node 5: " << endl;
    aGraph.dump();
    
    aGraph.findPath(2,2);
    cout << "Finding the path from node 2 to itself: " << endl;
    aGraph.dump();
    aGraph.findPath(4,0);
    cout << "Finding the path from node 4 to node 0: " << endl;
    aGraph.dump();
    
    Graph bGraph;
    bGraph.findPath(1,14);
    cout << "Finding the path from node 1 to node 14 in an empty Graph object: " << endl;
    bGraph.dump();

    cout << endl << "TESTER CLASS TESTS STARTING: " << endl << endl;
    Tester tester1;
    Tester tester2;
    Tester tester3;
    Tester tester4;
    Tester tester5;
    Tester tester6;
    Tester tester7;
    Tester tester8;

    //test build graph 
    tester6.testBuildGraph();

    //test empty graph 
    tester7.testEmptyGraph();

    //test find path
    tester1.testFindPath1();
    tester2.testFindPath2();
    tester3.testFindPath3();
    tester4.testFindPath4();
    tester5.testFindPath5();

    //test assignment operator
    tester8.testAssignOp();
    
    return 0;
}

void Tester::testBuildGraph() {
  // Test building a graph by the alternative constructor for a normal case
  cout << "TESTING BUILD GRAPH" << endl;
  Graph bGraph("testdata.txt");
  bGraph.buildGraph("testdata.txt");
  cout << "TEST BUILD GRAPH COMPLETE" << endl << endl;
}

void Tester::testEmptyGraph() {
  // Test creating an empty graph object
  // Test building a graph in an empty Graph object.  
  cout << "TESTING EMPTY GRAPH" << endl;
  Graph cGraph;   
  cGraph.buildGraph("testdata.txt");
  cout << "TESTING EMPTY GRAPH COMPLETE" << endl << endl;
}

bool Tester::testFindPath1() {
  //Test finding a path which does not exist in the graph.
  //return true if findPath return true, return false otherwise
  Graph dGraph("testdata.txt");
  cout << "Test finding a path which does not exist in the graph." << endl;
  if(dGraph.findPath(3, 4)) {
    dGraph.dump();
    cout << "Success" << endl;
    return true;
  } else {
    dGraph.dump();
    cout << "Failed" << endl;
    return false;
  }
}

bool Tester::testFindPath2() {
  //Test finding a path which exists in the graph.
  Graph dGraph("testdata.txt");
  cout << "Test finding a path which exists in the graph." << endl;
  if(dGraph.findPath(6, 13)) { 
    dGraph.dump();
    cout << "Success" << endl;
    return true;
  } else {
    dGraph.dump();
    cout << "Failed" << endl;
    return false;
  }
}

bool Tester::testFindPath3() {
  //Test finding a path from a node to itself.
  Graph dGraph("testdata.txt");
  cout << "Test finding a path from a node to itself." << endl;
  if(dGraph.findPath(7, 7)) {
    dGraph.dump();
    cout << "Success" << endl;
    return true;
  } else {
    dGraph.dump();
    cout << "Failed" << endl;
    return false;
  }
}

bool Tester::testFindPath4() {
  //Test finding a path in which the start node does not exist.
  Graph dGraph("testdata.txt");
  cout << "Test finding a path in which the start node does not exist." << endl;
  if(dGraph.findPath(-1, 10)) {
    dGraph.dump();
    cout << "Success" << endl;
    return true;
  } else {
    dGraph.dump();
    cout << "Failed" << endl;
    return false;
  }
}

bool Tester::testFindPath5() {
  //Test finding a path in which the end node does not exist
  Graph dGraph("testdata.txt");
  cout << "Test finding a path in which the end node does not exist." << endl;
  if(dGraph.findPath(11, 17)) {
    dGraph.dump();
    cout << "Success" << endl;
    return true;
  } else {
    dGraph.dump();
    cout << "Failed" << endl;
    return false;
  }
    
}

void Tester::testAssignOp() {
  // Test Graph class assignment operator for a normal case and an empty graph object.    
    //Your test should check whether a deep copy is created. There are two ways of doing this. 
    //You can compare the list pointers, they should not match. 
    //Then, you compare all values in the corresponding nodes, all values should match. 
    //Another way of checking on deep copy is to clear the rhs object, and check whether the current object contains data. 
    //Either way is acceptable.
  cout << endl << "TESTING ASSIGNMENT OPERATOR " << endl;
  Graph aGraph("testdata.txt");
  Graph copyGraph = aGraph;
  
  aGraph.clearGraph();

  cout << "CopyGraph numNodes: " << copyGraph.m_numNodes << endl;

  Node * temp = copyGraph.m_head;
  while(temp != nullptr) {
    cout << "Node " << temp ->m_value << " " << endl;

      if(temp->m_north != nullptr) {
        cout << "temp m_north value of " << temp->m_north->m_value << endl;
      }
      
      if(temp->m_east != nullptr) {
        cout << "temp m_east value of " << temp->m_east->m_value << endl;
      }
      
      if(temp->m_south != nullptr) {
        cout << "temp m_south value of " << temp->m_south->m_value << endl;
      }
      
      if(temp->m_west != nullptr) {
        cout << "temp m_west value of " << temp->m_west->m_value << endl;
      }
      temp = temp->m_next;
  }
  
    
}
