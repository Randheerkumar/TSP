#include <bits/stdc++.h>
using namespace std;
#define inf 1000000007
#define e 2.718
#define vpfi vector<pair<float,int > >
#define vvi vector<vector<int> > 
#define vvf vector<vector<float> >

vector<int>  ga(vector<vector<float> > &graph, vector<int> &v);
double gready(vector<vector<float> > &graph,vector<int> &state);
void crossover(vector<vector<int> > &temp, vector<vector<int> > &off);
void rank_f(vector<vector<int> > &ngen,vector<pair<float,int> > &rank_new,vector<vector<float> > &graph);
void replace(vector<vector<int> > &ngen, vector<vector<int > > &parrent,vector<pair<float,int> > &v,vector<pair<float,int> > &rank_old);
void mutate(vector<vector<int> > &temp, vector<vector<int> > &off);

vpfi rank_f2(vvi &ngen,vvf &graph);

double min_cots=10000000.0;
int check=1;

double random_f(){
	return abs(((double)rand())/ (double)RAND_MAX);
}

int N;

double cost(vector<int> &arr,vector<vector<float> > &graph){
  double ans=0;
  int n=arr.size();
  for(int i=0; i<n; i++)
       ans +=graph[arr[i]][arr[(i+1)%n]];
   return ans;
}


int main(int argc, char *argv[]){
      time_t start,end;
      start=clock();
	freopen(argv[1],"r",stdin);
	if(argv[2] != NULL) freopen(argv[2],"w",stdout);
	//else freopen("output.txt","w",stdout);

    string dist_type;
    int n;
    getline(cin,dist_type);
    if(dist_type.length()==0) getline(cin,dist_type);
   // cout<<dist_type<<endl;
    cin>>n;
   // cout<<n<<endl;
    N=n;
    vector<pair<float,float> > cities(n);
    float x,y;

    for(int i=0; i<n; i++){
    	cin>>x>>y;
    	cities[i]=make_pair(x,y);

    }
    vector<vector<float> > adj_matrix(n,vector<float>(n,0.0));
    int i=0,j=0;
    while(j < n){
        // cout<<j<<endl;
    	for(int i=0; i<n; i++) cin>>adj_matrix[j][i];
    	j++;	
    }
    j=0;
    vector<int> state(n+1);
    for(int i=0; i<N; i++) state[i]=i;
   min_cots=gready(adj_matrix,state);
  // cout<<"cost by gready : "<<min_cots<<endl;
   // cout<<"size="<<state.size()<<endl;
  //  for(auto x:state) cout<<x<<" ";
   vector<int> ans;
    ans=ga(adj_matrix,state);
    for(auto x : ans) cout<<x<<" ";
    cout<<endl;
   cout<<"\ncost is "<< cost(ans,adj_matrix)<<endl;  
     end=clock();
     double total_time=end-start;
	 total_time=total_time/CLOCKS_PER_SEC;
	// cout<<endl<<"time is:  "<<total_time<<endl;



  return 0;
}


double gready(vector<vector<float> > &graph, vector<int> &state){
	list<int> open;
    set<int> close;
   // vector<int> state(n+1);
    int k=0;
    int i=0,n=graph.size();
    open.push_back(i);
    float ans=0;
    int next=0;
    while(!open.empty()){

          int current=open.front();
          open.pop_front();
        //  cout<<current<<" ";
           state[k++]=current;
          while(close.find(current) != close.end() ){
             current=open.front();
             open.pop_front();
          }
          close.insert(current);
          
          float max=inf;
          bool flag=0;
          for(i=0; i<n; i++){
               if(max > graph[current][i] && close.find(i) == close.end() ){
                max=graph[current][i];
                next=i;
                flag=1;
               }
          }
          if(flag) open.push_back(next);
          
          if(flag) ans +=max;
    }
    //cout<<endl;
    ans +=graph[next][0];
    state[k++]=state[0];

return ans;
}

