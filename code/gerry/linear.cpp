/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2018-2025 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** linear.cxx : redistricting exercise with linear districts
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;

#include <sstream>
using std::stringstream;

#include <random>
using std::rand;

#include <string>
using std::string;

#include <vector>
using std::vector;

// answer code removed

class Districting;
class Population {
private:
  vector<Voter> population;
  bool trace{false};
public:
  // construct explicit population
  Population( vector<Voter> population,bool trace=false )
    : population(population),trace(trace) {};
  // construct from 0101 string
  Population( string rds,bool trace=false )
    : trace(trace) {
    int voter_count{0};
    for ( auto v : rds )
      if (v=='-')
        extend( Voter(voter_count++,-1) );
      else if (v=='+')
        extend( Voter(voter_count++,+1) );
      else
        cout << "Unrecognized affiliation marker <<" << v << ">>" << '\n';
  };
  // construct random population
// answer code removed
    : population(vector<Voter>(population_size,Voter(0,-1))),trace(trace) {
    if (population_size<0) {
      cout << "Illegal population size: " << population_size << '\n';
      throw(1); }
    // number the voters
    for (int ivoter=0; ivoter<population_size; ivoter++)
      population.at(ivoter).set_id(ivoter);
    // set random majority votes
    for ( int majority_count=0; majority_count<majority; ) {
      int try_set_this_one = rand() % population_size;
      try {
        if (population.at(try_set_this_one).affiliation()<0) {
          population.at(try_set_this_one).switch_affiliation();
          majority_count++;
        }
      } catch (std::out_of_range) {
        cout << "indexing out of range: " << try_set_this_one << '\n';        
      }
    }
  };
  int size() const { return population.size(); };
  auto &get_voters() const { return population; }
  void extend( Voter v ) { population.push_back(v); };
  int rule() const {
    int ones{0},minus{0};
    for (auto v : population)
      if (v.affiliation()>0)
        ones++;
      else if (v.affiliation()<0)
        minus++;
    return ones-minus;
  };
  int lean() const {
    int r = rule();
    if (r>0) return 1;
    else if (r<0) return -1;
    else return 0;
  };
  auto at(int i) { return population.at(i); };
  Population sub(int first,int last) {
    return Population( vector<Voter>(population.begin()+first,population.begin()+last) );
  };
  string print() { stringstream printed;
    printed << "[";
    for ( auto p : population )
      printed << p.print() << ",";
    printed << "]";
    return printed.str();
  };
  Districting minority_rules( int ndistricts,string="" );
};

class District {
private:
  vector<Voter> voters;
public:
  District() {};
  District( Voter v )
    : voters( vector<Voter>{v} ) {};
  District(vector<Voter> voters)
    : voters(voters) {};
  District( Population pop ) : voters(pop.get_voters()) {}
  int size() const { return voters.size(); };
  int lean() {
    int minus{0},ones{0};
    for (auto d : voters)
      if (d.affiliation()>0)
        ones++;
      else if (d.affiliation()<0)
        minus++;
    if (ones>minus) return 1;
    else if (ones<minus) return -1;
    else return 0;
  };
  void extend(Voter v) { voters.push_back(v); };
  District sub(int first,int last) {
    return District( vector<Voter>(voters.begin()+first,voters.begin()+last) );
  };
  string print() {
    stringstream printed;
    printed << "[";
    for ( auto v : voters )
      printed << v.print() << ",";
    printed << "]";
    return printed.str();
  };
};

class Districting {
private:
  vector<District> districts;
public:
  void add_new_district( Voter v ) {
    districts.push_back( District( vector<Voter>{v} ) );
  };
  void add_new_district( District d ) {
    districts.push_back( d );
  };
  Districting extend_with_new_district( Voter v ) {
    Districting extended(*this);
    extended.add_new_district( District(v) );
    return extended;
  };
  Districting extend_last_district( Voter v ) {
    Districting extended(*this);
    extended.districts.at(districts.size()-1).extend(v);
    return extended;
  };
  int size() const { return districts.size(); };
  int rule() const {
    int minus{0},ones{0};
    for (auto d : districts)
      if (d.lean()>0)
        ones++;
      else if (d.lean()<0)
        minus++;
    return ones-minus;
  };
  int lean() const {
    int m = rule();
    if (m>0) return 1;
    else if (m<0) return -1;
    else return 0;
  };
  string print() { stringstream printed;
    printed << "[" << districts.size() ;
    for ( auto d : districts ) printed << d.print() << ",";
    printed << "]";
    return printed.str();
  };
};

// answer code removed

