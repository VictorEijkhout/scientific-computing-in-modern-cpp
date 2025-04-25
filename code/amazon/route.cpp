/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2019-2024 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** route.cxx : doing a single salesman trip
 ****
 ****************************************************************/

#include <iostream>
using std::cerr, std::cin, std::cout;

#include <algorithm>
using std::any_of;

#include <random>
using std::rand;

#include <limits>
using std::numeric_limits;

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <optional>
using std::optional;

#include <tuple>
using std::tuple;

#include <cassert>
#include <cmath>
#define CLOSE(x,y) x==y || ( x!=0 && std::abs( (1.*x-y)/x )<1.e-5 ) || ( y!=0 && std::abs( (1.*x-y)/y )<1.e-5 )

// answer code removed
  void fix(bool fixval=true) { fixed = fixval; };
  auto is_fixed() const { return fixed; };
  string as_string() {
    stringstream h; h << "(" << icoord << "," << jcoord << ")";
    return h.str();
  };
};

class AddressList : public vector<Address> {
public:
  AddressList() {};
  AddressList( vector<Address> v ) : vector<Address>::vector<Address>(v)
  // : addresses(v)
      {};
  AddressList( vector<Address> v1,vector<Address> v2,vector<Address> v3 )
    : vector<Address>::vector<Address>(v1) {
    insert(end(),v2.begin(),v2.end());
    insert(end(),v3.begin(),v3.end());
  };
  void add_address( Address h ) { push_back(h); };
  vector<Address> get_addresses() { return *this; };
  //  auto size() const { return addresses.size(); };
  //  auto &at(unsigned i) { return addresses.at(i); };
  auto get(unsigned i) const { return at(i); };
  const Address &operator[](size_t i) { return at(i); };
  void erase_index(int i) { erase( begin()+i ); };
  auto get_and_erase(unsigned i) {
    auto return_address = get(i); erase_index(i); return return_address;
  };
  void reverse(size_t first,size_t last) {
    auto begin_loc = begin(); begin_loc += first;
    auto end_loc   = begin(); end_loc += last;
    std::reverse(begin_loc,end_loc);
  };
  auto length() const { auto sum = 0.f;
    for (size_t i=0; i<size()-1; ++i)
      sum += get(i).distance( get(i+1) );
    return sum;
  };
  auto average_distance() const {
    if (size()==1) 
      return numeric_limits<float>::max();
    else return length() / static_cast<float>( size()-1 );
  };
  optional<int> try_find_next_address( AddressList route_so_far,bool take_any=true ) const {
    if (size()>0) {
      if (route_so_far.size()==0) {
	return 0; 
      } else {
// answer code removed
      }
    } else return {};
  };
  AddressList greedy_route( bool any_address_will_do=true ) const {
    // start with an empty list, containing only the first address
    AddressList all( *this );
    AddressList route;
    // while not empty:
    // .. find the closest to the current house,
    // .. add to route, and delete from list-to-process
    for (;;) {
      optional<int> possible_next_house;
      if (route.size()==0)
	possible_next_house = 0;
      else
	possible_next_house = all.try_find_next_address(route,any_address_will_do);
      if (!possible_next_house) break;
      else {
	int index_of_closest_house =  possible_next_house.value();
	// add it to the route, remove from list
	route.add_address( all.get_and_erase(index_of_closest_house) );
      }
    }
    return route;
  };
  int index_of_house_closest_to( const Address &we_are_here ) const {
    auto index = 0;
    auto shortest_distance = get(index).distance(we_are_here);
    // find the closest address
    for (int house_index=1; house_index<size(); ++house_index) {
      // what is the distance to house_index?
      auto dist = get(house_index).distance(we_are_here);
      // if more, remember this house
      if (dist<shortest_distance) {
	shortest_distance = dist; index = house_index;
      }
    }
    return index;
  };
  string as_string() {
    stringstream a;
    for ( auto r : *this )
      a << " " << r.as_string();
    return a.str();
  }
};

