#include<stdio.h>
#include<omp.h>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

#define score 1
/*problem statement->
 * Given two sequences find the maximum alignment score and print the maximum align string 
 * */

//https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-096-algorithms-for-computational-biology-spring-2005/lecture-notes/lecture5_newest.pdf
int solve(string pat1,int len1,string pat2,int len2, vector<vector<int> > dp)
{
for(int i=0;i<len1+1;i++)
	dp[i][0]=0;
for(int j=0;j<len2+1;j++)
	dp[0][j]=0;

for(int i=0;i<len1,i++)
{
	for(int j=0;j<len2;j++)
	{
		if(s1[i][j]==s2[i][j])
			dp[i+1][j+1]=max(dp[i][j]+score,max(dp[i+1][j],dp[i][j+1])); //here s represents the score that is required for every match and mismatch ,for mismatch score here is 0 and for every match score is 1;
		else
			dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);

	}
}
return dp[len1+1][len2+1];
}


int main(){
string s1,s2;
cin>>s1>>s2;
int len1=s1.length(),len2=s2.length();

vector<vector<int> > dp(len1+2, vector<int> (len2+2,0));

int max_align=solve(&s1,&len1,&s2,&len2,&dp);

	return 0;
}
