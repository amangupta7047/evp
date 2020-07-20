#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mk make_pair
typedef pair<int, int> pii;
#define fs first
#define sc second 
#define sp <<" "<<

vector <pii> g[100005];
vector <pii> g1[100005];
int src,dest;
map <pii,int> mp;
int cs[105],cs_wt[105];
int n=100000;
int m;
int dis[100005];
int par[100005];
int currcharge;
int fullcharge;
int dist[52][100005];
vector <int> used_cs;

vector <int> dij(int st,int en)
{
	priority_queue<pair<int,int>>q;
	
	for(int i=0; i<100005; i++)
	{
		dis[i]=1e8;
		par[i]=-1;
	}

	q.push({0,st});
	dis[st]=0;

	while(!q.empty())
	{
		int u=q.top().sc;
		q.pop();
		for(int i=0; i<(int)g[u].size(); i++)
		{
			if(dis[u]+g[u][i].sc<dis[g[u][i].fs])
			{
				dis[g[u][i].fs]=dis[u]+g[u][i].sc;
				par[g[u][i].fs]=u;
				q.push({-dis[g[u][i].fs],g[u][i].fs});
			}
		}
	}

	vector <int> v;
	if(dis[en]==1e8)
		return v;
	int f=en;
	v.pb(en);
	while(par[f]!=st)
	{
		f=par[f];
		v.pb(f);
	}
	v.pb(st);
	reverse(v.begin(),v.end());
	return v;
}

vector <int> mindist()
{
	vector <int> ans;
	ans.clear();
	int mindist=1e8;
	int cnt=used_cs.size();
	if(dist[50][dest]<=currcharge)
	{
		return ans;
	}
	for(int i=0; i<cnt; i++)
	{
		if(dist[50][cs[used_cs[i]]]<=currcharge && dist[used_cs[i]][dest]<=fullcharge)
		{
			if(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]<mindist)
			{
				ans.clear();
				ans.pb(used_cs[i]);
				mindist=dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest];
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}

	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge && dist[used_cs[j]][dest]<=fullcharge)
				{
					if(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]<mindist)
					{
						ans.clear();
						ans.pb(used_cs[i]);
						ans.pb(used_cs[j]);
						mindist=dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest];
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}

	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge)
				{
					for(int k=0; k<cnt; k++)
					{
						if(dist[used_cs[j]][cs[used_cs[k]]]<=fullcharge && dist[used_cs[k]][dest]<=fullcharge)
						{
							if(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]<mindist)
							{
								ans.clear();
								ans.pb(used_cs[i]);
								ans.pb(used_cs[j]);
								ans.pb(used_cs[k]);
								mindist=dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest];
							}
						}
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}
	cout<<"Increse Range\n";
	exit(0);

}

