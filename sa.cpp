#include <bits/stdc++.h>
using namespace std;
#define inf 1000000007
#define e 2.718
double gready(vector<vector<float> > &graph,vector<int> &state);
vector<int> sa(vector<vector<float> > &graph, vector<int> &arr);
double random_gen(vector<int> &arr, vector<vector<float> > &graph);
double cost(vector<int> &arr,vector<vector<float> > &graph);

double min_cots=10000000.0;
int check=0;
double random_f(){
	return abs(((double)rand())/ (double)RAND_MAX);
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
   min_cots=gready(adj_matrix,state);
    state.pop_back();
   // cout<<"cost by gready : "<<min_cots<<endl;
  // for(int i=0; i<n; i++) state[i]=i;
    
    std::vector<int> ans;
    ans= sa(adj_matrix,state);
    for(auto x: ans) cout<<x<<" ";
   cout<<endl;
   cout<<"\ncost  : "<<min_cots<<endl;

     end=clock();
     double total_time=end-start;
	 total_time=total_time/CLOCKS_PER_SEC;
	// cout<<endl<<"time is:  "<<total_time<<endl;


  return 0;
}

vector<int>  sa(vector<vector<float> > &graph, vector<int> &arr){
      clock_t beg,ct;
      double current_time=0.0;
      beg=clock();
     int n=arr.size();
     std::vector<int> temp; 
     temp=arr;
     vector<int> best;
     vector<int> curr_state;
     best=arr;
     curr_state=arr; 
     double current=cost(temp,graph);
    // int T=1e5;        //time 120sec for T=1e5, in wrost case;
     float T=100000.0;
     bool flag=true;
     while(T > 0 && current_time < 295){
     for(int i=0; i<n; i++){
      if(flag)temp=curr_state;
      flag=false;
     	double next=random_gen(temp,graph);
     	double change_in_cost=current-next;
     	double term=(-1.0*change_in_cost)/T;
     	double sigmoid= 1.0/(1+pow(e,term));
      if(next < min_cots){
          min_cots=next;
          best=temp;
          cout.flush();
          for(auto x: best) cout<<x<<" ";
            cout<<endl;
        //  cout<<next<<endl;
        } 

     	 if(random_f() < sigmoid)
     	 {	
     		    current=next;            // current and next are cost of the tour
            curr_state=temp; 
            flag=true;
           // break;
     	 }
     }
     	
     T *=0.99999;
     ct=clock()-beg;
     current_time=ct/CLOCKS_PER_SEC;
 }
 return best;
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

double random_gen(vector<int> &arr, vector<vector<float> > &graph){
	int len=arr.size();
	float max1=-1000000,max2=-10000;
	int x1=0,y1=0,z=0,m=0,n=0;
 // vector<pair<float,int> > prt; 
     for(int i=0; i<len; i++){
           m=arr[i];
           n=arr[(i+1)%len];
           float weight=graph[m][n] ;
           //prt.push_back(make_pair(weight,(i+1)%len));

        if(graph[m][n] > max1){
        	max1=graph[m][n];
        	x1=(i+1)%len;
          z=i;
        }
        
     }
    
    for(int i=0; i<len; i++){
          m=arr[i];
          n=arr[(i+1)%len];
      if(graph[m][n]> max2 && i != z){
          max2=graph[m][n];
          y1=(i+1)%len;
        }
    }
     
   /*  sort(prt.begin(),prt.end());
     if(check==5)
      {for(auto x: prt) cout<<arr[x.second]<<"  ";
       cout<<"\n\n\n";
        cout<<arr[x1]<<" "<<arr[y1]<<" \n";

  //  x1=prt[0].second;
    // y1=prt[1].second;
    cout<<arr[x1]<<" "<<arr[y1]<<" "<<endl;

  }
     
   // cout<<x1<<" "<<y1<<" ";
    x1=prt[0].second;
     //y1=prt[1].second;
    // cout<<x1<<" "<<y1<<" "<<endl;
 /*   if(x1==n){
         arr[0]=arr[y1];  // for exchanging last edge
      }
      else if(y1==n){
          arr[0]=arr[x1];
      }
  *
     check++;
     */
     int temp=arr[x1];
     arr[x1]=arr[y1];
     arr[y1]=temp;
    return cost(arr,graph); 
   

}

double cost(vector<int> &arr,vector<vector<float> > &graph){
	double ans=0;
  int n=arr.size();
	for(int i=0; i<n; i++)
       ans +=graph[arr[i]][arr[(i+1)%n]];
   return ans;
}





	
