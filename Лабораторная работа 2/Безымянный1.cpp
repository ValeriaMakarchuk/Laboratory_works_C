#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Personal_information_about_student
{
	string surname;
	vector<int> ratings_for_the_homeWorks; 
	int rating_for_control_test;
	float average_score;
};

vector<string> Split_string(string s1)
{
	vector <string> v;
	for(int i=0;i<s1.length();i++){
		string buf;
		while(s1[i]!=' ' && i<s1.length()){
			buf.push_back(s1[i]);
			i++;
		}
		v.push_back(buf);
	}
	return v;
}
void Parse(Personal_information_about_student &A,string s1)
{
	vector <string> v=Split_string(s1);
	A.surname=v[0];
	A.rating_for_control_test=v[1][0]-48;
	for(int i=2;i<v.size();i++) A.ratings_for_the_homeWorks.push_back(v[i][0]-48);
		
}

void Calculation_of_a_lowest_passing_score(Personal_information_about_student &A)
{
	int sum_ratings_for_homeWorks=0;
	for(int i=0;i<A.ratings_for_the_homeWorks.size();i++)
		sum_ratings_for_homeWorks+=A.ratings_for_the_homeWorks[i]; 
	
	A.average_score= (sum_ratings_for_homeWorks/A.ratings_for_the_homeWorks.size() )*0.75 +0.25*A.rating_for_control_test;
	//cout<< A.average_score<<endl;
}

void Sort(string str,vector<Personal_information_about_student> &students )
{
	if(str=="name") sort(students.rbegin(),students.rend(),[](Personal_information_about_student A,Personal_information_about_student B)->bool{return A.surname>B.surname;}); 
	if(str=="test") sort(students.rbegin(),students.rend(),[](Personal_information_about_student A,Personal_information_about_student B)->bool{return A.average_score>B.average_score;}); 
}


void Read_of_file(vector<Personal_information_about_student> &students, string input_file)
{
	string s1=" ";
	ifstream in("input.txt");     // Открываем файл для считывания информации
    while(getline(in,s1)){
    	Personal_information_about_student A;
		Parse(A,s1);
		Calculation_of_a_lowest_passing_score(A);
		students.push_back(A);		
	}                         
  	
	in.close();                              //   Закрываем файл
} 
void Write_of_file(vector<Personal_information_about_student> students,string good_guys,string bad_guys)
{
	ofstream out1(good_guys);
	ofstream out2(bad_guys);
	for(int i=0;i<students.size();i++){
		if(students[i].average_score>3){
			out1<<students[i].surname <<endl;
			out1<<students[i].average_score<<endl;
			out1<<students[i].rating_for_control_test<<endl;
			for(int j=0;j<students[i].ratings_for_the_homeWorks.size();j++)
				out1<<students[i].ratings_for_the_homeWorks[j]<<" ";
			out1<<endl;	
		}
		else{
			out2<<students[i].surname<<endl;
			out2<<students[i].average_score<<endl;
			out2<<students[i].rating_for_control_test<<endl;
			for(int j=0;j<students[i].ratings_for_the_homeWorks.size();j++)
				out2<<students[i].ratings_for_the_homeWorks[j]<<" ";
			out2<<endl;	
		} 
	}
	out1.close();
	out2.close();
}

int main(int argc, char** argv) 
{
	string input_file="input.txt";
	string output_file="bad_guys.txt";
	string output_file_1="good_guys.txt";
	vector <Personal_information_about_student> Students;
	Read_of_file(Students,input_file);	
	Sort("test",Students);
	Write_of_file(Students,output_file_1,output_file);
	return 0;
}
