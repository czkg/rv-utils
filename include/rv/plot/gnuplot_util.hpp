// Copyright (C) 2015 Institute for Computer Graphics and Vision (ICG),
//   Graz University of Technology (TU GRAZ)

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the ICG, TU GRAZ.
// 4. Neither the name of the ICG, TU GRAZ nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY ICG, TU GRAZ ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ICG, TU GRAZ BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
