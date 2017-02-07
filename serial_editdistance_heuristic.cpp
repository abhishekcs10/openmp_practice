#include<stdio.h>
#include<omp.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define SCORE 1
/*problem statement->
 * Given two sequences find the maximum alignment score and print the maximum align string 
 * */

//https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-096-algorithms-for-computational-biology-spring-2005/lecture-notes/lecture5_newest.pdf
int solve(string &pat1,int &len1,string &pat2,int &len2)
{
vector<vector<int> >dp(len1+2,vector<int>(len2+2,0));
for(int i=0;i<len1+1;i++)
	dp[i][0]=0;
for(int j=0;j<len2+1;j++)
	dp[0][j]=0;

for(int i=0;i<len1;i++)
{
	for(int j=0;j<len2;j++)
	{
		if(pat1[i]==pat2[j])
			dp[i+1][j+1]=max(dp[i][j]+SCORE,max(dp[i+1][j],dp[i][j+1])); //here s represents the score that is required for every match and mismatch ,for mismatch score here is 0 and for every match score is 1;
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

vector<pair<int,int> > anchor_score;
int max_score=0,align=-1;
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
string text_mat=s2.substr(i,window);
int score=solve(anchor[j],window,text_mat,window);
if(score>=threshold)
{
anchor_score.push_back(make_pair(j,i));
}
}
}

for(int i=0;i<anchor_score.size();i++)
{
string pat_mat=anchor[anchor_score[i].first];
int left=2*(anchor_score[i].first-0);
int right=2*(len1-anchor_score[i].first-window);
int total_len=left+right+window;
int starting_ind=max(0,anchor_score[i].second-left);
int ending_ind=min(anchor_score[i].second+window+right,len2-1);
int char_len=ending_ind-starting_ind+1;
string pat_text=s2.substr(starting_ind,char_len);
int score_curr=solve(s1,len1,pat_text,char_len);
if(score_curr>max_score)
{
max_score=score_curr;
align=starting_ind;
max_align=char_len;
}
}
cout<<max_score<<" "<<s2.substr(align,max_align)<<endl;

return 0;
}
