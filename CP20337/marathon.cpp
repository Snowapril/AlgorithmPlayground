#include <bits/stdc++.h>
using namespace std;
int main(){
	ifstream a("marathon.inp");
	ofstream b("marathon.out");
	int e,i,w;
	a>>e>>e;
	int g[28][28]{0,};
	for(i=0;i<e;++i){
		char j,k;
		a>>j>>k>>w;
		g[k-97][j-97]=w;
		g[j-97][k-97]=w;
	}
	stack<array<int,3>>p,mp;
	bitset<28>v;
	p.push({0,});
	int d=0,ml=0;
	while(p.size()){
		auto&c=p.top();
		for(i=c[2];i<28;++i)
			if(g[c[1]][i]!=0&&c[0]!=i&&!v.test(i)){
				w=g[c[1]][i];
				c[2]=i+1;
				if(i==0){
					if(d+w==42&&ml<p.size()){
						ml=p.size();
						mp=p;
					}
				}
				else if(d+w<42){
					d+=w;
					p.push({c[1],i,0});
					v.set(i);
				}
				break;
			}
		if(i==28){
			p.pop();
			v.set(c[1],0);
			d-=g[c[1]][c[0]];
		}
	}
	if(ml==-1)
		b<<"NONE\n";
	else{
		b<<ml<<'\n';
		stack<char>t;
		while(mp.size()){
			t.push(mp.top()[1]+97);
			mp.pop();
		}
		while(t.size()!=1){
			b<<t.top()<<' ';
			t.pop();
		}
		b<<t.top();
	}
	b.close();
	a.close();
}