void fit(vvi &parrent,vector<float> &fitness, float *total_exptn,vpfi &rank_old){
        float temp=0;     
        float total_fitness=0.0;
        *total_exptn=0.0;
        int n=fitness.size();
        for(int i=0; i<n; i++)  total_fitness +=rank_old[i].first;

        for(int i=0; i<n; i++){
          temp=rank_old[i].first;
        fitness[i]= round(n/(temp*total_fitness));
         *total_exptn +=fitness[i];
      }
}


vector<int>  ga(vector<vector<float> > &graph, vector<int> &space){ 
      time_t beg,end;
	  beg=clock();
    
    space.pop_back();
    int n=space.size(),i=0;

        // cout<<"in ga and size is"<<space.size()<<endl;
  
// ***********************************************//
/*        
  generating initial parents (for offspring )

*/
      vector<vector<int> > parrent(space.size());
        vector<float> fitness(n,0.0);
        float total_exptn=0.0;
        float total_fitness=0.0;
        parrent[0]=space;
        parrent[1]=space;

        for(int j=0; j < n; j++){
              fitness[0] +=graph[space[j]][space[(j+1)%N]];
              }
        fitness[1]=fitness[0];
        total_fitness=2*fitness[0];   
 

        for(i=2; i<n; i++){
              int a=(int) rand()%n;
              int b=(int) rand()%n;
              int temp=space[a];
              space[a]=space[b];
              space[b]=temp;
              int j=0;

              for( j=0; j < n; j++){
              parrent[i].push_back(space[j]);
              fitness[i] +=graph[space[j]][space[(j+1)%N]];
              }

              total_fitness += ((1.0)/fitness[i]);

      }
      for(i=0; i<n; i++){
        fitness[i]= round(n/(fitness[i]*total_fitness));
         total_exptn +=fitness[i];
      } 
//***********************************************/
    
    float sum=0;
    int j=0,k=0;
    i=0;
     
     int i1,i2;
    
    int epoch=0;
    bool flag=false;
    j=0;
   vector<pair<float,int> > rank_new(N),rank_old(N);
   float ct=0.0;
    
  while(ct < 297)
  {
      vector<vector<int> > ngen(N);
      //ngen.clear();
     if(flag) fit(parrent,fitness,&total_exptn,rank_old);
      flag=true;
     // cout<<"Epoch"<<epoch<<endl;
     // rank_f(parrent,rank_old,graph);
      int limit=0;
      for(int x=0; x< N; x +=2){
        vector<vector<int> > temp(2),off(2);
        for(k=0; k<2; k++){
          i=0;
          sum= (rand())%((int)total_exptn+1);
          while(sum > 0 && i < n){
              sum -=fitness[i];
              i++;
          }
          i--;
          if(i < 0) i=0;
          temp[k]=parrent[i];
          //for(auto z : temp[k]) cout<<z<<" ";
            //cout<<endl;
          //  break;


        //   cout<<"Epoch"<<epoch<<endl;
        }
          //rank_f(parrent,rank_old,graph);
          crossover(temp,off);
          int prob=rand()%N;
          if(prob < N/30){
           
          mutate(temp,off);
          }
          //cout<<"crossover"<<endl;
          ngen[x]=off[0];
          ngen[x+1]=off[1]; 
      }

   rank_f(parrent,rank_old,graph);
   rank_f(ngen,rank_new,graph);
  //    rank_new=rank_f2(ngen,graph);
  // cout<<"before replace"<<endl;

   replace(ngen,parrent,rank_new,rank_old);
   cout.flush();
   for(auto x: parrent[rank_old[0].second]) cout<<x<<" ";
   cout<<endl;
   //cout<<"cost is :"<<cost(parrent[rank_old[0].second],graph);
   
   //cout<<"replace"<<endl;
   //rank_f(parrent,rank_old,graph);
// rank_old=rank_f2(parrent,graph);
 // epoch++; 
   end =clock()-beg;
   ct=end/CLOCKS_PER_SEC;
  // cout<<ct<<endl;
}

sort(rank_old.begin(),rank_old.end());
//cout<<"cost by genetic algorithm "<<rank_old[0].first<<endl;
return parrent[rank_old[0].second];



}
void mutate(vector<vector<int> > &temp, vector<vector<int> > &off){
     vector<int> v1,v2; 
     v1=temp[0];
     v2=temp[1];
     int n=temp[0].size(),j=0,k=0;
     int t=n;
     int hash1[n+1]={0},hash2[n+1]={0};
     int l=rand()%(N-1);
     int r=rand()%(N-1);
     if(l > r) swap(l,r);
     j=l;
     swap(v1[l],v1[r]);
     swap(v1[l],v1[r]);
   /*  while( l < r && l < n-1){
        swap(v1[j],v1[j+1]);
        swap(v2[j],v2[j+1]);
        j +=2;
        l +=2;
     } */
     off[1]=v1;
     off[0]=v2;

}