class Route : public AddressList {
public:
  Route() {
    AddressList::add_address( Address(0,0) );
  };
  Route( AddressList list ) : AddressList( list.get_addresses() ) {
    //AddressList::add_address( Address(0,0) );
    insert(begin(),Address(0,0));
    insert(end(),Address(0,0));
  };
  Route( vector<Address> address_list ) : AddressList( address_list ) {
    insert(begin(),Address(0,0));
    insert(end(),Address(0,0));
  };
  Route( vector<Address> one,vector<Address> two,vector<Address> three )
    : AddressList( one,two,three ) {
    insert(begin(),Address(0,0));
    insert(end(),Address(0,0));
  };
  void add_address( Address h ) {
    if (size()==0) {
      cerr << "Size of route can not be zero\n"; throw(1); }
    if (size()==1) {
      AddressList::add_address( h );
      AddressList::add_address( Address(0,0) );
    } else {
      // we already have the depot as start & end point, insert the new address
      insert(--end(),h);
    }
  };
  void fix(int i) { at(i).fix(); };
  auto has_fix(int first,int last) {
    return any_of(begin()+first,begin()+last,
		  [] (const Address &a ) -> bool { return a.is_fixed(); }
		  );
  };
  void append( Route other ) {
    insert(--end(),++other.begin(),--other.end());
  };
  auto greedy_route( bool any_address_will_do=true ) {
    auto first = begin(), last = end()-1;
    AddressList before_returning( vector<Address>(first,last) );
    auto greedy = before_returning.greedy_route(); greedy.erase_index(0);
    return Route( greedy );
  };
  auto reverse(size_t f,size_t l) {
    if (f<0 || l>=size()) {
      cerr << "Invalid indices to reverse" << '\n'; throw(1); }
    AddressList::reverse(f,l);
  };
  auto cut_in_three(int first,int last) const {
    auto
      one = vector<Address>( begin()+1,begin()+first ),
      two = vector<Address>( begin()+first,begin()+last ),
      three = vector<Address>( begin()+last,end()-1 );
    return tuple<vector<Address>,vector<Address>,vector<Address>>(one,two,three);
  };
  auto opt2(int first, int last) const {
    if (first==0 or last==size()) {
      cerr << "opt2 should not affect depot\n"; throw(1); }
    auto [one,two,three] = cut_in_three(first,last);
    std::reverse(two.begin(),two.end());
    Route opt_list(one,two,three);
    assert(opt_list.size()==size());
    return opt_list;
  };
  auto TSP() const {
    Route tsp(*this); auto cur_length=tsp.length();
    assert(tsp.size()==size());
    //cerr << "Start with length " << cur_length << '\n';
    for (int first=1; first<size()-2; ++first) {
      for (int last=size()-2; last>first; last--) {
	auto tmp = tsp.opt2(first,last); auto tmp_length = tmp.length();
	if (tmp_length<cur_length) {
	  //cerr << "down to " << tmp_length << '\n';
	  tsp = tmp;
	  assert(tsp.size()==size());
	  cur_length = tmp_length;
	}
      }
    }
    return tsp;
  };
  auto opt2_lr(Route other,int first, int last) const {
    auto len = last-first;
    auto sum_size = size()+other.size();
    Route
      save_me(*this),save_other(other);
    auto
      my_length = save_me.length(), other_length = save_other.length();
    if (first>size() || last>size()) {
      cerr << first << "," << last << " out of bounds\n";
      throw(1); }
    auto [one,two,three] = cut_in_three(first,last);
    auto two_r = two; std::reverse(two_r.begin(),two_r.end());
    for (int other_first=1; other_first<other.size()-2-len; ++other_first) {
      auto other_last = other_first+len;
      if (other.has_fix(other_first,other_last))
	continue;
      if (other_first>other.size() || other_last>other.size()) {
	cerr << other_first << "," << other_last << " out of bounds\n";
	throw(1); }
      auto [one_prime,two_prime,three_prime] = other.cut_in_three(other_first,other_last);
      auto two_prime_r = two_prime; std::reverse(two_prime_r.begin(),two_prime_r.end());

      Route opt_me,
	opt_me_f(one,two_prime,three),
	opt_me_r(one,two_prime_r,three);
      if (opt_me_f.length()<opt_me_r.length())
	opt_me = opt_me_f;
      else opt_me = opt_me_r;
      assert( opt_me.at(0)==Address(0,0) );
      assert( opt_me.at(opt_me.size()-1)==Address(0,0) );
      
      Route opt_other,
	opt_other_f(one_prime,two,three_prime),
	opt_other_r(one_prime,two_r,three_prime);
      if (opt_other_f.length()<opt_other_r.length())
	opt_other = opt_other_f;
      else opt_other = opt_other_r;

      if (opt_me.length()+opt_other.length()<my_length+other_length) {
	save_me = opt_me; save_other = opt_other;
	auto new_sum_size = save_me.size()+save_other.size();
	if (new_sum_size!=sum_size) {
	  cerr << "new sizes add up to " << new_sum_size
	       << "; should be " << sum_size << '\n';
	  throw(2);
	}
	my_length = save_me.length(); other_length = save_other.length();
	//cerr << "down to " << my_length << "," << other_length << '\n';
      }
    }
    return tuple<Route,Route>(save_me,save_other);
  };
};

