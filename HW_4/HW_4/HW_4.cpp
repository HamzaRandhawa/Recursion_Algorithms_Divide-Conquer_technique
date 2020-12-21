#include "pch.h"
#include <iostream>
#include <vector>
#include <Math.h>

using namespace std;

void Print(vector<int> V)
{
	for (int i = 0; i < V.size(); i++)
	{ 
		cout << V[i] << "\n";
	}
}

// 1.1
void Merge(vector<int> &C,const vector<int> &A,const vector<int> &B)
{
	int as = A.size(), bs = B.size();
	int cs = as + bs;

	int ai = 0, bi = 0, ci = 0;

	while (ci < cs)
	{
		if (ai >= as)
		{
			while (bi < bs)
			{
				C[ci++] = B[bi++];
			}
			return;
		}

		if (bi >= bs)
		{
			while (ai < as)
			{
				C[ci++] = A[ai++];
			}
			return;
		}
		if (A[ai] < B[bi])
			C[ci++] = A[ai++];
		else
			C[ci++] = B[bi++];
	}
}

// 1.2
void Merge_Sort(vector<int> &V)
{
	if (V.size() == 1)
		return;

	vector<int> L(V.begin(),V.begin()+ V.size() / 2), R(V.begin() + V.size() / 2, V.end() );
	Merge_Sort(L);
	Merge_Sort(R);

	Merge(V,L, R);
}


void Task_1()
{
	vector<int> A(100);
	for (int i = 0;  i < A.size();  i++)
	{
		A[i] = (rand() % 100) + 1;
	}
	Merge_Sort(A);

	cout << "\nAfter Merging : \n";
	Print(A);
}

// ____________________________________________________________________________________________

// 2.1

class node
{
public:
	int data;
	node* next;
};
class Linked_list
{
public:
	int size;
	node* head;
	node* tail;
public:
	Linked_list()
	{
		size = 0;
		head = tail = NULL;
	}

	void Insert_at_Tail(int val)
	{
		node* temp = new node;
		temp->data = val;
		temp->next = NULL;

		if (head == NULL)
		{
			head = tail = temp;
		}
		
		tail->next = temp;
		tail = temp;
		size++;
	}

	void Insert_Node_at_Tail(node* temp)
	{
		temp->next = NULL;

		if (head == NULL)
		{
			head = tail = temp;
		}

		tail->next = temp;
		tail = temp;
		size++;
	}

	int List_Size()
	{
		return size;
	}

	int Top()
	{
		if(head!=NULL)
			return head->data;
		return -1;
	}

	void Print_List_Helper(node* temp)
	{
		if (temp == NULL)
		{
			cout << "X\n";
			return;
		}
		cout << temp->data << "\n";
		Print_List_Helper(temp->next);
	}

	void Print_List()
	{
		cout << "\nList :\n";
		Print_List_Helper(head);
	}

	void Clear()
	{
		head = tail = NULL;
	}

};

// 1.1
void List_Merge(Linked_list &C, Linked_list &A, Linked_list &B)
{
	int as = A.List_Size(), bs = B.List_Size();
	int cs = as + bs;

	node* a_temp = A.head, *b_temp = B.head, *c_temp = C.head;
	node* temp;

	int ai = 0, bi = 0, ci = 0;
	while (a_temp || b_temp)
	{
		if (a_temp == NULL)
		{
			while (b_temp != NULL)
			{
				temp = b_temp;
				b_temp = b_temp->next;

				C.Insert_Node_at_Tail(temp);
				//b_temp = b_temp->next;
			}
			return;
		}

		if (b_temp == NULL)
		{
			while (a_temp != NULL)
			{
				temp = a_temp;
				a_temp = a_temp->next;
				C.Insert_Node_at_Tail(temp);

				//a_temp = a_temp->next;
			}
			return;
		}
		if (a_temp->data < b_temp->data)
		{
			temp = a_temp;
			a_temp = a_temp->next;

			C.Insert_Node_at_Tail(temp);
			//a_temp = a_temp->next;
		}
		else
		{
			temp = b_temp;
			b_temp = b_temp->next;

			C.Insert_Node_at_Tail(temp);
			//b_temp = b_temp->next;
		}
	}
}

