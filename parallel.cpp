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
int solve(string &pat1,int &len1,string &pat2,int &len2)
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

/*
int solve_str(string s1,int len1,string s2, int len2,int window,int threshold,int anchor_ind,int left,int max_len, vector<pair<int,int> > &anchor_score) //first int is score second int is index of text
{

if(anchor_ind<0||anchor_ind>=max_len)
return 0;

string pat_str=s1.substr(anchor_ind,window);
vector<vector<int> > dp(window+2, vector<int>(window+2,0));


for(int i=0;i<len2-window+1;i++)
{
int score=0;
string text=s2.substr(i,window);
if((score=solve(pat_str,window,text,window,dp))>=threshold)
{
//calculate left score
string left_pat=s1.substr(0,anchor_ind);
string right_pat=s1.substr(anchor_ind+window,len1-anchor_ind-window+1);
string left_text=s2.substr(0,i);
string right_text=s2.substr(i+window,len2-i-window+1);
int lpl=left_pat.length();
int rpl=right_pat.length();
int ltl=left_text.length();
int rtl=right_text.length();

int left=solve_str(left_pat,lpl,left_text,ltl,window,threshold,anchor_ind-1,anchor_score);
//calculate right score
int right=solve_str(right_pat,rpl,right_text,rtl,window,threshold,anchor_ind+window+1,anchor_score);

if(anchor_score[anchor_ind].first<= score+left+right){
anchor_score[anchor_ind].first=score+left+right;
anchor_score[anchor_ind].second=i;

}

}


}





}
*/

int main(){
string s1,s2;//s1 is to be searched s2 is text
cin>>s1>>s2;
int len1=s1.length(),len2=s2.length();
int window,threshold;
cin>>window>>threshold;

vector<pair<string,int> > anchor_score;

vector<string> anchor(len1-window+1,"");

int max_align=0;

for(int i=0;i<len1-window+1;i++)
{
anchor[i]=(s1.substr(i,window));
cout<<anchor[i]<<endl;

}

for (int i=0;i<len2-window+1;i++)
{
for(int j=0;j<anchor.size();j++)
{
string text_mat=s1.substr(i,window);
int score=solve(anchor[j],window,text_mat,window);
if(score>=threshold)
{
achor_score(push_back(make_pair(anchor[j],i)));
}
}
}


	return 0;
}
