#include<stdio.h>
#include<omp.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define score 1
/*problem statement->
 * Given two sequences find the maximum alignment score and print the maximum align string 
 * */

//https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-096-algorithms-for-computational-biology-spring-2005/lecture-notes/lecture5_newest.pdf
int solve(string &pat1,int &len1,string &pat2,int &len2, vector<vector<int> > &dp)
{
for(int i=0;i<len1+1;i++)
	dp[i][0]=0;
for(int j=0;j<len2+1;j++)
	dp[0][j]=0;

for(int i=0;i<len1;i++)
{
	for(int j=0;j<len2;j++)
	{
		if(pat1[i]==pat2[j])
			dp[i+1][j+1]=max(dp[i][j]+score,max(dp[i+1][j],dp[i][j+1])); //here s represents the score that is required for every match and mismatch ,for mismatch score here is 0 and for every match score is 1;
		else
			dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);

	}
}
return dp[len1][len2];
}


int main(){
string s1,s2;//s1 is to be searched s2 is text
cin>>s1>>s2;
int len1=s1.length(),len2=s2.length();
int window,threshold;
cin>>window>>threshold;
vector<vector<int> > dp(len1+2, vector<int> (len2+2,0));
int max_align=0;

for(int i=0;i<len1-window-1;i++)
{
vector<vector<int> > dpx(window+2, vector<int> (window+2,0));

for( int j=0;j<len2-window-1;j++)
{
string che1=s1.substr(i,window),che2=s2.substr(j,window);

if (solve(che1,window,che2, window, dpx)>=threshold)
{
string match_st=s2.substr(max(0,(j-i)),len1-i);
int le2=match_st.length();
cout<<match_st<<" this is matched"<<endl;
 max_align=max(max_align,solve(s1,len1,match_st,le2,dp));
}

}
}
cout<<max_align<<endl;
	return 0;
}
