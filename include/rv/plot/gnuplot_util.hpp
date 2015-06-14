#ifndef RV_PLOT_GNUPLOT_UTIL_H
#define RV_PLOT_GNUPLOT_UTIL_H

#include "gnuplot-iostream.h"

#include <map>
#include <limits>
#include <vector>

#include <boost/format.hpp>


namespace rv {
namespace gnuplot {


typedef std::map<std::string, std::vector<std::pair<float, float> > > pltdata_t;

inline void plot(gnuplotio::Gnuplot& gp, pltdata_t& pltdata, std::string title = "", std::string xlabel = "", std::string ylabel = "") {

  std::vector<std::string> keys;
  for(pltdata_t::iterator it = pltdata.begin(); it != pltdata.end(); ++it) {
      keys.push_back(it->first);
  }

  gp << "set autoscale xy\n";
  gp << "set grid\n";

  if(title.size() > 0) gp << boost::format("set title '%s'\n") % title;

  if(xlabel.size() > 0) gp << boost::format("set xlabel '%s'\n") % xlabel;
  if(ylabel.size() > 0) gp << boost::format("set ylabel '%s'\n") % ylabel;

  std::string pltstr = "plot ";
  for(size_t kidx = 0; kidx < keys.size(); ++kidx) {
    pltstr = pltstr + boost::str( boost::format("'-' with linespoints title '%s'") % keys[kidx] );

    if(kidx < keys.size() - 1) {
      pltstr = pltstr + ", ";
    }
  }
  pltstr = pltstr + "\n";

  gp << pltstr;

  for(size_t kidx = 0; kidx < keys.size(); ++kidx) {
    gp.send1d(pltdata[keys[kidx]]);
  }

  gp.flush();
}


} //ns gnuplot
} //ns rv

#endif