void crossover(vector<vector<int> > &temp, vector<vector<int> > &off){
     vector<int> v1,v2; 
     v1=temp[0];
     v2=temp[1];
     int n=temp[0].size(),j=0,k=0;
     int t=n;
     int hash1[n+1]={0},hash2[n+1]={0};
     int l=n/4,r=n/2;
    l=rand()%(N-1);
     r=rand()%(N-1);
     if(l > r) swap(l,r);
    // vector<int> vtemp;
     for(j=l; j < r; j++){
         off[0].push_back(v2[j]);
         hash1[v2[j]]=1;
         t--;
     }
     j=0;
     while(t > 0){
      if(! hash1[v2[j]])  {

        off[0].push_back(v2[j]);
        t--;
      }
      j++;
     }
    // l=n/4,r=n/2,t=n;
     t=n;
     for(j=l; j < r; j++){
         off[1].push_back(v1[j]);
         hash2[v1[j]]=1;
         t--;
     }
     j=0;
     while(t > 0){
      if(! hash2[v1[j]])   {
        off[1].push_back(v1[j]);
        t--;
      }
      j++;
    
     }
      

}

void replace(vvi &ngen, vvi &parrent,vpfi &rank_new,vpfi &rank_old){
    sort(rank_old.begin(),rank_old.end());
    sort(rank_new.begin(),rank_new.end());
    int n=rank_old.size();
    n=n/10;
    int a,b;
    int j=0,k=rank_old.size()-1;
    for(int i=0; i<n; i++){
        a=rank_old[k--].second;
        b=rank_new[j++].second;
         parrent[a]=ngen[b];
    }



}
void rank_f(vvi &ngen,vpfi &rank_new,vvf &graph){
      //   cout<<"in rank_f:"<<endl;
         int i=0,n=ngen.size(),j=0;
      //   cout<<"before for loop n="<<n<<endl;
         int a,b;
         for(i=0; i<n; i++){
              //cout<<"i="<<i<<" ";
              float cost=0;
            //  int len=ngen[i].size();
             for(j=0; j<N; j++){
              //cout<<"j="<<j<<" ";
               // cout<<"cost="<<cost<<endl;
                a=ngen[i][j];
                b=ngen[i][(j+1)%N];
               // cout<<graph[a][b]<<" ";
                cost +=graph[a][b];
             }
           //  cout<<"i="<<i<<" ";
            // rank_new.push_back(make_pair(cost,i));
             rank_new[i]=make_pair(cost,i);
            // cout<<rank_new[i].first;
         } 

}

vpfi rank_f2(vvi &ngen,vvf &graph){
      vpfi rank_new;
      // cout<<"in rank_f2:"<<endl;
       int a,b;
         int i=0,n=ngen.size(),j=0;
         for(i=0; i<n; i++){
              cout<<"i="<<i<<" ";
              float cost=0;
            //  int len=ngen[i].size();
             for(j=0; j<N; j++){
            //  cout<<"j="<<j<<" ";
                  a=ngen[i][j];
                  b=ngen[i][(j+1)%N];
                 cost +=graph[a][b];
             }
            // cout<<"i="<<i<<" ";
            // rank_new.push_back(make_pair(cost,i));
             rank_new[i]=make_pair(cost,i);
         }
     return rank_new;
}