auto TSP2( const Route &r1,const Route &r2, bool trace=false ) {
  Route tsp1(r1), tsp2(r2);
  auto
    cur_length_me = tsp1.length(),
    cur_length_other = tsp2.length();
  if (trace)
    cerr << "start with " << cur_length_me << "," << cur_length_other << '\n';
  for (int ipass=0; ipass<5; ++ipass) {
    if (trace)
      cerr << "Pass " << ipass << '\n';
    for (int first=1; first<tsp1.size()-1; ++first) {
      for (int last=tsp1.size()-1; last>first; last--) {
	if (tsp1.has_fix(first,last)) {
	  // if (trace)
	  //   cerr << "skipping segment " << first << "--" << last << '\n';
	  continue;
	}
	auto [tmp_me,tmp_other] = tsp1.opt2_lr(tsp2,first,last);
	auto tmp_length_me = tmp_me.length(),
	  tmp_length_other = tmp_other.length();
	if (tmp_length_me<cur_length_me && tmp_length_other<cur_length_other) {
	  tsp1 = tmp_me; tsp2 = tmp_other;
	  cur_length_me = tsp1.length(); cur_length_other = tsp2.length();
	  if (trace)
	    cerr << ".. down to " << cur_length_me << "," << cur_length_other << '\n';
	}
      }
    }
  }
  return tuple<Route,Route>(tsp1,tsp2);
};