int main() {

  cout << "Voters" << '\n';
  {
    cout << "Voter 5 is positive:" << '\n';
    Voter nr5(5,+1);
    cout << nr5.print() << '\n';
  }
  cout << '\n';

  {
    cout << "Voter 6 is negative:" << '\n';
    Voter nr6(6,-1);
    cout << nr6.print() << '\n';
  }
  cout << '\n';

  try {
    cout << "Voter 7 is weird:" << '\n';
    Voter nr7(7,3);
    cout << nr7.print() << '\n';
  } catch (...) {
    cout << "Error in creating voter 7" << '\n';
  }
  cout << "voters" << '\n';
  cout << '\n';

  /*
   * Population
   */
  {
    cout << "Populationbasics" << '\n';
    string pns( "-++--" );
    Population some(pns);
    cout << "Population from string "
         << pns << '\n';
    cout << ".. size: " << some.size() << '\n';
    cout << ".. lean: " << some.lean() << '\n';
    Population group=some.sub(1,3);
    cout << "sub population 1--3" << '\n';
    cout << ".. size: " << group.size() << '\n';
    cout << ".. lean: " << group.lean() << '\n';
    cout << "populationbasics" << '\n';
  }
  cout << '\n';

  /*
   * Districts
   */
  cout << "Districtbasics" << '\n';
  {
    cout << "Making district with one B voter"
         << '\n';
    Voter nr5(5,+1);
    District nine( nr5 );
    cout << ".. size: " << nine.size() << '\n';
    cout << ".. lean: " << nine.lean() << '\n';
  }
  cout << '\n';

  {
    cout << "Making district ABA" << '\n';
    District nine( vector<Voter>
		   { {1,-1},{2,+1},{3,-1} } );
    cout << ".. size: " << nine.size() << '\n';
    cout << ".. lean: " << nine.lean() << '\n';
  }
  cout << "districtbasics" << '\n';
  cout << '\n';

  /*
   * Districting
   */
  {
    cout << "Making single voter district B"
         << '\n';
    Districting state;
    state.add_new_district( Voter(1,+1) );
    cout << ".. lean: " << state.lean() << '\n';
  }
  cout << '\n';

  {
    cout << "Making single district ABA" << '\n';
    Districting state;
    state.add_new_district( District( vector<Voter>
                { Voter(1,-1),Voter(2,+1),Voter(3,-1) } ) );
    cout << ".. lean: " << state.lean() << '\n';
  }
  cout << '\n';

  {
    cout << "Gerryempty" << '\n';
    cout << "Making single voter population B" << '\n';
    Population people( vector<Voter>{ Voter(0,+1) } );
    cout << ".. size: " << people.size() << '\n';
    cout << ".. lean: " << people.lean() << '\n';

    Districting gerry;
    cout << "Start with empty districting:" << '\n';
    cout << ".. number of districts: "
         << gerry.size() << '\n';
    cout << "gerryempty" << '\n';

    cout << "Add one B voter:" << '\n';
    gerry = gerry.extend_with_new_district( people.at(0) );
    cout << ".. number of districts: " << gerry.size() << '\n';
    cout << ".. lean: " << gerry.lean() << '\n';
    cout << "add A A:" << '\n';
    gerry = gerry.extend_last_district( Voter(1,-1) );
    gerry = gerry.extend_last_district( Voter(2,-1) );
    cout << ".. number of districts: " << gerry.size() << '\n';
    cout << ".. lean: " << gerry.lean() << '\n';

    cout << "Add two B districts:" << '\n';
    gerry = gerry.extend_with_new_district( Voter(3,+1) );
    gerry = gerry.extend_with_new_district( Voter(4,+1) );
    cout << ".. number of districts: " << gerry.size() << '\n';
    cout << ".. lean: " << gerry.lean() << '\n';
  }
  cout << '\n';

  {
    cout << "District5" << '\n';
    Population five("+++--");
    cout << "Redistricting population: " << '\n'
         << five.print() << '\n';
    cout << ".. majority rule: " 
         << five.rule() << '\n';
    int ndistricts{3};
    auto gerry = five.minority_rules(ndistricts);
    cout << gerry.print() << '\n';
    cout << ".. minority rule: "
         << gerry.rule() << '\n';
    cout << "district5" << '\n';
  }
  cout << '\n';

  {
    Population random20(20,11);
    cout << "Redistricting population: " << '\n'
         << random20.print() << '\n';
    cout << ".. majority rule: " << '\n'
         << random20.rule() << '\n';
    int ndistricts{5};
    auto gerry = random20.minority_rules(ndistricts);
    cout << gerry.print() << '\n';
    cout << ".. minority rule: " << gerry.rule() << '\n';
  }
  cout << '\n';
#if 0
  {
    int size = 1000;
    cout << "Population size: " << size << '\n';
    for ( int ndistricts = 100; ndistricts>10; ndistricts--) {
      for ( int majority_by=1; majority_by<size/20; majority_by++) {
        Population population(size,size/2+majority_by);
        auto gerry = population.minority_rules(ndistricts);
        cout << "minority rule:" << gerry.rule() << '\n';
      }
    }
  }
  cout << '\n';
#endif

  return 0;
}
