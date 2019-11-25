#include<bits/stdc++.h>
using namespace std;

double profile[4][100]; ///a, t, c, g

void generate_profile(string motifs[], int t, int k)
{

    memset(profile, 0, sizeof(profile));
    for(int i=0; i<k; i++)
    {
        for(int j=0; j<t; j++)
        {
            if(motifs[j][i]=='a')
                profile[0][i]++;  //
            else if(motifs[j][i]=='t')
                profile[1][i]++;
            else if(motifs[j][i]=='c')
                profile[2][i]++;
            else
                profile[3][i]++;
        }
    }

    char ch[]= {'a', 't', 'c', 'g'};
    cout << "Count Matrix:" << endl;
    for(int i=0; i<4; i++)
    {
        cout <<ch[i]<< " : ";
        for(int j=0; j<k; j++)
        {
            cout << profile[i][j] << " ";
            profile[i][j]=(profile[i][j])/(double)t;
        }
        cout << endl;
    }

    cout << "Profile:" << endl;
    for(int i=0; i<4; i++)
    {
        cout <<ch[i]<< " : ";
        for(int j=0; j<k; j++)
            printf("%.2f\t", profile[i][j]);
        cout << endl;
    }

}

void get_profile_most(string dna[], string motifs[], int n, int t, int k)
{
    cout << endl;

    string best_motifs[100];
    for(int p=0; p<t; p++)
    {
        double mx=-1.0;
        for(int i=0; i<=n-k; i++)
        {
            double probab=1.0;
            string temp="";
            for(int j=i; j-i<k; j++)
            {
                temp.push_back(dna[p][j]);
                if(dna[p][j]=='a')
                    probab*=profile[0][j-i];
                else if(dna[p][j]=='t')
                    probab*=profile[1][j-i];
                else if(dna[p][j]=='c')
                    probab*=profile[2][j-i];
                else
                    probab*=profile[3][j-i];
            }
            cout << temp << ":";
            printf("%.2f  ", probab);
            if(probab>mx)
            {
                mx=probab;
                best_motifs[p]=temp;
            }
        }
        cout << endl;
    }

    cout << "\nAfter iteration1:\n";
    for(int i=0; i<t; i++)
        cout << best_motifs[i] << endl;
}

int main()
{
    int n, t, k;
    cin >> n >> t >> k;
    string dna[100];
    for(int i=0; i<t; i++)
        cin >> dna[i];

    string motifs[100];
    srand(time(NULL));
    for(int i=0; i<t; i++)
    {
        int x=rand()%(n-k);
        //cout << x << endl;
        motifs[i]="";
        for(int j=x; j-x<k; j++)
            motifs[i].push_back(dna[i][j]);
    }

    cout << "Randomly Picked Motifs:\n";
    for(int i=0; i<t; i++)
        cout << motifs[i] << endl;
    generate_profile(motifs,t,k);

    get_profile_most(dna, motifs, n, t, k);
    return 0;
}
/*
8 4 3
cgaatgca
tgcatgac
ggcagggc
tcacctgt
*/