vector <int> mintime()
{
	vector <int> ans;
	ans.clear();
	double mindist=1e8;
	int cnt=used_cs.size();
	if(dist[50][dest]<=currcharge)
	{
		return ans;
	}
	for(int i=0; i<cnt; i++)
	{
		if(dist[50][cs[used_cs[i]]]<=currcharge && dist[used_cs[i]][dest]<=fullcharge)
		{
			if((dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]+cs_wt[used_cs[i]])/40000.0+
				(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]-currcharge)*2.0/fullcharge<mindist)
			{
				ans.clear();
				ans.pb(used_cs[i]);
				mindist=(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]+cs_wt[used_cs[i]])/40000.0+
				(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]-currcharge)*2.0/fullcharge;
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}

	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge && dist[used_cs[j]][dest]<=fullcharge)
				{
					if((dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]])/40000.0
						+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]-currcharge)*2.0/fullcharge<mindist)
					{
						ans.clear();
						ans.pb(used_cs[i]);
						ans.pb(used_cs[j]);
						mindist=(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]])/40000.0
						+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]-currcharge)*2.0/fullcharge;
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}

	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge)
				{
					for(int k=0; k<cnt; k++)
					{
						if(dist[used_cs[j]][cs[used_cs[k]]]<=fullcharge && dist[used_cs[k]][dest]<=fullcharge)
						{
							if((dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]]+cs_wt[used_cs[k]])/40000.0
								+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]-currcharge)*2.0/fullcharge<mindist)
							{
								ans.clear();
								ans.pb(used_cs[i]);
								ans.pb(used_cs[j]);
								ans.pb(used_cs[k]);
								mindist=(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]]+cs_wt[used_cs[k]])/40000.0
								+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]-currcharge)*2.0/fullcharge;
							}
						}
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}
	cout<<"Increase Range\n";
	exit(0);

}
int main()
{
	fstream file,file2,file3;
	file.open("output.txt", ios::out | ios::trunc);
  	file.close();
	file.open ("output.txt", ios::in | ios::out | ios::ate);
	file2.open("output2.txt", ios::out | ios::trunc);
  	file2.close();
	file2.open ("output2.txt", ios::in | ios::out | ios::ate);
	file3.open("output3.txt", ios::out | ios::trunc);
  	file3.close();
	file3.open ("output3.txt", ios::in | ios::out | ios::ate);
	
	for(int i=0; i<50; i++)
	{
		cin>>cs[i]>>cs_wt[i];
	}
	cin>>m;
	for(int i=0; i<m; i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		g[u].pb({v,w});
		g1[u].pb({v,w});
		mp[{u,v}]=w;
	}

	cin>>src>>dest;

	int unavaible_nodes;
	cin>>unavaible_nodes;
	int b[unavaible_nodes];
	for(int i=0; i<unavaible_nodes; i++)
	{
		cin>>b[i];
		g[b[i]].clear();
	}

	cin>>currcharge>>fullcharge;
	currcharge=fullcharge*currcharge;
	currcharge/=100;
	
	for(int i=0; i<50; i++)
	{
		dij(cs[i],cs[i]);
		for(int j=0; j<100005; j++)
		{
			dist[i][j]=dis[j];
		}
	}

	dij(src,src);
	for(int i=0; i<100005; i++)
	{
		dist[50][i]=dis[i];
	}
	dij(dest,dest);
	for(int i=0; i<100005; i++)
	{
		dist[51][i]=dis[i];
	}

	file<<src<<" "<<dest<<endl;
	
	int totaldist=dist[50][dest];

	int extradist=max(5000,(int)0.5*totaldist);

	totaldist+=extradist;

	for(int i=0; i<50; i++)
	{
		if(dist[i][src]+dist[i][dest]<=totaldist)
		{
			if(cs[i]!=src)
				used_cs.pb(i);
			else 
				currcharge=fullcharge;
		}
	}

	int f=0;
	for(int i=0; i<(int)used_cs.size(); i++)
	{
		if(dist[i][src]<=currcharge)
			f=1;
	}
	if(f==0)
	{
		cout<<"Increase SOC, If SOC is 100 then try increasing range.\n";
		exit(0);
	}

	// for(auto i:used_cs)
	// {
	// 	cout<<i<<endl;
	// }

	vector <int> v=mindist();
	// for(auto i:v)
	// {
	// 	cout<<i<<endl;
	// }
	int tempsrc=src;
	double traveltym=0.0;
	double traveldist=0.0;
	for(int i=0; i<(int)v.size(); i++)
	{
		vector <int> v1=dij(tempsrc,cs[v[i]]);
		// cout<<cs[v[i]]<<endl;

		traveldist+=dis[cs[v[i]]];
		traveltym+=cs_wt[v[i]]/40000.0;

		if(v1[0]==src)
		{
			file<<src<<" ";
		}
		else 
		{
			file<<-v1[0]<<" ";
		}
		for(int j=1; j<(int)v1.size()-1; j++)
		{
			file<<v1[j]<<" ";
		}
		tempsrc=cs[v[i]];
	}
	vector <int> v1=dij(tempsrc,dest);

	traveldist+=dis[dest];

	traveltym+=(traveldist/40000.0+(traveldist - currcharge)*2.0/fullcharge);

	file3<<traveltym<<" ";
	file3<<traveldist<<endl;

	if(v1[0]==src)
	{
		file<<src<<" ";
	}
	else 
	{
		file<<-v1[0]<<" ";
	}
	for(int j=1; j<(int)v1.size()-1; j++)
	{
		file<<v1[j]<<" ";
	}
	file<<dest<<endl;

	for(int i=0; i<(int)v.size()-1; i++)
	{
		file2<<100*dist[v[i]][cs[v[i+1]]]/(double)fullcharge<<" ";
	}
	if((int)v.size())
	{
		file2<<100*dist[v.back()][dest]/(double)fullcharge<<endl;
	}
	v.clear();
	v=mintime();
	// for(auto i:v)
	// {
	// 	cout<<i<<endl;
	// }
	tempsrc=src;
	traveldist=0.0;
	traveltym=0.0;
	for(int i=0; i<(int)v.size(); i++)
	{
		vector <int> v1=dij(tempsrc,cs[v[i]]);

		traveldist+=dis[cs[v[i]]];
		traveltym+=cs_wt[v[i]]/40000.0;

		if(v1[0]==src)
		{
			file<<src<<" ";
		}
		else 
		{
			file<<-v1[0]<<" ";
		}
		for(int j=1; j<(int)v1.size()-1; j++)
		{
			file<<v1[j]<<" ";
		}
		tempsrc=cs[v[i]];
	}
	v1.clear();
	v1=dij(tempsrc,dest);

	traveldist+=dis[dest];

	traveltym+=(traveldist/40000.0+(traveldist - currcharge)*2.0/fullcharge);

	file3<<traveltym<<" ";
	file3<<traveldist<<endl;

	if(v1[0]==src)
	{
		file<<src<<" ";
	}
	else 
	{
		file<<-v1[0]<<" ";
	}
	for(int j=1; j<(int)v1.size()-1; j++)
	{
		file<<v1[j]<<" ";
	}
	file<<dest<<endl;

	for(int i=0; i<(int)v.size()-1; i++)
	{
		file2<<100*dist[v[i]][cs[v[i+1]]]/(double)fullcharge<<" ";
	}
	if((int)v.size())
	{
		file2<<100*dist[v.back()][dest]/(double)fullcharge<<endl;
	}

	file.close();
    return 0;
}