void List_Merge_Sort(Linked_list &list)
{
	if (list.List_Size() == 1)
		return;
	Linked_list Left, Right;
	node* itr = list.head,*temp;

	for (int i = 0;  i < list.List_Size()/2;  i++)
	{
		temp = itr;
		itr = itr->next;

		Left.Insert_Node_at_Tail(temp);
	}
	Left.tail->next = NULL;
	while (itr!=NULL)
	{
		temp = itr;
		itr = itr->next;

		Right.Insert_Node_at_Tail(temp);
	}
	Right.tail->next = NULL;


	List_Merge_Sort(Left);
	List_Merge_Sort(Right);

	list.Clear();
	List_Merge(list, Left, Right);
}

void Task_2()
{
	Linked_list list,list2,list3;

	for (int i = 0; i < 100; i++)
	{
		/*list.Insert_at_Tail(i);
		list2.Insert_at_Tail(i);*/

		list.Insert_at_Tail((rand() % 100) + 1);
		//list2.Insert_at_Tail((rand() % 100) + 1);
	}
	//List_Merge(list3, list, list2);

	cout << "\nList Before SOrting :\n\n";
	list.Print_List();

	List_Merge_Sort(list);
	cout << "\n\nList After Sorting :\n\n";

	list.Print_List();
}
// ____________________________________________________________________________________________

void Print_Matrix(vector<vector<int>> V)
{
	cout << "\nMatrix :\n\n\t";

	for (int i = 0; i < V.size(); i++)
	{
		for (int j = 0; j < V[i].size(); j++)
		{
			cout << V[i][j] << "   ";
		}
		cout << "\n\n\t";
	}
}
//3.1 
int BSrec(vector<int> V, int s, int e, int T)
{
	int mid = (s + e) / 2;
	if (s > e)
	{
		return -1;
	}
	if (V[mid] == T)
	{
		return mid;
	}
	else if (T > V[mid])		// Reverse as Matrix Rows are in Descending Order
	{
		return BSrec(V, mid + 1, e, T);
	}
	else if (T < V[mid])
	{
		return BSrec(V, s, mid - 1, T);
	}
}

int BS_Search(vector<int> V, int T)
{
	return BSrec(V, 0, V.size() - 1, T);
}
void Find_Value_in_Matrix(vector<vector<int>> V, int T)	// O (N. log N)
{
	int index;
	for (int i = 0; i < V.size(); i++)
	{
		index = BS_Search(V[i], T);
		if (index != -1)
		{
			cout << "\nValue " << T << " is in the Matrix at : M  [ " << i << " ]  [" << index << " ]";
			return;
		}
	}
	cout << "\nValue " << T << " is Not in the Matrix";
}
//3.2
int Find_in_Matrix_Rec(vector<vector<int>> V, int row_s, int col_e, int T)
{
	if (row_s > V.size() || col_e < 0)
	{
		cout << "\nValue " << T << " is Not in the Matrix";
		return 0;
	}
	if (T == V[row_s][col_e] )
	{
		cout << "\nValue " << T << " is in the Matrix at : M  [ " << row_s << " ]  [" << col_e << " ]";
		return 1;
	}
	if (T < V[row_s][col_e])
	{
		return Find_in_Matrix_Rec(V, row_s + 1, col_e, T);
	}
	else
	{
		return Find_in_Matrix_Rec(V, row_s, col_e-1, T);
	}
}

void Find_Value_in_Matrix_Efficient(vector<vector<int>> V, int T)	// O ( log N)
{
	int rows = V.size(), cols;
	if (rows != 0)
		cols = V[0].size();

	int row_s = 0, col_e = cols - 1;

	Find_in_Matrix_Rec(V, row_s, col_e, T);
}


