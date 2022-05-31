//**********************************************************************************
//
// Name: Julia Maddock
// Course: CS 3610
// Date (Y/M/D): 22 05 13
// Description: Project 4 - Quick Sort
//                        - Read unsorted list of ints into nxm matrix
//                        - Individually sort each sublist w/ Quick Sort
//                        - Implement a partition function
//                        - Pivot is set to median of 1st, middle, and last elem.
//                          of sublist
//                        -Implement merge function to merge sorted sublists
//                     
//**********************************************************************************

#include <iostream>
#include <vector>
#include <algorithm>
//#include <string_view>
#include <string>
#include <cmath>
#include <functional>
#include <queue>

#include <fstream>


using namespace std;


struct heapNode{
	int value = 0;
	int ID = 0;
};
  
class queueNode {
public :
  queueNode(){}
  priority_queue<int> q;
  vector<heapNode> qnodes;

  void print(){
    for(int i = 0; i < qnodes.size(); i++){
      cout<<"ID: "<<this->qnodes[i].ID<<endl;
      cout<<"VALUE: "<<this->qnodes[i].value<<endl;
    }
  }

  int linkNext(){
    vector<heapNode> temp = this->qnodes;
    temp.pop_back();
    return temp.back().ID;
  }

  void removeBack(){
    priority_queue<int> tempq;
    int SIZE = this->q.size() - 1;
    for(int i = 0; i < SIZE; i++){
      tempq.push(this->q.top());
      this->q.pop();
    }
    this->q = tempq;
    this->qnodes.pop_back();
  }

  void push(const heapNode &hn){

    this->q.push(hn.value);
    vector<heapNode> temp;
    temp.resize(q.size());
    priority_queue<int> tempq = q;

    int SIZE = q.size();
    
    for(int i = 0; i < SIZE; i++){
      temp[i].value = q.top();
      q.pop();
    }

    q = tempq;
    
    if(qnodes.size() > 0){
      for(int i = 0; i < q.size(); i++){
        for(int j = 0; j < q.size(); j++){
          if(qnodes[i].value == temp[j].value)
            temp[j].ID = this->qnodes[i].ID;
        }
      }
    }
  this->qnodes = temp;
  }
};


void print (string text, vector<int> const& v = {})
{

//    cout << text << ": ";
    for (const auto& e : v) cout << e << ' ';
//    cout << '\n';

}


//PARTITION FUNCTION

int partition(vector<int>& list, int first, int last) {
  // The pivot should be the median of the
  // first, middle, and last elements.
  // cout << "\nIt calls partition" << "\n";
  
  int middle = (first + last) / 2; //stores value of middle element
  int smallIndex = first; //initializes smallIndex var. as first element in subarray
  
  // cout << "  Initial smallIndex -> " << "loc: " << smallIndex << " [" << list[smallIndex] << "]\n";
  // cout << "\n  Partition Procedure: ";
  // partition procedure
  //Find median of first, middle, and last elem.s.
  if((list[first] < list[middle]) && (list[middle] < list[last]))
  {
     swap(list[first], list[middle]); //swap middle with first
//     cout << "middle swapped with first" << "\n";
  }
  else if ((list[first] < list[middle]) && (list[middle] > list[last]))
  {
    swap(list[first], list[last]); //swap last with first
//    cout << "last swapped with first" << "\n";
  }
  else if ((list[first] > list[middle]) && (list[middle] > list[last]))
  {
    swap(list[first], list[middle]); //swap middle with first
//    cout << "middle swapped with first 2nd" << "\n";
  }
  else
  {
     if(list[first] > list[last]) //last is pivot
     {
       swap(list[first], list[last]);
     }
     else
     {
       //do nothing b/c first is pivot
     }
  }  //close if/else series
  
  //set pivot
  int pivot = list[first];
  
  // cout << "\n" << "  Pivot is: " << pivot << "\n\n"; //check that pivot is chosen correctly
  // cout << "  first -> " << first << " [" << list[first] << "]\n\n";
  
  for(int index = first + 1; index <= last; index++){ //move to next
  
  // cout << "\nFor Loop: " << "\n\n";
  // cout << "  Index -> " << index << " [" << list[index] << "] \n\n";
 
      if (list[index] < pivot) //Case 2
      {
          // cout << "  If statement: \n\n";
          // cout << "    Small Index -> " << smallIndex << " [" << list[smallIndex] << "]\n\n";
          // cout << "    Small Index increments\n";
          
          smallIndex++; //smallIndex moves over 1 to encompass index into smaller list
          
          // cout << "    Small Index -> " << smallIndex << " [" << list[smallIndex] << "]\n";
          // cout << "    Index -> " << index << " [" << list[index] << "]\n\n";
          // cout << "   smallIndex value swaps with index value\n\n";
          
          swap(list[smallIndex], list[index]); //throws index in front of smallIndex
          
          // cout << "    Small Index -> " << smallIndex << " [" << list[smallIndex] << "]\n";
          // cout << "    Index -> "<< index << " [" << list[index] << "]\n";
      }                            //so that smallIndex last spot in smaller list
       
  } //close for loop
  
  swap(list[first], list[smallIndex]); //settle pivot; smallIndex now @ front of smaller list
  
  //PRINT PARTITIONED SUBARRAY, TO CHECK IF CORRECT
  //cout << "\nLIST: ";
  
  for(int j = 0; j < list.size(); j++)
       {
         //cout << list[j] << " ";
       }
       //cout << "\n";
       
  //PRINT smallIndex TO MAKE SURE IT RETURNS CORRECT PIVOT LOCATION     
  //cout << "\nsmallIndex: " << smallIndex << " [" << list[smallIndex] << "] \n";
  
  return smallIndex;  //returns pivot location of recently partitioned sublist
  
} //CLOSE PARTITION FUNCTION


