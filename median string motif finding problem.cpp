#include<bits/stdc++.h>
#define pb push_back
using namespace std;
char chSet[]= {'a','t','g','c'};
string best_motif[50], dna[50];
int hd_mn=INT_MAX;

int hamming_distance(string motif[], int noOfdNa, int len)
{
    int ans=0;
    for(int i=0; i<len; i++)
    {
        int a=0, t=0, c=0, g=0;
        for(int j=0; j<noOfdNa; j++)
        {
            if(motif[j][i]=='a')
                a++;
            else if(motif[j][i]=='c')
                c++;
            else if(motif[j][i]=='t')
                t++;
            else if(motif[j][i]=='g')
                g++;
        }
        ans+=(noOfdNa-max(a,max(t,max(c,g))));
    }
    return ans;
}

void get_motif(string kmer, int n, int t, int k)
{
    string motif[t];
    for(int i=0; i<t; i++)
    {
        int mn=k+2;
        for(int j=0; j<=n-k; j++)
        {
            string temp;
            int cnt=0;
            for(int x=j; x<j+k; x++)
            {
                if(kmer[x-j]!=dna[i][x])
                    cnt++;
                temp.pb(dna[i][x]);
            }
            if(mn>cnt)
            {
                mn=cnt;
                motif[i]=temp;
            }
        }
    }

    int hd=hamming_distance(motif,t,k);
    if(hd<hd_mn)
    {
        hd_mn=hd;
        for(int i=0; i<t; i++)
            best_motif[i]=motif[i];
    }
}

void generate_pattern(int n, int t, int k, int len, string pattern)
{
    if(len==k)
    {
        //cout << pattern << endl;
        get_motif(pattern, n, t, k);
        return;
    }
    for(int i=0; i<4; i++)
    {
        string temp=pattern;
        temp.pb(chSet[i]);
        generate_pattern(n,t,k,len+1,temp);
    }
}

int main()
{
    int n, t, k; //n=DNA length, t=Number of DNA, k=K-mer length
    cin >> n >> t >> k;
    for(int i=0; i<t; i++)
        cin >> dna[i];
    generate_pattern(n,t,k,0,"");

    cout << endl << "MOTIFS: " << endl;
    for(int i=0; i<t; i++)
        cout << best_motif[i] << endl;
    cout << "\nHamming Distance: "<< hd_mn << endl;

    return 0;
}
/*
Input1:
7 5 3
aactaga
aatcgaa
atctcga
aatcgtd
ggattag

Input2:
10 5 3
ttaccttaac
gatatctgtc
acggcgttcg
ccctaaagag
cgtcagaggt

Input3:
10 5 4
ttaattaaat
atatataaat
ttaaatttta
atataggaaa
tcagaaatag

Input4:
10 5 3
ttaattaaat
atatataaat
ttaaatttta
atataggaaa
tcagaaatag
*/
