#include <map>
#include <iostream>

template<typename T>
class histogram
{
  using impl_t=std::map<T,double>;
  
public:
  histogram(){}
  histogram(const T& x){m[x]=1.0;}
  
  using const_iterator=typename impl_t::const_iterator;
  
  const_iterator begin()const{return m.begin();}
  const_iterator end()const{return m.end();}
  
  void add(const T& x,double f){m[x]+=f;}
    
private:
  impl_t  m;
};

template<typename T>
std::ostream& operator<<(std::ostream& os,const histogram<T>& h)
{
  for(const auto& p:h){
    os<<p.first<<"\t";
    for(int n=p.second*120;n--;)os<<"*";
    os<<"\n";
  }
  return os;
}

template<typename T,typename F>
auto operator>>=(const histogram<T>& x,F&& f)
{
  decltype(f(x.begin()->first)) res;
  
  for(const auto& p:x){
    for(const auto& q:f(p.first)){
      res.add(q.first,q.second*p.second);
    }
  }

  return res;
}

histogram<int> dice(int n)
{
  histogram<int> res;
  for(int i=1;i<=n;++i)res.add(i,1.0/n);
  return res;
}

int main()
{
  auto h=dice(6)>>=dice;
  std::cout<<h;
}