void quicksort(vector<int>& list, int first, int last) {
//cout << "\nIt calls quicksort" << "\n";

  int pLoc;
  
  if(first == last) return;
  else if (first < last)
  {
//    cout << "\n\n FIRST < LAST \n\n";
    int pLoc = partition(list, first, last);
    quicksort(list, first, pLoc - 1);
    quicksort(list, pLoc + 1, last);
    
  }//close else if
  else 
  {
//    cout << "Thar be no list here, matey!";
  }
  
//  cout << "\n QUICKSORT LIST: ";
    
    for(int k = 0; k < list.size(); k++)
    {
//      cout << list[k] << " ";
    }
//    cout << "\n";
    
} //close quicksort func.


void multiway_merge( //merge sorted sublists into single output list
  vector<vector<int> >& input_lists, vector<int>& output_list
) 
{
  int SIZE = input_lists.size();
  int SIZE_ROW = input_lists[0].size();

  cout<<"size: "<<SIZE<<endl;
  cout<<"size row: "<<SIZE_ROW<<endl;

	queueNode bufferList;
  bufferList.qnodes.resize(SIZE);

  // for(int i = 0; i < SIZE; i++){
  //   for(int j = 0; j < input_lists[i].size(); j++){
  //     cout<<"list stuff:"<<input_lists[i][j]<<endl;
  //   }
  // }

  for(int i = 0; i < SIZE; i++){
    heapNode temp;
    temp.ID = i;
    temp.value = input_lists[i][0];
    input_lists[i].erase(input_lists[i].begin());
    bufferList.qnodes.push_back(temp);
    bufferList.push(temp);
  }
  int i;
  for(i = (SIZE * SIZE_ROW) - 1 ; i > -1; i--){

    output_list[i] = bufferList.qnodes.back().value;
    heapNode temp;
    temp.ID = bufferList.qnodes.back().ID;
    bufferList.removeBack();

    if(input_lists[temp.ID].size() == 1){
      cout<<"weee: "<<endl;
      temp.value = input_lists[temp.ID][0];
      input_lists[temp.ID].erase(input_lists[temp.ID].begin());
      temp.ID = bufferList.linkNext();
      bufferList.qnodes.push_back(temp);
      bufferList.push(temp);
      

    }else if(input_lists[temp.ID].size() == 0){
      i--;
      output_list[i] = bufferList.qnodes.back().value;
      bufferList.removeBack();
    }else{
      cout<<"weee2: "<<endl;
      temp.value = input_lists[temp.ID][0];
      bufferList.qnodes.push_back(temp);
      bufferList.push(temp);
      input_lists[temp.ID].erase(input_lists[temp.ID].begin());

    }
  }
  output_list[0] = bufferList.q.top();

  //bufferList.print();
} //close multiway_merge func.

int main(int argc, char** argv) {
  int n, m; //n = # of unordered sublists, m = # of elems per sublist

  ifstream myfile;
  myfile.open ("input2.dat");
  myfile >> n >> m;
  // while(!myfile.eof()){

  // }

  vector<vector<int> > input_lists(n, vector<int>(m)); //creates 2D vector input_lists of size n
                                                       //elems. are of size m
  for (int i = 0; i < n; ++i) { //generate ID for each sublist
    for (int j = 0; j < m; ++j) { //read input values into elements of each sublist
      myfile >> input_lists[i][j]; //read in completed matrix
    }
  }
  myfile.close();
  
  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list;
  output_list.resize(n*m);

  // for(int i = 0; i < n; i++)
  //   for(int j = 0; j < m; j++)
  //     cout<<"list "<<i<<" "<<input_lists[i][j]<<endl;

  multiway_merge(input_lists, output_list);
     

  for (int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
  cout << endl;

  return 1;
}
