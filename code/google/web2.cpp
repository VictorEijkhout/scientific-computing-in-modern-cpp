/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** web2.cxx : solution without a Link class
 ****
 ****************************************************************/

#include <cstdlib>
#include <cstring>

#include <cmath>
#include <random>
#include <ctime>

#include <iostream>
#include <sstream>
#include <iomanip>
using std::cout;
using std::fixed;
using std::setprecision;
using std::stringstream;

#include <memory>
using std::make_shared;
using std::shared_ptr;

#include <string>
using std::string;
using std::to_string;

#include <vector>
using std::vector;

// forward declaration of Page class
class Page;

// answer code removed

private:
  int globalID{-1};
public:
  void set_global_ID(int id) { globalID = id; };
  int global_ID() const { return globalID; };

// answer code removed
  const auto links() const { return outlinks; };
// answer code removed

  string as_string() {
    stringstream render;
    render << "Page: " << thename;
    if (outlinks.size()==0) render << "; no links.";
    else {
      render << "; links: [[ ";
      for ( auto l : outlinks )
        render << l->global_ID() << " ";
      render << "]]";
    }
    return render.str();
  };
};

class ProbabilityDistribution {
private:
  vector<float> probabilities;
public:
  ProbabilityDistribution(int size) {
    //cout << "make distribution on " << size << " point" << '\n';
    probabilities = vector<float>(size,0.);
  };
  void normalize() { float total{0.};
    for ( auto p : probabilities )
      total += p;
    if (total>0.) 
      for ( auto &p : probabilities )
	p /= total;
  };
  float &at(int i) {
    //cout << "access p(" << i << "/" << probabilities.size() << ")" << '\n';
    return probabilities.at(i);
  };
  int size() const {
    return probabilities.size();
  };
  int rank(int ipage) {
    auto value = probabilities.at(ipage); int rank = 0;
    for ( auto p : probabilities)
      if (p>value) ++rank;
    return rank;
  };
  void set_random() {
    for (int i=0; i<probabilities.size(); ++i)
      probabilities[i] = rand()/(float)RAND_MAX;
    normalize();
  };
  string stats() {
    int ntop = 5;
    vector<float> probs(ntop,0); vector<int> pages(ntop,1);
    for (int ip=0; ip<probabilities.size(); ++ip) {
      auto p = probabilities[ip];
      for (int it=0; it<ntop; ++it) {
	if (p>probs[it]) {
	  probs[it] = p; pages[it] = ip;
	  break;
	}
      }
    };
    stringstream statstring;
    for (int it=0; it<ntop; ++it) {
      statstring << pages[it] << ":" << fixed << setprecision(4) << probs[it];
      if (it<ntop-1) statstring << ", ";
    }
    return statstring.str();
  };
  string as_string() { stringstream render;
    for (int i=0; i<probabilities.size(); ++i)
      render << i << ":" << fixed << setprecision(2) << probabilities[i] << ", ";
    return render.str();
  };
};

// answer code removed
  void push_back( shared_ptr<Page> newpage ) {
    newpage->set_global_ID( pages.size() );
    pages.push_back(newpage);
  };
  int number_of_pages() const { return pages.size(); };
  const auto all_pages() const { return pages; };
  auto page(int idx) const { return pages.at(idx); };
  auto random_page() {
    int target = static_cast<int>(pages.size()*(rand()/(float)RAND_MAX));
    return pages.at(target); };
  void create_random_links(int avg_nlinks) {
    for ( auto p : pages ) {
      int nlinks = static_cast<int>(2*avg_nlinks*(rand()/(float)RAND_MAX));
      for (int ilink=0; ilink<nlinks; ++ilink)
	p->add_link(random_page());
    }
  };
  int max_degree() { int md{0};
    for ( auto p : pages ) if (p->degree()>md) md = p->degree();
    return md; };
  int min_degree() { int md = pages.size();
    for ( auto p : pages ) if (p->degree()<md) md = p->degree();
    return md; };
  auto random_walk( shared_ptr<Page> starter,int nsteps,bool trace=false) {
    if (trace) cout << starter->name();
    if (nsteps==0) {
      if (trace) cout << '\n';
      return starter;
    } else {
      if (trace) cout << ", ";
      if (starter->degree()==0)
	return random_walk( random_page(),nsteps-1,trace);
      else
	return random_walk( starter->random_click(),nsteps-1,trace);
    }
  };