int main() {

  cerr << "Addresstest" << '\n';
  {
    //codesnippet amazonaddressuse
    Address one(1.,1.),
      two(2.,2.);
    cerr << "Distance: "
	 << one.distance(two)
	 << '\n';
    //codesnippet end
  }
  cerr << ".. addresstest" << '\n';

  {
    AddressList deliveries;
    deliveries.add_address( Address(2) );
    deliveries.add_address( Address(1) );
    deliveries.add_address( Address(3) );

    Address depot(0,0);
    auto dist = depot.distance( deliveries[0] );
    cout << "Distance to first house should be 2. Check: " << dist << '\n';
    assert( CLOSE(dist,2) );
    dist = depot.distance( deliveries[2] );
    cout << "Distance to last house should be 3. Check: " << dist << '\n';
    assert( CLOSE(dist,3) );

    auto close_to_home = deliveries.index_of_house_closest_to(depot);
    auto close_idx = deliveries.index_of_house_closest_to(depot);
    cerr << "Address 1 should be closest to the depot. Check: "
	 << close_idx << '\n';
    assert( CLOSE(close_idx,1) );
    cerr << '\n';
  }

  {
    Route deliveries;
    deliveries.add_address( Address(2) );
    deliveries.add_address( Address(1) );
    deliveries.add_address( Address(3) );
    auto len1 = deliveries.length();
    cerr << "Route from depot to depot: "
	 << deliveries.as_string()
	 << "\n has length 8: " << len1
	 << '\n';
    assert( CLOSE(len1,8) );

    auto route = deliveries.greedy_route();
    auto len2 = route.length();
    cerr << "Greedy scheduling: "
	 << route.as_string()
	 << "\n should have length 6: " << len2
	 << '\n';
    assert( CLOSE(len2,6) );
    cerr << '\n';
  }

  {
    cerr << "Square5" << '\n';
    //codesnippet square5
    Route deliveries;
    deliveries.add_address( Address(0,5) );
    deliveries.add_address( Address(5,0) );
    deliveries.add_address( Address(5,5) );
    cerr << "Travel in order: "
         << deliveries.length() << '\n';
    assert( deliveries.size()==5 );
    auto route = deliveries.greedy_route();
    assert( route.size()==5 );
    auto len = route.length();
    cerr << "Square route:\n "
         << route.as_string()
         << "\n has length " << len << '\n';
    //codesnippet end
    assert( CLOSE(len,20) );
    cerr << ".. square5" << '\n';
    cerr << '\n';
  }

  {
    Route deliveries;
    deliveries.add_address( Address(-2) );
    deliveries.add_address( Address(-1) );
    deliveries.add_address( Address(1) );
    deliveries.add_address( Address(2) );
    cerr << "Original list: "
	 << deliveries.as_string()
	 << "\n length=" << deliveries.length() << '\n';
    deliveries.reverse(2,4);
    cerr << "flip middle two addresses: "
	 << deliveries.as_string()
	 << "\n length=" << deliveries.length() << '\n';
    auto better = deliveries.opt2(1,3);
    cerr << "better: "
	 << better.as_string()
	 << "\n length=" << better.length() << '\n';
    cerr << '\n';
  }

  {
    cerr << "Hundred houses\n";
    Route deliveries;
    for (int i=0; i<500; ++i) {
      auto
	housex = (100.f * rand())/((float)RAND_MAX),
	housey = (100.f * rand())/((float)RAND_MAX);
      deliveries.add_address( Address(housex,housey) );
    }

    cerr << "Route in order has length " << deliveries.length() << '\n';
    {
      auto tsp_naive = deliveries.TSP();
      cerr << "TSP based on mere listing has length: " << tsp_naive.length()
	   << " over naive " << deliveries.length() << '\n';
    }

    Route route = deliveries.greedy_route(); auto cur_length = route.length();
    auto first_length{cur_length};
    cerr << "Single route has length: " << route.length() << '\n';
    for (int attempt=0; attempt<500; ++attempt) {
      auto route_size = route.size();
      int
	first = static_cast<int>( route_size * static_cast<float>(rand()) / ((float)RAND_MAX) ),
	count = static_cast<int>( .5*(route.size()-first) * static_cast<float>(rand()) / ((float)RAND_MAX) ),
	last = first+count;
      if (first==0 || first==route_size-1 || count<=1) continue;
      //cerr << "flipping from " << first << "--" << last << '\n';
      auto other_route = route.opt2(first,last);
      auto tmp_length = other_route.length();
      //cerr << "   gives length " << tmp_length << '\n';
      if (tmp_length<cur_length) {
	cerr << " .. new route accepted with length " << tmp_length << '\n';
	cur_length = tmp_length; route = other_route;
      }
    }
    cerr << "Final route has length " << cur_length
	 << " over initial " << first_length << '\n';
    auto tsp = route.TSP();
    cerr << "TSP route has length " << tsp.length()
	 << " over initial " << first_length << '\n';
    cerr << '\n';    
  }

  {
    cerr << "Two routes\n";
    Route deliveries1, deliveries2;
    deliveries1.add_address( Address(2,0) );
    deliveries1.add_address( Address(3,2) );
    deliveries1.add_address( Address(2,3) );
    deliveries1.add_address( Address(0,2) );

    deliveries2.add_address( Address(3,1) );
    deliveries2.add_address( Address(2,1) );
    deliveries2.add_address( Address(1,2) );
    deliveries2.add_address( Address(1,3) );
    cerr << "Route1: " << deliveries1.as_string()
         << "\nroute2: " << deliveries2.as_string()
         << "\ntotal length " << deliveries1.length()+deliveries2.length()
         << '\n';
    auto [tsp1,tsp2] = TSP2(deliveries1,deliveries2,true);
    cerr << "TSP Route1: " << tsp1.as_string()
         << "\nroute2: " << tsp2.as_string()
         << "\ntotal length " << tsp1.length()+tsp2.length()
         << '\n';
    cerr << '\n';
  }
  
  {
    cerr << "Two routes\n";
    Route deliveries1, deliveries2;
    srand(3);
    for (int i=0; i<100; ++i) {
      auto
	housex = (200.f * rand())/((float)RAND_MAX),
	housey = (200.f * rand())/((float)RAND_MAX);
      deliveries1.add_address( Address(housex,housey) );
      housex = (200.f * rand())/((float)RAND_MAX);
      housey = (200.f * rand())/((float)RAND_MAX);
      deliveries2.add_address( Address(housex,housey) );
    }
    {
      Route total(deliveries1);
      total.append(deliveries2);
      Route greedy = total.greedy_route(), tsp = greedy.TSP();
      assert(total.size()==greedy.size());
      assert(total.size()==tsp.size());
      cerr << "Total route has greedy length " << greedy.length()
	   << " and TSP length " << tsp.length() << '\n';
    }
    Route
      route1 = deliveries1.greedy_route(),
      route2 = deliveries2.greedy_route();
    cerr << "greedy routes have length "
	 << route1.length() << ", " << route2.length() << '\n';
    auto [tsp1,tsp2] = TSP2(route1,route2,true);
    cerr << "TSP routes have length "
	 << tsp1.length() << ", " << tsp2.length() << '\n';
    cerr << '\n';
  }
  
  {
    cerr << "Two routes with fixes\n";
    Route deliveries1, deliveries2;
    srand(3);
    for (int i=0; i<100; ++i) {
      auto
	housex = (200.f * rand())/((float)RAND_MAX),
	housey = (200.f * rand())/((float)RAND_MAX);
      deliveries1.add_address( Address(housex,housey) );
      housex = (200.f * rand())/((float)RAND_MAX);
      housey = (200.f * rand())/((float)RAND_MAX);
      deliveries2.add_address( Address(housex,housey) );
    }
    for (int i=0; i<5; ++i) {
      auto
	house1 = static_cast<int>( (1.f * deliveries1.size() * rand())/((float)RAND_MAX) ),
	house2 = static_cast<int>( (1.f * deliveries2.size() * rand())/((float)RAND_MAX) );
      deliveries1.fix(house1); deliveries2.fix(house2);
    }
    Route
      route1 = deliveries1.greedy_route(),
      route2 = deliveries2.greedy_route();
    cerr << "greedy routes have length "
	 << route1.length() << ", " << route2.length() << '\n';
    auto [tsp1,tsp2] = TSP2(route1,route2,true);
    cerr << "TSP routes have length "
	 << tsp1.length() << ", " << tsp2.length() << '\n';
    cerr << '\n';
  }

  return 0;
}