void Search_In_Matrix(vector<vector<int>> V, int T)
{
	int choice,index;
	cout << "\n Option 1 : O (N. Log N)"
		<< "\n Option 2 : O(N) ";

	cout << "\nEnter Option : ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		Find_Value_in_Matrix(V, T);
		break;
	case 2:
		Find_Value_in_Matrix_Efficient(V, T);
		break;
	}
}

void Task_3()
{
	int T;

	vector<vector<int>> V;
	vector<int> v1;
	int val = 2000;
	for (int i = 0; i < 10; i++)
	{

		vector<int> v1;
		for (int j = 0; j < 10; j++)
		{
			v1.push_back((val-j));
		}
		val /= 2;
		V.push_back(v1);
	}
	Print_Matrix(V);
	cout << "\nWhich Value You want to Search : ";
	cin >> T;
	Search_In_Matrix(V,T);
}
// __________________________________________________________
//4
int Determinant(vector<vector<int>> V, int r, int c, int sum)
{
	if(r==0)
	return sum += V[r][c] * (-1 ^ (r + c))*Determinant(V, r+1, c, sum);
}

void Task_4()
{
	vector<vector<int>> V;
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{

		vector<int> v1;
		for (int j = 0; j < 10; j++)
		{
			v1.push_back(rand() % 10 + 1);
		}
		V.push_back(v1);
	}
	Print_Matrix(V);

	//Search_In_Matrix(V, T);
}

void Menu()
{
	cout <<
		"Task No 1 : Merge Sort\n"
		"Task No 2 : Merge Sort For Linked List\n"
		"Task No 3 : Find a Value in Matrix\n"
		"Task No 4 : Determinant of Matrix \n"
	/*	"Task No 5 : \n"
		"Task No 6 : \n"
		"Task No 7 : \n"

		"Task No 8 : \n"*/

		<< "\nTask No 10 : Exit";

	cout << "\n\nEnter Task No : ";

}
void sec_Menu_3_Options()
{
	cout << "\n Option 1 : Iteratively"
		<< "\n Option 2 : Recursively"
		<< "\n Option 3 : Recursive with memoization/Dynamic Programming";

	cout << "\nEnter Option : ";
}
void sec_Menu()
{
	cout << "\n Option 1 : Iteratively"
		<< "\n Option 2 : Recursively";

	cout << "\nEnter Option : ";
}
void sec_Menu_N_series()
{
	cout << "\n Option 1 : 1 + 2 + 3 + ... + N"
		<< "\n Option 2 :  1 + 3 + 5 + ... + N (N Odd)"
		<< "\n Option 3 :  1 + 2 + 4 + 8 + ... + 2^N"
		<< "\n Option 4 :  1 + 3 + 9 + ... + 3^N"
		<< "\n Option 5 :  1 + 3 + 9 + ... + N/9 + N/3 + N"
		<< "\n Option 5 :  1 + 2 + 4 + 8 + ... + N/2 + N";

	cout << "\nEnter Option : ";
}

void sec_Menu_nPr_nCr()
{
	cout << "\n Option 1 : nCr"
		<< "\n Option 2 : nPr";

	cout << "\nEnter Option : ";
}

void main()
{
	int choice, N;

	while (true)
	{
		Menu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			switch (choice)
			{
			case 1:
				Task_1();
				break;
			case 2:
				break;
			case 3:
				break;
			}
			break;


		case 2:
			Task_2();
		case 3:
			Task_3();
			break;

		case 4:
			Task_4();
			break;

		case 5:
			//Task_5();
			return;

		case 6:
			//Task_6();
			return;

		case 7:
			//Task_7();
			return;
		case 8:
			//Task_8();
			return;
		case 10:
			return;
		}
		cout << "\n\n";
	}

	cout << "\n\n";
}
