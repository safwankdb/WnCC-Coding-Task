#include<bits/stdc++.h>
using namespace std;
//Create a structure student to hold the roll no., marks, rank, and no. of people tied with within it for every student.
struct student
{
	float marks;
	int roll;
	int rank=0;
	int tied=0;
	student(int a,float b)
	{
		roll=a;
		marks=b;
	}
};
//Compare function to rank students.
bool studentCompare(student a,student b)
{
	return a.marks>b.marks;
}
//Checks the validity of th query
bool checkQuery(string s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if(s[i]<48||s[i]>57)
			return false;	
	}
	return true;
}
//Driver function
int main()
{
	ifstream input("Marksheet.csv");//Take the CSV file as input.
	vector<student> marksheet;//Declare collection of students' information as marksheet
	vector<int>rollToRank(1000);//Maps rank to every roll no. to skip searching by rol no in query.
	char x;//The comma seperating the two values, neat trick to reduce clutter.
	int roll;//roll no varible
	float marks;//marks variable
	while(input.good())
	{
		input>>roll>>x>>marks;//read input from CSV file
		student s(roll,marks);//create a student entry
		marksheet.push_back(s);//append the student to the collection
	}
	sort(marksheet.begin(),marksheet.end(),studentCompare);//sort the list markwise
	int rank=0,tiedCount=1,lowerBound=0,upperBound=0;//variable declaration and initialisation
	float previousMarks=marksheet[0].marks;//marks of the first person
	for(int i=0;i<marksheet.size();i++)
	{
		upperBound=i;//increment upperbound
		if((marksheet[i].marks==previousMarks)&&(i>0))
		{
			tiedCount++;//Increase tiedcount if marks are same as previous.
		}
		else
		{
			rank++;//Increment rank if marks are not same, thus greater than previous
			for(int t=lowerBound;t<upperBound;t++)
			{
				marksheet[t].tied=tiedCount;//Update tiedcount for all the tied students
			}
			tiedCount=1;//reset tiedcount
			lowerBound=i;//reset lowerbound
		}
		marksheet[i].rank=rank;//update rank
		previousMarks=marksheet[i].marks;//update previous marks
		rollToRank[marksheet[i].roll]=rank;//add mapping from roll no. to the rank given.
	}
	while(true)
	{
		cout<<"Enter Roll Number: ";//Ask for query
		string query;
		cin>>query;//Input query
		if(query=="stop")
			break;//Stop script when told to
		else if(!checkQuery(query))//if invalid query, alert and ask again.
		{
			cout<<"Please Enter Valid Query."<<endl;
		}
		else//if valid, convert string to int
		{
			int t=0;
			for(int i=0;i<query.size();i++)
			{
				t+=(query[i]-'0')*roundf(pow(10,query.size()-1-i));
			}
			if(t<1||t>1000)//check within range of roll no.
			{
				cout<<"Please Enter Valid Query."<<endl;
				continue;
			}
			//if valid, output the required data on stdout
			cout<<"Marks: "<<marksheet[rollToRank[t]].marks<<", Rank: "<<rollToRank[t]<<", Tied Between: "<<marksheet[rollToRank[t]].tied<<endl;
		}
	}
	return 0;//terminate program
}