// answer code removed
  void display() { cout << "Web of " << pages.size() << " pages " << '\n';
    for (int ipage=0; ipage<pages.size(); ++ipage)
      cout << ipage << "<<" << pages.at(ipage)->name() << ">>:\n  "
	   << pages.at(ipage)->as_string() << '\n';
  };
};

int main(int argc,char **argv) {

  ++argv; argc--;
  bool tracing{false};
  while (argc>=1) {
    if (!strcmp(argv[0],"-t"))
      tracing = true;
    ++argv; argc--;    
  }

// answer code removed
  cout << '\n';

  cout << "Install work link on homepage:" << '\n';
// answer code removed
  cout << '\n';

  cout << "More links on the homepage:" << '\n';
  for (int ilink=0; ilink<9; ++ilink) {
    homepage->add_link( make_shared<Page>(string("randompage")+to_string(ilink)) );
  }
  cout << homepage->as_string() << '\n';
  cout << '\n';

  cout << "Let's click!" << '\n';
// answer code removed

  {
    /*
     * We build our first internet
     */
    int netsize = 20, avglinks = 6;
    cout << "\nLet's build a large internet! size="
	 << netsize << "; avg degree=" << avglinks << '\n';
// answer code removed
    //  internet.display();
    cout << "Maximum degree: " << internet.max_degree() << '\n';
    cout << "Minimum degree: " << internet.min_degree() << '\n';
// answer code removed

    /*
     * Simple random walk
     */
    cout << "\nRandom walk lands you:";
    for (int ipage=0; ipage<landing_counts.size(); ++ipage)
      cout << " " << ipage << ":" << landing_counts.at(ipage);
    cout << "." << '\n';

    // couple of simple tests
    for (int ipage=1; ipage<=7; ipage+=2) {
      cout << "Testing with starting on page " << ipage << '\n';
      ProbabilityDistribution onestate(internet.number_of_pages());
      onestate.at(ipage) = 1.;
      cout << "Page " << ipage << ": " << internet.page(ipage)->as_string() << '\n';
      ProbabilityDistribution nextstate = internet.globalclick(onestate);
      cout << "click takes you to: " << nextstate.as_string() << '\n';
    }
  
    cout << "\nSet up a probability distribution" << '\n';
// answer code removed
    cout << ".. done probability distribution" << '\n';

    for (int step=0; step<5; ++step) {
      random_state = internet.globalclick(random_state);
      cout << "click takes you to: " << random_state.as_string() << '\n';
    }
    cout << "Top score: " << random_state.stats() << '\n';
  }

  {
    /*
     * We build a large internet 
     */
    int netsize = 5000, important = 2, avglinks = 5;
    Web internet(netsize);
    internet.create_random_links(avglinks);
    cout << "internet has " << internet.number_of_pages() << " pages" << '\n';
    /*
     * first a normal internet
     */
    ProbabilityDistribution
      random_state(internet.number_of_pages());
    random_state.set_random();
    for (int step=0; step<50; ++step) {
      random_state = internet.globalclick(random_state);
    }
    cout << "Top score: " << random_state.stats() << '\n';

    /*
     * Now we add some SEO
     */
    auto hyped_page = make_shared<Page>("hype");
    for (int extra=0; extra<4*avglinks; ++extra) {
      auto fake = make_shared<Page>(string("fake")+to_string(extra));
      fake->add_link(hyped_page);
      internet.push_back(fake);
    }
    internet.push_back(hyped_page);
    cout << "new internet has " << internet.number_of_pages() << " pages" << '\n';
    // and we iterate again
    random_state = ProbabilityDistribution(internet.number_of_pages());
    random_state.set_random();
    for (int step=0; step<500; ++step) {
      random_state = internet.globalclick(random_state);
    }
    cout << "Top score: " << random_state.stats() << '\n';
    cout << "hyped page scores at "
	 << random_state.rank(internet.number_of_pages()-1) << '\n';;
  }

  return 0;
}
